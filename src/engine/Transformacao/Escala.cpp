#include "Escala.h"

Escala::Escala(float x1,float y1,float z1) {
    x = x1;
    y = y1;
    z = z1;
}

void Escala::apply() {
    glScalef(x,y,z);
}

void Escala::print() {
    std::cout << x << y << z << std::endl;
}