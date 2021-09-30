//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_SCENEINTERSECT_H
#define LAB_1_SCENEINTERSECT_H


#include "../RenderObj/Object.h"

class ObjTracker {
protected:
    vector<Object*> masterObjList;
    vector<Object*> lightList;
public:
    ObjTracker();

    virtual Vec3 getIntersect(Ray currRay, bool closest, Object* &object) = 0;
    void addObject(Object* object);
    virtual void optimize() = 0;

    vector<Object*> getLightList();
    void setLightList(const vector<Object*> &lightList);

    const vector<Object *> &getMasterObjList() const;

    void setMasterObjList(const vector<Object *> &objList);
};


#endif //LAB_1_SCENEINTERSECT_H
