//
// Created by chouj on 3/7/2021.
//


#include "../Model/MaterialComponent/MatCompSolid.h"
#include "Object.h"


Vec3 Object::intersect(Ray ray) {
    double inf = VAL_INFINITY;
    return Vec3(inf, inf, inf);
}

Object::Object(BaseMaterial* objMat) : material(objMat) {}

Vec3 Object::infiniteVec3() {
    return Object::intersect(Ray());
}
bool Object::isLight() {
    if(material->colorEmission->getColor(0, 0).getMagnitude() > 0){
        return true;
    }
    return false;
}

int Object::ID() {
    return ID_Object;
}
