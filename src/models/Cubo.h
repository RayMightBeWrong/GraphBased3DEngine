#ifndef CUBO_H
#define CUBO_H
#include "Modelo.h"
#include <fstream>

namespace Modelos
{
    class Cubo : public Modelo {
    public:
        float tamanho;
        float subDivisions;
        Cubo(float tam,float sub);
		void saveModel(std::ofstream &file);
    private:
        void savePlaneTXY(float z,std::ofstream &file);
        void savePlaneTXZ(float y,std::ofstream &file);
        void savePlaneTYZ(float x,std::ofstream &file);
		void savePlaneTXYBack(float z,std::ofstream &file);
		void savePlaneTXZBack(float y,std::ofstream &file);
		void savePlaneTYZBack(float x,std::ofstream &file);
};

}

#endif