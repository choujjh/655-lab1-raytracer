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

Vec3 Light::calcDiffuse(Object* surface, Vec3 interPoint, Vec3 rayDir) {
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec3();
    }
    Vec3 od = surface->getColorDiffuse();
    Vec3 l = shadowRay(interPoint).normalize();
    Vec3 n = surface->normal(interPoint).normalize();
    double maxDiffuse = max(0, LinAlgOp().dot(n, l));
    Vec3 retVec = od * maxDiffuse * color * surface->getKDiffuse();

    return retVec;
}

Vec3 Light::calcSpec(Object* surface, Vec3 interPoint, Vec3 rayDir){
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec3();
    }
    Vec3 r = RenderOps().reflectionRay(surface->normal(interPoint).normalize(), shadowRay(interPoint).normalize());
    double ks = surface->getKSpecular();
    double maxSpec = max(0, LinAlgOp().dot(rayDir * -1, r));
    Vec3 os = surface->getColorSpec();
    double kgls = surface->getKgls();

    return color * os * ks * pow(maxSpec, kgls);
}
Vec3 Light::calcAmbient(Object* surface, Vec3 interPoint, Vec3 rayDir) {
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec3();
    }
    return color * surface->getColorDiffuse() * surface->getKAmbient();
}
bool Light::checkNormal(Object* surface, Vec3 interPoint, Vec3 rayDir) {
    if(LinAlgOp().dot(rayDir, surface->normal(interPoint)) > 0){
        return false;
    }
    return true;
}

Light::Light(const Vec3 &color) : color(color) {}
