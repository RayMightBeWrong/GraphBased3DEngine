#ifndef PLANO_H
#define PLANO_H
#include "Modelo.h"

namespace Modelos
{
    class Plano : public Modelo
{
public:
    int tamanho;
    float subDivisions;

    Plano(int l,float sub);
    void saveModel(std::ofstream &file);
private:
    void savePlaneTXZ(float y,std::ofstream &file);
};
}

#endif