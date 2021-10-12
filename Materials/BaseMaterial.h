//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../../Model/Vec/Vec3.h"
#include "MaterialComponent/MatComponent.h"

class BaseMaterial {
public:

    MatComponent<double>* kDiffuse;
    MatComponent<double>* kSpecular;
    MatComponent<double>* kAmbient;
    MatComponent<double>* kgls;
    MatComponent<double>* IOR;
    MatComponent<double>* opacity;

    MatComponent<Vec3>* colorDiffuse;
    MatComponent<Vec3>* colorSpec;
    MatComponent<Vec3>* colorEmission;

    BaseMaterial(MatComponent<double> *kDiffuse, MatComponent<double> *kSpecular, MatComponent<double> *kAmbient,
                 MatComponent<double> *kgls, MatComponent<double>* IOR, MatComponent<double>* opacity, MatComponent<Vec3> *colorDiffuse, MatComponent<Vec3> *colorSpec,
                 MatComponent<Vec3> *colorEmission);
};


#endif //RAYTRACER_MATERIAL_H
