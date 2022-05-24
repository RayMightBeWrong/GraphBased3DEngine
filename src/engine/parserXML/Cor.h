#ifndef Cor_H
#define Cor_H
#include <GL/glew.h>
#include <GL/glut.h>

class Cor {
    public:
        float *difusa;
        float *ambiente;
        float *especular;
        float *emissive;
        float shininess;
        Cor();
        Cor(float *difusa,
            float *ambiente,
            float *especular,
            float *emissive,
            float shininess);
        void apply();
};

#endif