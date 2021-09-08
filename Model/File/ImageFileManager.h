//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_IMAGEFILEMANAGER_H
#define RAYTRACER_IMAGEFILEMANAGER_H


#include "../Vec/Vec3.h"
#include <string>

using std::string;

class ImageFileManager {
private:
protected:

    unsigned int height;
    unsigned int width;
    string fileName;
    Vec3** image;

public:
    void virtual writeToFileInt(int maxVal) = 0;
    void virtual writeToFileInt();

    ImageFileManager(const string &fileName, unsigned int height, unsigned int width);

    const string &getFileName() const;

    void setFileName(const string &fileName);

    Vec3 **getImage() const;

    void setImage(Vec3 **image);

    ~ImageFileManager();


};


#endif //RAYTRACER_IMAGEFILEMANAGER_H
