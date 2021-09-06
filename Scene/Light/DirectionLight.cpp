//
// Created by chouj on 3/10/2021.
//

#include "DirectionLight.h"

Vec3 DirectionLight::shadowRay(Vec3 point){
    return dir * -1;
}
Vec3 DirectionLight::illumination(Vec3 point, Vec3 rayDir, Object* surface, bool occluded) {
    if(occluded){
        return Vec3(0.0, 0.0, 0.0);
    }
    return Light::calcDiffuse(surface, point, rayDir) + Light::calcSpec(surface, point, rayDir);;
}

DirectionLight::DirectionLight(const Vec3 &color, const Vec3 &dir) : Light(color), dir(dir) {}


