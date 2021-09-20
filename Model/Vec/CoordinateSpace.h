//
// Created by chouj on 9/20/2021.
//

#ifndef LAB_1_COORDINATESPACE_H
#define LAB_1_COORDINATESPACE_H


#include "Vec3.h"

class CoordinateSpace {
public:
    Vec3 direction;
    Vec3 up;
    Vec3 right;

    CoordinateSpace(const Vec3 &direction, const Vec3 &up, const Vec3 &right);

    CoordinateSpace();
};


#endif //LAB_1_COORDINATESPACE_H
