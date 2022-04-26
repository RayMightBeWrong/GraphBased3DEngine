#include "RotacaoEstatica.h"

RotacaoEstatica::RotacaoEstatica(float deg,float x1,float y1,float z1) {
    x = x1;
    y = y1;
    z = z1;
    angulo = deg;
}

void RotacaoEstatica::apply() {
    glRotatef(angulo,x,y,z);
}
