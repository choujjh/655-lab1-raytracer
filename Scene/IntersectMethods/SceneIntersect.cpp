//
// Created by chouj on 9/10/2021.
//

#include "SceneIntersect.h"

Vec3 SceneIntersect::getIntersect(Ray currRay, bool closest, Object *&object) const {
    Vec3 minInterVec = objList.at(0)->intersect(currRay);
    if(minInterVec.getMagnitude() < VAL_INFINITY){
        object = objList.at(0);
    }
    for(int i = 1; i < objList.size(); ++i){
        Vec3 interPoint = objList.at(i)->intersect(currRay);
        if (!closest && interPoint.getMagnitude() != VAL_INFINITY) {
            object = objList.at(i);
            return interPoint;
        }
        if ((interPoint - currRay.point).getMagnitude() < (minInterVec - currRay.point).getMagnitude()) {
            minInterVec = interPoint;
            object = objList.at(i);
        }
    }
    return minInterVec;
}
Vec3 SceneIntersect::getIntersect(Ray currRay, bool closest) const {
    Object* object;
    return getIntersect(currRay, closest, object);
}

void SceneIntersect::addObject(Object *object) {
    objList.push_back(object);
}

SceneIntersect::SceneIntersect() {}
