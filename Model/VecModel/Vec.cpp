//
// Created by chouj on 3/5/2021.
//

#include "Vec.h"

#import <cmath>

using std::pow;
using std::sqrt;

Vec::Vec() {
}

Vec::Vec(double first, double second, double third) {
    values.at(0) = first;
    values.at(1) = second;
    values.at(2) = third;
    calcMagnitude();
}
Vec::Vec(const Vec &obj){
    values.at(0) = obj.values.at(0);
    values.at(1) = obj.values.at(1);
    values.at(2) = obj.values.at(2);
    magnitude = obj.getMagnitude();;
}

Vec Vec::normalize() {
    double length = getMagnitude();
    for(int i = 0; i < values.size(); ++i){
        values.at(i) = values.at(i)/length;
    }
    calcMagnitude();
    return *this;
}

double Vec::getMagnitude() const {
    return magnitude;
}
void Vec::calcMagnitude() {
    double length = 0.0;
    for(double x: values){
        length += pow(x, 2);
    }
    magnitude = sqrt(length);
}

Vec Vec::operator-(Vec b) {
    Vec retVec;
    if(this->values.size() != b.values.size()){
        throw "size mismatch";
    }
    retVec.values.at(0) = this->values.at(0) - b.values.at(0);
    retVec.values.at(1) = this->values.at(1) - b.values.at(1);
    retVec.values.at(2) = this->values.at(2) - b.values.at(2);
    for(int i = 3; i < values.size(); ++i){
        retVec.values.at(i) = this->values.at(i) - b.values.at(i);
    }
    retVec.calcMagnitude();
    return retVec;
}
Vec Vec::operator+(Vec b) {
    Vec retVec;
    if(this->values.size() != b.values.size()){
        throw "size mismatch";
    }
    retVec.values.at(0) = this->values.at(0) + b.values.at(0);
    retVec.values.at(1) = this->values.at(1) + b.values.at(1);
    retVec.values.at(2) = this->values.at(2) + b.values.at(2);
    for(int i = 3; i < values.size(); ++i){
        retVec.values.at(i) = this->values.at(i) + b.values.at(i);
    }
    retVec.calcMagnitude();
    return retVec;
}
Vec Vec::operator*(double val) {
    Vec retVec;
    for(int i = 0; i < values.size(); ++i){
        retVec.values.at(i) = this->values.at(i) * val;
    }
    retVec.calcMagnitude();
    return retVec;
}
Vec Vec::operator/(double val) {
    Vec retVec;

    for(int i = 0; i < values.size(); ++i){
        retVec.values.at(i) = this->values.at(i) / val;
    }
    retVec.calcMagnitude();
    return retVec;
}
Vec Vec::operator*(Vec b) {
    Vec retVec;
    if(this->values.size() != b.values.size()){
        throw "size mismatch";
    }
    for(int i = 0; i < values.size(); ++i){
        retVec.values.at(i) = this->values.at(i) * b.values.at(i);
    }
    retVec.calcMagnitude();
    return retVec;
}
Vec Vec::operator/(Vec b) {
    Vec retVec;
    if(this->values.size() != b.values.size()){
        throw "size mismatch";
    }
    for(int i = 0; i < values.size(); ++i){
        retVec.values.at(i) = this->values.at(i) / b.values.at(i);
    }
    retVec.calcMagnitude();
    return retVec;
}