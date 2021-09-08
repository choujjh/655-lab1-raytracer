//
// Created by chouj on 9/8/2021.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include "Cam.h"
#include "RenderObj/Object.h"
#include "Light/Light.h"

class Scene {
private:
    Cam* renderCam;
    Vec3 backColor;
    vector<Object*> objList;
    vector<Light*> lightList;
public:

    Scene(Cam *renderCam, const Vec3 &backColor, vector<Object*> objList, vector<Light*> lightList);
    Scene(Cam *renderCam, const Vec3 &backColor);

    void addObject(Object* newObject);
    void addLight(Light* newLight);

    Cam *getRenderCam() const;
    void setRenderCam(Cam *renderCam);

    const Vec3 &getBackColor() const;
    void setBackColor(const Vec3 &backColor);

    const vector<Object *> &getObjList() const;
    void setObjList(const vector<Object *> &objList);

    const vector<Light *> &getLightList() const;
    void setLightList(const vector<Light *> &lightList);
};


#endif //RAYTRACER_SCENE_H
