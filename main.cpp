#include <limits>
#include <iostream>

#include "Ops/Ops.h"

#include "Scene.h"
#include "Model/Model.h"


/*TODO:
 * fix box resolution issue
 * make dot and cross and clip all part of Vec3
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
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0, 0, 1);
    Vec3 up(0, 1, 0);
    double fov = 28.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*>* objectList = new vector<Object*>();
    vector<Light*>* lightList = new vector<Light*>();
    createScene(objectList, lightList);

    /**setting up objects**/
    objectList->push_back(new Sphere(0.8, 0.1, 0.1, Vec3(1, 1, 1), Vec3(1.0, 1, 1.0), 4, Vec3(0.35, 0, -0.1), 0.05));
    objectList->push_back(new Sphere(0.3, 0.6, 0.1, Vec3(1, 0, 0), Vec3(0.5, 1, 0.5), 32, Vec3(0.2, 0, -0.1), 0.075));
    objectList->push_back(new Sphere(0.4, 0.5, 0.1, Vec3(0, 1, 0), Vec3(0.5, 1, 0.5), 32, Vec3(-0.6, 0, 0), 0.3));
    Vec3 a(0.3, -0.3, -0.4);
    Vec3 b(0.0, 0.3, -0.1);
    Vec3 c(-0.3, -0.3, 0.2);
    objectList->push_back(new Triangle(0.7, 0.2, 1.0, Vec3(0.0, 0.0, 1.0), Vec3(1.0, 1.0, 1.0), 32, a, b, c));
    a = Vec3(-0.2, 0.1, 0.1);
    b = Vec3(-0.2, -0.5, 0.2);
    c = Vec3(-0.2, 0.1, -0.3);
    objectList->push_back((new Triangle(0.9, 0.0, 0.1, Vec3(1, 1, 0), Vec3(1, 1, 1), 4, a, b, c)));

    /**lights**/
    lightList->push_back(new directionLight(Vec3(1.0, 1.0, 1.0), Vec3(-1.0, 0.0, 0.0)));
    lightList->push_back(new ambientLight(Vec3(0.2, 0.2, 0.2)));


    /**background color**/
    Vec3 backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, objectList, lightList, backColor, 1);
    currScene.render();

    delete renderCam;
    destroyScene(objectList, lightList);
}
void fun(string outFile){
    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0.1, 0.1, 1.2);
    Vec3 up(0, 1, 0);
    double fov = 55.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*>* objectList = new vector<Object*>();
    vector<Light*>* lightList = new vector<Light*>();
    createScene(objectList, lightList);

    /**setting up objects**/
    objectList->push_back(new Sphere(0.2, 0.8, 0.1, Vec3(1, 1, 0), Vec3(1, 1, 0), 4, Vec3(0.35, 0, -0.1), 0.3));
    objectList->push_back(new Sphere(0.8, 0.1, 0.1, Vec3(1, 1, 1), Vec3(1, 1, 1), 4, Vec3(-0.3, 0.3, -0.1), 0.1));
    objectList->push_back(new Sphere(0.8, 0.2, 0.1, Vec3(1, 1, 1), Vec3(1, 1, 1), 4, Vec3(-0.3, -0.1, -0.1), 0.15));

    objectList->push_back(new Sphere(0.8, 0.1, 0.1, Vec3(1, 1, 1), Vec3(1, 1, 1), 4, Vec3(0.0, 0.3, 0.0), 0.25));
    objectList->push_back(new Plane(0.6, 0.3, 0.1, Vec3(0.5, 0.5, 0.5), Vec3(1, 1, 1), 4, Vec3(0.0, 1.0, 0.0), -0.5));

    Vec3 a(0.0, 0.0, -2.5);
    Vec3 b(-0.5, 2.0, -0.5);
    Vec3 c(-0.5, 0.3, 0.5);
    objectList->push_back(new Triangle(0.6, 0.3, 0.1, Vec3(0.0, 0.5, 0.5), Vec3(1, 1, 1), 4, a, b, c));

    /**lights**/
    lightList->push_back(new directionLight(Vec3(1.0, 0.0, 0.0), Vec3(-1.0, -1.0, 0.0)));
    lightList->push_back(new directionLight(Vec3(0.0, 0.20, 0.70), Vec3(-0.1, -1.0, 0.0)));
    lightList->push_back(new ambientLight(Vec3(0.1, 0.1, 0.1)));

    /**background color**/
    Vec3 backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, objectList, lightList, backColor);
    currScene.render();

    delete renderCam;
    destroyScene(objectList, lightList);
}

void reflection(string outFile){
    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0, 0, 1.2);
    Vec3 up(0, 1, 0);
    double fov = 55.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*>* objectList = new vector<Object*>();
    vector<Light*>* lightList = new vector<Light*>();
    createScene(objectList, lightList);

    /**setting up objects**/
    objectList->push_back(new Sphere(0.0, 0.9, 0.1, Vec3(0.75, 0.75, 0.75), Vec3(1, 1, 1), 10, Vec3(0.0, 0.3, 0.0), 0.2));

    Vec3 a(0.0, -0.5, 0.5);
    Vec3 b(1.0, 0.5, 0.0);
    Vec3 c(0.0, -0.5, -0.5);
    objectList->push_back(new Triangle(0.4, 0.5, 0.1, Vec3(0, 0, 1), Vec3(1, 1, 1), 4, a, b, c));

    a = Vec3(0.0, -0.5, 0.5);
    b = Vec3(0.0, -0.5, -0.5);
    c = Vec3(-1.0, 0.5, 0.0);
    objectList->push_back(new Triangle(0.4, 0.5, 0.1, Vec3(1, 1, 0), Vec3(1, 1, 1), 4, a, b, c));

    /**lights**/
    lightList->push_back(new directionLight(Vec3(1.0, 1.0, 1.0), Vec3(0.0, -1.0, 0.0)));

    /**background color**/
    Vec3 backColor(0.2, 0.2, 0.2);

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
