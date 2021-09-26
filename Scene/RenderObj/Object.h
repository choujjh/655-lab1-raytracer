//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H

#include <string>

#include "../../Model/Vec/Vec3.h"
#include "../../Model/Vec/Ray.h"
#include "../Materials/BaseMaterial.h"


class Object {
public:
    BaseMaterial* material;

    Object(BaseMaterial* objMat);

    virtual Vec3 shadowRay(Vec3 point, Vec3 objectNormal) = 0;
    virtual Vec3 intersect(Ray ray);
    Vec3 infiniteVec3();
    virtual Vec3 normal(Vec3 point) = 0;
    virtual bool isLight();
    virtual std::string ToString();
};


#endif //RAYTRACER_OBJECT_H
