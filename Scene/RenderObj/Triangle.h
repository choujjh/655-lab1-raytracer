//
// Created by chouj on 3/15/2021.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include "Plane.h"

class Triangle: public Plane {
public:
    Vec3 a;
    Vec3 b;
    Vec3 c;

    Triangle(BaseMaterial *objMat, const Vec3 &a, const Vec3 &b, const Vec3 &c);

    Vec3 intersect(Ray ray) override;

    Vec3 normal(Vec3 point) override;

    Vec3 shadowRay(Vec3 point) override;
};


#endif //RAYTRACER_TRIANGLE_H
