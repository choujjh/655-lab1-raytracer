//
// Created by chouj on 3/13/2021.
//

#include "RenderOps.h"
#include "LinAlgOp.h"

#include <cmath>

Vec3 RenderOps::reflectionDirection(Vec3 normal, Vec3 initDir) {
    return initDir - (normal * 2 * normal.dot(initDir));
}
double RenderOps::max(double a, double b) {
    return a > b ? a : b;
}

Ray RenderOps::calcTransmissionRay(Vec3 I, Object* intersectObject, Vec3 interVec, bool isInsideObject){
    I.normalize();
    Vec3 n = intersectObject->normal(interVec).normalize();
    double normalScalar = isInsideObject ? -1: 1;

    double nit = intersectObject->material->IOR->getColor();;
    if(!isInsideObject) nit = 1 / intersectObject->material->IOR->getColor();

    double theta = acos((I*-1).dot(n * normalScalar));
    Vec3 T = I*nit;
    double a = nit*cos(theta);
    double b = sqrt(1 - nit*nit*(1-cos(theta) * cos(theta)));
//    double b = sqrt(1 + pow(nit, 2)* (pow(cos(theta), 2) - 1));
    T += n * (a - b);
    Vec3 epsilonPoint;
    if(isInsideObject){
        epsilonPoint = interVec + n * 0.001;
    }
    else {
        epsilonPoint = interVec - n * 0.001;
    }
    return Ray(epsilonPoint, T);
}