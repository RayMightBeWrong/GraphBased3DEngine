#ifndef MODELO_H
#define MODELO_H
#include <fstream>

namespace Modelos
{
    class Modelo
{
    public:
    virtual void saveModel(std::ofstream &file) = 0;
    static void writeV(std::ofstream& myFile, float x, float y, float z);
};
}

#endif