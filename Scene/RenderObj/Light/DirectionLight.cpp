//
// Created by chouj on 3/10/2021.
//

#include "DirectionLight.h"

Vec3 DirectionLight::shadowRay(Vec3 point, Vec3 objectNormal){
    return dir * -1;
}

DirectionLight::DirectionLight(BaseMaterial* material, const Vec3 &dir) : Light(material), dir(dir) {}

Vec3 DirectionLight::intersect(Ray ray) {
    return infiniteVec3();
}

Vec3 DirectionLight::normal(Vec3 point) {
    return infiniteVec3();
}


