//
// Created by chouj on 3/15/2021.
//

#include "Triangle.h"
#include "../../Model/Ops/LinAlgOp.h"
#include <limits>

Triangle::Triangle(const Material &objMat, const Vec3 &a, const Vec3 &b, const Vec3 &c)
        : Plane(objMat, Vec3(), 0), a(a), b(b), c(c) {
    n = LinAlgOp().cross((this->b - this->a).normalize(), (this->c - this->a).normalize()).normalize();
    d = n.dot(a);
}

Vec3 Triangle::intersect(Ray ray) {
    Vec3 planeIntersectPoint = Plane::intersect(ray);
    if(planeIntersectPoint.getMagnitude() == std::numeric_limits<double>::infinity()){
        return planeIntersectPoint;
    }
    double aSide = LinAlgOp().dot(LinAlgOp().cross(b - a, planeIntersectPoint - a).normalize(), n);
    if(aSide < 0){
        return Object::intersect(ray);
    }
    double bSide = LinAlgOp().dot(LinAlgOp().cross(c - b, planeIntersectPoint - b).normalize(), n);
    if(bSide < 0){
        return Object::intersect(ray);
    }
    double cSide = LinAlgOp().dot(LinAlgOp().cross(a - c, planeIntersectPoint - c).normalize(), n);
    if(cSide < 0){
        return Object::intersect(ray);
    }
    return planeIntersectPoint;
}

Vec3 Triangle::normal(Vec3 point) {
    return n;
}

