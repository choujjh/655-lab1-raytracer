//
// Created by chouj on 9/4/2021.
//

#include "Material.h"

Material::Material(double kDiffuse, double kSpecular, double kAmbient, double kgls, const Vec3 &colorDiffuse,
                   const Vec3 &colorSpec, const Vec3 &colorEmission) : kDiffuse(kDiffuse), kSpecular(kSpecular),
                                                                       kAmbient(kAmbient), kgls(kgls),
                                                                       colorDiffuse(colorDiffuse), colorSpec(colorSpec),
                                                                       colorEmission(colorEmission) {}
