#include "TranslacaoTemporizada.h"

TranslacaoTemporizada::TranslacaoTemporizada(float t,bool a,std::vector<float> pontos){
    time = t;
    alinhado = a;
    pontosCurva = pontos;
}

void TranslacaoTemporizada::apply() {
    // Codigo para aplicar a transformaçao
    std::cout << "Translacao temporizada" << std::endl;
    for (int i = 0; i < pontosCurva.size();i = i+3) {
        std::cout << pontosCurva[i] << "; ";
        std::cout << pontosCurva[i+1] << "; ";
        std::cout << pontosCurva[i+2] << "; " << std::endl;
    }
}