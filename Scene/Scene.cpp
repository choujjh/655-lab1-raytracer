//
// Created by chouj on 9/8/2021.
//

#include "Scene.h"

void Scene::addObject(Object* newObject){
    objTracker->addObject(newObject);
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

ObjTracker* Scene::getObjTracker() {
    return objTracker;
}

void Scene::setObjTracker(ObjTracker* objTracker) {
    Scene::objTracker = objTracker;
}

Scene::Scene(Cam *renderCam, const Vec3 &backColor, ObjTracker* objTracker) : renderCam(renderCam),
                                                                              backColor(backColor),
                                                                              objTracker(objTracker) {}
