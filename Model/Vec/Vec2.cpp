//
// Created by chouj on 10/11/2021.
//

#include "Vec2.h"
#include <cmath>

Vec2::Vec2(): u(0), v(0), magnitude(0) {}

Vec2::Vec2(double u, double v): u(u), v(v) {
    calcMagnitude();
}
Vec2::Vec2(const Vec2 &obj){
    u = obj.u;
    v = obj.v;
    calcMagnitude();
}

bool Vec2::isNan(){
    if(std::isnan(u)|| std::isnan(v)){
        return true;
    }
    return false;
}
Vec2 Vec2::normalize() {
    double length = getMagnitude();
    u /= length;
    v /= length;
    calcMagnitude();
    return *this;
}
Vec2 Vec2::clip(double min, double max){
    u = u > max ? max : u < min ? min : u;
    v = v > max ? max : v < min ? min : v;
    calcMagnitude();
    return *this;
}

double Vec2::getMagnitude() const {
    return magnitude;
}
void Vec2::calcMagnitude() {
    magnitude = sqrt(pow(u, 2) + pow(v, 2));
}

double Vec2::dot(Vec2 b){
    return this->u * b.u + this->v * b.v;
}

Vec2 Vec2::operator-(Vec2 b) {
    return Vec2(this->u - b.u, this->v - b.v);
}
Vec2 Vec2::operator+(Vec2 b) {
    return Vec2(this->u + b.u, this->v + b.v);
}
void Vec2::operator+=(Vec2 b){
    u += b.u;
    v += b.v;
    calcMagnitude();
}
void Vec2::operator-=(Vec2 b){
    u -= b.u;
    v -= b.v;
    calcMagnitude();
}
Vec2 Vec2::operator*(double val) {
    return Vec2(this->u * val, this->v * val);
}
Vec2 Vec2::operator/(double val) {
    return Vec2(this->u / val, this->v / val);
}
Vec2 Vec2::operator*(Vec2 b) {
    return Vec2(this->u * b.u, this->v * b.v);
}
Vec2 Vec2::operator/(Vec2 b) {
    return Vec2(this->u / b.u, this->v / b.v);
}