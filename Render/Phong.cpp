//
// Created by chouj on 9/10/2021.
//

#include <cmath>
#include <iostream>

#include "Phong.h"
#include "../Model/Ops/RenderOps.h"

Phong::Phong(Scene *renderScene) : Integrator(renderScene) {}

Vec3 Phong::radiance(Ray ray, int depth, int levReflectRecursion, int sampleDensity) {
    //return if recursion limit is reached
    if(depth >= levReflectRecursion){
        return renderScene->getBackColor();
    }

    //find intersection
    Object* intersectObject = nullptr;

    Vec3 interVec = renderScene->getObjTracker()->getIntersect(ray, true, intersectObject);
    if(interVec.getMagnitude() == VAL_INFINITY || interVec.getMagnitude() == NEG_INFINITY || interVec.isNan()) {
        if(depth == 0) {
            return renderScene->getBackColor();
        }
        return Vec3();
    }

    //get uv
    double u, v;
    intersectObject->getUV(interVec, u, v);

    if(intersectObject->isLight()){
        return intersectObject->material->colorEmission->getColor(u, v);
    }
    //initializing variables for light calculations
    double normalScalar = 1.0;
    Vec3 n = intersectObject->normal(interVec);
    bool isInsideObject = (ray.direction.dot(n) > 0);
    if(isInsideObject) normalScalar = -1.0;
    double opacity = intersectObject->material->opacity->getColor(u, v);

//    return intersectObject->material->colorDiffuse->getColor(u, v);

    //surf color
    CoordinateSpace cs = RenderOps().makeCoordinateSystem(ray.direction, n * normalScalar);
    double offsetX = 0;//RenderOps().randFloatValue(-0.1, 0.1);
    double offsetY = 0;//RenderOps().randFloatValue(-0.1, 0.1);
    Ray colorRay = Ray(ray.direction +cs.up * offsetY + cs.right * offsetX, ray.point);
    Vec3 surfColor = calcSurfColor(colorRay, interVec, intersectObject, normalScalar, u, v);
    return surfColor;
    //refl color
    offsetX = RenderOps().randFloatValue(-0.1, 0.1);
    offsetY = RenderOps().randFloatValue(-0.1, 0.1);
    Vec3 reflDir = RenderOps().reflectionDirection(n * normalScalar, ray.direction);
    reflDir = (reflDir + cs.up * offsetY + cs.right * offsetX).normalize();
    Vec3 epsilonPoint = interVec + intersectObject->normal(interVec) * normalScalar * 0.001;
    Vec3 reflColor = radiance(Ray(reflDir, epsilonPoint), depth + 1, levReflectRecursion, sampleDensity) * intersectObject->material->kSpecular->getColor(u, v) *
                     intersectObject->material->kSpecular->getColor(u, v);
    Vec3 refrColor = Vec3();
    double fresnelEffect;
    if(opacity > 0) {
        offsetX = RenderOps().randFloatValue(-0.05, 0.05);
        offsetY = RenderOps().randFloatValue(-0.05, 0.05);
        Ray transRay = RenderOps().calcTransmissionRay(ray.direction, intersectObject, interVec, isInsideObject, u, v);
        transRay.direction = (transRay.direction + cs.up * offsetY + cs.right * offsetX).normalize();
        double iorLeft = 1.0;
        double iorEntered = intersectObject->material->IOR->getColor(u, v);
        if(isInsideObject){
            iorLeft = intersectObject->material->IOR->getColor(u, v);
            iorEntered = 1.0;
        }

        refrColor = radiance(transRay, depth + 1, levReflectRecursion, sampleDensity);
        fresnelEffect = RenderOps().calcFresnelReflectAmount(iorLeft, iorEntered, n, ray.direction);

        return  surfColor * (1.0 - opacity) + intersectObject->material->colorDiffuse->getColor(u, v) * (reflColor * fresnelEffect + refrColor * (1 - fresnelEffect) * opacity);
    }
//    else if(opacity == 0){
//        return surfColor;
//    }
    return surfColor + reflColor;

}
Vec3 Phong::calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, double normalScalar, double u, double v) {
    if(ray.isNan() || interVec.isNan()){
        return Vec3(0, 0, 0);
    }
    Vec3 surfColor;
    Vec3 epsilonPoint = interVec + intersectObject->normal(interVec) * normalScalar * 0.001;
    for (int i = 0; i < renderScene->getObjTracker()->getLightList().size(); ++i){
        Ray shadowRay = Ray(epsilonPoint, renderScene->getObjTracker()->getLightList().at(i)->shadowRay(interVec, intersectObject->normal(interVec) * normalScalar));
        Object* shadowObject = nullptr;
        Vec3 shadowIntersect = renderScene->getObjTracker()->getIntersect(shadowRay, true, shadowObject);
        bool isOccluded = true;
        if (shadowObject == nullptr || shadowObject->isLight() || shadowIntersect.getMagnitude() == VAL_INFINITY || shadowIntersect.getMagnitude() == NEG_INFINITY ||
                shadowObject == renderScene->getObjTracker()->getLightList().at(i)) {
            isOccluded = false;
        }
        if (!isOccluded) {
            Vec3 addColor = calcLighting(intersectObject, renderScene->getObjTracker()->getLightList().at(i), interVec,
                                         shadowRay.direction, shadowIntersect, normalScalar, u, v);
            surfColor += addColor;
        }
        else if(shadowObject->material->opacity->getColor(u, v) > 0.0){
            Vec3 addColor = calcLighting(intersectObject, renderScene->getObjTracker()->getLightList().at(i), interVec,
                                         shadowRay.direction, shadowIntersect, normalScalar, u, v);
            surfColor += addColor * (1.0 - shadowObject->material->opacity->getColor(u, v));
        }
    }
    return surfColor;
}

