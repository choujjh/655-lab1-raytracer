//
// Created by chouj on 9/23/2021.
//

#include "BruteForce.h"

Vec3 BruteForce::getIntersect(Ray currRay, bool closest, Object *&object) {
    Vec3 minInterVec = masterObjList.at(0)->intersect(currRay);
    if(minInterVec.getMagnitude() < VAL_INFINITY && minInterVec.getMagnitude() > NEG_INFINITY){
        object = masterObjList.at(0);
    }
    for(int i = 1; i < masterObjList.size(); ++i){
        Vec3 interPoint = masterObjList.at(i)->intersect(currRay);
        if (!closest && interPoint.getMagnitude() != VAL_INFINITY && interPoint.getMagnitude() != NEG_INFINITY) {
            object = masterObjList.at(i);
            return interPoint;
        }
        if ((interPoint - currRay.point).getMagnitude() < (minInterVec - currRay.point).getMagnitude()) {
            minInterVec = interPoint;
            object = masterObjList.at(i);
        }
    }
    return minInterVec;
}

BruteForce::BruteForce() {}


void BruteForce::optimize() {
}
