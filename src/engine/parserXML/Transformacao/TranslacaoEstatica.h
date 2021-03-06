#ifndef TRANSLATEESTATICA_H
#define TRANSLATEESTATICA_H
#include "Transformacao.h"

class TranslacaoEstatica : public Transformacao {
    public:
        float x;
        float y;
        float z;
        TranslacaoEstatica(float x1,float y1,float z1);
        void apply(float time, int option);
    private:
        void buildRotMatrix(float *x, float *y, float *z, float *m);
};

#endif
