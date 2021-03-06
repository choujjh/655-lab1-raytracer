//
// Created by chouj on 3/13/2021.
//

#include "RenderOps.h"

#include <cmath>

Vec3 reflectionDirection(Vec3 normal, Vec3 initDir) {
    return initDir - (normal * 2 * normal.dot(initDir));
}
double max(double a, double b) {
    return a > b ? a : b;
}

Ray calcTransmissionRay(Vec3 I, Object* intersectObject, Vec3 interVec, bool isInsideObject, Vec2 objectUV){
    I.normalize();
    Vec3 n = intersectObject->normal(interVec).normalize();
    double normalScalar = isInsideObject ? -1: 1;

    double nit = intersectObject->material->ior(objectUV);
    if(!isInsideObject) nit = 1 / intersectObject->material->ior(objectUV);

    double theta = acos((I*-1).dot(n * normalScalar));
    Vec3 T = I*nit;
    double a = nit*cos(theta);
    double b = sqrt(1 - nit*nit*(1-cos(theta) * cos(theta)));
    //double b = sqrt(1 + pow(nit, 2)* (pow(cos(theta), 2) - 1));
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
double calcFresnelReflectAmount(double iorLeft, double iorEntered, Vec3 normal, Vec3 incident){
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

CoordinateSpace makeCoordinateSystem(Vec3 direction, Vec3 normal){
    Vec3 right = direction.cross(normal);
    Vec3 up = right.cross(direction);

    return CoordinateSpace(direction.normalize(), up.normalize(), right.normalize());
}

double randFloatValue(double min, double max){

    if(min > max) std::swap(max, min);
    double randValue = ((double)rand())/ ((double) RAND_MAX);
    return randValue * (max - min) + min;
}
double tentFloatRandGen(double min, double max){
    if(min > max) std::swap(max, min);
    double randVal = randFloatValue(0.0, 2.0);
    double direction = 0.0;
    if (randVal < 1.0){direction = sqrt(randVal) - 1.0;}
    else {direction = 1.0 - sqrt(2-randVal);}
    return (direction + 1) / 2 * (max - min) + min;
}
Vec3 randomPointBetweenPoints(Vec3 a, Vec3 b, bool useTent){
    Vec3 ab = b - a;
    double t = useTent? tentFloatRandGen(): randFloatValue();
    return ab * t + a;

}
Vec3 randomPointOnSphere(CoordinateSpace cs, double radius, Vec3 center, double horMin, double horMax, double vertMin, double vertMax){
    double theta = randFloatValue(horMin, horMax);
    double phi = randFloatValue(vertMin, vertMax);
    Vec3 xy = cs.up * sin(theta) + cs.right * cos(theta);
    Vec3 newDir = (xy * cos(phi) + cs.direction * sin(phi));
    newDir = newDir * radius;
    return newDir + center;
}