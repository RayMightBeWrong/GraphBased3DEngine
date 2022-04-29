#ifndef ESCALA_H
#define ESCALA_H
#include "Transformacao.h"

class Escala : public Transformacao {
    public:
        float x;
        float y;
        float z;
        Escala(float x1,float y1,float z1);
        void apply(float time);
};
#endif