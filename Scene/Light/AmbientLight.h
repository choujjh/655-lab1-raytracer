//
// Created by chouj on 3/12/2021.
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H



#include "Light.h"

class AmbientLight: public Light {
    Vec3 shadowRay(Vec3 point) override;
    Vec3 illumination(Vec3 point, Vec3 rayDir, Object* surface, bool occluded) override;

public:
    AmbientLight(const Vec3 &color);

};


#endif //RAYTRACER_AMBIENTLIGHT_H
