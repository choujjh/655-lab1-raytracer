//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../../Model/Vec/Vec3.h"
#include "MaterialComponent/MatComponent.h"

class BaseMaterial {
public:
    MatComponent<Vec3>* Diff_Refl_Transm;
    MatComponent<Vec3>* Rough_Gloss_Transl;
    MatComponent<Vec3>* color;
    MatComponent<Vec3>* KGLS_IOR_gamma;
//    MatComponent<double>* kDiffuse;
//    MatComponent<double>* kSpecular;
//    MatComponent<double>* kAmbient;
//    MatComponent<double>* kgls;
//    MatComponent<double>* IOR;
//    MatComponent<double>* opacity;
//
//    MatComponent<Vec3>* colorDiffuse;
//    MatComponent<Vec3>* colorSpec;
//    MatComponent<Vec3>* colorEmission;

//    BaseMaterial(MatComponent<double> *kDiffuse, MatComponent<double> *kSpecular, MatComponent<double> *kAmbient,
//                 MatComponent<double> *kgls, MatComponent<double>* IOR, MatComponent<double>* opacity, MatComponent<Vec3> *colorDiffuse, MatComponent<Vec3> *colorSpec,
//                 MatComponent<Vec3> *colorEmission);
    BaseMaterial(MatComponent<Vec3> *diffReflTransm, MatComponent<Vec3> *glossTransl, MatComponent<Vec3> *color,
                 MatComponent<Vec3> *kglsIorGamma);
};


#endif //RAYTRACER_MATERIAL_H
