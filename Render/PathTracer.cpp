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
        return renderScene->getBackColor();
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

    Vec3 surfColor = calcSurfColor(ray, interVec, intersectObject, n, interObjectUV);

    double diffuse = intersectObject->material->diffuse(interObjectUV);
    double reflect = intersectObject->material->reflective(interObjectUV);
    double transmission = intersectObject->material->transmission(interObjectUV);
    double randBRDF = randFloatValue(0, diffuse + reflect + transmission);
    Vec3 randDir = Vec3(randFloatValue(), randFloatValue(), randFloatValue());

    Vec3 epsilonPoint = interVec + n * 0.001;
    //send out a diffuse ray
    Vec3 pathColor = Vec3();
    double fresnelEffect = calcFresnelReflectAmount(1, 1.5, n, ray.direction);

    //reflection ray
    double offsetX = randFloatValue(-1 * intersectObject->material->gloss(interObjectUV), intersectObject->material->gloss(interObjectUV));
    double offsetY = randFloatValue(-1 * intersectObject->material->gloss(interObjectUV), intersectObject->material->gloss(interObjectUV));
    Vec3 reflDir = reflectionDirection(n, ray.direction);
    CoordinateSpace cs = makeCoordinateSystem(reflDir, n);
    reflDir = (reflDir + cs.up * offsetY + cs.right * offsetX).normalize();
    Vec3 reflColor = radiance(Ray(epsilonPoint, reflDir), depth + 1, levReflectRecursion) * intersectObject->material->getColor(interObjectUV);
    if(randBRDF < diffuse){
        CoordinateSpace cs = makeCoordinateSystem(n, randDir);
        Vec3 dir = randomPointOnSphere(cs, 1, Vec3(), 0, 2 * M_PI, 0, M_PI / 2);
        pathColor = radiance(Ray(epsilonPoint, dir), depth + 1, levReflectRecursion);
    }
    //send out a reflect ray
    else if(randBRDF < diffuse + reflect){
        pathColor = reflColor;
    }
    //send out a transmission ray
    else{
        offsetX = randFloatValue(-1 * intersectObject->material->translucency(interObjectUV), intersectObject->material->translucency(interObjectUV));
        offsetY = randFloatValue(-1 * intersectObject->material->translucency(interObjectUV), intersectObject->material->translucency(interObjectUV));

        double normDirAngle = ray.direction.dot(n);
        //total internal reflection
        double iorValue = !isInsideObject? (1/ intersectObject->material->ior(interObjectUV)) : intersectObject->material->ior(interObjectUV);
        double interiorAngle = 1 - (iorValue * iorValue) * (1 - normDirAngle * normDirAngle);

        if (interiorAngle < 0) {
            pathColor = reflColor;
        }
        else {

            Ray transRay = calcTransmissionRay(ray.direction, intersectObject, interVec, isInsideObject,
                                                           interObjectUV);
            CoordinateSpace cs = makeCoordinateSystem(transRay.direction, Vec3(randFloatValue(), randFloatValue(), randFloatValue()));
            transRay.direction = (transRay.direction + cs.up * offsetY + cs.right * offsetX).normalize();

            pathColor = radiance(transRay, depth + 1, levReflectRecursion);
        }
    }
//    return pathColor;
    return ((surfColor + pathColor) * (1 - fresnelEffect) + reflColor * (fresnelEffect));// * ((levReflectRecursion - depth) * 1.0 / levReflectRecursion);
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
    return surfColor;// / renderScene->getObjTracker()->getLightList().size();
}

Vec3 PathTracer::calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV) {
    Vec3 od = surface->material->getColor(objectUV);
    Vec3 l = rayDir;
    double maxDiffuse = max(0, normal.dot(l));
    Vec3 lightEmission = light->material->getColor(lightUV) * light->material->gamma(lightUV);
    Vec3 retVec = od * maxDiffuse * lightEmission * surface->material->diffuse(objectUV);

    return retVec;
}

PathTracer::PathTracer(Scene *renderScene) : Integrator(renderScene) {}
