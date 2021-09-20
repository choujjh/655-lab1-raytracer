//
// Created by chouj on 3/8/2021.
//

#include<fstream>
#include<iostream>
#include<iomanip>
#include <thread>

using std::ofstream;
using std::endl;

#include "RenderController.h"
#include "../Model/Ops/RenderOps.h"

using std::cout, std::endl;

RenderController::RenderController(ImageFileManager *file, const Scene &currScene, Integrator* integrator,
                                   int sampleDensity, int levReflectRecursion) :
                                   file(file),
                                   currScene(currScene),
                                   integrator(integrator),
                                   sampleDensity(sampleDensity),
                                   levReflectRecursion(levReflectRecursion) {
    int height = currScene.getRenderCam()->getHeight();
    int width = currScene.getRenderCam()->getWidth();
    rays.resize(height * sampleDensity);
    for(int i = 0; i < rays.size(); ++i) {
        rays.at(i).resize(width * sampleDensity);
    }
}


void RenderController::render() {
    /**initialize rays**/
    initializeRays();
    /**get image color**/
//    int numCores = std::thread::hardware_concurrency();
    vector<std::thread> threadList;
//    int usedCores = 0;
    for (int row = 0; row < currScene.getRenderCam()->getHeight(); ++row) {
        threadList.push_back(std::thread(&RenderController::renderRow, this, row));
//        ++usedCores;
        if (row == currScene.getRenderCam()->getHeight() - 1) {//could also check to see if num cores are already used
            for (int i = 0; i < threadList.size(); ++i) {
                threadList.at(i).join();
            }
            threadList.clear();
        }
    }
}
void RenderController::renderRow(int row){
    for(int col = 0; col < currScene.getRenderCam()->getWidth(); ++col){
        file->getImage()[row][col] = calcPixel(row, col).clip(0, 1);
    }
}

void RenderController::initializeRays(){
    Vec3 newIncrX = Vec3(currScene.getRenderCam()->getIncrementX()) / sampleDensity;
    Vec3 newIncrY = Vec3(currScene.getRenderCam()->getIncrementY()) / sampleDensity;
    Vec3 currRow = Vec3(currScene.getRenderCam()->getStart())
                   - newIncrX * ((sampleDensity - 1))
                   + newIncrY * ((sampleDensity - 1));

    for(int row = 0; row < currScene.getRenderCam()->getHeight() * sampleDensity; ++row){
        Vec3 currCol = currRow;
        for(int col = 0; col < currScene.getRenderCam()->getWidth() * sampleDensity; ++col){
            rays.at(row).at(col).direction = (currCol - currScene.getRenderCam()->getLookFrom()).normalize();
            rays.at(row).at(col).point = currScene.getRenderCam()->getLookFrom();
            currCol += newIncrX;
        }
        currRow -= newIncrY;
    }
}

Vec3 RenderController::calcPixel(int row, int col){
    Vec3 color(0, 0, 0);
    for(int subRow = 0; subRow < sampleDensity; ++ subRow){
        for(int subCol = 0; subCol < sampleDensity; ++subCol){
            Ray currRay = rays.at(row * sampleDensity + subRow).at(col * sampleDensity + subCol);
            color += getColor(currRay, 0);
        }
    }

    return color / (sampleDensity * sampleDensity);
}

Vec3 RenderController::getColor(Ray ray, int currLevel){
    return integrator->radiance(ray, currLevel, levReflectRecursion);
}
