//
// Created by chouj on 3/7/2021.
//

#include "Sphere.h"

#include <cmath>

const Vec3 &Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(const Vec3 &center) {
    Sphere::center = center;
}

double Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(double radius) {
    Sphere::radius = radius;
}

Sphere::Sphere(const Material &objMat, const Vec3 &center, double radius) : Object(objMat), center(center),
                                                                            radius(radius) {}

Vec3 Sphere::intersect(Ray ray) {
    ray.direction.normalize();

    Vec3 oc = center - ray.point;
    double tca = ray.direction.dot(oc);
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

Vec3 Sphere::normal(Vec3 point) {
    Vec3 normal = (point - center).normalize();
    return normal;
}
