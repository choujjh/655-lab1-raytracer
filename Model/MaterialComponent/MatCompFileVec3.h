//
// Created by chouj on 9/29/2021.
//

#ifndef INC_655_LAB1_RAYTRACER_MATCOMPFILEVEC3_H
#define INC_655_LAB1_RAYTRACER_MATCOMPFILEVEC3_H

#include <Ops/RenderOps.h>
#include <cmath>
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
        // getting tiling textures
        if(u == 1.0) u = 0.999;
        if(v == 1.0) v = 0.999;
        u = fmod(u, 1.0);
        v = fmod(v, 1.0);
        if(u < 0.0) u = 1 + u;
        if(v < 0.0) v = 1 + v;

        unsigned int pixelRow = v * imageFile.getHeight();
        unsigned int pixelCol = u * imageFile.getWidth();

        Vec3 var = imageFile.getImage()[pixelRow][pixelCol];
        return var;
    }
    Vec3 getColor() override {
        return imageFile.getImage()[0][0];
    }
};


#endif //INC_655_LAB1_RAYTRACER_MATCOMPFILEVEC3_H
