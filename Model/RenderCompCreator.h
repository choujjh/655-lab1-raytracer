//
// Created by chouj on 9/6/2021.
//

#ifndef RAYTRACER_CLASSCREATOR_H
#define RAYTRACER_CLASSCREATOR_H

#include <vector>
#include "Material/MatComponent.h"
#include "Material/MatCompSolid.h"

#include "../Scene/RenderObj/Object.h"
#include "../Scene/RenderObj/Triangle.h"
#include "../Scene/RenderObj/Sphere.h"

#include "../Scene/Light/Light.h"
#include "../Scene/Light/AmbientLight.h"
#include "../Scene/Light/DirectionLight.h"
#include "File/ImageFileManager.h"
#include "File/PPMFileManager.h"


using std::vector;
class RenderCompCreator {
private:
    vector<MatComponent<double>*> matCompDoubles;
    vector<MatComponent<Vec3>*> matCompVec3;
    vector<ImageFileManager*> fileManagers;
public:
    vector<Object*> objects;
    vector<Light*> lights;

    RenderCompCreator();

    ~RenderCompCreator();

    MatComponent<double>* makeMatSolidD(double val){
        MatCompSolid<double>* t = new MatCompSolid<double>(val);// = new MatCompSolid<double>(val);
        matCompDoubles.push_back(t);
        return t;
    }
    MatComponent<Vec3>* makeMatSolidV3(double r, double g, double b){
        MatCompSolid<Vec3>* tempMatComp = new MatCompSolid<Vec3>(Vec3(r, g, b));
        matCompVec3.push_back(tempMatComp);
        return tempMatComp;
    }
    MatComponent<Vec3>* makeMatSolidV3(const Vec3 &vec){
        MatCompSolid<Vec3>* tempMatComp = new MatCompSolid<Vec3>(vec);
        matCompVec3.push_back(tempMatComp);
        return tempMatComp;
    }
    Object* makeTriangle(Material *objMat, const Vec3 &a, const Vec3 &b, const Vec3 &c){
        Object* tempObject = new Triangle(objMat, a, b, c);
        objects.push_back(tempObject);
        return tempObject;
    }
    Object* makeSphere(Material *objMat, const Vec3 &center, double radius){
        Object* tempObject = new Sphere(objMat, center, radius);
        objects.push_back(tempObject);
        return tempObject;
    }
    Object* makePlane(Material *objMat, const Vec3 &n, double d){
        Object* tempObject = new Plane(objMat, n, d);
        objects.push_back(tempObject);
        return tempObject;
    }
    Light* makeAmbientLight(const Vec3 &color){
        Light* tempLight = new AmbientLight(color);
        lights.push_back(tempLight);
        return tempLight;
    }
    Light* makeDirectionLight(const Vec3 &color, const Vec3 &dir){
        Light* tempLight = new DirectionLight(color, dir);
        lights.push_back(tempLight);
        return tempLight;
    }
    ImageFileManager* makePPMFileManager(const string &fileName, unsigned int height, unsigned int width){
        ImageFileManager* tempManager = new PPMFileManager(fileName, height, width);
        fileManagers.push_back(tempManager);
        return tempManager;
    }


};


#endif //RAYTRACER_CLASSCREATOR_H
