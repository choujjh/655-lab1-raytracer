//
// Created by chouj on 9/10/2021.
//

#include "PointLight.h"

Vec3 PointLight::shadowRay(Vec3 point) {
    return this->position - point;
}

PointLight::PointLight(BaseMaterial* material, const Vec3 &position) : Light(material), position(position), intersectionSphere(Sphere(material, position, 0.01)) {}

Vec3 PointLight::intersect(Ray ray) {
    //TODO: get intersections for point lights
    return infiniteVec3();
}

Vec3 PointLight::normal(Vec3 point) {
    return infiniteVec3();
}