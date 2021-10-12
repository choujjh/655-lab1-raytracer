//
// Created by chouj on 9/6/2021.
//

#ifndef RAYTRACER_MATCOMPONENT_H
#define RAYTRACER_MATCOMPONENT_H

#include "../Vec/Vec2.h"

template <class T>
class MatComponent {
public:
    virtual T getColor(double u, double v) = 0;
    virtual T getColor(Vec2 uv) = 0;
    virtual T getColor() = 0;
};


#endif //RAYTRACER_MATCOMPONENT_H
