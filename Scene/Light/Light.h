//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include<string>

#include "../RenderObj/Object.h"
#include "../../Model/Vec/Vec3.h"

using std::string;
class Light {
public:
    Vec3 color;

    Light(const Vec3 &color);

    virtual Vec3 shadowRay(Vec3 point) = 0;
    virtual bool isAmbient() = 0;


};


#endif //RAYTRACER_LIGHT_H
