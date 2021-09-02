//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Object.h"
#include "../../VecModel/Vec.h"


class Sphere: public Object {
private:
    Vec center;
    double radius;
public:
    Sphere(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec, double kgls,
           const Vec &center, double radius);

    Vec intersect(OffVec ray) override;

    Vec normal(Vec point) override;

    const Vec &getCenter() const;

    void setCenter(const Vec &center);

    double getRadius() const;

    void setRadius(double radius);
};


#endif //RAYTRACER_SPHERE_H
