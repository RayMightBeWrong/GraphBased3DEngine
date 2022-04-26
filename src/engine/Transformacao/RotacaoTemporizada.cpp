#include "RotacaoTemporizada.h"

RotacaoTemporizada::RotacaoTemporizada(float t,float x1,float y1,float z1){
    time = t;
    x = x1;
    y = y1;
    z = z1;
}

void RotacaoTemporizada::apply() {
    std::cout << "Rotacao temporizada" << std::endl;
}