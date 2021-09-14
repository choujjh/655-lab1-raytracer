//
// Created by chouj on 9/10/2021.
//

#include <cmath>

#include "Phong.h"
#include "../Model/Ops/RenderOps.h"

Phong::Phong(Scene *renderScene) : Integrator(renderScene) {}

Vec3 Phong::radiance(Ray ray, int depth, int levReflectRecursion) {

    //return if recursion limit is reached
    if(depth >= levReflectRecursion){
        return renderScene->getBackColor();
    }

    //find intersection
    Object* intersectObject = nullptr;

    Vec3 interVec = renderScene->getObjTracker()->getIntersect(ray, true, intersectObject);
    if(interVec.getMagnitude() == VAL_INFINITY || interVec.getMagnitude() == NEG_INFINITY) {
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
    Vec3 epsilonPoint = interVec + intersectObject->normal(interVec) * normalScalar * 0.001;
    Ray reflRay(epsilonPoint, RenderOps().reflectionDirection(n * normalScalar, ray.direction));
    Vec3 reflColor = radiance(reflRay, depth + 1, levReflectRecursion) * intersectObject->material->kSpecular->getColor() *
                     intersectObject->material->kSpecular->getColor();

    //refr color
    Vec3 refrColor(0.0, 0.0, 0.0);

    if(opacity > 0) {

        Ray transRay = RenderOps().calcTransmissionRay(ray.direction, intersectObject, interVec, isInsideObject);
        Vec3 transDir = transRay.direction;
        transDir.normalize();

        refrColor = radiance(transRay, depth + 1, levReflectRecursion);
    }
    return ((surfColor + reflColor) * (1.0 - opacity) + refrColor * opacity).clip(0, 1);
}
Vec3 Phong::calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, double normalScalar) {
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
            addColor.clip(0, 1);
            surfColor += addColor;
        }
        else if(shadowObject->material->opacity->getColor() > 0.0){
            Vec3 addColor = calcLighting(intersectObject, renderScene->getLightList().at(i), interVec,
                                         ray.direction, normalScalar);
            addColor.clip(0, 1);
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