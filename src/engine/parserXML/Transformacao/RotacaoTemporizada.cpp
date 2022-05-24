#include "RotacaoTemporizada.h"

RotacaoTemporizada::RotacaoTemporizada(float t,float x1,float y1,float z1){
    tempo = t;
    x = x1;
    y = y1;
    z = z1;
}

void RotacaoTemporizada::apply(float time) {
    float angle = (fmod(time, tempo) / tempo) * 360;
    glRotatef(angle,x,y,z);
}