//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_IMAGEFILEMANAGER_H
#define RAYTRACER_IMAGEFILEMANAGER_H


#include "Vec/Vec3.h"
#include "File/Writer/WriteImageStrategy.h"
#include <string>

using std::string;
enum{
    WRITE_PPM
};
class ImageFile {
private:

    unsigned int height;
    unsigned int width;
    Vec3** image;

    void deleteImage();
public:
    void writeToFile(string writeFile, unsigned int strategy);

    void openFile(string imageFile);
    ImageFile(unsigned int height, unsigned int width);
    ImageFile();

    unsigned int getHeight() const;

    unsigned int getWidth() const;

    Vec3 **getImage() const;

    ~ImageFile();


};


#endif //RAYTRACER_IMAGEFILEMANAGER_H
