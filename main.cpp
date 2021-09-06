#include <limits>
#include <iostream>


#include "Scene.h"
#include "RenderCompCreator.h"


/*TODO:
 * sampling
 * multi- threading
 * lights as objects
 * different illumination model
 * path tracing
 * kd trees
 * */

using std::string;
using std::vector;

void diffuse(string outFile){
    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0, 0, 1);
    Vec3 up(0, 1, 0);
    double fov = 28.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*> objectList = vector<Object*>();
    vector<Light*> lightList = vector<Light*>();
    RenderCompCreator sceneComp;

    sceneComp.makeMatSolidD(0.8);

    /**setting up objects**/
    Material MSphere1(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere1, Vec3(0.35, 0, -0.1), 0.05));

    Material MSphere2(sceneComp.makeMatSolidD(0.3),
                      sceneComp.makeMatSolidD(0.6),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(32),
                      sceneComp.makeMatSolidV3(1, 0, 0),
                      sceneComp.makeMatSolidV3(0.5, 1, 0.5),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere2, Vec3(0.2, 0, -0.1), 0.075));

    Material MSphere3(sceneComp.makeMatSolidD(0.4),
                      sceneComp.makeMatSolidD(0.5),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(32),
                      sceneComp.makeMatSolidV3(0, 1, 0),
                      sceneComp.makeMatSolidV3(0.5, 1, 0.5),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere3, Vec3(-0.6, 0, 0), 0.3));

    Material MTriangle1(sceneComp.makeMatSolidD(0.7),
                      sceneComp.makeMatSolidD(0.2),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(32),
                      sceneComp.makeMatSolidV3(0, 0, 1.0),
                      sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    Vec3 a(0.3, -0.3, -0.4);
    Vec3 b(0.0, 0.3, -0.1);
    Vec3 c(-0.3, -0.3, 0.2);
    objectList.push_back(sceneComp.makeTriangle(MTriangle1, a, b, c));

    Material MTriangle2(sceneComp.makeMatSolidD(0.9),
                        sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidV3(1, 1, 0),
                        sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
                        sceneComp.makeMatSolidV3(Vec3()));
    a = Vec3(-0.2, 0.1, 0.1);
    b = Vec3(-0.2, -0.5, 0.2);
    c = Vec3(-0.2, 0.1, -0.3);
    objectList.push_back((sceneComp.makeTriangle(MTriangle2, a, b, c)));

    /**lights**/
    lightList.push_back(sceneComp.makeDirectionLight(Vec3(1.0, 1.0, 1.0), Vec3(-1.0, 0.0, 0.0)));
    lightList.push_back(sceneComp.makeAmbientLight(Vec3(0.2, 0.2, 0.2)));


    /**background color**/
    Vec3 backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, &objectList, &lightList, backColor, 1);
    currScene.render();

    delete renderCam;
}
void fun(string outFile){
    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0.1, 0.1, 1.2);
    Vec3 up(0, 1, 0);
    double fov = 55.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*> objectList = vector<Object*>();
    vector<Light*> lightList = vector<Light*>();
    RenderCompCreator sceneComp;

    /**setting up objects**/
    Material MSphere1(sceneComp.makeMatSolidD(0.2),
                      sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(1, 1, 0),
                      sceneComp.makeMatSolidV3(1.0, 1, 0.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere1, Vec3(0.35, 0, -0.1), 0.3));

    Material MSphere2(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1.0, 1, 1),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere2, Vec3(-0.3, 0.3, -0.1), 0.1));

    Material MSphere3(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.2),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere3, Vec3(-0.3, -0.1, -0.1), 0.15));

    Material MSphere4(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere4, Vec3(0.0, 0.3, 0.0), 0.25));

    Material MPlane1(sceneComp.makeMatSolidD(0.6),
                      sceneComp.makeMatSolidD(0.3),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(0.5, 0.5, 0.5),
                      sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makePlane(MPlane1, Vec3(0.0, 1.0, 0.0), -0.5));

    Material MTriangle1(sceneComp.makeMatSolidD(0.6),
                     sceneComp.makeMatSolidD(0.3),
                     sceneComp.makeMatSolidD(0.1),
                     sceneComp.makeMatSolidD(4),
                     sceneComp.makeMatSolidV3(0, 0.5, 0.5),
                     sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                     sceneComp.makeMatSolidV3(Vec3()));
    Vec3 a(0.0, 0.0, -2.5);
    Vec3 b(-0.5, 2.0, -0.5);
    Vec3 c(-0.5, 0.3, 0.5);
    objectList.push_back(sceneComp.makeTriangle(MTriangle1, a, b, c));

    /**lights**/
    lightList.push_back(sceneComp.makeDirectionLight(Vec3(1.0, 0.0, 0.0), Vec3(-1.0, -1.0, 0.0)));
    lightList.push_back(sceneComp.makeDirectionLight(Vec3(0.0, 0.20, 0.70), Vec3(-0.1, -1.0, 0.0)));
    lightList.push_back(sceneComp.makeAmbientLight(Vec3(0.1, 0.1, 0.1)));

    /**background color**/
    Vec3 backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, &objectList, &lightList, backColor);
    currScene.render();

    delete renderCam;
}

void reflection(string outFile){
    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0, 0, 1.2);
    Vec3 up(0, 1, 0);
    double fov = 55.0;

    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
    vector<Object*> objectList = vector<Object*>();
    vector<Light*> lightList = vector<Light*>();
    RenderCompCreator sceneComp;

    /**setting up objects**/
    Material MSphere1(sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidD(0.9),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidV3(0.75, 0.75, 0.75),
                        sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                        sceneComp.makeMatSolidV3(Vec3()));
    objectList.push_back(sceneComp.makeSphere(MSphere1, Vec3(0.0, 0.3, 0.0), 0.2));

    Material MTriangle1(sceneComp.makeMatSolidD(0.4),
                      sceneComp.makeMatSolidD(0.5),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidV3(0, 0, 1),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(Vec3()));
    Vec3 a(0.0, -0.5, 0.5);
    Vec3 b(1.0, 0.5, 0.0);
    Vec3 c(0.0, -0.5, -0.5);
    objectList.push_back(sceneComp.makeTriangle(MTriangle1, a, b, c));

    Material MTriangle2(sceneComp.makeMatSolidD(0.4),
                        sceneComp.makeMatSolidD(0.5),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidV3(1, 1, 0),
                        sceneComp.makeMatSolidV3(1, 1, 1),
                        sceneComp.makeMatSolidV3(Vec3()));
    a = Vec3(0.0, -0.5, 0.5);
    b = Vec3(0.0, -0.5, -0.5);
    c = Vec3(-1.0, 0.5, 0.0);
    objectList.push_back(sceneComp.makeTriangle(MTriangle2, a, b, c));

    /**lights**/
    lightList.push_back(sceneComp.makeDirectionLight(Vec3(1.0, 1.0, 1.0), Vec3(0.0, -1.0, 0.0)));

    /**background color**/
    Vec3 backColor(0.2, 0.2, 0.2);

    Scene currScene(outFile, renderCam, &objectList, &lightList, backColor, 3);
    currScene.render();

    delete renderCam;
}
int main() {
//    diffuse("diffuse.ppm");
//    reflection("reflection.ppm");
    fun("personal.ppm");
    return 0;
}
