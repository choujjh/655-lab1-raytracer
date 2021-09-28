//
// Created by chouj on 9/27/2021.
//

#include <cmath>
#include <algorithm>
#include <AxisAlignBox.h>
#include "MediumSplit.h"

Vec3 MediumSplit::getIntersect(Ray currRay, bool closest, Object *&object) {
    return traverseTree(currRay, closest, object, root);
}
Vec3 MediumSplit::traverseTree(Ray currRay, bool closest, Object *&object, IntersectTreeNode* node){
    //if its a leaf
    if(node->isLeaf()){
        Vec3 objMin(VAL_INFINITY, VAL_INFINITY, VAL_INFINITY);
        for(int i = 0; i < node->objects.size(); ++i){
            Vec3 objIntersect = node->objects.at(i)->intersect(currRay);
            if(!objIntersect.isNan()) {
                if (!closest && objIntersect.getMagnitude() != VAL_INFINITY &&
                    objIntersect.getMagnitude() != NEG_INFINITY) {
                    object = node->objects.at(i);
                    return objIntersect;
                }
                if ((objIntersect - currRay.point).getMagnitude() < (objMin - currRay.point).getMagnitude()) {
                    objMin = objIntersect;
                    object = node->objects.at(i);
                }
            }
        }
        return objMin;
    }
    //if it intersects the bounding box
    Vec3 nodeIntersectPoint = node->intersectObject->intersect(currRay);
    if(!nodeIntersectPoint.isNan() && nodeIntersectPoint.getMagnitude() != VAL_INFINITY && nodeIntersectPoint.getMagnitude() != NEG_INFINITY){
        Object* rightObject;
        Object* leftObject;
        Vec3 rightIntersect = traverseTree(currRay, closest, rightObject, node->right);
        Vec3 leftIntersect = traverseTree(currRay, closest, leftObject, node->left);
        if((rightIntersect - currRay.point).getMagnitude() < (leftIntersect - currRay.point).getMagnitude()){
            object = rightObject;
            return rightIntersect;
        }
        object = leftObject;
        return leftIntersect;
        //get the
    }
    //if it doesnt intersect the bounding box
    return object->infiniteVec3();
}


void MediumSplit::optimize() {
    Vec3 max(NEG_INFINITY, NEG_INFINITY, NEG_INFINITY);
    Vec3 min(VAL_INFINITY, VAL_INFINITY, VAL_INFINITY);
    for(int i = 0; i < objList.size(); ++i){
        if(max.x < objList.at(i)->maxVals.x) max.x = objList.at(i)->maxVals.x;
        if(max.y < objList.at(i)->maxVals.y) max.y = objList.at(i)->maxVals.y;
        if(max.z < objList.at(i)->maxVals.z) max.z = objList.at(i)->maxVals.z;

        if(min.x > objList.at(i)->minVals.x) min.x = objList.at(i)->minVals.x;
        if(min.y > objList.at(i)->minVals.y) min.y = objList.at(i)->minVals.y;
        if(min.z > objList.at(i)->minVals.z) min.z = objList.at(i)->minVals.z;
    }
    max.calcMagnitude();
    min.calcMagnitude();
    vector<int> axisOrder(3);
    axisOrder.at(0) = X_Axis;
    double xWidth = fabs(max.x - min.x);
    double yWidth = fabs(max.y - min.y);
    double zWidth = fabs(max.z - min.z);
    vector<double> axisSort{xWidth, yWidth, zWidth};
    for(int i = 0; i < axisOrder.size(); ++i){
        double maxVal = NEG_INFINITY;
        int saveIndex = 0;
        for(int j = 0; j < axisSort.size(); ++j){
            if(axisSort.at(j) > maxVal) {
                maxVal = axisSort.at(j);
                saveIndex = j;
            }
        }
        axisOrder.at(i) = saveIndex;
        axisSort.at(saveIndex) = NEG_INFINITY;
    }
    root = generateTree(0, objList, min, max, axisOrder);
}

MediumSplit::~MediumSplit() {
    for(auto node:nodeList){
        if(node->intersectObject != nullptr){
            delete node->intersectObject;
        }
        delete node;
    }
}

IntersectTreeNode* MediumSplit::generateTree(int depth, vector<Object*> objects, Vec3 min, Vec3 max, vector<int> axisOrder){
    nodeList.push_back(new IntersectTreeNode(nullptr, nullptr, nullptr));
    IntersectTreeNode* currNode = nodeList.at(nodeList.size() - 1);
    if(depth > levSubdivision || objects.size() <= ObjectPerLeaf){
        for(auto object: objects){
            currNode->addObject(object);
        }
        return currNode;
    }
    currNode->intersectObject = new AxisAlignBox(nullptr, max, min);
    Vec3 newMax;
    Vec3 newMin;
    double newLimit = 0.0;
    vector<Object*> childLessThan;
    vector<Object*> childGreaterThan;
    switch(axisOrder.at(depth % axisOrder.size())){
        case X_Axis:
            newLimit = min.x + (max.x - min.x)/2.0;
            newMax = Vec3(newLimit, max.y, max.z);
            newMin = Vec3(newLimit, min.y, min.z);
            for(int i = 0; i < objects.size(); ++i){
                if(objects.at(i)->maxVals.x > newLimit){
                    childGreaterThan.push_back(objects.at(i));
                }
                if(objects.at(i)->minVals.x < newLimit){
                    childLessThan.push_back(objects.at(i));
                }
            }
            break;
        case Y_Axis:
            newLimit = min.y + (max.y - min.y)/2.0;
            newMax = Vec3(max.x, newLimit, max.z);
            newMin = Vec3(min.x, newLimit, min.z);
            for(int i = 0; i < objects.size(); ++i){
                if(objects.at(i)->maxVals.y > newLimit){
                    childGreaterThan.push_back(objects.at(i));
                }
                if(objects.at(i)->minVals.y < newLimit){
                    childLessThan.push_back(objects.at(i));
                }
            }
            break;
        case Z_Axis:
            newLimit = min.z + (max.z - min.z)/2.0;
            newMax = Vec3(max.x, max.y, newLimit);
            newMin = Vec3(min.x, min.y, newLimit);
            for(int i = 0; i < objects.size(); ++i){
                if(objects.at(i)->maxVals.z > newLimit){
                    childGreaterThan.push_back(objects.at(i));
                }
                if(objects.at(i)->minVals.z < newLimit){
                    childLessThan.push_back(objects.at(i));
                }
            }
            break;
    }
    currNode->right = generateTree(depth + 1, childGreaterThan, newMin, max, axisOrder);
    currNode->left = generateTree(depth + 1, childLessThan, min, newMax, axisOrder);
    return currNode;
}

MediumSplit::MediumSplit(int levSubdivision, int objectPerSub) : levSubdivision(levSubdivision), ObjectPerLeaf(objectPerSub) {}
