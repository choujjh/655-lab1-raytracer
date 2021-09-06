//
// Created by chouj on 3/12/2021.
//

#include "AmbientLight.h"


Vec3 ambientLight::shadowRay(Vec3 point) {
    return Vec3(0.0, 0.0, 0.0);
}
Vec3 ambientLight::illumination(Vec3 point, Vec3 rayDir, Object* surface, bool occluded) {
    return Light::calcAmbient(surface, point, rayDir);
}

ambientLight::ambientLight(const Vec3 &color) : Light(color) {}
