#include "TranslacaoEstatica.h"

TranslacaoEstatica::TranslacaoEstatica(float x1,float y1,float z1){
    x = x1;
    y = y1;
    z = z1;
}

void TranslacaoEstatica::apply(float time, int option) {
    glTranslatef(x,y,z);
}
