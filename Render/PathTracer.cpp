//
// Created by chouj on 10/14/2021.
//

#include "PathTracer.h"

Vec3 PathTracer::radiance(Ray ray, int depth, int levReflectRecursion, int sampleDensity) {
    return Vec3();
}

PathTracer::PathTracer(Scene *renderScene) : Integrator(renderScene) {}
