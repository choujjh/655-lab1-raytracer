//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_PPMFILEMANAGER_H
#define RAYTRACER_PPMFILEMANAGER_H


#include <cmath>
#include <fstream>

#include "ImageFile.h"

using std::ofstream;
using std::endl;

class PPMFileWriter: public WriteImageStrategy{

public:
    PPMFileWriter(const string &fileName, unsigned int height, unsigned int width);

public:
    void writeToFile(Vec3** image, int maxVal) override;

};


#endif //LAB_1_PPMFILEMANAGER_H
