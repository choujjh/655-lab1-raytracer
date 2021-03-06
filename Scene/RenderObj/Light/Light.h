//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include<string>

#include "../RenderObj/Object.h"
#include "../../Model/Vec/Vec3.h"

using std::string;
class Light: public Object {
public:
    Light(BaseMaterial *objMat);

    //object functions
    virtual Vec3 intersect(Ray ray) = 0;
    virtual Vec3 normal(Vec3 point) = 0;

    virtual Vec3 shadowRay(Vec3 point, Vec3 objectNormal) = 0;
    Vec2 getUV(Vec3 point) override;

    bool isLight() override;


};


#endif //RAYTRACER_LIGHT_H
