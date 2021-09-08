//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Object.h"


class Sphere: public Object {
private:
    Vec3 center;
    double radius;
public:
    Sphere(Material *objMat, const Vec3 &center, double radius);

    Vec3 intersect(Ray ray) override;

    Vec3 normal(Vec3 point) override;

    const Vec3 &getCenter() const;

    void setCenter(const Vec3 &center);

    double getRadius() const;

    void setRadius(double radius);
};


#endif //RAYTRACER_SPHERE_H
