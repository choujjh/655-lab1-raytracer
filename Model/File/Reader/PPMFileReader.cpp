//
// Created by chouj on 9/29/2021.
//

#include "PPMFileReader.h"
#include <iostream>

#include <fstream>
#include "Reader/ReadImageStrategy.h"
#include "Reader/PPMFileReader.h"

using std::ifstream;
using std::cout;
using std::endl;
Vec3** PPMFileReader::readImage(string readFile, unsigned int& height, unsigned int& width) {
    ifstream ppmFile;
    ppmFile.open(readFile);
    if(!ppmFile.is_open()){
        cout << readFile << " file not opened" << endl;
        return nullptr;
    }
    string tempString;
    int maxColor;
    Vec3** image = nullptr;
    ppmFile >> tempString;
    ppmFile >> width;
    ppmFile >> height;
    ppmFile >> maxColor;
    image = new Vec3*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec3[width];
    }
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            int temp;
            ppmFile >> temp;
            image[row][col].x = static_cast<double>(temp)/maxColor;
            ppmFile >> temp;
            image[row][col].y = static_cast<double>(temp)/maxColor;
            ppmFile >> temp;
            image[row][col].z = static_cast<double>(temp)/maxColor;
        }
    }
    ppmFile.close();
    return image;
}
