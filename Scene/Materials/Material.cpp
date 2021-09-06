//
// Created by chouj on 9/4/2021.
//

#include "Material.h"

Material::Material(MatComponent<double> *kDiffuse, MatComponent<double> *kSpecular, MatComponent<double> *kAmbient,
                   MatComponent<double> *kgls, MatComponent<Vec3> *colorDiffuse, MatComponent<Vec3> *colorSpec,
                   MatComponent<Vec3> *colorEmission) : kDiffuse(kDiffuse), kSpecular(kSpecular), kAmbient(kAmbient),
                                                        kgls(kgls), colorDiffuse(colorDiffuse), colorSpec(colorSpec),
                                                        colorEmission(colorEmission) {}
