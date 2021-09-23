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

    Vec3 calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, double normalScalar);

    Vec3 calcLighting(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
    Vec3 calcSpec(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
    Vec3 calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
    Vec3 calcAmbient(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
};


#endif //LAB_1_PHONG_H
