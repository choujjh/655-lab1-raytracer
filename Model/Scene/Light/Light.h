//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "../../VecModel/Vec.h"
#include "../RenderObj/Object.h"

class Light {
private:
    double max(double a, double b);
public:
    Vec color;

    Light(const Vec &color);

    virtual Vec shadowRay(Vec point) = 0;
    virtual Vec illumination(Vec point, Vec rayDir, Object* surface, bool occluded) = 0;

    Vec calcSpec(Object* surface, Vec interPoint, Vec rayDir);
    Vec calcDiffuse(Object* surface, Vec interPoint, Vec rayDir);
    Vec calcAmbient(Object* surface, Vec interPoint, Vec rayDir);

    bool checkNormal(Object *surface, Vec interPoint, Vec rayDir);
};


#endif //RAYTRACER_LIGHT_H
