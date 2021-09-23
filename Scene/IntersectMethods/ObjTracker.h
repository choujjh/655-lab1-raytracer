//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_SCENEINTERSECT_H
#define LAB_1_SCENEINTERSECT_H


#include "../RenderObj/Object.h"

class ObjTracker {
protected:
    vector<Object*> objList;
public:
    ObjTracker();

    virtual Vec3 getIntersect(Ray currRay, bool closest, Object* &object) const;
    virtual void addObject(Object* object);
    virtual void optimize();
};


#endif //LAB_1_SCENEINTERSECT_H
