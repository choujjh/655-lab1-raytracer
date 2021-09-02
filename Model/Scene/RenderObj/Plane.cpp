//
// Created by chouj on 3/13/2021.
//

#include "Plane.h"
#include "../../../Ops/LinAlgOp.h"

Plane::Plane(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec, double kgls,
             const Vec &n, double d) : Object(kDiffuse, kSpecular, ka, colorDiffuse, colorSpec, kgls),
                                       n(n), d(d) {}
Vec Plane::intersect(OffVec ray) {
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
Vec Plane::normal(Vec point) {
    return n;
}

