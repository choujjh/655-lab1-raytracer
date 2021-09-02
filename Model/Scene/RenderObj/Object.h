//
// Created by chouj on 3/7/2021.
//

#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include "../../VecModel/OffVec.h"

class Object {
protected:
    double kDiffuse;
    double kSpecular;
    double kAmbient;
    Vec colorDiffuse;
    Vec colorSpec;
    double kgls;
public:
    Object(double kDiffuse, double kSpecular, double ka, const Vec &colorDiffuse, const Vec &colorSpec, double kgls);

    Object();

    virtual Vec intersect(OffVec ray);
    virtual Vec normal(Vec point) = 0;

    double getKDiffuse() const;
    void setKDiffuse(double kDiffuse);
    double getKSpecular() const;
    void setKSpecular(double kSpecular);
    double getKAmbient() const;
    void setKAmbient(double kAmbient);
    const Vec &getColorDiffuse() const;
    void setColorDiffuse(const Vec &colorDiffuse);
    const Vec &getColorSpec() const;
    void setColorSpec(const Vec &colorSpec);
    double getKgls() const;
    void setKgls(double kgls);
};


#endif //RAYTRACER_OBJECT_H
