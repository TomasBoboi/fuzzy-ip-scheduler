#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector
{
    public:
        Vector(int m) : _m(m) { vect = new int[m]; }

        ~Vector() { delete[] vect; }

        int get_m() const { return _m; }

        int get(int j) const { return vect[j]; }

        void set(int pos, int val) { vect[pos] = val; }

        void print();

        void min_vect(Vector *v2, Vector *result);

    private:
        int _m;
        int *vect;
};

#endif
