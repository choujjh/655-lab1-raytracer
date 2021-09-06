//
// Created by chouj on 3/6/2021.
//

#ifndef RAYTRACER_LINALGOP_H
#define RAYTRACER_LINALGOP_H


#include "../Vec/Vec3.h"

class LinAlgOp {
public:
    double static dot(Vec3 a, Vec3 b);
    Vec3 static cross(Vec3 a, Vec3 b);
};


#endif //RAYTRACER_LINALGOP_H
