//
// Created by chouj on 10/14/2021.
//

#ifndef RAYTRACER_PATHTRACER_H
#define RAYTRACER_PATHTRACER_H

#include "Integrator.h"

class PathTracer: public Integrator{
public:
    PathTracer(Scene *renderScene);

    Vec3 radiance(Ray ray, int depth, int levReflectRecursion) override;
    Vec3 calcSurfColor(Ray ray, Vec3 interVec, Object* intersectObject, Vec3 normal, Vec2 objectUV);
    Vec3 calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV);

};


#endif //RAYTRACER_PATHTRACER_H
