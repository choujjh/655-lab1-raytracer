//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H



#include "../RenderObj/Object.h"
#include "../../Model/Vec/Vec3.h"

class Light {
private:
    double max(double a, double b);
public:
    Vec3 color;

    Light(const Vec3 &color);

    virtual Vec3 shadowRay(Vec3 point) = 0;
    virtual Vec3 illumination(Vec3 point, Vec3 rayDir, Object* surface, bool occluded) = 0;

    Vec3 calcSpec(Object* surface, Vec3 interPoint, Vec3 rayDir);
    Vec3 calcDiffuse(Object* surface, Vec3 interPoint, Vec3 rayDir);
    Vec3 calcAmbient(Object* surface, Vec3 interPoint, Vec3 rayDir);

    bool checkNormal(Object *surface, Vec3 interPoint, Vec3 rayDir);
};


#endif //RAYTRACER_LIGHT_H
