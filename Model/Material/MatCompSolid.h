//
// Created by chouj on 9/6/2021.
//

#ifndef RAYTRACER_MATCOMPSOLID_H
#define RAYTRACER_MATCOMPSOLID_H


#include "MatComponent.h"

template <class T>
class MatCompSolid: public MatComponent<T>{
public:
    T getColor(double u, double v) override;

    T getColor() override;

    MatCompSolid(T solid);
private:
    T solid;
};


#endif //RAYTRACER_MATCOMPSOLID_H
