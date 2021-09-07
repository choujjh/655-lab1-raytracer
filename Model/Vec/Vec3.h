//
// Created by chouj on 3/5/2021.
//

#ifndef RAYTRACER_VEC_H
#define RAYTRACER_VEC_H
#include <vector>
#include <limits>

#ifndef VAL_INFINITY
#define VAL_INFINITY std::numeric_limits<double>::infinity()
#endif

using std::vector;

class Vec3 {
private:
    void calcMagnitude();
    double magnitude;
public:
    double x, y, z;

    Vec3();
    Vec3(double x, double y, double z);
    Vec3(const Vec3 &obj);

    Vec3 normalize();
    Vec3 clip(double min, double max);

    double getMagnitude() const;

    double dot(Vec3 b);
    Vec3 cross(Vec3 b);

    Vec3 operator-(Vec3 b);
    Vec3 operator+(Vec3 b);
    void operator+=(Vec3 b);
    void operator-=(Vec3 b);
    Vec3 operator*(double val);
    Vec3 operator/(double val);
    Vec3 operator*(Vec3 b);
    Vec3 operator/(Vec3 b);
};


#endif //RAYTRACER_VEC_H
