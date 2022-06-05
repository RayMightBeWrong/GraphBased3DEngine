#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

class Transformacao {
    public:
        virtual void apply(float time, int option) = 0;
};
#endif