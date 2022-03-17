#ifndef ROTACAO_H
#define ROTACAO_H
#include "Transformacao.h"

class Rotacao : public Transformacao {
    public:
        float angulo;
        float x;
        float y;
        float z;
        Rotacao(float deg,float x1,float y1,float z1);
        void apply();
        void print();
};

#endif