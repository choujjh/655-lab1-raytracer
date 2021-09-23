//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "../../Model/Vec/Vec3.h"
#include "../../Model/Vec/Ray.h"
#include "../Materials/Material.h"

class Object {
public:
    Material* material;

    Object(Material* objMat);

    virtual Vec3 intersect(Ray ray);
    Vec3 infiniteVec3();
    virtual Vec3 normal(Vec3 point) = 0;
    virtual bool isLight();
};


#endif //RAYTRACER_OBJECT_H
