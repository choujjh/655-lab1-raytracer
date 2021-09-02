//
// Created by chouj on 3/6/2021.
//

#include "linAlgOp.h"

double LinAlgOp::dot(Vec a, Vec b) {
    if(a.values.size() == b.values.size()){
        double dotVal = 0;
        for(int i = 0; i < a.values.size(); ++i){
            dotVal += a.values.at(i) * b.values.at(i);
        }
        return dotVal;
    }
    throw "vector size mismatch";
}

Vec LinAlgOp::cross(Vec a, Vec b) {
    if(a.values.size() !=3 || b.values.size() != 3){
        throw "vector size greater than 3";
    }
    double first = (a.values.at(1) * b.values.at(2)) - (b.values.at(1) * a.values.at(2));
    double second = -((a.values.at(0) * b.values.at(2)) - (b.values.at(0) * a.values.at(2)));
    double third = (a.values.at(0) * b.values.at(1)) - (b.values.at(0) * a.values.at(1));

    return Vec(first, second, third);
}

