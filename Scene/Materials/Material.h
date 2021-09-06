//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../../Model/Vec/Vec3.h"
#include "../../Model/Material/MatComponent.h"

class Material {
public:

    MatComponent<double>* kDiffuse;
    MatComponent<double>* kSpecular;
    MatComponent<double>* kAmbient;
    MatComponent<double>* kgls;

    MatComponent<Vec3>* colorDiffuse;
    MatComponent<Vec3>* colorSpec;
    MatComponent<Vec3>* colorEmission;

    Material(MatComponent<double> *kDiffuse, MatComponent<double> *kSpecular, MatComponent<double> *kAmbient,
             MatComponent<double> *kgls, MatComponent<Vec3> *colorDiffuse, MatComponent<Vec3> *colorSpec,
             MatComponent<Vec3> *colorEmission);
};


#endif //RAYTRACER_MATERIAL_H
