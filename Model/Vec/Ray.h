//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_OFFVEC_H
#define RAYTRACER_OFFVEC_H

#include "Vec3.h"

class Ray {
public:
    Vec3 point;
    Vec3 direction;
    Ray(const Vec3 &point, const Vec3 &direction);
    Ray();

    bool isNan();
};


#endif //RAYTRACER_OFFVEC_H
