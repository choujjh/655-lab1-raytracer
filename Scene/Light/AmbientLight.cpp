//
// Created by chouj on 3/12/2021.
//

#include "AmbientLight.h"


Vec3 AmbientLight::shadowRay(Vec3 point) {
    return Vec3(0.0, 0.0, 0.0);
}
AmbientLight::AmbientLight(const Vec3 &color) : Light(color) {}

bool AmbientLight::isAmbient() {
    return true;
}