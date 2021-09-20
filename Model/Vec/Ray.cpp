//
// Created by chouj on 3/8/2021.
//

#include "Ray.h"

Ray::Ray(const Vec3 &point, const Vec3 &direction) {
    this->point = point;
    this->direction = direction;
    this->direction.normalize();
}

Ray::Ray() {
    this->point = Vec3();
    this->direction = Vec3();
}

bool Ray::isNan(){
    if(point.isNan() || direction.isNan()){
        return true;
    }
    return false;
}

