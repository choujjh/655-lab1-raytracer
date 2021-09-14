#include <limits>
#include <iostream>
#include <chrono>

#include "Render/RenderController.h"
#include "Model/RenderCompCreator.h"
#include "Model/Ops/RenderOps.h"
#include "Scene/Materials/Material.h"

/*TODO:
 * multi- threading
 * lights as objects
 * different illumination model
 * path tracing
 * kd trees
 * */

using std::string;
using std::vector;

void diffuse(string outFile){
    RenderCompCreator sceneComp;

    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0, 0, 1);
    Vec3 up(0, 1, 0);
    double fov = 28.0;
    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);

    /**setting up Scene**/
    Vec3 backColor(0.2, 0.2, 0.2);

    Scene currScene(renderCam, backColor, sceneComp.makeSceneIntersect());

    /**objects**/
    Material MSphere1(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    Object* sphere = sceneComp.makeSphere(&MSphere1, Vec3(0.35, 0, -0.1), 0.05);
    currScene.addObject(sphere);

    Material MSphere2(sceneComp.makeMatSolidD(0.3),
                      sceneComp.makeMatSolidD(0.6),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(32),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(1, 0, 0),
                      sceneComp.makeMatSolidV3(0.5, 1, 0.5),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere2, Vec3(0.2, 0, -0.1), 0.075));

    Material MSphere3(sceneComp.makeMatSolidD(0.4),
                      sceneComp.makeMatSolidD(0.5),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(32),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(0, 1, 0),
                      sceneComp.makeMatSolidV3(0.5, 1, 0.5),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere3, Vec3(-0.6, 0, 0), 0.3));

    Material MTriangle1(sceneComp.makeMatSolidD(0.7),
                      sceneComp.makeMatSolidD(0.2),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(32),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(0, 0, 1.0),
                      sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    Vec3 a(0.3, -0.3, -0.4);
    Vec3 b(0.0, 0.3, -0.1);
    Vec3 c(-0.3, -0.3, 0.2);
    currScene.addObject(sceneComp.makeTriangle(&MTriangle1, a, b, c));

    Material MTriangle2(sceneComp.makeMatSolidD(0.9),
                        sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidD(1.0),
                        sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidV3(1, 1, 0),
                        sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
                        sceneComp.makeMatSolidV3(Vec3()));
    a = Vec3(-0.2, 0.1, 0.1);
    b = Vec3(-0.2, -0.5, 0.2);
    c = Vec3(-0.2, 0.1, -0.3);
    currScene.addObject((sceneComp.makeTriangle(&MTriangle2, a, b, c)));

    /**lights**/
    currScene.addLight(sceneComp.makeDirectionLight(Vec3(1.0, 1.0, 1.0), Vec3(-1.0, 0.0, 0.0)));
    currScene.addLight(sceneComp.makeAmbientLight(Vec3(0.2, 0.2, 0.2)));


    /**File**/
    ImageFileManager* fManager = sceneComp.makePPMFileManager(outFile, renderCam->getHeight(), renderCam->getWidth());


    RenderController controller(fManager, currScene, sceneComp.makePhongIntegrator(&currScene), 1, 1);
    controller.render();
    fManager->writeToFileInt();

    delete renderCam;
}

void fun(string outFile){
    RenderCompCreator sceneComp;

    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0.1, 0.1, 1.2);
    Vec3 up(0, 1, 0);
    double fov = 55.0;
    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);

    /**setting up Scene**/
    Vec3 backColor(0.2, 0.2, 0.2);
    Scene currScene(renderCam, backColor, sceneComp.makeSceneIntersect());

    /**objects**/
    Material MSphere1(sceneComp.makeMatSolidD(0.2),
                      sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(1, 1, 0),
                      sceneComp.makeMatSolidV3(1.0, 1, 0.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere1, Vec3(0.35, 0, -0.1), 0.3));

    Material MSphere2(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1.0, 1, 1),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere2, Vec3(-0.3, 0.3, -0.1), 0.1));

    Material MSphere3(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.2),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere3, Vec3(-0.3, -0.1, -0.1), 0.15));

    Material MSphere4(sceneComp.makeMatSolidD(0.8),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere4, Vec3(0.0, 0.3, 0.0), 0.25));

    Material MPlane1(sceneComp.makeMatSolidD(0.6),
                      sceneComp.makeMatSolidD(0.3),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(0.5, 0.5, 0.5),
                      sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                      sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makePlane(&MPlane1, Vec3(0.0, 1.0, 0.0), -0.5));

    Material MTriangle1(sceneComp.makeMatSolidD(0.6),
                     sceneComp.makeMatSolidD(0.3),
                     sceneComp.makeMatSolidD(0.1),
                     sceneComp.makeMatSolidD(4),
                     sceneComp.makeMatSolidD(1.0),
                     sceneComp.makeMatSolidD(0.0),
                     sceneComp.makeMatSolidV3(0, 0.5, 0.5),
                     sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                     sceneComp.makeMatSolidV3(Vec3()));
    Vec3 a(0.0, 0.0, -2.5);
    Vec3 b(-0.5, 2.0, -0.5);
    Vec3 c(-0.5, 0.3, 0.5);
    currScene.addObject(sceneComp.makeTriangle(&MTriangle1, a, b, c));

    /**lights**/
    currScene.addLight(sceneComp.makeDirectionLight(Vec3(1.0, 0.0, 0.0), Vec3(-1.0, -1.0, 0.0)));
    currScene.addLight(sceneComp.makeDirectionLight(Vec3(0.0, 0.20, 0.70), Vec3(-0.1, -1.0, 0.0)));
    currScene.addLight(sceneComp.makeAmbientLight(Vec3(0.1, 0.1, 0.1)));

    /**File**/
    ImageFileManager* fManager = sceneComp.makePPMFileManager(outFile, renderCam->getHeight(), renderCam->getWidth());

    RenderController controller(fManager, currScene, sceneComp.makePhongIntegrator(&currScene), 2, 1);
    controller.render();
    fManager->writeToFileInt();

    delete renderCam;
}

