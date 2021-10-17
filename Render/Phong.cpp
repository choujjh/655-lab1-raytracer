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
    Vec2 interObjectUV = intersectObject->getUV(interVec);

    //if its a light
    if(intersectObject->isLight()){
        return intersectObject->material->getColor(interObjectUV) * intersectObject->material->gamma(interObjectUV);
    }

    //initializing variables for light calculations
    Vec3 n = intersectObject->normal(interVec);
    //if inside object
    bool isInsideObject = ray.direction.dot(n) >= 0;
    if(isInsideObject) n = n * -1;
    double opacity = intersectObject->material->transmission(interObjectUV);

    //surf color
    CoordinateSpace cs = RenderOps().makeCoordinateSystem(ray.direction, n);
    double offsetX = 0;
    double offsetY = 0;
    Ray colorRay = Ray(ray.direction +cs.up * offsetY + cs.right * offsetX, ray.point);
    Vec3 surfColor = calcSurfColor(colorRay, interVec, intersectObject, n, interObjectUV);

    //refl color
    offsetX = RenderOps().randFloatValue(-1 * intersectObject->material->gloss(interObjectUV), intersectObject->material->gloss(interObjectUV));
    offsetY = RenderOps().randFloatValue(-1 * intersectObject->material->gloss(interObjectUV), intersectObject->material->gloss(interObjectUV));
    Vec3 reflDir = RenderOps().reflectionDirection(n, ray.direction);
    reflDir = (reflDir + cs.up * offsetY + cs.right * offsetX).normalize();
    Vec3 epsilonPoint = interVec + intersectObject->normal(interVec) * 0.001;
    Vec3 reflColor = radiance(Ray(epsilonPoint, reflDir), depth + 1, levReflectRecursion, sampleDensity) *
            intersectObject->material->reflective(interObjectUV) *
                     intersectObject->material->reflective(interObjectUV);


    double fresnelEffect = RenderOps().calcFresnelReflectAmount(1, 1.5, n, ray.direction);;
    if(opacity > 0) {
        offsetX = RenderOps().randFloatValue(-1 * intersectObject->material->translucency(interObjectUV), intersectObject->material->translucency(interObjectUV));
        offsetY = RenderOps().randFloatValue(-1 * intersectObject->material->translucency(interObjectUV), intersectObject->material->translucency(interObjectUV));
        Ray transRay = RenderOps().calcTransmissionRay(ray.direction, intersectObject, interVec, isInsideObject, interObjectUV);
        transRay.direction = (transRay.direction + cs.up * offsetY + cs.right * offsetX).normalize();
        double iorLeft = 1.0;
        double iorEntered = intersectObject->material->ior(interObjectUV);
        if(isInsideObject){
            iorLeft = intersectObject->material->ior(interObjectUV);
            iorEntered = 1.0;
        }

        Vec3 refrColor = radiance(transRay, depth + 1, levReflectRecursion, sampleDensity);
        fresnelEffect = RenderOps().calcFresnelReflectAmount(iorLeft, iorEntered, n, ray.direction);

        return  surfColor * (1.0 - opacity) + intersectObject->material->getColor(interObjectUV) *
        (reflColor * fresnelEffect + refrColor * (1 - fresnelEffect) * opacity);
    }
    return surfColor + intersectObject->material->getColor(interObjectUV) *
                                         (reflColor * (1 - fresnelEffect));

}
Vec3 Phong::calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, Vec3 normal, Vec2 objectUV) {
    if(ray.isNan() || interVec.isNan()){
        return Vec3(0, 0, 0);
    }
    Vec3 surfColor;
    Vec3 epsilonPoint = interVec + normal * 0.001;
    for (int i = 0; i < renderScene->getObjTracker()->getLightList().size(); ++i){
        Ray shadowRay = Ray(epsilonPoint, renderScene->getObjTracker()->getLightList().at(i)->shadowRay(interVec, normal));
        Object* shadowObject = nullptr;
        Vec3 shadowIntersect = renderScene->getObjTracker()->getIntersect(shadowRay, true, shadowObject);
        bool isOccluded = true;
        if (shadowObject == nullptr || shadowObject->isLight() || shadowIntersect.getMagnitude() == VAL_INFINITY || shadowIntersect.getMagnitude() == NEG_INFINITY ||
                shadowObject == renderScene->getObjTracker()->getLightList().at(i)) {
            isOccluded = false;
        }
        if (!isOccluded) {
            Vec3 addColor = calcLighting(intersectObject, renderScene->getObjTracker()->getLightList().at(i), interVec,
                                         shadowRay.direction, shadowIntersect, normal, objectUV);
            surfColor += addColor;
        }
        else if(shadowObject->material->transmission(objectUV) > 0.0){
            Vec3 addColor = calcLighting(intersectObject, renderScene->getObjTracker()->getLightList().at(i), interVec,
                                         shadowRay.direction, shadowIntersect, normal, objectUV);
            surfColor += addColor * (1.0 - shadowObject->material->transmission(objectUV));
        }
    }
    return surfColor;
}

Vec3 Phong::calcLighting(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 shadowIntersect, Vec3 normal, Vec2 objectUV) {
    if(light->ID() == light->ID_Ambient_Light){
        return calcAmbient(surface, light, objectUV);
    }
    Vec2 lightUV;
    if(shadowIntersect.getMagnitude() != VAL_INFINITY && shadowIntersect.getMagnitude() != NEG_INFINITY){
        lightUV = light->getUV(shadowIntersect);
    }
    Vec3 lighting = calcDiffuse(surface, light, interPoint, rayDir, normal, objectUV, lightUV); //+
                    //calcSpec(surface, light, interPoint, rayDir, normalScalar, objectUV, lightUV);
    if(lighting.isNan()){
        return Vec3();
    }
    return lighting;

}
Vec3 Phong::calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV) {
    Vec3 od = surface->material->getColor(objectUV);
    Vec3 l = rayDir;
    double maxDiffuse = RenderOps().max(0, normal.dot(l));
    Vec3 lightEmission = light->material->getColor(lightUV) * light->material->gamma(lightUV);
    Vec3 retVec = od * maxDiffuse * lightEmission * surface->material->diffuse(objectUV);

    return retVec;
}
Vec3 Phong::calcSpec(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV){
    Vec3 r = RenderOps().reflectionDirection(normal,
                                             (rayDir) * -1);
    double ks = surface->material->reflective(objectUV);
    double maxSpec = RenderOps().max(0, (rayDir * -1).dot(r));
    Vec3 os = surface->material->getColor(objectUV);
    double kgls = surface->material->kgls(objectUV);
    Vec3 lightEmission = light->material->getColor(lightUV) * light->material->gamma(lightUV);

    return lightEmission * os * ks * pow(maxSpec, kgls);
}
Vec3 Phong::calcAmbient(Object* surface, Object* light, Vec2 objectUV) {
    Vec3 lightEmission = light->material->getColor(Vec2()) * light->material->gamma(Vec2());
    return lightEmission * surface->material->getColor(objectUV) * surface->material->diffuse(objectUV) * 0.001;
}