//
// Created by chouj on 3/10/2021.
//

#include "DirectionLight.h"

Vec directionLight::shadowRay(Vec point){
    return dir * -1;
}
Vec directionLight::illumination(Vec point, Vec rayDir, Object* surface, bool occluded) {
    if(occluded){
        return Vec(0.0, 0.0, 0.0);
    }
    return Light::calcDiffuse(surface, point, rayDir) + Light::calcSpec(surface, point, rayDir);
}

directionLight::directionLight(const Vec &color, const Vec &dir) : Light(color), dir(dir) {}


