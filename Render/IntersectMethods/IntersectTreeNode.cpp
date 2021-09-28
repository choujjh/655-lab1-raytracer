//
// Created by chouj on 9/27/2021.
//

#include "IntersectTreeNode.h"

IntersectTreeNode::IntersectTreeNode(IntersectTreeNode *left, IntersectTreeNode *right, Object *intersectObject) : left(
        left), right(right), intersectObject(intersectObject) {}

bool IntersectTreeNode::isLeaf(){
    if(right == nullptr && left == nullptr){
        return true;
    }
    if(objects.size() == 0){
        return false;
    }
    if(intersectObject == nullptr){
        return false;
    }
    return true;
}
void IntersectTreeNode::addObject(Object* object){
    objects.push_back(object);
}