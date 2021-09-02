//
// Created by chouj on 3/5/2021.
//

#ifndef RAYTRACER_VEC_H
#define RAYTRACER_VEC_H
#include <vector>
using std::vector;


class Vec {
private:
    void calcMagnitude();
    double magnitude;
public:
    vector<double> values{0.0, 0.0, 0.0};

    Vec();
    Vec(double first, double second, double third);
    Vec(const Vec &obj);

    Vec normalize();

    double getMagnitude() const;

    Vec operator-(Vec b);
    Vec operator+(Vec b);
    Vec operator*(double val);
    Vec operator/(double val);
    Vec operator*(Vec b);
    Vec operator/(Vec b);
};


#endif //RAYTRACER_VEC_H
