//
// Created by chouj on 9/8/2021.
//

#include "ImageFileWriter.h"

void ImageFileWriter::writeToFileInt() {
    writeToFileInt(255);
}

const string &ImageFileWriter::getFileName() const {
    return fileName;
}

void ImageFileWriter::setFileName(const string &fileName) {
    ImageFileWriter::fileName = fileName;
}

Vec3 **ImageFileWriter::getImage() const {
    return image;
}

void ImageFileWriter::setImage(Vec3 **image) {
    ImageFileWriter::image = image;
}

ImageFileWriter::ImageFileWriter(const string &fileName, unsigned int height, unsigned int width) : fileName(fileName) {
    this->height = height;
    this->width = width;
    image = new Vec3*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec3[width];
    }

}

ImageFileWriter::~ImageFileWriter() {
    for(int i = 0; i < height; ++i){
        delete image[i];
    }
    delete image;
}
