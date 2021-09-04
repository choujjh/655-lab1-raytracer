//
// Created by chouj on 3/13/2021.
//

#include "Plane.h"
#include "../../../Ops/LinAlgOp.h"

Plane::Plane(double kDiffuse, double kSpecular, double ka, const Vec3 &colorDiffuse, const Vec3 &colorSpec, double kgls,
             const Vec3 &n, double d) : Object(kDiffuse, kSpecular, ka, colorDiffuse, colorSpec, kgls),
                                       n(n), d(d) {}
Vec3 Plane::intersect(Ray ray) {
    ray.direction.normalize();
    double den = LinAlgOp().dot(n, ray.direction);
    if(den == 0.0){
        return Object::intersect(ray);
    }
    double t = -(LinAlgOp().dot(n, ray.point) - d) / den;
    if(t <= 0) {
        return Object::intersect(ray);
    }
    return ray.point + ray.direction * t;
}
Vec3 Plane::normal(Vec3 point) {
    return n;
}

