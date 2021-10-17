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

    Vec3 calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, Vec3 normal, Vec2 ObjectUV);

    Vec3 calcLighting(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 shadowIntersect, Vec3 normal, Vec2 objectUV);
    Vec3 calcSpec(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV);
    Vec3 calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV);
    Vec3 calcAmbient(Object* surface, Object* light, Vec2 objectUV);
};


#endif //LAB_1_PHONG_H
