//
// Created by chouj on 3/13/2021.
//

#include "RenderOps.h"
#include "LinAlgOp.h"

Vec3 RenderOps::reflectionRay(Vec3 normal, Vec3 initDir) {
    return initDir - (normal * 2 * normal.dot(initDir));
}
double RenderOps::max(double a, double b) {
    return a > b ? a : b;
}