//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include<string>
#include<vector>

#include "Model/VecModel/Vec.h"
#include "Model/Scene/RenderObj/Object.h"
#include "Model/Scene/Light/Light.h"
#include "Model/Scene/Cam.h"

using std::vector;
using std::string;

class Scene {
private:
    string fileName;
    Cam* renderCam;
    vector<Object*>* objList;
    vector<Light*>* lightList;

    Vec** image;
    vector<vector<OffVec>> rays;
    Vec backColor;

    int levReflect;

    void writeToFileInt(int maxVal);
    void initializeRays();
    Vec calcPixel(int row, int col);
    Vec getIntersect(OffVec currRay, bool closest, int &objIndex);
    Vec getColor(OffVec ray, int currLevel);
    Vec clip(double min, double max, Vec clipVec);
public:
    Scene(const string &fileName, Cam *renderCam, vector<Object *> *objList, vector<Light *> *lightList, Vec backColor, int levReflect = 1);
    ~Scene();
    void render();
};


#endif //RAYTRACER_SCENE_H
