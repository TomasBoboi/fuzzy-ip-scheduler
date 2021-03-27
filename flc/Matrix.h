#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector.h"

class Matrix
{
    public:
        Matrix(int m, int n);
        ~Matrix();
        int get_m() const { return _m; }
        int get_n() const { return _n; }
        void set(int i, int j, int val) { mat[i][j] = val; }
        int get(int i, int j) const { return mat[i][j]; }
        void print();
        void max_column(Vector *v);
        void min_matrix(Matrix *m2, Matrix *result);
        void max_matrix(Matrix *m2, Matrix *result);
        void min_vector(Vector *v, Matrix *result);

    private:
        int _m;
        int _n;
        int **mat;
};

#endif
