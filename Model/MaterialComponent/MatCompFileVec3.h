//
// Created by chouj on 9/29/2021.
//

#ifndef INC_655_LAB1_RAYTRACER_MATCOMPFILEVEC3_H
#define INC_655_LAB1_RAYTRACER_MATCOMPFILEVEC3_H

#include <Ops/RenderOps.h>
#include "File/ImageFile.h"
#include "MatComponent.h"
class MatCompFileVec3: public MatComponent<Vec3> {
private:
    ImageFile imageFile;
public:
    MatCompFileVec3(string& textureFile) {
        imageFile.openFile(textureFile);
    }

public:
    Vec3 getColor(double u, double v) override {
        unsigned int pixelRow = v == 1? imageFile.getHeight() - 1: v * imageFile.getHeight();
        unsigned int pixelCol = u == 1? imageFile.getWidth() - 1: u * imageFile.getWidth();
        if(u > 1.0){
            return Vec3(RenderOps().randFloatValue(0.5, 1), 0, 0);
        }
        else if(u < 0.0){
            return Vec3(RenderOps().randFloatValue(0, 0.5), 0, 0);
        }
        else if(v > 1.0){
            return Vec3(0, RenderOps().randFloatValue(0.5, 1), 0);
        }
        else if(v < 0.0){
            return Vec3(0, RenderOps().randFloatValue(0, 0.5), 0);
        }
        Vec3 var = imageFile.getImage()[pixelRow][pixelCol];
        return var; Vec3(u, v, 0);
    }
    Vec3 getColor() override {
        return imageFile.getImage()[0][0];
    }
};


#endif //INC_655_LAB1_RAYTRACER_MATCOMPFILEVEC3_H
