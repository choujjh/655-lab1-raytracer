//
// Created by chouj on 9/29/2021.
//

#ifndef RAYTRACER_PPMFILEREADER_H
#define RAYTRACER_PPMFILEREADER_H

#include "ReadImageStrategy.h"

class PPMFileReader: public ReadImageStrategy {
    Vec3** readImage(string readFile, unsigned int& height, unsigned int& width) override;
};


#endif //RAYTRACER_PPMFILEREADER_H
