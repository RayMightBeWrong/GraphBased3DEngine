#include "LuzPosicional.h"
#include <iostream>

LuzPosicional::LuzPosicional(float x1,float y1,float z1) {
    px = x1;
    py = y1;
    pz = z1;
}

void LuzPosicional::apply(int i) {
    float pos[4] = {px,py,pz,1.0};
    float diffuse[4] = {1,1,1,1};
    float spec[4] = {1,1,1,1};

    if (i == 0) {
        glLightfv(GL_LIGHT0,GL_POSITION,pos);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,spec);
    }
    if (i == 1) {
        glLightfv(GL_LIGHT1,GL_POSITION,pos);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT1,GL_SPECULAR,spec);
    }
    if (i == 2) {
        glLightfv(GL_LIGHT2,GL_POSITION,pos);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT2,GL_SPECULAR,spec);
    }
    if (i == 3) {
        glLightfv(GL_LIGHT3,GL_POSITION,pos);
        glLightfv(GL_LIGHT3,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT3,GL_SPECULAR,spec);
    }
    if (i == 4) {
        glLightfv(GL_LIGHT4,GL_POSITION,pos);
        glLightfv(GL_LIGHT4,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT4,GL_SPECULAR,spec);
    }
    if (i == 5) {
        glLightfv(GL_LIGHT5,GL_POSITION,pos);
        glLightfv(GL_LIGHT5,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT5,GL_SPECULAR,spec);
    }
    if (i == 6) {
        glLightfv(GL_LIGHT6,GL_POSITION,pos);
        glLightfv(GL_LIGHT6,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT6,GL_SPECULAR,spec);
    }
    if (i == 7) {
        glLightfv(GL_LIGHT7,GL_POSITION,pos);
        glLightfv(GL_LIGHT7,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT7,GL_SPECULAR,spec);
    }

}