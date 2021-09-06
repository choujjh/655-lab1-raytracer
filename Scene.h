//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include<string>
#include<vector>
#include "Scene/Cam.h"
#include "Scene/RenderObj/Object.h"
#include "Scene/Light/Light.h"


using std::vector;
using std::string;

class Scene {
private:
    string fileName;
    Cam* renderCam;
    vector<Object*>* objList;
    vector<Light*>* lightList;

    Vec3** image;
    vector<vector<Ray>> rays;
    Vec3 backColor;

    int levReflectRecursion;

    void writeToFileInt(int maxVal);
    void initializeRays();
    Vec3 calcPixel(int row, int col);
    Vec3 getIntersect(Ray currRay, bool closest, int &objIndex);
    Vec3 getColor(Ray ray, int currLevel);
public:
    Scene(const string &fileName, Cam *renderCam, vector<Object *> *objList, vector<Light *> *lightList, Vec3 backColor, int levReflect = 1);
    ~Scene();
    void render();
};


#endif //RAYTRACER_SCENE_H
