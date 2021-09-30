//
// Created by chouj on 9/10/2021.
//

#include "ObjTracker.h"

void ObjTracker::addObject(Object *object) {
    masterObjList.push_back(object);
    if(object->isLight()){
        lightList.push_back(object);
    }
}

const vector<Object *> &ObjTracker::getMasterObjList() const {
    return masterObjList;
}

void ObjTracker::setMasterObjList(const vector<Object *> &objList) {
    ObjTracker::masterObjList = objList;
}

vector<Object*> ObjTracker::getLightList() {
    return lightList;
}
void ObjTracker::setLightList(const vector<Object*> &lightList){
    this->lightList = lightList;
}
ObjTracker::ObjTracker(){}
