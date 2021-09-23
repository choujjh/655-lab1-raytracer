//
// Created by chouj on 3/13/2021.
//

#include "Plane.h"


Plane::Plane(BaseMaterial *objMat, const Vec3 &n, double d) : Object(objMat), n(n), d(d) {}
Vec3 Plane::intersect(Ray ray) {
    ray.direction.normalize();
    double den = n.dot(ray.direction);
    if(den == 0.0){
        return infiniteVec3();
    }
    if(den == NEG_INFINITY){
        return infiniteVec3() * -1;
    }

    double t = -(n.dot(ray.point) - d) / den;
    if(t <= 0) {
        return infiniteVec3();
    }
    return ray.point + ray.direction * t;
}

Vec3 Plane::normal(Vec3 point) {
    return n;
}

Vec3 Plane::shadowRay(Vec3 point) {
    return n * -1;
}

