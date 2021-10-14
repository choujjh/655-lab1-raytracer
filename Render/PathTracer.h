//
// Created by chouj on 10/14/2021.
//

#ifndef RAYTRACER_PATHTRACER_H
#define RAYTRACER_PATHTRACER_H

#include "Integrator.h"

class PathTracer: public Integrator{
public:
    PathTracer(Scene *renderScene);

    Vec3 radiance(Ray ray, int depth, int levReflectRecursion, int sampleDensity) override;

};


#endif //RAYTRACER_PATHTRACER_H
