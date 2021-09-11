//
// Created by chouj on 3/10/2021.
//

#ifndef RAYTRACER_DIRECTIONLIGHT_H
#define RAYTRACER_DIRECTIONLIGHT_H

#include "Light.h"

class DirectionLight: public Light {
public:
    Vec3 dir;
    Vec3 shadowRay(Vec3 point) override;

    DirectionLight(const Vec3 &color, const Vec3 &dir);

    bool isAmbient() override;
};


#endif //RAYTRACER_DIRECTIONLIGHT_H
