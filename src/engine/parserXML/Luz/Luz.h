#ifndef LUZ_H
#define LUZ_H
#include <GL/glew.h>
#include <GL/glut.h>

class Luz {
    public:
        virtual void apply(int i) = 0;
};

#endif