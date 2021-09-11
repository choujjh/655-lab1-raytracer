//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "Cam.h"
#include "RenderObj/Object.h"
#include "Light/Light.h"
#include "IntersectMethods/SceneIntersect.h"

class Scene {
private:
    Cam* renderCam;
    Vec3 backColor;
    vector<Light*> lightList;
    SceneIntersect* objTracker;
public:
    Scene(Cam *renderCam, const Vec3 &backColor, SceneIntersect* objTracker);

    SceneIntersect* getObjTracker();
    void setObjTracker(SceneIntersect* objTracker);

    void addObject(Object* newObject);
    void addLight(Light* newLight);

    Cam *getRenderCam() const;
    void setRenderCam(Cam *renderCam);

    const Vec3 &getBackColor() const;
    void setBackColor(const Vec3 &backColor);

    const vector<Light *> &getLightList() const;
    void setLightList(const vector<Light *> &lightList);
};


#endif //RAYTRACER_SCENE_H
