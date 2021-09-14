//
// Created by chouj on 3/7/2021.
//


#include "Object.h"


Vec3 Object::intersect(Ray ray) {
    double inf = VAL_INFINITY;
    return Vec3(inf, inf, inf);
}

Object::Object(Material* objMat) : material(objMat) {}

Vec3 Object::infiniteVec3() {
    return Object::intersect(Ray());
}
