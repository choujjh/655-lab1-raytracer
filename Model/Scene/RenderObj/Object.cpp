//
// Created by chouj on 3/7/2021.
//


#include "Object.h"

#include <limits>


Vec3 Object::intersect(Ray ray) {
    double inf = std::numeric_limits<double>::infinity();
    return Vec3(inf, inf, inf);
}

Object::Object(const Material &objMat) : objMat(objMat) {}
