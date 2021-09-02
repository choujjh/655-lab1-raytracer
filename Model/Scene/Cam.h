//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_CAM_H
#define RAYTRACER_CAM_H

#include "../VecModel/Vec.h"

class Cam {
private:
    Vec start;
    Vec incrementX;
    Vec incrementY;
    Vec lookFrom;
    Vec lookAt;
    Vec up;
    double fov;
    double width;
    double height;

public:
    Cam(const Vec &lookFrom, const Vec &lookAt, const Vec &up, double fov, double width, double height);

    const Vec &getStart() const;

    void setStart(const Vec &start);

    const Vec &getIncrementX() const;

    void setIncrementX(const Vec &incrementX);

    const Vec &getIncrementY() const;

    void setIncrementY(const Vec &incrementY);

    const Vec &getLookFrom() const;

    void setLookFrom(const Vec &lookFrom);

    const Vec &getLookAt() const;

    void setLookAt(const Vec &lookAt);

    const Vec &getUp() const;

    void setUp(const Vec &up);

    double getFov() const;

    void setFov(double fov);

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);
};


#endif //RAYTRACER_CAM_H
