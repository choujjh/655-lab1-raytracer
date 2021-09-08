//
// Created by chouj on 9/8/2021.
//

#include "ImageFileManager.h"

void ImageFileManager::writeToFileInt() {
    writeToFileInt(255);
}

const string &ImageFileManager::getFileName() const {
    return fileName;
}

void ImageFileManager::setFileName(const string &fileName) {
    ImageFileManager::fileName = fileName;
}

Vec3 **ImageFileManager::getImage() const {
    return image;
}

void ImageFileManager::setImage(Vec3 **image) {
    ImageFileManager::image = image;
}

ImageFileManager::ImageFileManager(const string &fileName, unsigned int height, unsigned int width) : fileName(fileName) {
    this->height = height;
    this->width = width;
    image = new Vec3*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec3[width];
    }

}

ImageFileManager::~ImageFileManager() {
    for(int i = 0; i < height; ++i){
        delete image[i];
    }
    delete image;
}
