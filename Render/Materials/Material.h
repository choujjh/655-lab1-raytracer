//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../../Model/Vec/Vec3.h"

class Material {
public:

    double kDiffuse;
    double kSpecular;
    double kAmbient;
    double kgls;

    Material(double kDiffuse, double kSpecular, double kAmbient, double kgls);

    virtual Vec3 GetColorDiffuse() = 0;
    virtual Vec3 GetColorSpec() = 0;
    virtual Vec3 GetColorEmission() = 0;
};


#endif //RAYTRACER_MATERIAL_H
