//
// Created by chouj on 9/20/2021.
//

#include "CoordinateSpace.h"

CoordinateSpace::CoordinateSpace(const Vec3 &direction, const Vec3 &up, const Vec3 &right) : direction(direction),
                                                                                             up(up), right(right) {}

CoordinateSpace::CoordinateSpace() : direction(Vec3(0, 0, 1)), up(Vec3(0, 1, 0)), right(Vec3(1, 0, 0)) {}

bool CoordinateSpace::isNan(){
    if(direction.isNan() || up.isNan() || right.isNan()){
        return true;
    }
    return false;
}
