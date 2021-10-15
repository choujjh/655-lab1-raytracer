//
// Created by chouj on 9/4/2021.
//

#include "BaseMaterial.h"



BaseMaterial::BaseMaterial(MatComponent<Vec3> *diffReflTransm, MatComponent<Vec3> *glossTransl,
                           MatComponent<Vec3> *color, MatComponent<Vec3> *kglsIorGamma) : Diff_Refl_Transm(
        diffReflTransm), Rough_Gloss_Transl(glossTransl), color(color), KGLS_IOR_gamma(kglsIorGamma) {}
