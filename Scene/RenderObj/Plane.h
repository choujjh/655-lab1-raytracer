//
// Created by chouj on 3/13/2021.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "Object.h"

class Plane: public Object {
protected:
    Vec3 n;
    double d;
public:
    Plane(BaseMaterial *objMat, const Vec3 &n, double d);

    Vec3 intersect(Ray ray) override;
    Vec3 normal(Vec3 point) override;

    Vec3 shadowRay(Vec3 point) override;
};


#endif //RAYTRACER_PLANE_H
