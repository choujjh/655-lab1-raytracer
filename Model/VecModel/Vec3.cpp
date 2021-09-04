//
// Created by chouj on 3/5/2021.
//

#include "Vec3.h"

#import <cmath>

using std::pow;
using std::sqrt;

Vec3::Vec3() {
}

Vec3::Vec3(double first, double second, double third) {
    x = first;
    y = second;
    z = third;
    calcMagnitude();
}
Vec3::Vec3(const Vec3 &obj){
    x = obj.x;
    y = obj.y;
    z = obj.z;
    calcMagnitude();
}

Vec3 Vec3::normalize() {
    double length = getMagnitude();
    x /= length;
    y /= length;
    z /= length;
    calcMagnitude();
    return *this;
}
Vec3 Vec3::clip(double min, double max){
    x = x > max ? max : x < min ? min : x;
    y = y > max ? max : y < min ? min : y;
    z = z > max ? max : z < min ? min : z;
    return *this;
}

double Vec3::getMagnitude() const {
    return magnitude;
}
void Vec3::calcMagnitude() {
    magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vec3 Vec3::operator-(Vec3 b) {
    return Vec3(this->x - b.x, this->y - b.y, this->z - b.z);
}
Vec3 Vec3::operator+(Vec3 b) {
    return Vec3(this->x + b.x, this->y + b.y, this->z + b.z);
}
Vec3 Vec3::operator+=(Vec3 b){
    return *this + b;
}
Vec3 Vec3::operator*(double val) {
    return Vec3(this->x * val, this->y * val, this->z * val);
}
Vec3 Vec3::operator/(double val) {
    return Vec3(this->x / val, this->y / val, this->z / val);
}
Vec3 Vec3::operator*(Vec3 b) {
    return Vec3(this->x * b.x, this->y * b.y, this->z * b.z);
}
Vec3 Vec3::operator/(Vec3 b) {
    return Vec3(this->x / b.x, this->y / b.y, this->z / b.z);
}