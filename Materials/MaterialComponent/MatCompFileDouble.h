//
// Created by chouj on 10/12/2021.
//

#ifndef RAYTRACER_MATCOMPFILEVEC3_H
#define RAYTRACER_MATCOMPFILEVEC3_H

#include <Ops/RenderOps.h>
#include <cmath>
#include "File/ImageFile.h"
#include "MatComponent.h"
class MatCompFileDouble: public MatComponent<double> {
private:
    ImageFile imageFile;
public:
    MatCompFileDouble(string& textureFile) {
        imageFile.openFile(textureFile);
    }

public:
    double getColor(double u, double v) override {
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
        return var.x;
    }
    double getColor() override {
        return imageFile.getImage()[0][0].x;
    }

    double getColor(Vec2 uv) override {
        return getColor(uv.u, uv.v);
    }
};


#endif //RAYTRACER_MATCOMPFILEVEC3_H

