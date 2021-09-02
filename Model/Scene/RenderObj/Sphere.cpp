//
// Created by chouj on 3/7/2021.
//

#include "Sphere.h"
#include "../../../Ops/LinAlgOp.h"

#include <cmath>

const Vec &Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(const Vec &center) {
    Sphere::center = center;
}

double Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(double radius) {
    Sphere::radius = radius;
}

Sphere::Sphere(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec, double kgls,
               const Vec &center, double radius) : Object(kDiffuse, kSpecular, ka, colorDiffuse, colorSpec, kgls) {
    this->center = center;
    this->radius = radius;
}

Vec Sphere::intersect(OffVec ray) {
    ray.direction.normalize();

    Vec oc = center - ray.point;
    double tca = LinAlgOp().dot(ray.direction, oc);
    if(tca < 0.0){
        return Object::intersect(ray);
    }
    double thcSqr = radius * radius - oc.getMagnitude() * oc.getMagnitude() + tca * tca;
    if(thcSqr < 0.0){
        return Object::intersect(ray);
    }
    else if((center - ray.point).getMagnitude() < radius) {
        return ray.point + ray.direction * (tca + sqrt(thcSqr));
    }
    return ray.point + ray.direction * (tca - sqrt(thcSqr));
}

Vec Sphere::normal(Vec point) {
    Vec normal = (point - center).normalize();
    return normal;
}
