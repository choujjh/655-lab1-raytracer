//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../../VecModel/Vec3.h"
#include "../../VecModel/Ray.h"

class Material {
public:

    double kDiffuse;
    double kSpecular;
    double kAmbient;
    double kgls;

    Vec3 colorDiffuse;
    Vec3 colorSpec;
    Vec3 colorEmission;

    Material(double kDiffuse, double kSpecular, double kAmbient, double kgls, const Vec3 &colorDiffuse,
             const Vec3 &colorSpec, const Vec3 &colorEmission);
};


#endif //RAYTRACER_MATERIAL_H
