//
// Created by chouj on 10/14/2021.
//

#include "../Model/Ops/RenderOps.h"
#include "PathTracer.h"

Vec3 PathTracer::radiance(Ray ray, int depth, int levReflectRecursion) {
    //return if recursion limit is reached
    if(depth >= levReflectRecursion){
        return Vec3();
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
    bool isInsideObject = ray.direction.dot(n) >= 0;
    if(isInsideObject) n = n * -1;

    Vec3 color = calcSurfColor(ray, interVec, intersectObject, n, interObjectUV);

    double diffuse = intersectObject->material->diffuse(interObjectUV);
    double reflect = intersectObject->material->reflective(interObjectUV);
    double transmission = intersectObject->material->transmission(interObjectUV);
    double randBRDF = RenderOps().randFloatValue(0, diffuse + reflect + transmission);
    Vec3 randDir = Vec3(RenderOps().randFloatValue(), RenderOps().randFloatValue(), RenderOps().randFloatValue());

    Vec3 epsilonPoint = interVec + n * 0.001;
    //send out a diffuse ray
    Vec3 pathColor = Vec3();
    double fresnelEffect = RenderOps().calcFresnelReflectAmount(1, 1.5, n, ray.direction);
    if(randBRDF < diffuse){
        CoordinateSpace cs = RenderOps().makeCoordinateSystem(n, randDir);
        Vec3 dir = RenderOps().randomPointOnSphere(cs, 1, interVec, 0, 2 * M_PI, 0, M_PI / 2);
        pathColor = radiance(Ray(epsilonPoint, dir), depth + 1, levReflectRecursion);
    }
    //send out a reflect ray
    else if(randBRDF < diffuse + reflect){

        double offsetX = RenderOps().randFloatValue(-1 * intersectObject->material->gloss(interObjectUV), intersectObject->material->gloss(interObjectUV));
        double offsetY = RenderOps().randFloatValue(-1 * intersectObject->material->gloss(interObjectUV), intersectObject->material->gloss(interObjectUV));
        Vec3 reflDir = RenderOps().reflectionDirection(n, ray.direction);
        CoordinateSpace cs = RenderOps().makeCoordinateSystem(reflDir, n);
        reflDir = (reflDir + cs.up * offsetY + cs.right * offsetX).normalize();
        pathColor = radiance(Ray(epsilonPoint, reflDir), depth + 1, levReflectRecursion);

        pathColor =
        (pathColor * (1 - fresnelEffect));
    }
    //send out a transmission ray
    else{

    }
    return color + pathColor;
}

Vec3 PathTracer::calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, Vec3 normal, Vec2 objectUV) {
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
            Vec2 lightUV = renderScene->getObjTracker()->getLightList().at(i)->getUV(shadowIntersect);
            Vec3 addColor = calcDiffuse(intersectObject, renderScene->getObjTracker()->getLightList().at(i), interVec, shadowRay.direction, normal, objectUV, lightUV);
            surfColor += addColor;
        }
    }
    return surfColor/renderScene->getObjTracker()->getLightList().size();
}

Vec3 PathTracer::calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV) {
    Vec3 od = surface->material->getColor(objectUV);
    Vec3 l = rayDir;
    double maxDiffuse = RenderOps().max(0, normal.dot(l));
    Vec3 lightEmission = light->material->getColor(lightUV) * light->material->gamma(lightUV);
    Vec3 retVec = od * maxDiffuse * lightEmission * surface->material->diffuse(objectUV);

    return retVec;
}

PathTracer::PathTracer(Scene *renderScene) : Integrator(renderScene) {}
