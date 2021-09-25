//
// Created by chouj on 3/7/2021.
//

#include "Sphere.h"

#include <cmath>

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
                                                                          radius(radius) {}

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

Vec3 Sphere::shadowRay(Vec3 point) {
    return (this->center - point).normalize();
}
