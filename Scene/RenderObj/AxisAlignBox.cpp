//
// Created by chouj on 9/25/2021.
//

#include <cmath>
#include "../../Model/Ops/RenderOps.h"
#include "AxisAlignBox.h"

Vec3 AxisAlignBox::shadowRay(Vec3 point, Vec3 objectNormal) {
    return Vec3();
}

Vec3 AxisAlignBox::intersect(Ray ray) {
    double tNear = NEG_INFINITY;
    double tFar = VAL_INFINITY;
    double t1 = 0;
    double t2 = 0;
    //check x
    if(calcAxisT(ray.point.x, ray.direction.x, minVals.x, maxVals.x, t1, t2)) {
        if (t1 > t2) std::swap(t1, t2);
        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;
        if (tNear > tFar || tFar < 0) return infiniteVec3();
    }
    //check y
    if(calcAxisT(ray.point.y, ray.direction.y, minVals.y, maxVals.y, t1, t2)) {
        if (t1 > t2) std::swap(t1, t2);
        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;
        if (tNear > tFar || tFar < 0) return infiniteVec3();
    }
    //check z
    if(calcAxisT(ray.point.z, ray.direction.z, minVals.z, maxVals.z, t1, t2)) {
        if(t1 > t2) std::swap(t1, t2);
        if(t1 > tNear) tNear = t1;
        if(t2 < tFar) tFar = t2;
        if(tNear > tFar || tFar < 0) return infiniteVec3();
    }
    return ray.direction * tNear + ray.point;
    return infiniteVec3();
}
bool AxisAlignBox::calcAxisT(double point, double direction, double min, double max, double& t1, double& t2){
    if(direction == 0){
        if(point > max || point < min){
            return false;
        }
    }
    t1 = (min - point)/direction;
    t2 = (max - point)/direction;
    return true;
}

Vec3 AxisAlignBox::normal(Vec3 point) {
    //TODO:get normal calculations
    Vec3 normal = Vec3(minVals.x - maxVals.x, 0, 0);
    double min = fabs(point.x - minVals.x);
    if(fabs(point.x - maxVals.x) < min){
        min = fabs(point.x - maxVals.x);
        normal = Vec3(maxVals.x - minVals.x, 0, 0);
    }
    if(fabs(point.y - maxVals.y) < min){
        min = fabs(point.y - maxVals.y);
        normal = Vec3(0, maxVals.y - minVals.y, 0);
    }
    if(fabs(point.y - minVals.y) < min){
        min = fabs(point.y - minVals.y);
        normal = Vec3(0, minVals.y - maxVals.y, 0);
    }
    if(fabs(point.z - minVals.z) < min){
        min = fabs(point.z - minVals.z);
        normal = Vec3(0, 0, minVals.z - maxVals.z);
    }
    if(fabs(point.z - maxVals.z) < min) {
        normal = Vec3(0, 0, maxVals.z - minVals.z);
    }
    return normal.normalize();
}

AxisAlignBox::AxisAlignBox(BaseMaterial *objMat, const Vec3 &maxVals, const Vec3 &minVals) : Object(objMat),
                                                                                             maxVals(maxVals),
                                                                                             minVals(minVals) {}
