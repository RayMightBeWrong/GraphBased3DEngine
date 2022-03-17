#ifndef GRUPO_H
#define GRUPO_H
#include <vector>
#include <string>
#include "Transformacao/Transformacao.h"
#include "Transformacao/Translacao.h"
#include "Transformacao/Rotacao.h"
#include "Transformacao/Escala.h"

class Grupo {
    public:
        std::vector<Transformacao*> transformacoes;
        std::vector<std::string> modelos;
        std::vector<Grupo> subgrupos;
        std::vector<GLuint> modelsIndex;
    private:
        void aplicarTransformacoes();
};

#endif