//
// Created by chouj on 3/13/2021.
//

#include "RenderOps.h"
#include "LinAlgOp.h"

Vec RenderOps::reflectionRay(Vec normal, Vec initDir) {
    return normal * 2 * LinAlgOp().dot(normal, initDir) - initDir;
}