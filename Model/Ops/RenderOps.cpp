//
// Created by chouj on 3/13/2021.
//

#include "RenderOps.h"

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

double RenderOps::calcFresnelReflectAmount(double iorLeft, double iorEntered, Vec3 normal, Vec3 incident){
    // code from https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
    normal.normalize();
    incident.normalize();

    double r0 = (iorLeft - iorEntered) / (iorLeft + iorEntered);
    r0 *= r0;
    double cosX = normal.dot(incident) * -1;
    if(iorLeft > iorEntered){
        double nit = iorLeft/iorEntered;
        double sinT2 = nit*nit*(1.0-cosX*cosX);
        //total internal reflection
        if(sinT2 > 1.0)
            return 1.0;
        cosX = sqrt(1.0-sinT2);
    }
    double x = 1.0-cosX;
    double ret = r0 + (1.0 - r0) * x * x * x * x * x;
    //ret = (OBJECT_REFLECTIVITY + (1.0-OBJECT_REFLECTIVITY) * ret);
    return ret;
}

CoordinateSpace RenderOps::makeCoordinateSystem(Vec3 direction, Vec3 normal){
    Vec3 right = direction.cross(normal);
    Vec3 up = right.cross(direction);

    return CoordinateSpace(direction.normalize(), up.normalize(), right.normalize());
}
double RenderOps::randFloatValue(double min, double max){
    if(min > max) std::swap(max, min);
    double randValue = ((double)rand())/ ((double) RAND_MAX);
    return randValue * (max - min) + min;
}
double RenderOps::tentFloatRandGen(double min, double max){
    if(min > max) std::swap(max, min);
    double randVal = randFloatValue(0.0, 2.0);
    double direction = 0.0;
    if (randVal < 1.0){direction = sqrt(randVal) - 1.0;}
    else {direction = 1.0 - sqrt(2-randVal);}
    return (direction + 1) / 2 * (max - min) + min;
}