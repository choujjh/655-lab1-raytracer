//
// Created by chouj on 3/13/2021.
//

#include "Plane.h"


Plane::Plane(const Material &objMat, const Vec3 &n, double d) : Object(objMat), n(n), d(d) {}
Vec3 Plane::intersect(Ray ray) {
    ray.direction.normalize();
    double den = n.dot(ray.direction);
    if(den == 0.0){
        return Object::intersect(ray);
    }

    double t = -(n.dot(ray.point) - d) / den;
    if(t <= 0) {
        return Object::intersect(ray);
    }
    return ray.point + ray.direction * t;
}

Vec3 Plane::normal(Vec3 point) {
    return n;
}

