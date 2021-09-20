//
// Created by chouj on 3/13/2021.
//

#ifndef RAYTRACER_RENDEROP_H
#define RAYTRACER_RENDEROP_H


#include "../Vec/Vec3.h"
#include "../Vec/Ray.h"
#include "../../Scene/RenderObj/Object.h"
#include "../Vec/CoordinateSpace.h"

class RenderOps {
public:
    Vec3 reflectionDirection(Vec3 normal, Vec3 initDir);
    double max(double a, double b);
    Ray calcTransmissionRay(Vec3 I, Object* intersectObject, Vec3 interVec, bool isInsideObject);
    double calcFresnelReflectAmount(double iorLeft, double iorEntered, Vec3 normal, Vec3 incident);
    CoordinateSpace makeCoordinateSystem(Vec3 direction, Vec3 normal);
};


#endif //RAYTRACER_RENDEROP_H
