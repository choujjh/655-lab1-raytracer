//
// Created by chouj on 3/6/2021.
//

#ifndef RAYTRACER_LINALGOP_H
#define RAYTRACER_LINALGOP_H


#include "../Model/VecModel/Vec.h"

class LinAlgOp {
public:
    double static dot(Vec a, Vec b);
    Vec static cross(Vec a, Vec b);
};


#endif //RAYTRACER_LINALGOP_H
