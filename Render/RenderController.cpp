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

RenderController::RenderController(ImageFileManager *file, const Scene &currScene, Integrator* integrator, bool randomSamples,
                                   int sampleDensity, int levReflectRecursion) :
                                   file(file),
                                   currScene(currScene),
                                   integrator(integrator),
                                   randomSamples(randomSamples),
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
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = std::chrono::high_resolution_clock::now();

//    vector<std::thread> threadList(currScene.getRenderCam()->getHeight());
//    for (int row = 0; row < currScene.getRenderCam()->getHeight(); ++row) {
//        threadList.at(row) = std::thread(&RenderController::renderRow, this, row);
//    }
//    for (int i = 0; i < threadList.size(); ++i) {
//        threadList.at(i).join();
//        if(i%50 == 0){
//            auto t2 = std::chrono::high_resolution_clock::now();
//            cout << "finished row " << i << " in " <<  duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << " seconds: " <<
//            std::fixed << std::setprecision(3) << (i / currScene.getRenderCam()->getHeight()) * 100.0 << "% complete" << endl;
//            t1 = std::chrono::high_resolution_clock::now();
//        }
//    }


//    int numCores = std::thread::hardware_concurrency();
//    vector<std::thread> threadList;
//    int usedCores = 0;
//    for (int row = 191; row < currScene.getRenderCam()->getHeight(); ++row) {
//        renderRow(row);
//        threadList.push_back(std::thread(&RenderController::renderRow, this, row));
//        ++usedCores;
//        if (row == currScene.getRenderCam()->getHeight() - 1 ||
//            usedCores % numCores == 0) {//could also check to see if num cores are already used
//            for (int i = 0; i < threadList.size(); ++i) {
//                threadList.at(i).join();
//            }
//            threadList.clear();
//            auto t2 = std::chrono::high_resolution_clock::now();
//            cout << "finished row " << row << " in " <<  duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << " seconds: " <<
//                 std::fixed << std::setprecision(3) << ((row + 1) / currScene.getRenderCam()->getHeight()) * 100.0 << "% complete" << endl;
//            t1 = std::chrono::high_resolution_clock::now();
//        }
//    }
    renderRow(205);
}
void RenderController::renderRow(int row){
//    for(int col = 0; col < currScene.getRenderCam()->getWidth(); ++col){
//        file->getImage()[row][col] = calcPixel(row, col).clip(0, 1);
//    }
    file->getImage()[row][249] = calcPixel(row, 249).clip(0, 1);
}

void RenderController::initializeRays(){

    Vec3 incrX = currScene.getRenderCam()->getIncrementX();
    Vec3 incrY = currScene.getRenderCam()->getIncrementY();
    Vec3 currRow = currScene.getRenderCam()->getStart();
    if(!randomSamples){
        currRow = Vec3(currScene.getRenderCam()->getStart())
                   - (incrX / sampleDensity) * ((sampleDensity - 1))
                   + (incrY / sampleDensity) * ((sampleDensity - 1));
    }
    for(int row = 0; row < currScene.getRenderCam()->getHeight(); ++row){
        Vec3 currCol = currRow;
        for(int col = 0; col < currScene.getRenderCam()->getWidth(); ++col){

            //sampling Density
            if(randomSamples) {
                for (int newRow = 0; newRow < sampleDensity; ++newRow) {
                    for (int newCol = 0; newCol < sampleDensity; ++newCol) {
                        int savedRow = row * sampleDensity + newRow;
                        int savedCol = col * sampleDensity + newCol;
                        if (randomSamples) {
                            double offsetX = RenderOps().tentFloatRandGen(-0.5, 0.5);
                            double offsetY = RenderOps().tentFloatRandGen(-0.5, 0.5);

                            rays.at(savedRow).at(savedCol).direction = (currCol +
                                                                        incrX * offsetX - incrY * offsetY -
                                                                        currScene.getRenderCam()->getLookFrom()).normalize();
                            rays.at(savedRow).at(savedCol).point = currScene.getRenderCam()->getLookFrom();
                        } else {
                            rays.at(savedRow).at(savedCol).direction = (currCol +
                                                                        (incrX / sampleDensity) * newRow +
                                                                        (incrY / sampleDensity) * newCol -
                                                                        currScene.getRenderCam()->getLookFrom()).normalize();
                            rays.at(savedRow).at(savedCol).point = currScene.getRenderCam()->getLookFrom();
                        }
                    }
                }
            }

            currCol += incrX;
        }
        currRow -= incrY;
    }
}

Vec3 RenderController::calcPixel(int row, int col){
    Vec3 color(0, 0, 0);
    for(int subRow = 0; subRow < sampleDensity; ++ subRow){
        for(int subCol = 0; subCol < sampleDensity; ++subCol){
            Ray currRay = rays.at(row * sampleDensity + subRow).at(col * sampleDensity + subCol);
            color += getColor(currRay);
        }
    }

    return color / (sampleDensity * sampleDensity);
}

Vec3 RenderController::getColor(Ray ray){
    integrator->setSampleDensity(randomSamples);
    return integrator->radiance(ray, 0, levReflectRecursion, sampleDensity);
}
