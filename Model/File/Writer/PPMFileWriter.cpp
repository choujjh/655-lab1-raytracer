//
// Created by chouj on 9/8/2021.
//


#include "PPMFileWriter.h"

void PPMFileWriter::writeToFile(Vec3** image, int maxVal){
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

PPMFileWriter::PPMFileWriter(const string &fileName, unsigned int height, unsigned int width) : WriteImageStrategy(
        fileName, height, width) {}
