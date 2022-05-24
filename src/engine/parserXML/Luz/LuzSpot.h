#ifndef LUZSPOT_H
#define LUZSPOT_H
#include "Luz.h"

class LuzSpot : public Luz {
    public:
        float px;
        float py;
        float pz;
        float dx;
        float dy;
        float dz;
        float cutoff;
        LuzSpot(float px,float py,float pz,float dx,float dy,float dz,float cutoff);
        void apply(int i);

};

#endif