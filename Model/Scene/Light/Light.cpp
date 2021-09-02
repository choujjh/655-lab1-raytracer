//
// Created by chouj on 3/8/2021.
//

#include "Light.h"
#include "../../../Ops/LinAlgOp.h"
#include "../../../Ops/RenderOps.h"

#include <cmath>

double Light::max(double a, double b){
    if(a < b) {
        return b;
    }
    return a;
}

Vec Light::calcDiffuse(Object* surface, Vec interPoint, Vec rayDir) {
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec();
    }
    Vec od = surface->getColorDiffuse();
    Vec l = shadowRay(interPoint).normalize();
    Vec n = surface->normal(interPoint).normalize();
    double maxDiffuse = max(0, LinAlgOp().dot(n, l));
    Vec retVec = od * maxDiffuse * color * surface->getKDiffuse();

    return retVec;
}

Vec Light::calcSpec(Object* surface, Vec interPoint, Vec rayDir){
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec();
    }
    Vec r = RenderOps().reflectionRay(surface->normal(interPoint).normalize(), shadowRay(interPoint).normalize());
    double ks = surface->getKSpecular();
    double maxSpec = max(0, LinAlgOp().dot(rayDir * -1, r));
    Vec os = surface->getColorSpec();
    double kgls = surface->getKgls();

    return color * os * ks * pow(maxSpec, kgls);
}
Vec Light::calcAmbient(Object* surface, Vec interPoint, Vec rayDir) {
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec();
    }
    return color * surface->getColorDiffuse() * surface->getKAmbient();
}
bool Light::checkNormal(Object* surface, Vec interPoint, Vec rayDir) {
    if(LinAlgOp().dot(rayDir, surface->normal(interPoint)) > 0){
        return false;
    }
    return true;
}

Light::Light(const Vec &color) : color(color) {}
