//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "../../VecModel/Ray.h"
#include "../../Render/Materials/Material.h"

class Object {
public:
    Material objMat;

    Object(const Material &objMat);

    virtual Vec3 intersect(Ray ray) = 0;
    virtual Vec3 normal(Vec3 point) = 0;
};


#endif //RAYTRACER_OBJECT_H
