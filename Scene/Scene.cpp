//
// Created by chouj on 9/8/2021.
//

#include "Scene.h"

Scene::Scene(Cam *renderCam, const Vec3 &backColor, vector<Object*> objList, vector<Light*> lightList) : renderCam(
        renderCam), backColor(backColor), objList(objList), lightList(lightList) {}

Scene::Scene(Cam *renderCam, const Vec3 &backColor) : renderCam(
        renderCam), backColor(backColor) {}

void Scene::addObject(Object* newObject){
    objList.push_back(newObject);
}
void Scene::addLight(Light* newLight){
    lightList.push_back(newLight);
}

Cam *Scene::getRenderCam() const {
    return renderCam;
}

void Scene::setRenderCam(Cam *renderCam) {
    Scene::renderCam = renderCam;
}

const Vec3 &Scene::getBackColor() const {
    return backColor;
}

void Scene::setBackColor(const Vec3 &backColor) {
    Scene::backColor = backColor;
}

const vector<Object *> &Scene::getObjList() const {
    return objList;
}

void Scene::setObjList(const vector<Object *> &objList) {
    Scene::objList = objList;
}

const vector<Light *> &Scene::getLightList() const {
    return lightList;
}

void Scene::setLightList(const vector<Light *> &lightList) {
    Scene::lightList = lightList;
}
