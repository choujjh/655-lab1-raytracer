//
// Created by chouj on 9/8/2021.
//


#include "PPMFileReader.h"

void PPMFileReader::writeToFileInt(int maxVal){
    ofstream out;
    out.open(fileName);

    out << "P3" << endl;
    out << width << " " << height << endl;
    out << maxVal << endl;
    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col){
            out << round(image[row][col].x * maxVal) << " " << round(image[row][col].y * maxVal) << " " << round(image[row][col].z * maxVal) << " ";
        }
        out << endl;
    }
    out.close();

}

PPMFileReader::PPMFileReader(const string &fileName, unsigned int height, unsigned int width) : ImageFileWriter(
        fileName, height, width) {}