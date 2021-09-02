#include <limits>
#include <iostream>

#include "Ops/Ops.h"

#include "Scene.h"
#include "Model/Model.h"


/*TODO:
 * fix box resolution issue
 * make dot and cross and clip all part of Vec
 * overload += and -=
 * sampling
 * multi- threading
 * lights as objects
 * different illumination model
 * path tracing
 * kd trees
 * */

using std::string;
using std::vector;

void createScene(vector<Object*>* objectList, vector<Light*>* lightList){
    objectList = new vector<Object*>();
    lightList = new vector<Light*>();
}
void destroyScene(vector<Object*>* objectList, vector<Light*>* lightList){
    for(int i = 0; i < objectList->size(); ++i){
        delete objectList->at(i);
    }
    delete objectList;
    for(int i = 0; i < lightList->size(); ++i){
        delete lightList->at(i);
    }
    delete lightList;
}
void diffuse(string outFile){
    /**setting up camera**/
    Vec cameraLookAt(0, 0, 0.0);
    Vec cameraLookFrom(0, 0, 1);
    Vec up(0, 1, 0);
    double fov = 28.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*>* objectList = new vector<Object*>();
    vector<Light*>* lightList = new vector<Light*>();
    createScene(objectList, lightList);

    /**setting up objects**/
    objectList->push_back(new Sphere(0.8, 0.1, 0.1, Vec(1, 1, 1), Vec(1.0, 1, 1.0), 4, Vec(0.35, 0, -0.1), 0.05));
    objectList->push_back(new Sphere(0.3, 0.6, 0.1, Vec(1, 0, 0), Vec(0.5, 1, 0.5), 32, Vec(0.2, 0, -0.1), 0.075));
    objectList->push_back(new Sphere(0.4, 0.5, 0.1, Vec(0, 1, 0), Vec(0.5, 1, 0.5), 32, Vec(-0.6, 0, 0), 0.3));
    Vec a(0.3, -0.3, -0.4);
    Vec b(0.0, 0.3, -0.1);
    Vec c(-0.3, -0.3, 0.2);
    objectList->push_back(new Triangle(0.7, 0.2, 1.0, Vec(0.0, 0.0, 1.0), Vec(1.0, 1.0, 1.0), 32, a, b, c));
    a = Vec(-0.2, 0.1, 0.1);
    b = Vec(-0.2, -0.5, 0.2);
    c = Vec(-0.2, 0.1, -0.3);
    objectList->push_back((new Triangle(0.9, 0.0, 0.1, Vec(1, 1, 0), Vec(1, 1, 1), 4, a, b, c)));

    /**lights**/
    lightList->push_back(new directionLight(Vec(1.0, 1.0, 1.0), Vec(-1.0, 0.0, 0.0)));
    lightList->push_back(new ambientLight(Vec(0.2, 0.2, 0.2)));


    /**background color**/
    Vec backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, objectList, lightList, backColor, 1);
    currScene.render();

    delete renderCam;
    destroyScene(objectList, lightList);
}
void fun(string outFile){
    /**setting up camera**/
    Vec cameraLookAt(0, 0, 0.0);
    Vec cameraLookFrom(0.1, 0.1, 1.2);
    Vec up(0, 1, 0);
    double fov = 55.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*>* objectList = new vector<Object*>();
    vector<Light*>* lightList = new vector<Light*>();
    createScene(objectList, lightList);

    /**setting up objects**/
    objectList->push_back(new Sphere(0.2, 0.8, 0.1, Vec(1, 1, 0), Vec(1, 1, 0), 4, Vec(0.35, 0, -0.1), 0.3));
    objectList->push_back(new Sphere(0.8, 0.1, 0.1, Vec(1, 1, 1), Vec(1, 1, 1), 4, Vec(-0.3, 0.3, -0.1), 0.1));
    objectList->push_back(new Sphere(0.8, 0.2, 0.1, Vec(1, 1, 1), Vec(1, 1, 1), 4, Vec(-0.3, -0.1, -0.1), 0.15));

    objectList->push_back(new Sphere(0.8, 0.1, 0.1, Vec(1, 1, 1), Vec(1, 1, 1), 4, Vec(0.0, 0.3, 0.0), 0.25));
    objectList->push_back(new Plane(0.6, 0.3, 0.1, Vec(0.5, 0.5, 0.5), Vec(1, 1, 1), 4, Vec(0.0, 1.0, 0.0), -0.5));

    Vec a(0.0, 0.0, -2.5);
    Vec b(-0.5, 2.0, -0.5);
    Vec c(-0.5, 0.3, 0.5);
    objectList->push_back(new Triangle(0.6, 0.3, 0.1, Vec(0.0, 0.5, 0.5), Vec(1, 1, 1), 4, a, b, c));

    /**lights**/
    lightList->push_back(new directionLight(Vec(1.0, 0.0, 0.0), Vec(-1.0, -1.0, 0.0)));
    lightList->push_back(new directionLight(Vec(0.0, 0.20, 0.70), Vec(-0.1, -1.0, 0.0)));
    lightList->push_back(new ambientLight(Vec(0.1, 0.1, 0.1)));

    /**background color**/
    Vec backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, objectList, lightList, backColor);
    currScene.render();

    delete renderCam;
    destroyScene(objectList, lightList);
}

void reflection(string outFile){
    /**setting up camera**/
    Vec cameraLookAt(0, 0, 0.0);
    Vec cameraLookFrom(0, 0, 1.2);
    Vec up(0, 1, 0);
    double fov = 55.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*>* objectList = new vector<Object*>();
    vector<Light*>* lightList = new vector<Light*>();
    createScene(objectList, lightList);

    /**setting up objects**/
    objectList->push_back(new Sphere(0.0, 0.9, 0.1, Vec(0.75, 0.75, 0.75), Vec(1, 1, 1), 10, Vec(0.0, 0.3, 0.0), 0.2));

    Vec a(0.0, -0.5, 0.5);
    Vec b(1.0, 0.5, 0.0);
    Vec c(0.0, -0.5, -0.5);
    objectList->push_back(new Triangle(0.4, 0.5, 0.1, Vec(0, 0, 1), Vec(1, 1, 1), 4, a, b, c));

    a = Vec(0.0, -0.5, 0.5);
    b = Vec(0.0, -0.5, -0.5);
    c = Vec(-1.0, 0.5, 0.0);
    objectList->push_back(new Triangle(0.4, 0.5, 0.1, Vec(1, 1, 0), Vec(1, 1, 1), 4, a, b, c));

    /**lights**/
    lightList->push_back(new directionLight(Vec(1.0, 1.0, 1.0), Vec(0.0, -1.0, 0.0)));

    /**background color**/
    Vec backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, objectList, lightList, backColor, 2);
    currScene.render();

    delete renderCam;
    destroyScene(objectList, lightList);
}
int main() {
    diffuse("diffuse.ppm");
    reflection("reflection.ppm");
    fun("personal.ppm");
    return 0;
}
