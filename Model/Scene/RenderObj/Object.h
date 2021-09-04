//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "../../VecModel/Ray.h"

class Object {
protected:
    double kDiffuse;
    double kSpecular;
    double kAmbient;
    Vec3 colorDiffuse;
    Vec3 colorSpec;
    double kgls;
public:
    Object(double kDiffuse, double kSpecular, double ka, const Vec3 &colorDiffuse, const Vec3 &colorSpec, double kgls);

    Object();

    virtual Vec3 intersect(Ray ray);
    virtual Vec3 normal(Vec3 point) = 0;

    double getKDiffuse() const;
    void setKDiffuse(double kDiffuse);
    double getKSpecular() const;
    void setKSpecular(double kSpecular);
    double getKAmbient() const;
    void setKAmbient(double kAmbient);
    const Vec3 &getColorDiffuse() const;
    void setColorDiffuse(const Vec3 &colorDiffuse);
    const Vec3 &getColorSpec() const;
    void setColorSpec(const Vec3 &colorSpec);
    double getKgls() const;
    void setKgls(double kgls);
};


#endif //RAYTRACER_OBJECT_H
