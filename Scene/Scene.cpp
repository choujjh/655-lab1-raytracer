//
// Created by chouj on 9/8/2021.
//

#include "Scene.h"

void Scene::addObject(Object* newObject){
    objTracker->addObject(newObject);
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

const vector<Light *> &Scene::getLightList() const {
    return lightList;
}

void Scene::setLightList(const vector<Light *> &lightList) {
    Scene::lightList = lightList;
}

ObjTracker* Scene::getObjTracker() {
    return objTracker;
}

void Scene::setObjTracker(ObjTracker* objTracker) {
    Scene::objTracker = objTracker;
}

Scene::Scene(Cam *renderCam, const Vec3 &backColor, ObjTracker* objTracker) : renderCam(renderCam),
                                                                              backColor(backColor),
                                                                              objTracker(objTracker) {}
