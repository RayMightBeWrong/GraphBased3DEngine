#ifndef PLANO_H
#define PLANO_H
#include "Modelo.h"

namespace Modelos
{
    class Plano : public Modelo
{
public:
    float tamanho;
    float subDivisions;

    Plano(float l,float sub);
    void saveModel(std::ofstream &file);
private:
    void savePlaneTXZ(float y,std::ofstream &file);
};
}

#endif