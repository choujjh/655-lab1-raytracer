//
// Created by chouj on 9/29/2021.
//

#ifndef RAYTRACER_WRITERSTRATEGY_H
#define RAYTRACER_WRITERSTRATEGY_H

#include <string>
#include <Vec/Vec3.h>

using std::string;
class WriteImageStrategy {
protected:
    string fileName;
    unsigned int height;
    unsigned int width;

public:
    virtual void writeToFile(Vec3** image, int maxVal) = 0;

    WriteImageStrategy(const string &fileName, int height, int width);
};


#endif //RAYTRACER_WRITERSTRATEGY_H
