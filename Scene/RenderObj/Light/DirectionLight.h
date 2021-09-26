//
// Created by chouj on 3/10/2021.
//

#ifndef RAYTRACER_DIRECTIONLIGHT_H
#define RAYTRACER_DIRECTIONLIGHT_H

#include "Light.h"

class DirectionLight: public Light {
public:
    Vec3 dir;
    Vec3 shadowRay(Vec3 point, Vec3 objectNormal) override;

    DirectionLight(BaseMaterial* material, const Vec3 &dir);


    Vec3 intersect(Ray ray) override;

    Vec3 normal(Vec3 point) override;
};


#endif //RAYTRACER_DIRECTIONLIGHT_H
