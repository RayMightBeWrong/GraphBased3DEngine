#ifndef TRANSLATETEMPORIZADA_H
#define TRANSLATETEMPORIZADA_H
#include "Transformacao.h"
#include <math.h>
#include <vector>
#include <cstring>

class TranslacaoTemporizada : public Transformacao {
    public:
        float tempo;
        bool alinhado;
        std::vector<float> pontosCurva;
        int nr_pontos;
        float *prevY;
        TranslacaoTemporizada(float t,bool al,std::vector<float> ps);
        void apply(float time, int option);
    
    private:
        void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
        void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
        void renderCatmullRomCurve();
        void buildRotMatrix(float *x, float *y, float *z, float *m);
        void cross(float *a, float *b, float *res);
        void normalize(float *a);
        void multMatrixVector(float m[4][4], float *v, float *res);
};

#endif