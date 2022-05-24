#ifndef GRUPO_H
#define GRUPO_H
#include <vector>
#include <string>
#include "Modelo.h"
#include "Transformacao/Transformacao.h"
#include "Transformacao/TranslacaoEstatica.h"
#include "Transformacao/TranslacaoTemporizada.h"
#include "Transformacao/RotacaoTemporizada.h"
#include "Transformacao/RotacaoEstatica.h"
#include "Transformacao/Escala.h"

class Grupo {
    public:
        std::vector<Transformacao*> transformacoes;
        std::vector<Modelo> modelos;
        std::vector<Grupo> subgrupos;
        std::vector<GLuint> modelsIndex;
};

#endif