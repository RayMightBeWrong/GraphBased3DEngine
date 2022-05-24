#ifndef LUZDIR_H
#define LUZDIR_H
#include "Luz.h"

class LuzDirecional : public Luz {
    public:
        float dx;
        float dy;
        float dz;
        LuzDirecional(float x1,float y1,float z1);
        void apply(int i);
};

#endif