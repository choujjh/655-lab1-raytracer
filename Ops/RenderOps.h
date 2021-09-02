//
// Created by chouj on 3/13/2021.
//

#ifndef RAYTRACER_RENDEROP_H
#define RAYTRACER_RENDEROP_H


#include "../Model/VecModel/Vec.h"

class RenderOps {
public:
    static Vec reflectionRay(Vec normal, Vec initDir);

};


#endif //RAYTRACER_RENDEROP_H
