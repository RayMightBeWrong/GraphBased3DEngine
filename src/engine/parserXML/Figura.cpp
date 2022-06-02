#include "Figura.h"

Figura::Figura(std::string model,std::string text,Cor cor) {
    modelName = model;
    textureName = text;
    corFigura = cor;
    textureBuffer = 0;
}