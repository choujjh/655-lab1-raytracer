//
// Created by chouj on 3/15/2021.
//

#include "Triangle.h"
#include "../../Model/Ops/LinAlgOp.h"
#include <limits>
#include "../../Model/Ops/RenderOps.h"

Triangle::Triangle(BaseMaterial *objMat, const Vec3 &a, const Vec3 &b, const Vec3 &c)
        : Plane(objMat, Vec3(), 0), a(a), b(b), c(c) {
    n = LinAlgOp().cross((this->b - this->a).normalize(), (this->c - this->a).normalize()).normalize();
    d = n.dot(a);

    double maxX = findMaxVal(a.x, b.x, c.x);
    double maxY = findMaxVal(a.y, b.y, c.y);
    double maxZ = findMaxVal(a.z, b.z, c.z);

    double minX = findMinVal(a.x, b.x, c.x);
    double minY = findMinVal(a.y, b.y, c.y);
    double minZ = findMinVal(a.z, b.z, c.z);
    maxVals = Vec3(maxX, maxY, maxZ);
    minVals = Vec3(minX, minY, minZ);

}
double Triangle::findMaxVal(double a, double b, double c) {
    double currMax = a;
    if(currMax < b) currMax = b;
    if(currMax < c) currMax = c;
    return currMax;
}
double Triangle::findMinVal(double a, double b, double c) {
    double currMin = a;
    if(currMin > b) currMin = b;
    if(currMin > c) currMin = c;
    return currMin;
}

Vec3 Triangle::intersect(Ray ray) {
    Vec3 planeIntersectPoint = Plane::intersect(ray);
    if(planeIntersectPoint.getMagnitude() == VAL_INFINITY || planeIntersectPoint.getMagnitude() == NEG_INFINITY){
        return planeIntersectPoint;
    }
    double aSide = LinAlgOp().dot(LinAlgOp().cross(b - a, planeIntersectPoint - a).normalize(), n);
    double bSide = LinAlgOp().dot(LinAlgOp().cross(c - b, planeIntersectPoint - b).normalize(), n);
    double cSide = LinAlgOp().dot(LinAlgOp().cross(a - c, planeIntersectPoint - c).normalize(), n);
    if((aSide < 0 && bSide < 0 && cSide < 0) || (aSide > 0 && bSide > 0 && cSide > 0)) {
        return planeIntersectPoint;
    }
    return infiniteVec3();
}

Vec3 Triangle::normal(Vec3 point) {
    return n;
}

Vec3 Triangle::shadowRay(Vec3 point, Vec3 objectNormal) {
    Vec3 aPrime = RenderOps().randomPointBetweenPoints(a, b);
    Vec3 bPrime = RenderOps().randomPointBetweenPoints(a, c);
    return (RenderOps().randomPointBetweenPoints(aPrime, bPrime) - point).normalize();
}
void Triangle::getUV(Vec3 point, double& u, double& v) {
    //TODO: implement triangle
    u = 0.0;
    v = 0.0;
}

