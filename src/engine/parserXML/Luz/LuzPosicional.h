#ifndef LUZPOS_H
#define LUZPOS_H
#include "Luz.h"

class LuzPosicional : public Luz {
    public:
        float px;
        float py;
        float pz;
        LuzPosicional(float x1,float y1,float z1);
        void apply(int i);

};

#endif