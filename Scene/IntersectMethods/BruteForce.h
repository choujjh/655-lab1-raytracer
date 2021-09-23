//
// Created by chouj on 9/23/2021.
//

#ifndef RAYTRACER_BRUTEFORCE_H
#define RAYTRACER_BRUTEFORCE_H


#include "ObjTracker.h"

class BruteForce: public ObjTracker {
public:
    BruteForce();

    Vec3 getIntersect(Ray currRay, bool closest, Object *&object) override;

    void Optimize() override;

};


#endif //RAYTRACER_BRUTEFORCE_H
