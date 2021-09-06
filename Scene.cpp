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
#include "Model/Ops/RenderOps.h"

using std::cout, std::endl;

void Scene::writeToFileInt(int maxVal){
    ofstream out;
    out.open(fileName);

    out << "P3" << endl;
    out << renderCam->getWidth() << " " << renderCam->getHeight() << endl;
    out << maxVal << endl;
    for(int row = 0; row < renderCam->getHeight(); ++row){
        for(int col = 0; col < renderCam->getWidth(); ++col){
            out << round(image[row][col].x * maxVal) << " " << round(image[row][col].y * maxVal) << " " << round(image[row][col].z * maxVal) << " ";
        }
        out << endl;
    }
    out.close();
}

void Scene::render() {
    /**initialize rays**/
    initializeRays();
    /**get image color**/
    for(int row = 0; row < renderCam->getHeight(); ++row){
        for(int col = 0; col < renderCam->getWidth(); ++col){
            image[row][col] = calcPixel(row, col);
        }
    }
    /**write image array to file**/
    writeToFileInt(255);
}

void Scene::initializeRays(){
    Vec3 currRow = this->renderCam->getStart();
    int row = 0;
    int col = 0;
    for(row = 0; row < renderCam->getHeight(); ++row){
        Vec3 currCol = currRow;
        for(col = 0; col < renderCam->getWidth(); ++col){
            try {
                    Vec3 dirRay = (currCol - renderCam->getLookFrom()).normalize();
                    rays.at(row).at(col).direction = dirRay;
                    rays.at(row).at(col).point = renderCam->getLookFrom();
                    currCol = currCol + renderCam->getIncrementX();
            }
            catch(...){
                cout << "row: " << row << " col: " << col << endl;
            }
        }
        currRow = currRow - renderCam->getIncrementY();
    }
}

Vec3 Scene::calcPixel(int row, int col){
    Ray currRay = rays.at(row).at(col);

    return getColor(currRay, 0);
}

Vec3 Scene::getColor(Ray ray, int currLevel){
    if(currLevel > this->levReflectRecursion){
        return Vec3();
    }
    int objIndex = -1;
    Vec3 interVec = getIntersect(ray, true, objIndex);
    if (interVec.getMagnitude() == std::numeric_limits<double>::infinity()) {
        return backColor;
    }

    Vec3 n = objList->at(objIndex)->normal(interVec);
    Vec3 epsilonPoint = interVec + n * 0.001;
    Vec3 color(0.0, 0.0, 0.0);

    for(int i = 0; i < lightList->size(); ++i) {
        Ray shadowRay = Ray(epsilonPoint, lightList->at(i)->shadowRay(interVec));
        int shadowIndex = -1;
        Vec3 shadowIntersect = getIntersect(shadowRay, false, shadowIndex);
        bool occluded = true;
        if (shadowIntersect.getMagnitude() == std::numeric_limits<double>::infinity()) {
            occluded = false;
        }
        Vec3 addColor = lightList->at(i)->illumination(interVec, ray.direction, objList->at(objIndex), occluded) + color;
        addColor.clip(0, 1);

        color = addColor;
    }
    Vec3 refRay = RenderOps().reflectionRay(n, ray.direction * -1);
    Ray newRay(epsilonPoint, refRay);
    color += getColor(newRay, currLevel + 1) * objList->at(objIndex)->objMat->kSpecular * objList->at(objIndex)->objMat->kSpecular;
    color.clip(0, 1);

    return color;
}

Vec3 Scene::getIntersect(Ray currRay, bool closest, int &objIndex) {
    Vec3 minInterVec = objList->at(0)->intersect(currRay);
    if(minInterVec.getMagnitude() < std::numeric_limits<double>::infinity()){
        objIndex = 0;
    }
    for(int i = 1; i < objList->size(); ++i){
        Vec3 interPoint = objList->at(i)->intersect(currRay);
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

Scene::Scene(const string &fileName, Cam *renderCam, vector<Object *> *objList, vector<Light *> *lightList, Vec3 backColor, int levReflect) : fileName(
        fileName), renderCam(renderCam), objList(objList), lightList(lightList), backColor(backColor), levReflectRecursion(levReflect){
    int height = renderCam->getHeight();
    int width = renderCam->getWidth();
    image = new Vec3*[height];
    for(int i = 0; i < height; ++i){
        image[i] = new Vec3[width];
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



