//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "Cam.h"
#include "RenderObj/Object.h"
#include "Light/Light.h"
#include "IntersectMethods/ObjTracker.h"

class Scene {
private:
    Cam* renderCam;
    Vec3 backColor;
    ObjTracker* objTracker;
public:
    Scene(Cam *renderCam, const Vec3 &backColor, ObjTracker* objTracker);

    ObjTracker* getObjTracker();
    void setObjTracker(ObjTracker* objTracker);

    void addObject(Object* newObject);

    Cam *getRenderCam() const;
    void setRenderCam(Cam *renderCam);

    const Vec3 &getBackColor() const;
    void setBackColor(const Vec3 &backColor);
};


#endif //RAYTRACER_SCENE_H
