//
// Created by chouj on 9/6/2021.
//

#include "RenderCompCreator.h"

RenderCompCreator::RenderCompCreator() {}

RenderCompCreator::~RenderCompCreator() {
    for(auto curr: objects){
        delete curr;
    }
    for(auto curr: lights){
        delete curr;
    }
    for( auto curr: matCompDoubles){
        delete curr;
    }
    for( auto curr: matCompVec3){
        delete curr;
    }
}
