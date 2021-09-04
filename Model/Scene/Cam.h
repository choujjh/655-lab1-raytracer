//
// Created by chouj on 3/8/2021.
//

#ifndef RAYTRACER_CAM_H
#define RAYTRACER_CAM_H

#include "../VecModel/Vec3.h"

class Cam {
private:
    Vec3 start;
    Vec3 incrementX;
    Vec3 incrementY;
    Vec3 lookFrom;
    Vec3 lookAt;
    Vec3 up;
    double fov;
    double width;
    double height;

public:
    Cam(const Vec3 &lookFrom, const Vec3 &lookAt, const Vec3 &up, double fov, double width, double height);

    const Vec3 &getStart() const;

    void setStart(const Vec3 &start);

    const Vec3 &getIncrementX() const;

    void setIncrementX(const Vec3 &incrementX);

    const Vec3 &getIncrementY() const;

    void setIncrementY(const Vec3 &incrementY);

    const Vec3 &getLookFrom() const;

    void setLookFrom(const Vec3 &lookFrom);

    const Vec3 &getLookAt() const;

    void setLookAt(const Vec3 &lookAt);

    const Vec3 &getUp() const;

    void setUp(const Vec3 &up);

    double getFov() const;

    void setFov(double fov);

    double getWidth() const;

    void setWidth(double width);

    double getHeight() const;

    void setHeight(double height);
};


#endif //RAYTRACER_CAM_H
