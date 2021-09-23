//
// Created by chouj on 9/10/2021.
//

#include "ObjTracker.h"

Vec3 ObjTracker::getIntersect(Ray currRay, bool closest, Object *&object) {
    if(!isOptimized){
        Optimize();
    }
    return Vec3();
}

void ObjTracker::addObject(Object *object) {
    objList.push_back(object);
    if(object->isLight()){
        lightList.push_back(object);
    }
    isOptimized = false;
}

const vector<Object *> &ObjTracker::getObjList() const {
    return objList;
}

void ObjTracker::setObjList(const vector<Object *> &objList) {
    ObjTracker::objList = objList;
}

vector<Object*> ObjTracker::getLightList() {
    return lightList;
}
void ObjTracker::setLightList(const vector<Object*> &lightList){
    this->lightList = lightList;
}

void ObjTracker::Optimize(){
    isOptimized = true;
}
ObjTracker::ObjTracker(): isOptimized(false) {}
