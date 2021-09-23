//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_SCENEINTERSECT_H
#define LAB_1_SCENEINTERSECT_H


#include "../RenderObj/Object.h"

class ObjTracker {
protected:
    vector<Object*> objList;
    vector<Object*> lightList;
    bool isOptimized;
public:
    ObjTracker();

    virtual Vec3 getIntersect(Ray currRay, bool closest, Object* &object);
    void addObject(Object* object);
    virtual void Optimize() = 0;

    vector<Object*> getLightList();
    void setLightList(const vector<Object*> &lightList);

    const vector<Object *> &getObjList() const;

    void setObjList(const vector<Object *> &objList);
};


#endif //LAB_1_SCENEINTERSECT_H
