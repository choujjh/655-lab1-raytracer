//
// Created by chouj on 9/29/2021.
//

#ifndef RAYTRACER_READIMAGESTRATEGY_H
#define RAYTRACER_READIMAGESTRATEGY_H
#include <string>
#include <Vec/Vec3.h>

using std::string;
class ReadImageStrategy {
public:
    virtual Vec3** readImage(string readFile, unsigned int& height, unsigned int& width, bool normalizeSum) = 0;
};


#endif //RAYTRACER_READIMAGESTRATEGY_H
