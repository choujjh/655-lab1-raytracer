//
// Created by chouj on 3/12/2021.
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H


#include "../../VecModel/vec.h"
#include "Light.h"

class ambientLight: public Light {
    Vec shadowRay(Vec point) override;
    Vec illumination(Vec point, Vec rayDir, Object* surface, bool occluded) override;

public:
    ambientLight(const Vec &color);

};


#endif //RAYTRACER_AMBIENTLIGHT_H
