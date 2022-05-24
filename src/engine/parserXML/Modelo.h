#ifndef Modelo_H
#define Modelo_H
#include <vector>
#include <string>
#include "Cor.h"

class Modelo {
    public:
        std::string modelName;
        std::string textureName;
        Cor corModelo;
        Modelo(std::string model,std::string text,Cor cor);
};

#endif