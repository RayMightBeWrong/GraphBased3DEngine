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
        void printSucess(std::string file);

    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indexes;
        void buildCubo();
        void buildPlaneTXY(float z);
        void buildPlaneTXZ(float y);
        void buildPlaneTYZ(float x);
		void buildPlaneTXYBack(float z);
		void buildPlaneTXZBack(float y);
		void buildPlaneTYZBack(float x);
        void addVertex(std::vector<float> &vertexs, 
						std::vector<unsigned int> &indexes, 
							float x, float y, float z);
        int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};

}

#endif