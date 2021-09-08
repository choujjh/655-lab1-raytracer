//
// Created by chouj on 3/8/2021.
//
#include<fstream>

#include<iostream>
#include<iomanip>
#include<cmath>
#include<limits>

using std::ofstream;
using std::endl;

#include "RenderController.h"
#include "../Model/Ops/RenderOps.h"

#include <iostream>

using std::cout, std::endl;

void RenderController::render() {
    /**initialize rays**/
    initializeRays();
    /**get image color**/
    for(int row = 0; row < currScene.getRenderCam()->getHeight(); ++row){
        for(int col = 0; col < currScene.getRenderCam()->getWidth(); ++col){
            file->getImage()[row][col] = calcPixel(row, col);
        }
    }
    /**write image array to file**/
    file->writeToFileInt();
}

void RenderController::initializeRays(){
    Vec3 currRow = this->currScene.getRenderCam()->getStart();
    int row = 0;
    int col = 0;
    for(row = 0; row < currScene.getRenderCam()->getHeight(); ++row){
        Vec3 currCol = currRow;
        for(col = 0; col < currScene.getRenderCam()->getWidth(); ++col){
            Vec3 dirRay = (currCol - currScene.getRenderCam()->getLookFrom()).normalize();
            rays.at(row).at(col).direction = dirRay;
            rays.at(row).at(col).point = currScene.getRenderCam()->getLookFrom();
            currCol = currCol + currScene.getRenderCam()->getIncrementX();

        }
        currRow = currRow - currScene.getRenderCam()->getIncrementY();
    }
}

Vec3 RenderController::calcPixel(int row, int col){
    Ray currRay = rays.at(row).at(col);

    return getColor(currRay, 0);
}

Vec3 RenderController::getColor(Ray ray, int currLevel){
    if(currLevel > this->levReflectRecursion){
        return Vec3();
    }
    int objIndex = -1;
    Vec3 interVec = getIntersect(ray, true, objIndex);
    if (interVec.getMagnitude() == std::numeric_limits<double>::infinity()) {
        return currScene.getBackColor();
    }

    Vec3 n = currScene.getObjList().at(objIndex)->normal(interVec);
    Vec3 epsilonPoint = interVec + n * 0.001;
    Vec3 color(0.0, 0.0, 0.0);

    for(int i = 0; i < currScene.getLightList().size(); ++i) {
        Ray shadowRay = Ray(epsilonPoint, currScene.getLightList().at(i)->shadowRay(interVec));
        int shadowIndex = -1;
        Vec3 shadowIntersect = getIntersect(shadowRay, false, shadowIndex);
        bool occluded = true;
        if (shadowIntersect.getMagnitude() == std::numeric_limits<double>::infinity()) {
            occluded = false;
        }
        Vec3 addColor = currScene.getLightList().at(i)->illumination(interVec, ray.direction, currScene.getObjList().at(objIndex), occluded) + color;
        addColor.clip(0, 1);

        color = addColor;
    }
    Vec3 refRay = RenderOps().reflectionRay(n, ray.direction * -1);
    Ray newRay(epsilonPoint, refRay);
    color += getColor(newRay, currLevel + 1) * currScene.getObjList().at(objIndex)->objMat->kSpecular->getColor() * currScene.getObjList().at(objIndex)->objMat->kSpecular->getColor();
    color.clip(0, 1);

    return color;
}

Vec3 RenderController::getIntersect(Ray currRay, bool closest, int &objIndex) {
    Vec3 minInterVec = currScene.getObjList().at(0)->intersect(currRay);
    if(minInterVec.getMagnitude() < std::numeric_limits<double>::infinity()){
        objIndex = 0;
    }
    for(int i = 1; i < currScene.getObjList().size(); ++i){
        Vec3 interPoint = currScene.getObjList().at(i)->intersect(currRay);
        if (!closest && interPoint.getMagnitude() != std::numeric_limits<double>::infinity()) {
            return interPoint;
        }
        if ((interPoint - currRay.point).getMagnitude() < (minInterVec - currRay.point).getMagnitude()) {
            minInterVec = interPoint;
            objIndex = i;
        }
    }
    return minInterVec;
}

RenderController::RenderController(ImageFileManager *file, const Scene &currScene, int samplingDensity,
                                   int levReflectRecursion) : file(file), currScene(currScene),
                                                              samplingDensity(samplingDensity),
                                                              levReflectRecursion(levReflectRecursion) {
    int height = currScene.getRenderCam()->getHeight();
    int width = currScene.getRenderCam()->getWidth();
    rays.resize(height);
    for(int i = 0; i < rays.size(); ++i){
        rays.at(i).resize(width);
    }
}




