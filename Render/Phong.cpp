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
    Object* object = nullptr;
    Vec3 interVec = renderScene->getObjTracker()->getIntersect(ray, true, object);

    if(interVec.getMagnitude() == VAL_INFINITY || interVec.getMagnitude() == NEG_INFINITY) {
        return renderScene->getBackColor();
    }

    //initializing variables for light calculations
    Vec3 n = object->normal(interVec);
    Vec3 epsilonPoint = interVec + n * 0.001;
    Vec3 color(0.0, 0.0, 0.0);

    for(int i = 0; i < renderScene->getLightList().size(); ++i) {
        Ray shadowRay = Ray(epsilonPoint, renderScene->getLightList().at(i)->shadowRay(interVec));
        Vec3 shadowIntersect = renderScene->getObjTracker()->getIntersect(shadowRay, false);
        bool occluded = true;
        if (shadowIntersect.getMagnitude() == VAL_INFINITY || shadowIntersect.getMagnitude() == NEG_INFINITY) {
            occluded = false;
        }
//        emission
//        if(object->objMat->colorEmission->getColor().getMagnitude() != 0.0){
//            return object->objMat->colorEmission->getColor() * 2;
//        }
        if(!occluded) {

            Vec3 addColor = calcLighting(object, renderScene->getLightList().at(i), interVec, ray.direction);
            addColor.clip(0, 1);

            color += addColor;
        }
    }
    Vec3 refRay = RenderOps().reflectionRay(n, ray.direction);
    Ray newRay(epsilonPoint, refRay);
    color += radiance(newRay, depth + 1, levReflectRecursion) * object->objMat->kSpecular->getColor() * object->objMat->kSpecular->getColor();
    color.clip(0, 1);

    return color;
}

Vec3 Phong::calcLighting(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir) {
    if(light->isAmbient()){
        return calcAmbient(surface, light, interPoint, rayDir);
    }
    return calcDiffuse(surface, light, interPoint, rayDir) + calcSpec(surface, light, interPoint, rayDir);

}

Vec3 Phong::calcDiffuse(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir) {
    Vec3 od = surface->objMat->colorDiffuse->getColor();
    Vec3 l = light->shadowRay(interPoint).normalize();
    Vec3 n = surface->normal(interPoint).normalize();
    double maxDiffuse = RenderOps().max(0, n.dot(l));
    Vec3 retVec = od * maxDiffuse * light->color * surface->objMat->kDiffuse->getColor();

    return retVec;
}
Vec3 Phong::calcSpec(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir){
    Vec3 r = RenderOps().reflectionRay(surface->normal(interPoint).normalize(), (light->shadowRay(interPoint).normalize()) * -1);
    double ks = surface->objMat->kSpecular->getColor();
    double maxSpec = RenderOps().max(0, (rayDir * -1).dot(r));
    Vec3 os = surface->objMat->colorSpec->getColor();
    double kgls = surface->objMat->kgls->getColor();

    return light->color * os * ks * pow(maxSpec, kgls);
}
Vec3 Phong::calcAmbient(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir) {

    return light->color * surface->objMat->colorDiffuse->getColor() * surface->objMat->kAmbient->getColor();
}
bool Phong::checkNormal(Object* surface, Vec3 interPoint, Vec3 rayDir) {
    if(rayDir.dot(surface->normal(interPoint)) > 0){
        return false;
    }
    return true;
}
