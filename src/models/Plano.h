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
    void printSucess(std::string file);

private:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textCoords;
    std::vector<unsigned int> indexes;
    void buildPlaneTXZ(float y);
    void addVertex(std::vector<float> &vertexs, std::vector<unsigned int> &indexes, float x, float y, float z);
    int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};
}

#endif
