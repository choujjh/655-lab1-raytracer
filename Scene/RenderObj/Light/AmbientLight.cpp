//
// Created by chouj on 3/12/2021.
//

#include "AmbientLight.h"


Vec3 AmbientLight::shadowRay(Vec3 point, Vec3 objectNormal) {
    return Vec3(0.0, 0.0, 0.0);
}
AmbientLight::AmbientLight(BaseMaterial* material) : Light(material) {}

Vec3 AmbientLight::intersect(Ray ray) {
    return infiniteVec3();
}

Vec3 AmbientLight::normal(Vec3 point) {
    return infiniteVec3();
}

int AmbientLight::ID() {
    return ID_Ambient_Light;
}
