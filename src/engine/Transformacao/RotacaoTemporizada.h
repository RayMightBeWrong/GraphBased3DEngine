#ifndef ROTATETEMPORIZADA_H
#define ROTATETEMPORIZADA_H
#include "Transformacao.h"
#include <vector>

class RotacaoTemporizada : public Transformacao {
    public:
        float time;
        float x;
        float y;
        float z;
        RotacaoTemporizada(float t,float x1,float y1,float z1);
        void apply();
};

#endif