void reflection(string outFile){
    RenderCompCreator sceneComp;

    /**setting up camera**/
    Vec3 cameraLookAt(0, 0, 0.0);
    Vec3 cameraLookFrom(0, 0.2, 1.2);
    Vec3 up(0, 1, 0);
    double fov = 55.0;
    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);

    /**setting up Scene**/
    Vec3 backColor(0.8, 0.8, 0.8);
    Scene currScene(renderCam, backColor, sceneComp.makeSceneIntersect());

    /**setting up objects**/
    Material MSphere1(sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidD(0.9),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidD(1.5),
                        sceneComp.makeMatSolidD(1.0),
                        sceneComp.makeMatSolidV3(0.75, 0.75, 0.75),
                        sceneComp.makeMatSolidV3(1.0, 1, 1.0),
                        sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makeSphere(&MSphere1, Vec3(0.0, 0.3, 0.0), 0.2));

    Material MTriangle1(sceneComp.makeMatSolidD(0.4),
                      sceneComp.makeMatSolidD(0.5),
                      sceneComp.makeMatSolidD(0.1),
                      sceneComp.makeMatSolidD(4),
                      sceneComp.makeMatSolidD(1.0),
                      sceneComp.makeMatSolidD(0.0),
                      sceneComp.makeMatSolidV3(0, 0, 1),
                      sceneComp.makeMatSolidV3(1, 1, 1),
                      sceneComp.makeMatSolidV3(Vec3()));
    Vec3 a(0.0, -0.5, 0.5);
    Vec3 b(1.0, 0.5, 0.0);
    Vec3 c(0.0, -0.5, -0.5);
    currScene.addObject(sceneComp.makeTriangle(&MTriangle1, a, b, c));

    Material MPlane1(sceneComp.makeMatSolidD(0.4),
                        sceneComp.makeMatSolidD(0.5),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidD(1.0),
                        sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidV3(0.6, 0.6, 0.6),
                        sceneComp.makeMatSolidV3(1, 1, 1),
                        sceneComp.makeMatSolidV3(Vec3()));
    currScene.addObject(sceneComp.makePlane(&MPlane1, Vec3(0, 1, 0), -0.5));

    Material MTriangle2(sceneComp.makeMatSolidD(0.4),
                        sceneComp.makeMatSolidD(0.5),
                        sceneComp.makeMatSolidD(0.1),
                        sceneComp.makeMatSolidD(4),
                        sceneComp.makeMatSolidD(1.0),
                        sceneComp.makeMatSolidD(0.0),
                        sceneComp.makeMatSolidV3(1, 1, 0),
                        sceneComp.makeMatSolidV3(1, 1, 1),
                        sceneComp.makeMatSolidV3(Vec3(1, 1, 0)));
    c = Vec3(0.0, -0.5, 0.5);
    b = Vec3(0.0, -0.5, -0.5);
    a = Vec3(-1.0, 0.5, 0.0);
    currScene.addObject(sceneComp.makeTriangle(&MTriangle2, a, b, c));
//    currScene.addObject(sceneComp.makePlane(&MTriangle2, Vec3(0, 1, 0), -0.5));

    /**lights**/
    currScene.addLight(sceneComp.makePointLight(Vec3(0.9, 0.9, 0.9), Vec3(0.0, 3.0, 0.0)));

    /**File**/
    ImageFileManager* fManager = sceneComp.makePPMFileManager(outFile, renderCam->getHeight(), renderCam->getWidth());

    RenderController controller(fManager, currScene, sceneComp.makePhongIntegrator(&currScene) , 1, 7);
    controller.render();
    fManager->writeToFileInt();

    delete renderCam;
}
int main() {

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = std::chrono::high_resolution_clock::now();
//    diffuse("diffuse.ppm");
    auto t2 = std::chrono::high_resolution_clock::now();
//    std::cout << "diffuse took " << duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << " seconds" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    reflection("reflection.ppm");
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "reflection took " << duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << " seconds" << endl;

//    t1 = std::chrono::high_resolution_clock::now();
//    fun("personal.ppm");
//    t2 = std::chrono::high_resolution_clock::now();
//    std::cout << "personal took " << duration_cast<milliseconds>(t2 - t1).count() / 1000.0 << " seconds" << endl;

//    #define PI 3.14159265
//
//    Vec3 I(1, -1, 0);
//    I.normalize();
//    Vec3 n(0, 1, 0);
//    n.normalize();
//
//    double nit = 1.0/1.5;
//    double theta = acos((I*-1).dot(n));
//    std::cout << "theta:" << theta * 180.0 / PI << endl;
//    Vec3 T = I*nit;
//    double a = nit*cos(theta);
//    double b = sqrt(1 + pow(nit, 2)* (pow(cos(theta), 2) - 1));
//    T += n * (a - b);
//    std::cout << T.x << " " << T.y << " " << T.z << endl;
//    Vec3 tRayDir =

    return 0;
}
