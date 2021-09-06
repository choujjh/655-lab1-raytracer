//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "../../Render/Materials/Material.h"
#include "../../Model/Vec/Vec3.h"
#include "../../Model/Vec/Ray.h"

class Object {
public:
    Material* objMat;

    Object(Material* objMat);

    virtual Vec3 intersect(Ray ray) = 0;
    virtual Vec3 normal(Vec3 point) = 0;
};


#endif //RAYTRACER_OBJECT_H
