//
// Created by chouj on 9/6/2021.
//

#ifndef RAYTRACER_CLASSCREATOR_H
#define RAYTRACER_CLASSCREATOR_H

#include <vector>
#include "../Render/IntersectMethods/MediumSplit.h"
#include "../Render/IntersectMethods/BruteForce.h"
#include "MaterialComponent/MatComponent.h"
#include "MaterialComponent/MatCompSolid.h"
#include "MaterialComponent/MatCompFileV3.h"

#include "../Scene/RenderObj/Object.h"
#include "../Scene/RenderObj/Triangle.h"
#include "../Scene/RenderObj/Sphere.h"
#include "../Scene/RenderObj/AxisAlignBox.h"

#include "../Scene/RenderObj/Light/Light.h"
#include "../Scene/RenderObj/Light/AmbientLight.h"
#include "../Scene/RenderObj/Light/DirectionLight.h"
#include "../Scene/RenderObj/Light/PointLight.h"
#include "File/ImageFile.h"
#include "File/Writer/PPMFileWriter.h"
#include "../Render/Integrator.h"
#include "../Render/Phong.h"
#include "../Render/PathTracer.h"


using std::vector;
class RenderCompCreator {
private:
    vector<MatComponent<double>*> matCompDoubles;
    vector<MatComponent<Vec3>*> matCompVec3;
    vector<ImageFile*> fileManagers;
    vector<Integrator*> integrators;
    vector<ObjTracker*> objTracker;
    vector<BaseMaterial*> materials;
    vector<Object*> objects;
public:


    RenderCompCreator();

    ~RenderCompCreator();

    MatComponent<double>* makeMatSolidD(double val){
        MatComponent<double>* t = new MatCompSolid<double>(val);// = new MatCompSolid<double>(val);
        matCompDoubles.push_back(t);
        return t;
    }
    MatComponent<Vec3>* makeMatSolidV3(double r, double g, double b, bool normalizeSum = false){
        MatComponent<Vec3>* tempMatComp = new MatCompSolidV3(Vec3(r, g, b), normalizeSum);
        matCompVec3.push_back(tempMatComp);
        return tempMatComp;
    }
    MatComponent<Vec3>* makeMatSolidV3(const Vec3 &vec, bool normalizeSum = false){
        MatComponent<Vec3>* tempMatComp = new MatCompSolidV3(vec, normalizeSum);
        matCompVec3.push_back(tempMatComp);
        return tempMatComp;
    }
    MatComponent<Vec3>* makeMatFileV3(string file, bool normalizeSum = false){
        MatComponent<Vec3>* tempMatComp = new MatCompFileV3(file, normalizeSum);
        matCompVec3.push_back(tempMatComp);
        return tempMatComp;
    }

    Object* makeTriangle(BaseMaterial *objMat, const Vec3 &a, const Vec3 &b, const Vec3 &c){
        Object* tempObject = new Triangle(objMat, a, b, c);
        objects.push_back(tempObject);
        return tempObject;
    }
    Object* makeTriangle(BaseMaterial *objMat, const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec2 &aUv, const Vec2 &bUv, const Vec2 &cUv){
        Object* tempObject = new Triangle(objMat, a, b, c, aUv, bUv, cUv);
        objects.push_back(tempObject);
        return tempObject;
    }
    Object* makeSphere(BaseMaterial *objMat, const Vec3 &center, double radius){
        Object* tempObject = new Sphere(objMat, center, radius);
        objects.push_back(tempObject);
        return tempObject;
    }
    Object* makeAxisAlignBox(BaseMaterial *objMat, const Vec3 &maxVals, const Vec3 &minVals){
        Object* tempObject = new AxisAlignBox(objMat, maxVals, minVals);
        objects.push_back(tempObject);
        return tempObject;
    }

    Light* makeAmbientLight(BaseMaterial* material){
        Light* tempLight = new AmbientLight(material);
        objects.push_back(tempLight);
        return tempLight;
    }
    Light* makeDirectionLight(BaseMaterial* material, const Vec3 &dir){
        Light* tempLight = new DirectionLight(material, dir);
        objects.push_back(tempLight);
        return tempLight;
    }
    Light* makePointLight(BaseMaterial* material, const Vec3 &position){
        Light* tempLight = new PointLight(material, position);
        objects.push_back(tempLight);
        return tempLight;
    }

    BaseMaterial* makeLightMaterial(MatComponent<Vec3>* color, MatComponent<Vec3>* gamma){
        MatComponent<Vec3>* tempVec3 = makeMatSolidV3(0, 0, 0);
        MatComponent<double>* tempDoub = makeMatSolidD(0.0);
        BaseMaterial* tempMaterial = new BaseMaterial(
                tempVec3, tempVec3, color, gamma);
        materials.push_back(tempMaterial);
        return tempMaterial;
    }

    ImageFile* makeImageFile(unsigned int height, unsigned int width){
        ImageFile* tempManager = new ImageFile(height, width);
        fileManagers.push_back(tempManager);
        return tempManager;
    }
    Integrator* makePhongIntegrator(Scene* scene){
        Integrator* tempIntegrator = new Phong(scene);
        integrators.push_back(tempIntegrator);
        return tempIntegrator;
    }
    Integrator* makePathTracerIntegrator(Scene* scene){
        Integrator* tempIntegrator = new PathTracer(scene);
        integrators.push_back(tempIntegrator);
        return tempIntegrator;
    }
    ObjTracker* makeBruteForceTracker(){
        ObjTracker* tempSceneIntersect = new BruteForce();
        objTracker.push_back(tempSceneIntersect);
        return tempSceneIntersect;
    }
    ObjTracker* makeMediumSplitTracker(int levSubdivision, int objectPerLeaf){
        ObjTracker* tempSceneIntersect= new MediumSplit(levSubdivision, objectPerLeaf);
        objTracker.push_back(tempSceneIntersect);
        return tempSceneIntersect;
    }

};


#endif //RAYTRACER_CLASSCREATOR_H
