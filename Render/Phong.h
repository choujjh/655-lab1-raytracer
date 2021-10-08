//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_PHONG_H
#define LAB_1_PHONG_H


#include "Integrator.h"

class Phong: public Integrator {
public:
    Phong(Scene *renderScene);

private:
    Vec3 radiance(Ray ray, int depth, int levReflectRecursion, int sampleDensity) override;

    Vec3 calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, double normalScalar, double u , double v);

    Vec3 calcLighting(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 shadowIntersect, double normalScalar, double objectU, double objectV);
    Vec3 calcSpec(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar, double objectU, double objectV, double lightU, double lightV);
    Vec3 calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar, double objectU, double objectV, double lightU, double lightV);
    Vec3 calcAmbient(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar, double u, double v);
};


#endif //LAB_1_PHONG_H
