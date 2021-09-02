//
// Created by chouj on 3/13/2021.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "../../VecModel/Vec.h"
#include "Object.h"

class Plane: public Object {
protected:
    Vec n;
    double d;
public:
    Plane(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec, double kgls,
          const Vec &n, double d);

    Vec intersect(OffVec ray) override;
    Vec normal(Vec point) override;

};


#endif //RAYTRACER_PLANE_H
