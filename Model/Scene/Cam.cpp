//
// Created by chouj on 3/8/2021.
//

#include "cam.h"
#include "../../Ops/LinAlgOp.h"
#include <cmath>

const double pi = acos(-1);
Cam::Cam(const Vec &lookFrom, const Vec &lookAt, const Vec &up, double fov, double width, double height) : lookFrom(lookFrom),
                                                                                                           lookAt(lookAt),
                                                                                                           up(up), fov(fov),
                                                                                                           width(width),
                                                                                                           height(height) {
    Vec zPrime = this->lookAt - this->lookFrom;
    Vec xPrime = LinAlgOp().cross(zPrime, up);
    Vec yPrime = LinAlgOp().cross(xPrime, zPrime);

    double zMag = zPrime.getMagnitude();
    double xMag = zMag * tan(fov * (pi/180.0));
    double yMag = xMag * height / width;

    xPrime.normalize();
    yPrime.normalize();
    zPrime.normalize();

    this->incrementX = xPrime * (2 * xMag) / width;
    this->incrementY = yPrime * (2 * yMag) / height;
    this->start = this->lookAt - incrementX * (width/2.0 - 0.5) + incrementY * (height/2.0 - 0.5);
}

const Vec &Cam::getStart() const {
    return start;
}

void Cam::setStart(const Vec &start) {
    Cam::start = start;
}

const Vec &Cam::getIncrementX() const {
    return incrementX;
}

void Cam::setIncrementX(const Vec &incrementX) {
    Cam::incrementX = incrementX;
}

const Vec &Cam::getIncrementY() const {
    return incrementY;
}

void Cam::setIncrementY(const Vec &incrementY) {
    Cam::incrementY = incrementY;
}

const Vec &Cam::getLookFrom() const {
    return lookFrom;
}

void Cam::setLookFrom(const Vec &lookFrom) {
    Cam::lookFrom = lookFrom;
}

const Vec &Cam::getLookAt() const {
    return lookAt;
}

void Cam::setLookAt(const Vec &lookAt) {
    Cam::lookAt = lookAt;
}

const Vec &Cam::getUp() const {
    return up;
}

void Cam::setUp(const Vec &up) {
    Cam::up = up;
}

double Cam::getFov() const {
    return fov;
}

void Cam::setFov(double fov) {
    Cam::fov = fov;
}

double Cam::getWidth() const {
    return width;
}

void Cam::setWidth(double width) {
    Cam::width = width;
}

double Cam::getHeight() const {
    return height;
}

void Cam::setHeight(double height) {
    Cam::height = height;
}
