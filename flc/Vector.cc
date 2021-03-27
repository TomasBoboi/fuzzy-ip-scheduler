#include "Vector.h"
#include <iostream>

void Vector::print()
{
    for (int i = 0; i < _m; i++)
    {
        std::cout << vect[i] << " ";
    }

    std::cout << std::endl;
}

void Vector::min_vect(Vector *v2, Vector *result)
{
    if (v2->_m != this->_m)
    {
        std::cout << "ERROR!!! vectors have different sizes\n";
    }

    for (int i = 0; i < this->_m; i++)
    {
        result->vect[i] = (this->vect[i] <= v2->vect[i]) ? this->vect[i] : v2->vect[i];
    }
}
