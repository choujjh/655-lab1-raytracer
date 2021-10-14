//
// Created by chouj on 9/29/2021.
//

#include "PPMFileReader.h"
#include <iostream>

#include <fstream>
#include "../../Ops/RenderOps.h"
#include "Reader/ReadImageStrategy.h"
#include "Reader/PPMFileReader.h"

using std::ifstream;
using std::cout;
using std::endl;
Vec3** PPMFileReader::readImage(string readFile, unsigned int& height, unsigned int& width, bool normalizeSum) {
    ifstream ppmFile;
    ppmFile.open(readFile);
    if(!ppmFile.is_open()){
        cout << readFile << " file not opened" << endl;
        height = 1;
        width = 1;
        Vec3** image = new Vec3*[height];
        image[0] = new Vec3[width];
        image[0][0] = Vec3(RenderOps().randFloatValue(), RenderOps().randFloatValue(), RenderOps().randFloatValue());
        return image;
    }
    string tempString;
    int maxColor;
    Vec3** image = nullptr;
    ppmFile >> tempString;
    ppmFile.ignore();
    width = getNextNumber(ppmFile);
    height = getNextNumber(ppmFile);
    maxColor = getNextNumber(ppmFile);
    image = new Vec3*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec3[width];
    }
    for(int row = height - 1; row >= 0; --row){
        for(int col = 0; col < width; ++col){
            double temp;
            temp = getNextNumber(ppmFile);
            image[row][col].x = temp/maxColor;
            temp = getNextNumber(ppmFile);
            image[row][col].y = temp/maxColor;
            temp = getNextNumber(ppmFile);
            image[row][col].z = temp/maxColor;
            if(normalizeSum){
                image[row][col].normalizeSum();
            }
//            cout << row << " " << col << ": " << image[row][col].x << " " << image[row][col].y << " " << image[row][col].z << endl;
        }
    }
    ppmFile.close();
    return image;
}
double PPMFileReader::getNextNumber(ifstream& in){
    string tempString;
    while(!in.eof()){
        in >> tempString;
        in.ignore();
        if(isdigit(tempString.at(0))){
            return atof(tempString.c_str());
        }
        cout << tempString << endl;
        if(tempString.at(0) == '#'){
            getline(in, tempString);
            cout << tempString << endl;
        }
    }
    return 0.0;
}
