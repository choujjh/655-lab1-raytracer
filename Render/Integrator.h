//
// Created by chouj on 9/4/2021.
//

#ifndef RAYTRACER_RENDERALG_H
#define RAYTRACER_RENDERALG_H


#include "../Model/Vec/Vec3.h"
#include "../Model/Vec/Ray.h"
#include "../Scene/Scene.h"

class Integrator {
protected:
    Scene* renderScene;
public:
    Integrator(Scene *renderScene);

public:
    virtual Vec3 radiance(Ray ray, int depth, int levReflectRecursion, int sampleDensity) = 0;
};


#endif //RAYTRACER_RENDERALG_H
