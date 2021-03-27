#ifndef _FLC_H_
#define _FLC_H_

#include <string.h>
#include <omnetpp.h>
#include <set>
#include <string>
#include <iostream>

#include "../src/Queue.h"
#include "../src/Sink.h"
#include "../scheduler/WRRFLCScheduler.h"

#include "Matrix.h"
#include "Term.h"

using namespace std;
using namespace omnetpp;

#define MAX_NR_TERMS 16
#define MAX_NR_INP 20

class FLC : public cSimpleModule
{
    public:
        ~FLC();
        int fuzzy_inference(int *inp, int nb_inp, int delta);

    private:
        int bits_n;  /* number of binary vectors representing a membership function */
        int bits_m;  /* number of bits in each vector */
        int n_inp;   /* number of inputs */
        int n_rules; /* number of rules */
        int nb_terms[MAX_NR_INP + 1];
        Term *m_functions[MAX_NR_INP + 1][MAX_NR_TERMS]; /* membership functions for input and output*/
        int **rules;
        cOutVector qtime, qtimew;
        cOutVector res_dep, result_dep;

        Matrix *fuzzify(int crisp_in, int delta);
        int defuzify(Matrix *mat);
        double scale(double n, double m, double a, double b, double x);

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif
