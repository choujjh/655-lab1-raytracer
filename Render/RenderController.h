//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_RENDER_CONTROLLER_H
#define RAYTRACER_RENDER_CONTROLLER_H

#include<string>
#include<vector>
#include "../Scene/Cam.h"
#include "../Scene/RenderObj/Object.h"
#include "../Scene/RenderObj/Light/Light.h"
#include "../Scene/Scene.h"
#include "File/Writer/ImageFileWriter.h"
#include "Integrator.h"
#include "../Model/Vec/CoordinateSpace.h"


using std::vector;
using std::string;

class RenderController {
private:

    //vector of rays

    vector<vector<Ray>> rays;
    ImageFileWriter* file;
    Scene currScene;
    Integrator* integrator;
    int samples;
    int levReflectRecursion;

    vector<double> times;

    void initializeRays();
    Vec3 calcPixel(int row, int col);
    Vec3 getColor(Ray ray);
public:
    RenderController(ImageFileWriter *file, const Scene &currScene, Integrator* integrator, int samples,
                     int levReflectRecursion);
    void renderRow(int row);
    void render();
};


#endif //RAYTRACER_RENDER_CONTROLLER_H
