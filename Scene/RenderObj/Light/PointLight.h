//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_POINTLIGHT_H
#define LAB_1_POINTLIGHT_H


#include "../Sphere.h"
#include "Light.h"

class PointLight: public Light {
private:
    Vec3 position;
    Sphere intersectionSphere;
public:
    PointLight(BaseMaterial* material, const Vec3 &position);

    Vec3 shadowRay(Vec3 point) override;

    Vec3 intersect(Ray ray) override;

    Vec3 normal(Vec3 point) override;


};


#endif //LAB_1_POINTLIGHT_H
