#ifndef TESSELATION_H
#define TESSELATION_H
#include "Modelo.h"
#include <math.h>
#include "Patch.h"

namespace Modelos
{
    class Tesselation : public Modelo
{
    public:
        std::vector<Patch> patches;
        Tesselation(std::vector<std::vector<int>> indices, std::vector<float> pontos,float tesselation);
        void saveModel(std::ofstream &file);
        void printSucess(std::string file);

    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indexes;
        void buildTesselation();
};


}

#endif