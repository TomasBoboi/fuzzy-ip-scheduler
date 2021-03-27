#ifndef _TERM_H_
#define _TERM_H_

#include "Matrix.h"
#include <iostream>
#include <string>

class Term
{
    public:
        Term(int a, int b, int c, int d, std::string name) : _a(a), _b(b), _c(c), _d(d), _name(name) {}

        ~Term() {}

        std::string getName() const { return _name; }

        int getTermRep(int m, int n, Matrix *mat);

    private:
        std::string _name;
        int _a, _b, _c, _d;
};

#endif
