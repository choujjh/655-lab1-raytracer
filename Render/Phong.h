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
    Vec3 radiance(Ray ray, int depth, int levReflectRecursion) override;

    Vec3 calcLighting(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
    Vec3 calcSpec(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
    Vec3 calcDiffuse(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
    Vec3 calcAmbient(Object* surface, Light* light, Vec3 interPoint, Vec3 rayDir, double normalScalar);
};


#endif //LAB_1_PHONG_H
