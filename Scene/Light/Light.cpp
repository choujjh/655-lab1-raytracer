//
// Created by chouj on 3/8/2021.
//

#include "Light.h"
#include "../../Model/Ops/RenderOps.h"

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
    Vec3 od = surface->objMat.colorDiffuse->getColor();
    Vec3 l = shadowRay(interPoint).normalize();
    Vec3 n = surface->normal(interPoint).normalize();
    double maxDiffuse = max(0, n.dot(l));
    Vec3 retVec = od * maxDiffuse * color * surface->objMat.kDiffuse->getColor();

    return retVec;
}

Vec3 Light::calcSpec(Object* surface, Vec3 interPoint, Vec3 rayDir){
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec3();
    }
    Vec3 r = RenderOps().reflectionRay(surface->normal(interPoint).normalize(), shadowRay(interPoint).normalize());
    double ks = surface->objMat.kSpecular->getColor();
    double maxSpec = max(0, (rayDir * -1).dot(r));
    Vec3 os = surface->objMat.colorSpec->getColor();
    double kgls = surface->objMat.kgls->getColor();

    return color * os * ks * pow(maxSpec, kgls);
}
Vec3 Light::calcAmbient(Object* surface, Vec3 interPoint, Vec3 rayDir) {
    if(!checkNormal(surface, interPoint, rayDir)){
        return Vec3();
    }

    return color * surface->objMat.colorDiffuse->getColor() * surface->objMat.kAmbient->getColor();
}
bool Light::checkNormal(Object* surface, Vec3 interPoint, Vec3 rayDir) {
    if(rayDir.dot(surface->normal(interPoint)) > 0){
        return false;
    }
    return true;
}

Light::Light(const Vec3 &color) : color(color) {}
