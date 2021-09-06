//
// Created by chouj on 9/6/2021.
//

#ifndef LAB_1_MATCOMPONENT_H
#define LAB_1_MATCOMPONENT_H

template <class T>
class MatComponent {
public:
    virtual T getColor(double u, double v) = 0;
    virtual T getColor() = 0;
};


#endif //LAB_1_MATCOMPONENT_H
