//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_PPMFILEMANAGER_H
#define RAYTRACER_PPMFILEMANAGER_H


#include <cmath>
#include <fstream>

#include "ImageFileManager.h"

using std::ofstream;
using std::endl;

class PPMFileManager: public ImageFileManager{

public:
    PPMFileManager(const string &fileName, unsigned int height, unsigned int width);

    void writeToFileInt(int maxVal) override;

};


#endif //LAB_1_PPMFILEMANAGER_H
