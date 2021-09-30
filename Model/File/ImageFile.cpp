//
// Created by chouj on 9/8/2021.
//

#include <File/Writer/PPMFileWriter.h>
#include "ImageFile.h"
#include <iostream>
#include <File/Reader/ReadImageStrategy.h>
#include <File/Reader/PPMFileReader.h>

using std::cout;

void ImageFile::writeToFile(string fileName, unsigned int strategy) {
    WriteImageStrategy* write;
    if(strategy == WRITE_PPM){
        write = new PPMFileWriter(fileName, height, width);
        write->writeToFile(image, 255);
    }
    else{
        std::cout << "Write file format not supported" << endl;
    }
    if(write != nullptr) {
        delete write;
    }
}
void ImageFile::openFile(string imageFile) {
    if(image != nullptr){
        deleteImage();
        height = 0;
        width = 0;
    }
    //string extension stuff
    int index = imageFile.find_last_of('.') != string::npos ? imageFile.find_last_of('.') + 1: -1;
    if(index == -1){
        cout << "Read file format not supported" << endl;
        return;
    }
    string extension = imageFile.substr(index);
    for(int i = 0; i < extension.size(); ++i){
        extension.at(i) = tolower(extension.at(i));
    }

    //finding the image type
    ReadImageStrategy* read;
    if(extension == "ppm"){
        read = new PPMFileReader();
        image = read->readImage(imageFile, height, width);
    }
    delete read;

}

Vec3 **ImageFile::getImage() const {
    return image;
}

ImageFile::ImageFile(unsigned int height, unsigned int width) {
    this->height = height;
    this->width = width;
    image = new Vec3*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec3[width];
    }

}
ImageFile::ImageFile() : height(0), width(0) {}

ImageFile::~ImageFile() {
    deleteImage();
}
void ImageFile::deleteImage(){
    for(int i = 0; i < height; ++i){
        delete image[i];
    }
    delete image;
    image = nullptr;
}

unsigned int ImageFile::getHeight() const {
    return height;
}

unsigned int ImageFile::getWidth() const {
    return width;
}
