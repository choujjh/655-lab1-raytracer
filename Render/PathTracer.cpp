//
// Created by chouj on 10/14/2021.
//

#include "../Model/Ops/RenderOps.h"
#include "PathTracer.h"

Vec3 PathTracer::radiance(Ray ray, int depth, int levReflectRecursion, int sampleDensity) {

    return Vec3();
}

Vec3 PathTracer::calcDiffuse(Object* surface, Object* light, Vec3 interPoint, Vec3 rayDir, Vec3 normal, Vec2 objectUV, Vec2 lightUV) {
    Vec3 od = surface->material->getColor(objectUV);
    Vec3 l = rayDir;
    double maxDiffuse = RenderOps().max(0, normal.dot(l));
    Vec3 lightEmission = light->material->getColor(lightUV) * light->material->gamma(lightUV);
    Vec3 retVec = od * maxDiffuse * lightEmission * surface->material->diffuse(objectUV);

    return retVec;
}

PathTracer::PathTracer(Scene *renderScene) : Integrator(renderScene) {}
