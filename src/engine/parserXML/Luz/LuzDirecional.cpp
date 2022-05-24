#include "LuzDirecional.h"


LuzDirecional::LuzDirecional(float x1,float y1,float z1) {
    dx = x1;
    dy = y1;
    dz = z1;
}

void LuzDirecional::apply(int i) {
    float diretion[4] = {dx,dy,dz,0.0};
    float diffuse[4] = {1,1,1,1};
    float spec[4] = {1,1,1,1};

    if (i == 0) {
        glLightfv(GL_LIGHT0,GL_POSITION,diretion);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,spec);
    }
    if (i == 1) {
        glLightfv(GL_LIGHT1,GL_POSITION,diretion);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT1,GL_SPECULAR,spec);
    }
    if (i == 2) {
        glLightfv(GL_LIGHT2,GL_POSITION,diretion);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT2,GL_SPECULAR,spec);
    }
    if (i == 3) {
        glLightfv(GL_LIGHT3,GL_POSITION,diretion);
        glLightfv(GL_LIGHT3,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT3,GL_SPECULAR,spec);
    }
    if (i == 4) {
        glLightfv(GL_LIGHT4,GL_POSITION,diretion);
        glLightfv(GL_LIGHT4,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT4,GL_SPECULAR,spec);
    }
    if (i == 5) {
        glLightfv(GL_LIGHT5,GL_POSITION,diretion);
        glLightfv(GL_LIGHT5,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT5,GL_SPECULAR,spec);
    }
    if (i == 6) {
        glLightfv(GL_LIGHT6,GL_POSITION,diretion);
        glLightfv(GL_LIGHT6,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT6,GL_SPECULAR,spec);
    }
    if (i == 7) {
        glLightfv(GL_LIGHT7,GL_POSITION,diretion);
        glLightfv(GL_LIGHT7,GL_DIFFUSE,diffuse);
        glLightfv(GL_LIGHT7,GL_SPECULAR,spec);
    }

}