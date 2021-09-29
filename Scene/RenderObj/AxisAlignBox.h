//
// Created by chouj on 9/25/2021.
//

#ifndef INC_655_LAB1_RAYTRACER_AXISALIGNBOX_H
#define INC_655_LAB1_RAYTRACER_AXISALIGNBOX_H


#include "Object.h"

class AxisAlignBox: public Object {
public:
    AxisAlignBox(BaseMaterial *objMat, const Vec3 &maxVals, const Vec3 &minVals);
    bool calcAxisT(double point, double direction, double min, double max, double &t1, double &t2);

    Vec3 shadowRay(Vec3 point, Vec3 objectNormal) override;

    Vec3 intersect(Ray ray) override;

    Vec3 normal(Vec3 point) override;

    void getUV(Vec3 point, double& u, double& v) override;
};


#endif //INC_655_LAB1_RAYTRACER_AXISALIGNBOX_H
