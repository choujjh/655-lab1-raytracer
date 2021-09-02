//
// Created by chouj on 3/8/2021.
//

#include "OffVec.h"

OffVec::OffVec(const Vec &point, const Vec &direction) {
    this->point = point;
    this->direction = direction;
    this->direction.normalize();
}

OffVec::OffVec() {
    this->point = Vec();
    this->direction = Vec();
}

