#ifndef ROTACAOESTATICA_H
#define ROTACAOESTATICA_H
#include "Transformacao.h"

class RotacaoEstatica : public Transformacao {
    public:
        float angulo;
        float x;
        float y;
        float z;
        RotacaoEstatica(float deg,float x1,float y1,float z1);
        void apply();
};

#endif