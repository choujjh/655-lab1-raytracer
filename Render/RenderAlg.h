//
// Created by chouj on 9/4/2021.
//

#ifndef RAYTRACER_RENDERALG_H
#define RAYTRACER_RENDERALG_H


#include "../Model/Vec/Vec3.h"
#include "../Model/Vec/Ray.h"

class RenderAlg {
    virtual Vec3 radiance(Ray ray, int depth) = 0;

};


#endif //RAYTRACER_RENDERALG_H
