//
// Created by chouj on 9/10/2021.
//

#include "PointLight.h"

Vec3 PointLight::shadowRay(Vec3 point) {
    return this->position - point;
}

bool PointLight::isAmbient() {
    return false;
}

PointLight::PointLight(const Vec3 &color, const Vec3 &position) : Light(color), position(position) {}
