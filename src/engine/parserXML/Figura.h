#ifndef Modelo_H
#define Modelo_H
#include <vector>
#include <string>
#include "Cor.h"

class Figura {
    public:
        std::string modelName;
        std::string textureName;
        Cor corFigura;
        unsigned int textureBuffer;
        Figura(std::string model,std::string text,Cor cor);
};

#endif