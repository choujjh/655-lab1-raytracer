//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_POINTLIGHT_H
#define LAB_1_POINTLIGHT_H


#include "Light.h"

class PointLight: public Light {
private:
    Vec3 position;
public:
    PointLight(const Vec3 &color, const Vec3 &position);

    Vec3 shadowRay(Vec3 point) override;
    bool isAmbient() override;


};


#endif //LAB_1_POINTLIGHT_H
