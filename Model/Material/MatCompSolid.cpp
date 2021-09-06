//
// Created by chouj on 9/6/2021.
//

#include "MatCompSolid.h"

template<class T>
MatCompSolid<T>::MatCompSolid(T solid):solid(solid) {}

template<class T>
T MatCompSolid<T>::getColor(double u, double v) {
    return solid;
}

template<class T>
T MatCompSolid<T>::getColor() {
    return solid;
}


