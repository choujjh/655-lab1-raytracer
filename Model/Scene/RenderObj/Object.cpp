//
// Created by chouj on 3/7/2021.
//


#include "Object.h"

#include <limits>
double Object::getKDiffuse() const {
    return kDiffuse;
}
void Object::setKDiffuse(double kDiffuse) {
    Object::kDiffuse = kDiffuse;
}
double Object::getKSpecular() const {
    return kSpecular;
}
void Object::setKSpecular(double kSpecular) {
    Object::kSpecular = kSpecular;
}
double Object::getKAmbient() const {
    return kAmbient;
}
void Object::setKAmbient(double kAmbient) {
    this->kAmbient = kAmbient;
}
const Vec3 &Object::getColorDiffuse() const {
    return colorDiffuse;
}
void Object::setColorDiffuse(const Vec3 &colorDiffuse) {
    Object::colorDiffuse = colorDiffuse;
}
const Vec3 &Object::getColorSpec() const {
    return colorSpec;
}
void Object::setColorSpec(const Vec3 &colorSpec) {
    Object::colorSpec = colorSpec;
}
double Object::getKgls() const {
    return kgls;
}
void Object::setKgls(double kgls) {
    kgls = kgls;
}

Object::Object(double kDiffuse, double kSpecular, double ka, const Vec3 &colorDiffuse, const Vec3 &colorSpec, double kgls) {
    this->kDiffuse = kDiffuse;
    this->kSpecular = kSpecular;
    this->kAmbient = ka;
    this->colorDiffuse = colorDiffuse;
    this->colorSpec = colorSpec;
    this->kgls = kgls;
}

Object::Object() {}

Vec3 Object::intersect(Ray ray) {
    double inf = std::numeric_limits<double>::infinity();
    return Vec3(inf, inf, inf);
}
