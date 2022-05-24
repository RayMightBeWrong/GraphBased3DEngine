#include "LuzSpot.h"
#include <iostream>

LuzSpot::LuzSpot(float x1,float y1,float z1,float x2,float y2,float z2,float cut) {
    px = x1;
    py = y1;
    pz = z1;
    dx = x2;
    dy = y2;
    dz = z2;
    cutoff = cut;
}

void LuzSpot::apply(int i) {
    float diretion[3] = {dx,dy,dz};
    float pos[4] = {px,py,pz,1.0};
    
    if (i == 0) {
        glLightfv(GL_LIGHT0,GL_POSITION,pos);
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 1) {
        glLightfv(GL_LIGHT1,GL_POSITION,pos);
        glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 2) {
        glLightfv(GL_LIGHT2,GL_POSITION,pos);
        glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 3) {
        glLightfv(GL_LIGHT3,GL_POSITION,pos);
        glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 4) {
        glLightfv(GL_LIGHT4,GL_POSITION,pos);
        glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT4,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 5) {
        glLightfv(GL_LIGHT5,GL_POSITION,pos);
        glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT5,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 6) {
        glLightfv(GL_LIGHT6,GL_POSITION,pos);
        glLightfv(GL_LIGHT6,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT6,GL_SPOT_CUTOFF,cutoff);
    }
    if (i == 7) {
        glLightfv(GL_LIGHT7,GL_POSITION,pos);
        glLightfv(GL_LIGHT7,GL_SPOT_DIRECTION,diretion);
        glLightf(GL_LIGHT7,GL_SPOT_CUTOFF,cutoff);
    }

}