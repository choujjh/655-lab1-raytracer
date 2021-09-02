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

#include "Scene.h"
#include "Ops/RenderOps.h"

void Scene::writeToFileInt(int maxVal){
    ofstream out;
    out.open(fileName);

    out << "P3" << endl;
    out << renderCam->getHeight() << " " << renderCam->getWidth() << endl;
    out << maxVal << endl;
    for(int row = 0; row < renderCam->getWidth(); ++row){
        for(int col = 0; col < renderCam->getHeight(); ++col){
            int r = round(image[row][col].values.at(0) * maxVal);
            int g = round(image[row][col].values.at(1) * maxVal);
            int b = round(image[row][col].values.at(2) * maxVal);
            out << r << " " << g << " " << b << " ";
        }
        out << endl;
    }
    out.close();
}

void Scene::render() {
    /**initialize rays**/
    initializeRays();
    /**get image color**/
    for(int row = 0; row < renderCam->getWidth(); ++row){
        for(int col = 0; col < renderCam->getHeight(); ++col){
            image[row][col] = calcPixel(row, col);
        }
    }
    /**write image array to file**/
    writeToFileInt(255);
}

void Scene::initializeRays(){
    Vec currRow = this->renderCam->getStart();
    for(int row = 0; row < renderCam->getWidth(); ++row){
        Vec currCol = currRow;
        for(int col = 0; col < renderCam->getHeight(); ++col){
            Vec dirRay = (currCol - renderCam->getLookFrom()).normalize();
            rays.at(row).at(col).direction = dirRay;
            rays.at(row).at(col).point = renderCam->getLookFrom();
            currCol = currCol + renderCam->getIncrementX();
        }
        currRow = currRow - renderCam->getIncrementY();
    }
}

Vec Scene::calcPixel(int row, int col){
//    std::cout << "row: " << row << ", col: " << col << endl;
    //partition in the samples then call for each
    OffVec currRay = rays.at(row).at(col);

    return getColor(currRay, 0);
}

Vec Scene::getColor(OffVec ray, int currLevel){
    if(currLevel > this->levReflect){
        return Vec();
    }
    int objIndex = -1;
    Vec interVec = getIntersect(ray, true, objIndex);
    if (interVec.getMagnitude() == std::numeric_limits<double>::infinity()) {
        return backColor;
    }

    Vec n = objList->at(objIndex)->normal(interVec);
    Vec epsilonPoint = interVec + n * 0.001;
    Vec color(0.0, 0.0, 0.0);

    for(int i = 0; i < lightList->size(); ++i) {
        OffVec shadowRay = OffVec(epsilonPoint, lightList->at(i)->shadowRay(interVec));
        int shadowIndex = -1;
        Vec shadowIntersect = getIntersect(shadowRay, false, shadowIndex);
        bool occluded = true;
        if (shadowIntersect.getMagnitude() == std::numeric_limits<double>::infinity()) {
            occluded = false;
        }
        Vec addColor = clip(0, 1, lightList->at(i)->illumination(interVec, ray.direction, objList->at(objIndex), occluded) + color);

        color = addColor;
    }
    Vec refRay = RenderOps().reflectionRay(n, ray.direction * -1);
    OffVec newRay(epsilonPoint, refRay);
    color = clip(0, 1, color + getColor(newRay, currLevel + 1) * objList->at(objIndex)->getKSpecular() * objList->at(objIndex)->getKSpecular());

    return color;
}

Vec Scene::clip(double min, double max, Vec clipVec){
    if (clipVec.values.at(0) > max) {
        clipVec.values.at(0) = max;
    }
    if (clipVec.values.at(1) > max) {
        clipVec.values.at(1) = max;
    }
    if (clipVec.values.at(2) > max) {
        clipVec.values.at(2) = max;
    }

    if (clipVec.values.at(0) < min) {
        clipVec.values.at(0) = min;
    }
    if (clipVec.values.at(1) < min) {
        clipVec.values.at(1) = min;
    }
    if (clipVec.values.at(2) < min) {
        clipVec.values.at(2) = min;
    }
    return clipVec;
}

Vec Scene::getIntersect(OffVec currRay, bool closest, int &objIndex) {
    Vec minInterVec = objList->at(0)->intersect(currRay);
    if(minInterVec.getMagnitude() < std::numeric_limits<double>::infinity()){
        objIndex = 0;
    }
    for(int i = 1; i < objList->size(); ++i){
        Vec interPoint = objList->at(i)->intersect(currRay);
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

Scene::Scene(const string &fileName, Cam *renderCam, vector<Object *> *objList, vector<Light *> *lightList, Vec backColor, int levReflect) : fileName(
        fileName), renderCam(renderCam), objList(objList), lightList(lightList), backColor(backColor), levReflect(levReflect){
    int height = renderCam->getHeight();
    int width = renderCam->getWidth();
    image = new Vec*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec[width];
    }
    rays.resize(height);
    for(int i = 0; i < rays.size(); ++i){
        rays.at(i).resize(width);
    }
}

Scene::~Scene(){
    int height = renderCam->getHeight();
    for(int i = 0; i < height; ++i){
        delete image[i];
    }
    delete image;
}



