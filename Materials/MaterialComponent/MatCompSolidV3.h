//
// Created by chouj on 10/14/2021.
//

#ifndef RAYTRACER_MATCOMPV3_H
#define RAYTRACER_MATCOMPV3_H


#include "../../Model/Vec/Vec3.h"
#include "MatComponent.h"

class MatCompSolidV3: public MatComponent<Vec3> {
public:
    Vec3 getColor(double u, double v){
        return val;
    }
    virtual Vec3 getColor(){
        return val;
    }
    virtual Vec3 getColor(Vec2 uv){
        return val;
    }

    MatCompSolidV3(Vec3 val, bool normalizeSum = false): val(val) {
        if(normalizeSum){
            val.normalizeSum();
        }
    }
protected:
    Vec3 val;
};


#endif //RAYTRACER_MATCOMPV3_H
