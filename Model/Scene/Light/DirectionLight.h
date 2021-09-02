//
// Created by chouj on 3/10/2021.
//

#ifndef RAYTRACER_DIRECTIONLIGHT_H
#define RAYTRACER_DIRECTIONLIGHT_H

#include "../../VecModel/OffVec.h"
#include "Light.h"

class directionLight: public Light {
public:
    Vec dir;
    Vec shadowRay(Vec point) override;

    directionLight(const Vec &color, const Vec &dir);

    Vec illumination(Vec point, Vec rayDir, Object *surface, bool occluded) override;
};


#endif //RAYTRACER_DIRECTIONLIGHT_H
