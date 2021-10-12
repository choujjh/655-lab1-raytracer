//
// Created by chouj on 9/4/2021.
//

#include "BaseMaterial.h"

//BaseMaterial::BaseMaterial(MatComponent<double> *kDiffuse, MatComponent<double> *kSpecular, MatComponent<double> *kAmbient,
//                           MatComponent<double> *kgls, MatComponent<double>* IOR, MatComponent<double>* opacity,
//                           MatComponent<Vec3> *colorDiffuse, MatComponent<Vec3> *colorSpec, MatComponent<Vec3> *colorEmission):
//        kDiffuse(kDiffuse),
//        kSpecular(kSpecular),
//        kAmbient(kAmbient),
//        kgls(kgls),
//        IOR(IOR),
//        opacity(opacity),
//        colorDiffuse(colorDiffuse),
//        colorSpec(colorSpec),
//        colorEmission(colorEmission) {}

        //drt index
        //glossiness translucency
        //ior
        //color
        //gama
        //uv normal maps


BaseMaterial::BaseMaterial(MatComponent<Vec3> *diffReflTransm, MatComponent<Vec3> *glossTransl,
                           MatComponent<Vec3> *color, MatComponent<Vec3> *kglsIorGamma) : Diff_Refl_Transm(
        diffReflTransm), Rough_Gloss_Transl(glossTransl), color(color), KGLS_IOR_gamma(kglsIorGamma) {}
