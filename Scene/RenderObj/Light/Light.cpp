//
// Created by chouj on 3/8/2021.
//

#include "Light.h"


bool Light::isLight() {
    return true;
}

Light::Light(BaseMaterial *objMat) : Object(objMat) {}

Vec2 Light::getUV(Vec3 point) {
    return Vec2();
}

