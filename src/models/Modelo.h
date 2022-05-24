#ifndef MODELO_H
#define MODELO_H
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

namespace Modelos
{
    class Modelo
{
    public:
    virtual void saveModel(std::ofstream &file) = 0;
    virtual void printSucess(std::string) = 0;
    static void writeFile(std::ofstream& myFile, 
						std::vector<float> &vertexs, 
						std::vector<unsigned int> &indexes,
                        std::vector<float> normals);
    static void writeNrVertices(std::ofstream& myFile, int nrVertices);
    static void writeV(std::ofstream& myFile, float x, float y, float z,float nx, float ny, float nz);
    static void writeIndexes(std::ofstream& myFile, std::vector<unsigned int> &indexes);
    static void normalize(float *a);
};
}

#endif
