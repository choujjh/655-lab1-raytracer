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
        return renderScene->getBackColor();
    }

    //initializing variables for light calculations
    double normalScalar = 1.0;
    Vec3 n = intersectObject->normal(interVec);
    bool isInsideObject = (ray.direction.dot(n) > 0);
    if(isInsideObject) normalScalar = -1.0;
    double opacity = intersectObject->material->opacity->getColor();

    //surf color
    Vec3 surfColor = calcSurfColor(ray, interVec, intersectObject, normalScalar);

    //refl color
    CoordinateSpace cs = RenderOps().makeCoordinateSystem(ray.direction, n * normalScalar);
    double offsetX = RenderOps().randFloatValue(-0.1, 0.1);
    double offsetY = RenderOps().randFloatValue(-0.1, 0.1);
    Vec3 reflDir = RenderOps().reflectionDirection(n * normalScalar, ray.direction);
    reflDir = (reflDir + cs.up * offsetY + cs.right * offsetX).normalize();
    Vec3 epsilonPoint = interVec + intersectObject->normal(interVec) * normalScalar * 0.001;
    Vec3 reflColor = radiance(Ray(reflDir, epsilonPoint), depth + 1, levReflectRecursion, sampleDensity) * intersectObject->material->kSpecular->getColor() *
                     intersectObject->material->kSpecular->getColor();

    if(opacity > 0) {
        offsetX = RenderOps().randFloatValue(-0.1, 0.1);
        offsetY = RenderOps().randFloatValue(-0.1, 0.1);
        Ray transRay = RenderOps().calcTransmissionRay(ray.direction, intersectObject, interVec, isInsideObject);
        transRay.direction = (transRay.direction + cs.up * offsetY + cs.right * offsetX).normalize();
        double iorLeft = 1.0;
        double iorEntered = intersectObject->material->IOR->getColor();
        if(isInsideObject){
            iorLeft = intersectObject->material->IOR->getColor();
            iorEntered = 1.0;
        }

        Vec3 refrColor = radiance(transRay, depth + 1, levReflectRecursion, sampleDensity);
        double fresnelEffect = RenderOps().calcFresnelReflectAmount(iorLeft, iorEntered, n, ray.direction);

        return  surfColor * (1.0 - opacity) + intersectObject->material->colorDiffuse->getColor() * (reflColor * fresnelEffect + refrColor * (1 - fresnelEffect) * opacity);
    }
    return surfColor + reflColor;

}
Vec3 Phong::calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, double normalScalar) {
    if(ray.isNan() || interVec.isNan()){
        return Vec3(0, 0, 0);
    }
    Vec3 surfColor;
    Vec3 epsilonPoint = interVec + intersectObject->normal(interVec) * normalScalar * 0.001;
    for (int i = 0; i < renderScene->getLightList().size(); ++i) {
        Ray shadowRay = Ray(epsilonPoint, renderScene->getLightList().at(i)->shadowRay(interVec));
        Object* shadowObject = nullptr;
        Vec3 shadowIntersect = renderScene->getObjTracker()->getIntersect(shadowRay, false, shadowObject);
        bool occluded = true;
        if (shadowIntersect.getMagnitude() == VAL_INFINITY || shadowIntersect.getMagnitude() == NEG_INFINITY) {
            occluded = false;
        }
        if (!occluded) {

            Vec3 addColor = calcLighting(intersectObject, renderScene->getLightList().at(i), interVec,
                                         ray.direction, normalScalar);
            surfColor += addColor;
        }
        else if(shadowObject->material->opacity->getColor() > 0.0){
            Vec3 addColor = calcLighting(intersectObject, renderScene->getLightList().at(i), interVec,
                                         ray.direction, normalScalar);
            surfColor += addColor * (1.0 - shadowObject->material->opacity->getColor());
        }
    }
    return surfColor;
}

Vec3 Phong::calcLighting(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar) {
    if(light->isAmbient()){
        return calcAmbient(surface, light, interPoint, rayDir, normalScalar);
    }
    return calcDiffuse(surface, light, interPoint, rayDir, normalScalar) + calcSpec(surface, light, interPoint, rayDir, normalScalar);

}
Vec3 Phong::calcDiffuse(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar) {
    Vec3 od = surface->material->colorDiffuse->getColor();
    Vec3 l = light->shadowRay(interPoint).normalize();
    Vec3 n = surface->normal(interPoint).normalize() * normalScalar;
    double maxDiffuse = RenderOps().max(0, n.dot(l));
    Vec3 retVec = od * maxDiffuse * light->color * surface->material->kDiffuse->getColor();

    return retVec;
}
Vec3 Phong::calcSpec(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar){
    Vec3 r = RenderOps().reflectionDirection(surface->normal(interPoint).normalize() * normalScalar,
                                             (light->shadowRay(interPoint).normalize()) * -1);
    double ks = surface->material->kSpecular->getColor();
    double maxSpec = RenderOps().max(0, (rayDir * -1).dot(r));
    Vec3 os = surface->material->colorSpec->getColor();
    double kgls = surface->material->kgls->getColor();

    return light->color * os * ks * pow(maxSpec, kgls);
}
Vec3 Phong::calcAmbient(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar) {

    return light->color * surface->material->colorDiffuse->getColor() * surface->material->kAmbient->getColor();
}