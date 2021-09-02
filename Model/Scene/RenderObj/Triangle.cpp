//
// Created by chouj on 3/15/2021.
//

#include "Triangle.h"
#include "../../../Ops/LinAlgOp.h"
#include <limits>

Vec Triangle::intersect(OffVec ray) {
    Vec planeIntersectPoint = Plane::intersect(ray);
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
Vec Triangle::normal(Vec point) {
    return n;
}
Triangle::Triangle(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec,
                   double kgls, const Vec &a, const Vec &b, const Vec &c):
        Plane(kDiffuse, kSpecular, ka, colorDiffuse, colorSpec, kgls, Vec(), 0), a(a), b(b), c(c) {
    Vec testA = this->b - this->a;
    Vec testB = this->c - this->a;
    n = LinAlgOp().cross((this->b - this->a).normalize(), (this->c - this->a).normalize()).normalize();
    d = LinAlgOp().dot(n, a);
}
