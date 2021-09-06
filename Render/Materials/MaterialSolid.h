//
// Created by chouj on 9/6/2021.
//

#ifndef RAYTRACER_MATERIALSOLID_H
#define RAYTRACER_MATERIALSOLID_H


#include "Material.h"

class MaterialSolid: public Material {
public:
    Vec3 colorDiffuse;
    Vec3 colorSpec;
    Vec3 colorEmission;

    MaterialSolid(double kDiffuse, double kSpecular, double kAmbient, double kgls, const Vec3 &colorDiffuse,
                  const Vec3 &colorSpec, const Vec3 &colorEmission);

    Vec3 GetColorDiffuse() override;

    Vec3 GetColorSpec() override;

    Vec3 GetColorEmission() override;
};


#endif //RAYTRACER_MATERIALSOLID_H
