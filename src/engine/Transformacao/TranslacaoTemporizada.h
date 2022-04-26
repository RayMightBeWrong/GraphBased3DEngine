#ifndef TRANSLATETEMPORIZADA_H
#define TRANSLATETEMPORIZADA_H
#include "Transformacao.h"
#include <vector>

class TranslacaoTemporizada : public Transformacao {
    public:
        float time;
        bool alinhado;
        std::vector<float> pontosCurva;
        TranslacaoTemporizada(float t,bool al,std::vector<float> ps);
        void apply();
};

#endif