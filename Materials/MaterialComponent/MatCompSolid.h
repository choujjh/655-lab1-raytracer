//
// Created by chouj on 9/6/2021.
//

#ifndef RAYTRACER_MATCOMPSOLID_H
#define RAYTRACER_MATCOMPSOLID_H


#include "MatComponent.h"

template <typename T>
class MatCompSolid: public MatComponent<T>{
public:
    T getColor(double u, double v) override {
        return val;
    }
    T getColor() override {
        return val;
    }

    T getColor(Vec2 uv) override {
        return val;
    }

    MatCompSolid(T val): val(val){}
protected:
    T val;
};


#endif //RAYTRACER_MATCOMPSOLID_H
