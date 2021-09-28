//
// Created by chouj on 9/27/2021.
//

#ifndef RAYTRACER_MEDIUMSPLIT_H
#define RAYTRACER_MEDIUMSPLIT_H


#include "IntersectTreeNode.h"
#include "ObjTracker.h"

class MediumSplit: public ObjTracker {
private:
    vector<IntersectTreeNode*> nodeList;
protected:
    int levSubdivision;
    int ObjectPerLeaf;
    IntersectTreeNode* root;
public:
    Vec3 getIntersect(Ray currRay, bool closest, Object *&object) override;
    Vec3 traverseTree(Ray currRay, bool closest, Object *&object, IntersectTreeNode* node);

    void optimize() override;

    IntersectTreeNode* generateTree(int depth, vector<Object*> objects, Vec3 min, Vec3 max, vector<int> axisOrder);

    virtual ~MediumSplit();

    MediumSplit(int levSubdivision, int objectPerSub);
};


#endif //RAYTRACER_MEDIUMSPLIT_H
