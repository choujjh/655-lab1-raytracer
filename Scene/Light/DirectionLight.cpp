//
// Created by chouj on 3/10/2021.
//

#include "DirectionLight.h"

Vec3 DirectionLight::shadowRay(Vec3 point){
    return dir * -1;
}

DirectionLight::DirectionLight(const Vec3 &color, const Vec3 &dir) : Light(color), dir(dir) {}

bool DirectionLight::isAmbient() {
    return false;
}


