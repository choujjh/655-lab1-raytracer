//
// Created by chouj on 3/12/2021.
//

#include "AmbientLight.h"


Vec ambientLight::shadowRay(Vec point) {
    return Vec(0.0, 0.0, 0.0);
}
Vec ambientLight::illumination(Vec point, Vec rayDir, Object* surface, bool occluded) {
    return Light::calcAmbient(surface, point, rayDir);
}

ambientLight::ambientLight(const Vec &color) : Light(color) {}
