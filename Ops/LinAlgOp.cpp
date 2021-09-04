//
// Created by chouj on 3/6/2021.
//

#include "linAlgOp.h"

double LinAlgOp::dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 LinAlgOp::cross(Vec3 a, Vec3 b) {
    return Vec3((a.y * b.z - b.y * a.z),
                (b.x * a.z - a.x * b.z),
                (a.x * b.y - b.x * a.y));
}

