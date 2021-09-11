//
// Created by chouj on 9/10/2021.
//

#ifndef LAB_1_SCENEINTERSECT_H
#define LAB_1_SCENEINTERSECT_H


#include "../RenderObj/Object.h"

class SceneIntersect {
protected:
    vector<Object*> objList;
public:
    SceneIntersect();

    virtual Vec3 getIntersect(Ray currRay, bool closest, Object* &object) const;
    virtual Vec3 getIntersect(Ray currRay, bool closest) const;
    virtual void addObject(Object* object);
};


#endif //LAB_1_SCENEINTERSECT_H