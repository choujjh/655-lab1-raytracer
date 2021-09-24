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

using std::cout;
using std::endl;

RenderController::RenderController(ImageFileManager *file, const Scene &currScene, Integrator* integrator,
                                   int samples, int levReflectRecursion) :
                                   file(file),
                                   currScene(currScene),
                                   integrator(integrator),
                                   samples(samples),
                                   levReflectRecursion(levReflectRecursion) {
    if(this->samples < 1){
        this->samples = 1;
    }
    int height = currScene.getRenderCam()->getHeight();
    int width = currScene.getRenderCam()->getWidth();
    rays.resize(height);
    for(int i = 0; i < rays.size(); ++i) {
        rays.at(i).resize(width * samples);
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

    int numCores = std::thread::hardware_concurrency();
    int activeCores = 0;
    vector<std::thread> threadList;
    for(int row = 0; row < currScene.getRenderCam()->getHeight(); ++row){
        while(activeCores == numCores){
            for(int i = 0; i < threadList.size(); ++i){
                if(threadList.at(i).joinable()){
                    threadList.at(i).join();
                    --activeCores;
                    threadList.erase(threadList.begin() + i);
                    break;
                }
            }
            threadList.at(0).join();
            --activeCores;
            threadList.erase(threadList.begin());
        }
        cout << "pushed row " << row << " to be rendered" << endl;
        threadList.push_back(std::thread(&RenderController::renderRow, this, row));
        ++activeCores;
    }
    for(int i = 0; i < threadList.size(); ++i){
        threadList.at(i).join();
    }
    threadList.clear();
}
void RenderController::renderRow(int row){
    srand(std::hash<std::thread::id>{}(std::this_thread::get_id()) + row * 17);
    for(int col = 0; col < currScene.getRenderCam()->getWidth(); ++col){
        Vec3 temp = calcPixel(row, col).clip(0, 1);
        file->getImage()[row][col] = temp;
    }
}

void RenderController::initializeRays(){

    Vec3 incrX = currScene.getRenderCam()->getIncrementX();
    Vec3 incrY = currScene.getRenderCam()->getIncrementY();
    Vec3 currRow = currScene.getRenderCam()->getStart();
    for(int row = 0; row < currScene.getRenderCam()->getHeight(); ++row){
        Vec3 currCol = currRow;
        for(int col = 0; col < currScene.getRenderCam()->getWidth(); ++col){

            //sampling Density
            for (int newCol = 0; newCol < samples; ++newCol) {
                int savedCol = col * samples + newCol;
                double offsetX = RenderOps().tentFloatRandGen(-1.0, 1.0);
                double offsetY = RenderOps().tentFloatRandGen(-1.0, 1.0);

                rays.at(row).at(savedCol).direction = (currCol +
                                                       incrX * offsetX - incrY * offsetY -
                                                       currScene.getRenderCam()->getLookFrom()).normalize();
                rays.at(row).at(savedCol).point = currScene.getRenderCam()->getLookFrom();
            }
            currCol += incrX;
        }
        currRow -= incrY;
    }
}

Vec3 RenderController::calcPixel(int row, int col){
    Vec3 color(0, 0, 0);
    for(int subCol = 0; subCol < samples; ++subCol){
        Ray currRay = rays.at(row).at(col * samples + subCol);
        color += getColor(currRay);
    }
    return color / samples;
}

Vec3 RenderController::getColor(Ray ray){
    return integrator->radiance(ray, 0, levReflectRecursion, samples);
}
