//
// Created by chouj on 9/6/2021.
//

#include "MaterialSolid.h"

MaterialSolid::MaterialSolid(double kDiffuse, double kSpecular, double kAmbient, double kgls, const Vec3 &colorDiffuse,
                             const Vec3 &colorSpec, const Vec3 &colorEmission) : Material(kDiffuse, kSpecular, kAmbient,
                                                                                          kgls),
                                                                                 colorDiffuse(colorDiffuse),
                                                                                 colorSpec(colorSpec),
                                                                                 colorEmission(colorEmission) {}

Vec3 MaterialSolid::GetColorDiffuse() {
    return colorDiffuse;
}

Vec3 MaterialSolid::GetColorSpec() {
    return colorSpec;
}

Vec3 MaterialSolid::GetColorEmission() {
    return colorEmission;
}
