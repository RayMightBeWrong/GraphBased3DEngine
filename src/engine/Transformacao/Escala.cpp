#include "Escala.h"

Escala::Escala(float x1,float y1,float z1) {
    x = x1;
    y = y1;
    z = z1;
}

void Escala::apply(float time) {
    glScalef(x,y,z);
}