//
// Created by chouj on 3/13/2021.
//

#ifndef RAYTRACER_RENDEROP_H
#define RAYTRACER_RENDEROP_H


#include <cmath>
#include "../Vec/Vec3.h"
#include "../Vec/Ray.h"
#include "../../Scene/RenderObj/Object.h"
#include "../Vec/CoordinateSpace.h"

Vec3 reflectionDirection(Vec3 normal, Vec3 initDir);
double max(double a, double b);
Ray calcTransmissionRay(Vec3 I, Object* intersectObject, Vec3 interVec, bool isInsideObject, Vec2 objectUV);
double calcFresnelReflectAmount(double iorLeft, double iorEntered, Vec3 normal, Vec3 incident);
CoordinateSpace makeCoordinateSystem(Vec3 direction, Vec3 normal);
double randFloatValue(double min = 0.0, double max = 1.0);
double tentFloatRandGen(double min = 0.0, double max = 1.0);
Vec3 randomPointBetweenPoints(Vec3 a, Vec3 b, bool useTent = false);
Vec3 randomPointOnSphere(CoordinateSpace cs, double radius, Vec3 center, double horMin = 0, double horMax = 2 * M_PI, double vertMin = -1 * M_PI / 2 , double vertMax = M_PI / 2);


#endif //RAYTRACER_RENDEROP_H
