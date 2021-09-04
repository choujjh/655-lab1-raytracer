//
// Created by chouj on 3/15/2021.
//

#include "Triangle.h"
#include "../../../Ops/LinAlgOp.h"
#include <limits>

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
Triangle::Triangle(double kDiffuse, double kSpecular, double ka, const Vec3 &colorDiffuse, const Vec3 &colorSpec,
                   double kgls, const Vec3 &a, const Vec3 &b, const Vec3 &c):
        Plane(kDiffuse, kSpecular, ka, colorDiffuse, colorSpec, kgls, Vec3(), 0), a(a), b(b), c(c) {
    Vec3 testA = this->b - this->a;
    Vec3 testB = this->c - this->a;
    n = LinAlgOp().cross((this->b - this->a).normalize(), (this->c - this->a).normalize()).normalize();
    d = LinAlgOp().dot(n, a);
}
