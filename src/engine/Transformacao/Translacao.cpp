#include "Translacao.h"

Translacao::Translacao(float x1,float y1,float z1){
    x = x1;
    y = y1;
    z = z1;
}

void Translacao::apply() {
    glTranslatef(x,y,z);
}

void Translacao::print() {
    std::cout << x << y << z << std::endl;
}