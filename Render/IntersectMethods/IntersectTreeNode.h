//
// Created by chouj on 9/27/2021.
//

#ifndef RAYTRACER_INTERSECTTREENODE_H
#define RAYTRACER_INTERSECTTREENODE_H


#include "../../Scene/RenderObj/Object.h"

enum{X_Axis, Y_Axis, Z_Axis};
class IntersectTreeNode {
public:
    IntersectTreeNode* left;
    IntersectTreeNode* right;
    Object* intersectObject;
    vector<Object*> objects;

    IntersectTreeNode(IntersectTreeNode *left, IntersectTreeNode *right, Object *intersectObject);

    bool isLeaf();
    void addObject(Object* object);
};


#endif //RAYTRACER_INTERSECTTREENODE_H
