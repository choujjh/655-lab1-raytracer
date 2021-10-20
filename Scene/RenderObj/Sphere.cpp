//
// Created by chouj on 3/7/2021.
//

#include "Sphere.h"

#include <math.h>
#include "../../Model/Ops/RenderOps.h"

const Vec3 &Sphere::getCenter() const {
    return center;
}

void Sphere::setCenter(const Vec3 &center) {
    Sphere::center = center;
}

double Sphere::getRadius() const {
    return radius;
}

void Sphere::setRadius(double radius) {
    Sphere::radius = radius;
}

Sphere::Sphere(BaseMaterial *objMat, const Vec3 &center, double radius) : Object(objMat), center(center),
                                                                          radius(radius) {
    maxVals = Vec3(center.x + radius, center.y + radius, center.z + radius);
    minVals = Vec3(center.x - radius, center.y - radius, center.z - radius);
}

Vec3 Sphere::intersect(Ray ray) {
    ray.direction.normalize();

    //inside sphere
    bool isInsideSphere = false;
    if((ray.point - center).getMagnitude() < radius){
        isInsideSphere = true;
    }

    //check to see if direction points the same way as towards the center of the sphere
    Vec3 oc = center - ray.point;
    double tca = ray.direction.dot(oc);
    if(tca < 0.0 && !isInsideSphere){
        return infiniteVec3();
    }

    //calc Thc^2
    double thcSqr = radius * radius - oc.getMagnitude() * oc.getMagnitude() + tca * tca;
    if(thcSqr < 0.0){
        return infiniteVec3();
    }
    else if(isInsideSphere) {
        return ray.point + ray.direction * (tca + sqrt(thcSqr));
    }
    return ray.point + ray.direction * (tca - sqrt(thcSqr));
}

Vec3 Sphere::normal(Vec3 point) {
    Vec3 normal = (point - center).normalize();
    return normal;
}

Vec3 Sphere::shadowRay(Vec3 point, Vec3 objectNormal) {
    double nx = randFloatValue();
    double ny = randFloatValue();
    double nz = randFloatValue();
    if((point - center).getMagnitude() < radius){
        CoordinateSpace cs = makeCoordinateSystem(objectNormal, Vec3(nx, ny, nz));
        return randomPointOnSphere(cs, 1, point,0, 2 * M_PI, 0, M_PI / 2) - point;
    }

    Vec3 dirFromLight = (this->center - point).normalize();
    CoordinateSpace cs = makeCoordinateSystem(dirFromLight, Vec3(nx, ny, nz));
    Vec3 randPoint = randomPointOnSphere(cs, radius, center,0, 2 * M_PI, 0, M_PI / 2);
    return (randPoint - point).normalize();
}

Vec2 Sphere::getUV(Vec3 point) {
    double u = 0, v = 0;
    Vec3 localVec = point - center;
    if(localVec.x == 0 && localVec.z == 0){
        u = 0.0;
    }
    else{
        double newZ = -1 * localVec.z;
        if(localVec.x >= 0.0) {
            u = (2 * M_PI + atan(newZ / localVec.x)) / (2 * M_PI);
            u = fmod(u, 1.0);
        }
        else{
            u = (M_PI + atan(newZ / localVec.x)) / (2 * M_PI);
        }

    }
    v =  (asin(localVec.y/radius) + (M_PI/2)) / M_PI;
    return Vec2(u, v);
}