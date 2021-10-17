#include <iostream>
#include <chrono>
#include <RenderOps.h>

#include "Render/RenderController.h"
#include "Model/RenderCompCreator.h"

/*TODO:
 * path tracing
 * medium split to do width
 * kd trees
 * salmon goldsmith algorithm
 * uv normal maps
 * ppm file reader (faster)
 * obj parser
 * scene parser
 * */

using std::string;
using std::vector;

//void diffuse(string outFile){
//    RenderCompCreator sceneComp;
//
//    /**setting up camera**/
//    Vec3 cameraLookAt(0, 0, 0.0);
//    Vec3 cameraLookFrom(0, 0.5, 1);
//    Vec3 up(0, 1, 0);
//    double fov = 28.0;
//    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
//
//    /**setting up Scene**/
//    Vec3 backColor(0.2, 0.2, 0.2);
//
//    Scene currScene(renderCam, backColor, sceneComp.makeBruteForceTracker());
//
//    /**objects**/
//    BaseMaterial MSphere1(sceneComp.makeMatSolidD(0.8),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(4),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(1, 1, 1),
//                          sceneComp.makeMatSolidV3(1.0, 1, 1.0),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere1, Vec3(0.35, 0, -0.1), 0.05));
//
//    BaseMaterial MSphere2(sceneComp.makeMatSolidD(0.3),
//                          sceneComp.makeMatSolidD(0.6),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(32),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(1, 0, 0),
//                          sceneComp.makeMatSolidV3(0.5, 1, 0.5),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere2, Vec3(0.2, 0, -0.1), 0.075));
//
//    BaseMaterial MSphere3(sceneComp.makeMatSolidD(0.4),
//                          sceneComp.makeMatSolidD(0.5),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(32),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(0, 1, 0),
//                          sceneComp.makeMatSolidV3(0.5, 1, 0.5),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere3, Vec3(-0.6, 0, 0), 0.3));
//
//    BaseMaterial MTriangle1(sceneComp.makeMatSolidD(0.7),
//                            sceneComp.makeMatSolidD(0.2),
//                            sceneComp.makeMatSolidD(0.1),
//                            sceneComp.makeMatSolidD(32),
//                            sceneComp.makeMatSolidD(1.0),
//                            sceneComp.makeMatSolidD(0.0),
//                            sceneComp.makeMatSolidV3(0, 0, 1.0),
//                            sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
//                            sceneComp.makeMatSolidV3(Vec3()));
//    Vec3 a(0.3, -0.3, -0.4);
//    Vec3 b(0.0, 0.3, -0.1);
//    Vec3 c(-0.3, -0.3, 0.2);
//    currScene.addObject(sceneComp.makeTriangle(&MTriangle1, a, b, c));
//
//    BaseMaterial MTriangle2(sceneComp.makeMatSolidD(0.9),
//                            sceneComp.makeMatSolidD(0.0),
//                            sceneComp.makeMatSolidD(0.1),
//                            sceneComp.makeMatSolidD(4),
//                            sceneComp.makeMatSolidD(1.0),
//                            sceneComp.makeMatSolidD(0.0),
//                            sceneComp.makeMatSolidV3(1, 1, 0),
//                            sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
//                            sceneComp.makeMatSolidV3(Vec3()));
//    a = Vec3(-0.2, 0.1, 0.1);
//    b = Vec3(-0.2, -0.5, 0.2);
//    c = Vec3(-0.2, 0.1, -0.3);
//    currScene.addObject((sceneComp.makeTriangle(&MTriangle2, a, b, c)));
//
//    /**lights**/
//    currScene.addObject(sceneComp.makeDirectionLight(sceneComp.makeLightMaterial(sceneComp.makeMatSolidV3(1.0, 1.0, 1.0)), Vec3(-1.0, 0.0, 0.0)));
//    currScene.addObject(sceneComp.makeAmbientLight(sceneComp.makeLightMaterial(sceneComp.makeMatSolidV3(0.2, 0.2, 0.2))));
//
//
//    /**File**/
//    ImageFile* imageFile = sceneComp.makeImageFile(renderCam->getHeight(), renderCam->getWidth());
//
//
//    RenderController controller(imageFile, currScene, sceneComp.makePhongIntegrator(&currScene), 1, 1);
//    controller.render();
//    imageFile->writeToFile(outFile, WRITE_PPM);
//
//    delete renderCam;
//}
//
//void fun(string outFile){
//    RenderCompCreator sceneComp;
//
//    /**setting up camera**/
//    Vec3 cameraLookAt(0, 0, 0.0);
//    Vec3 cameraLookFrom(0.1, 0.1, 1.2);
//    Vec3 up(0, 1, 0);
//    double fov = 55.0;
//    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);
//
//    /**setting up Scene**/
//    Vec3 backColor(0.2, 0.2, 0.2);
//    Scene currScene(renderCam, backColor, sceneComp.makeBruteForceTracker());
//
//    /**objects**/
//    BaseMaterial MSphere1(sceneComp.makeMatSolidD(0.2),
//                          sceneComp.makeMatSolidD(0.8),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(4),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(1, 1, 0),
//                          sceneComp.makeMatSolidV3(1.0, 1, 0.0),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere1, Vec3(0.35, 0, -0.1), 0.3));
//
//    BaseMaterial MSphere2(sceneComp.makeMatSolidD(0.8),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(4),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(1, 1, 1),
//                          sceneComp.makeMatSolidV3(1.0, 1, 1),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere2, Vec3(-0.3, 0.3, -0.1), 0.1));
//
//    BaseMaterial MSphere3(sceneComp.makeMatSolidD(0.8),
//                          sceneComp.makeMatSolidD(0.2),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(4),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(1, 1, 1),
//                          sceneComp.makeMatSolidV3(1.0, 1, 1.0),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere3, Vec3(-0.3, -0.1, -0.1), 0.15));
//
//    BaseMaterial MSphere4(sceneComp.makeMatSolidD(0.8),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(0.1),
//                          sceneComp.makeMatSolidD(4),
//                          sceneComp.makeMatSolidD(1.0),
//                          sceneComp.makeMatSolidD(0.0),
//                          sceneComp.makeMatSolidV3(1, 1, 1),
//                          sceneComp.makeMatSolidV3(1, 1, 1),
//                          sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeSphere(&MSphere4, Vec3(0.0, 0.3, 0.0), 0.25));
//
//    BaseMaterial MPlane1(sceneComp.makeMatSolidD(0.6),
//                         sceneComp.makeMatSolidD(0.3),
//                         sceneComp.makeMatSolidD(0.1),
//                         sceneComp.makeMatSolidD(4),
//                         sceneComp.makeMatSolidD(1.0),
//                         sceneComp.makeMatSolidD(0.0),
//                         sceneComp.makeMatSolidV3(0.5, 0.5, 0.5),
//                         sceneComp.makeMatSolidV3(1.0, 1, 1.0),
//                         sceneComp.makeMatSolidV3(Vec3()));
//    currScene.addObject(sceneComp.makeAxisAlignBox(&MPlane1, Vec3(4.0, 0.0, 4.0), Vec3(-4.0, -1.0, -4.0)));
//
//    BaseMaterial MTriangle1(sceneComp.makeMatSolidD(0.6),
//                            sceneComp.makeMatSolidD(0.3),
//                            sceneComp.makeMatSolidD(0.1),
//                            sceneComp.makeMatSolidD(4),
//                            sceneComp.makeMatSolidD(1.0),
//                            sceneComp.makeMatSolidD(0.0),
//                            sceneComp.makeMatSolidV3(0, 0.5, 0.5),
//                            sceneComp.makeMatSolidV3(1.0, 1, 1.0),
//                            sceneComp.makeMatSolidV3(Vec3()));
//    Vec3 a(0.0, 0.0, -2.5);
//    Vec3 b(-0.5, 2.0, -0.5);
//    Vec3 c(-0.5, 0.3, 0.5);
//    currScene.addObject(sceneComp.makeTriangle(&MTriangle1, a, b, c));
//
//    /**lights**/
//    currScene.addObject(sceneComp.makeDirectionLight(sceneComp.makeLightMaterial(sceneComp.makeMatSolidV3(1.0, 0.0, 0.0)), Vec3(-1.0, -1.0, 0.0)));
//    currScene.addObject(sceneComp.makeDirectionLight(sceneComp.makeLightMaterial(sceneComp.makeMatSolidV3(0.0, 0.20, 0.70)), Vec3(-0.1, -1.0, 0.0)));
//    currScene.addObject(sceneComp.makeAmbientLight(sceneComp.makeLightMaterial(sceneComp.makeMatSolidV3(0.1, 0.1, 0.1))));
//
//    /**File**/
//    ImageFile* imageFile = sceneComp.makeImageFile(renderCam->getHeight(), renderCam->getWidth());
//
//    RenderController controller(imageFile, currScene, sceneComp.makePhongIntegrator(&currScene), 2, 7);
//    controller.render();
//    imageFile->writeToFile(outFile, WRITE_PPM);
//
//    delete renderCam;
//}

