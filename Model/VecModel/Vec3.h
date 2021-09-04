//
// Created by chouj on 3/5/2021.
//

#ifndef RAYTRACER_VEC_H
#define RAYTRACER_VEC_H
#include <vector>
using std::vector;


class Vec3 {
private:
    void calcMagnitude();
    double magnitude;
public:
    double x, y, z;

    Vec3();
    Vec3(double first, double second, double third);
    Vec3(const Vec3 &obj);

    Vec3 normalize();
    Vec3 clip(double min, double max);

    double getMagnitude() const;

    Vec3 operator-(Vec3 b);
    Vec3 operator+(Vec3 b);
    Vec3 operator+=(Vec3 b);
    Vec3 operator*(double val);
    Vec3 operator/(double val);
    Vec3 operator*(Vec3 b);
    Vec3 operator/(Vec3 b);
};


#endif //RAYTRACER_VEC_H
