//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_OFFVEC_H
#define RAYTRACER_OFFVEC_H

#include "Vec.h"

class OffVec {
public:
    Vec point;
    Vec direction;
    OffVec(const Vec &point, const Vec &direction);
    OffVec();

};


#endif //RAYTRACER_OFFVEC_H
