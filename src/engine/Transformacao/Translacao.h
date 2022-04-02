#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "Transformacao.h"

class Translacao : public Transformacao {
    public:
        float x;
        float y;
        float z;
        Translacao(float x1,float y1,float z1);
        void apply();
};

#endif