void reflection(string outFile){
    RenderCompCreator sceneComp;

    /**setting up camera**/
    Vec3 cameraLookAt(0, 0.15, 0.0);
//    Vec3 cameraLookFrom(0, 1.5, 1.7);
    Vec3 cameraLookFrom(0, 0.3, 2.3);
    Vec3 up(0, 1, 0);
    double fov = 40.0;
    Cam* renderCam = new Cam(cameraLookFrom, cameraLookAt, up, fov, 512, 512);

    /**setting up Scene**/
    Vec3 backColor(0.1, 0.8, 0.8);
//    Scene currScene(renderCam, backColor, sceneComp.makeMediumSplitTracker(6, 3));
    Scene currScene(renderCam, backColor, sceneComp.makeBruteForceTracker());

    /**setting up objects**/
    BaseMaterial MSphere1(sceneComp.makeMatSolidV3(0.0, 0.0, 1.0, true),
                          sceneComp.makeMatSolidV3(0.0, 0.0, 0.1),
                          sceneComp.makeMatSolidV3(1.0, 1.0, 1.0),
//                          sceneComp.makeMatSolidV3(0.4941, 0.97647, 1.0),
//                          sceneComp.makeMatFileV3("1_test.ppm"),
                          sceneComp.makeMatSolidV3(4, 1.5, 0));
    Vec3 a = Vec3(-0.5, 0.05, 0.2);
    Vec3 b = Vec3(0.5, 0.05, 0.2);
    Vec3 c = Vec3(0, 0.6, -0.3);
    Vec2 aUv = Vec2(-0.2, 0);
    Vec2 bUv = Vec2(1.2, 0);
    Vec2 cUv = Vec2(0.5, 1.5);
//    currScene.addObject(sceneComp.makeTriangle(&MSphere1, a, b, c/*, aUv, bUv, cUv*/));
    currScene.addObject(sceneComp.makeSphere(&MSphere1, Vec3(0, 0.35, 0), 0.3));

    BaseMaterial MBox1(sceneComp.makeMatSolidV3(1, 0.0, 0.0, true),
                         sceneComp.makeMatSolidV3(0.0, 0.2, 0.0),
                         sceneComp.makeMatSolidV3(0.3, 0.3, 0.9),
                         sceneComp.makeMatSolidV3(4, 1.5, 0));
    BaseMaterial MBox2(sceneComp.makeMatSolidV3(1.0, 0.0, 0.0),
                       sceneComp.makeMatSolidV3(0.0, 0.2, 0.0),
                       sceneComp.makeMatSolidV3(1, 1, 1),
                       sceneComp.makeMatSolidV3(4, 1.5, 0));
    Vec3 max = Vec3(3, 0, 3);
    Vec3 min = Vec3(0, -3, 0);

    currScene.addObject(sceneComp.makeAxisAlignBox(&MBox1, max, min));
    currScene.addObject(sceneComp.makeAxisAlignBox(&MBox1, max * -1, min));
    max = Vec3(3, 0, -3);
    currScene.addObject(sceneComp.makeAxisAlignBox(&MBox2, max, min));
    currScene.addObject(sceneComp.makeAxisAlignBox(&MBox2, max * -1, min));

//    currScene.addObject(sceneComp.makeSphere(sceneComp.makeLightMaterial(sceneComp.makeMatSolidV3(1, 1, 1),sceneComp.makeMatSolidV3(0, 0, 1.0)), Vec3(-2.3, 2.35, 2.5), 0.7));
    currScene.addObject(sceneComp.makeSphere(sceneComp.makeLightMaterial(sceneComp.makeMatFileV3("1_test.ppm"), sceneComp.makeMatSolidV3(0, 0, 1.0)), Vec3(0, 0, 0), 3000));

    /**lights**/

    /**File**/
    ImageFile* imageFile = sceneComp.makeImageFile(renderCam->getHeight(), renderCam->getWidth());

    RenderController controller(imageFile, currScene, sceneComp.makePhongIntegrator(&currScene), 35, 7);
    controller.render();
    imageFile->writeToFile(outFile, WRITE_PPM);

    delete renderCam;
}
int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
//
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

    return 0;
}
