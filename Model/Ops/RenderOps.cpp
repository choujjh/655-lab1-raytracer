//
// Created by chouj on 3/13/2021.
//

#include "RenderOps.h"
#include "LinAlgOp.h"

Vec3 RenderOps::reflectionRay(Vec3 normal, Vec3 initDir) {
    return normal * 2 * LinAlgOp().dot(normal, initDir) - initDir;
}