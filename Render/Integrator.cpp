//
// Created by chouj on 9/4/2021.
//

#include "Integrator.h"

Integrator::Integrator(Scene *renderScene) : renderScene(renderScene) {
    randSample = false;
}

void Integrator::setSampleDensity(bool randSample) {
    this->randSample = randSample;
}
