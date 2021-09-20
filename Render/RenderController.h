//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_RENDER_CONTROLLER_H
#define RAYTRACER_RENDER_CONTROLLER_H

#include<string>
#include<vector>
#include "../Scene/Cam.h"
#include "../Scene/RenderObj/Object.h"
#include "../Scene/Light/Light.h"
#include "../Scene/Scene.h"
#include "../Model/File/ImageFileManager.h"
#include "Integrator.h"
#include "../Model/Vec/CoordinateSpace.h"


using std::vector;
using std::string;

class RenderController {
private:

    //vector of rays

    vector<vector<Ray>> rays;
    ImageFileManager* file;
    Scene currScene;
    Integrator* integrator;

    int sampleDensity;
    int levReflectRecursion;

    void initializeRays();
    Vec3 calcPixel(int row, int col);
    Vec3 getColor(Ray ray, int currLevel);
public:
    RenderController(ImageFileManager *file, const Scene &currScene, Integrator* integrator, int sampleDensity,
                     int levReflectRecursion);
    void renderRow(int row);
    void render();
};


#endif //RAYTRACER_RENDER_CONTROLLER_H
