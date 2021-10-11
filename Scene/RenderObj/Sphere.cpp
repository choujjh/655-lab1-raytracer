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
    double nx = RenderOps().randFloatValue();
    double ny = RenderOps().randFloatValue();
    if((point - center).getMagnitude() < radius){
        double nz = RenderOps().randFloatValue();
        CoordinateSpace cs = RenderOps().makeCoordinateSystem(objectNormal, Vec3(nx, ny, nz));
        return (cs.right * RenderOps().tentFloatRandGen(-1, 1) + cs.up * RenderOps().tentFloatRandGen(-1, 1) + cs.direction * RenderOps().randFloatValue(0, 1)).normalize();
    }

    Vec3 dir = (this->center - point).normalize();
    double nz = (dir.x * nx + dir.y * ny)/dir.z;
    CoordinateSpace cs = RenderOps().makeCoordinateSystem(dir, Vec3(nx, ny, nz));
    double randTheta = RenderOps().randFloatValue(0, 2 * M_PI);
    double randRadius = RenderOps().randFloatValue(0, radius);
    double y = sin(randTheta) * randRadius;
    double x = cos(randTheta) * randRadius;
    Vec3 randPoint = center + cs.up * y + cs.right * x;
    return (randPoint - point).normalize();
}

void Sphere::getUV(Vec3 point, double &u, double &v) {
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
}