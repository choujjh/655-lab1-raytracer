//
// Created by chouj on 3/13/2021.
//

#ifndef RAYTRACER_RENDEROP_H
#define RAYTRACER_RENDEROP_H


#include "../Model/VecModel/Vec3.h"

class RenderOps {
public:
    static Vec3 reflectionRay(Vec3 normal, Vec3 initDir);

};


#endif //RAYTRACER_RENDEROP_H
