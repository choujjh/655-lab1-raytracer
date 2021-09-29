//
// Created by chouj on 3/8/2021.
//

#include "Light.h"


bool Light::isLight() {
    return true;
}

Light::Light(BaseMaterial *objMat) : Object(objMat) {}

void Light::getUV(Vec3 point, double& u, double& v) {
    u = 0.0;
    v = 0.0;
}

