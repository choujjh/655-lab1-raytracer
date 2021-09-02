//
// Created by chouj on 3/15/2021.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include "Plane.h"

class Triangle: public Plane {
public:
    Vec a;
    Vec b;
    Vec c;

    Triangle(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec,
             double kgls, const Vec &a, const Vec &b, const Vec &c);

    Vec intersect(OffVec ray) override;

    Vec normal(Vec point) override;

};


#endif //RAYTRACER_TRIANGLE_H
