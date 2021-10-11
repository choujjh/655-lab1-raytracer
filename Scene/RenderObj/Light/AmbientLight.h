//
// Created by chouj on 3/12/2021.
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H



#include "Light.h"

class AmbientLight: public Light {
    Vec3 shadowRay(Vec3 point, Vec3 objectNormal) override;

public:
    AmbientLight(BaseMaterial* material);

    Vec3 intersect(Ray ray) override;

    Vec3 normal(Vec3 point) override;

    int ID() override;
};


#endif //RAYTRACER_AMBIENTLIGHT_H
