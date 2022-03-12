#ifndef MODELO_H
#define MODELO_H
#include <fstream>
#include <vector>

namespace Modelos
{
    class Modelo
{
    public:
    virtual void saveModel(std::ofstream &file) = 0;
    static void writeFile(std::ofstream& myFile, 
						std::vector<float> &vertexs, 
						std::vector<unsigned int> &indexes);
    static void writeNrVertices(std::ofstream& myFile, int nrVertices);
    static void writeV(std::ofstream& myFile, float x, float y, float z);
    static void writeIndexes(std::ofstream& myFile, std::vector<unsigned int> &indexes);
};
}

#endif
