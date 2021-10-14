//
// Created by chouj on 9/29/2021.
//

#ifndef RAYTRACER_PPMFILEREADER_H
#define RAYTRACER_PPMFILEREADER_H

#include "ReadImageStrategy.h"
#include <istream>
using std::ifstream;

class PPMFileReader: public ReadImageStrategy {
private:
    double getNextNumber(ifstream& in);
public:
    Vec3** readImage(string readFile, unsigned int& height, unsigned int& width, bool normalizeSum) override;
};


#endif //RAYTRACER_PPMFILEREADER_H