Vec3 Phong::calcLighting(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 shadowIntersect, double normalScalar, double objectU, double objectV) {
    if(light->ToString() == "Ambient Light"){
        return calcAmbient(surface, light, interPoint, rayDir, normalScalar, objectU , objectV);
    }
    double lightU = 0;
    double lightV = 0;
    if(shadowIntersect.getMagnitude() != VAL_INFINITY && shadowIntersect.getMagnitude() != NEG_INFINITY){
        light->getUV(shadowIntersect, lightU, lightV);
    }
    Vec3 lighting = calcDiffuse(surface, light, interPoint, rayDir, normalScalar, objectU , objectV, lightU, lightV) +
                    calcSpec(surface, light, interPoint, rayDir, normalScalar, objectU, objectV, lightU, lightV);
    if(lighting.isNan()){
        return Vec3();
    }
    return lighting;

}
Vec3 Phong::calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar, double objectU, double objectV, double lightU, double lightV) {
    Vec3 od = surface->material->colorDiffuse->getColor(objectU, objectV);
    Vec3 l = rayDir;
    Vec3 n = surface->normal(interPoint).normalize() * normalScalar;
    double maxDiffuse = RenderOps().max(0, n.dot(l));
    Vec3 retVec = od * maxDiffuse * light->material->colorEmission->getColor(lightU, lightV) * surface->material->kDiffuse->getColor(objectU, objectV);

    return retVec;
}
Vec3 Phong::calcSpec(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar, double objectU, double objectV, double lightU, double lightV){
    Vec3 r = RenderOps().reflectionDirection(surface->normal(interPoint).normalize() * normalScalar,
                                             (rayDir) * -1);
    double ks = surface->material->kSpecular->getColor(objectU, objectV);
    double maxSpec = RenderOps().max(0, (rayDir * -1).dot(r));
    Vec3 os = surface->material->colorSpec->getColor(objectU, objectV);
    double kgls = surface->material->kgls->getColor(objectU, objectV);

    return light->material->colorEmission->getColor(lightU, lightV) * os * ks * pow(maxSpec, kgls);
}
Vec3 Phong::calcAmbient(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar, double u, double v) {
    return light->material->colorEmission->getColor(0, 0) * surface->material->colorDiffuse->getColor(u, v) * surface->material->kAmbient->getColor(u, v);
}