//
// Created by chouj on 10/11/2021.
//

#ifndef RAYTRACER_VEC2_H
#define RAYTRACER_VEC2_H


class Vec2 {
private:
    double magnitude;
public:
    double u, v;
    Vec2();

    Vec2(double u, double v);
    Vec2(const Vec2 &obj);
    void calcMagnitude();

    bool isNan();
    Vec2 normalize();
    Vec2 clip(double min, double max);

    double getMagnitude() const;

    double dot(Vec2 b);

    Vec2 operator-(Vec2 b);
    Vec2 operator+(Vec2 b);
    void operator+=(Vec2 b);
    void operator-=(Vec2 b);
    Vec2 operator*(double val);
    Vec2 operator/(double val);
    Vec2 operator*(Vec2 b);
    Vec2 operator/(Vec2 b);
};


#endif //RAYTRACER_VEC2_H
