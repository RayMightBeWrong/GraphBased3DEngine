#ifndef TORUS_H
#define TORUS_H
#include "Modelo.h"
#include <math.h>

namespace Modelos
{
    class Torus : public Modelo
{
    public:
        float raio;
        float distCentro;
        int rings;
        int slices;
        Torus(float r,float dist,int rs,int sl);
        void saveModel(std::ofstream &file);
        void printSucess(std::string file);

    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indexes;
        std::vector<float> normals;
        void buildTorus();
        void addVertex(std::vector<float> &vertexs, std::vector<unsigned int> &indexes, float x, float y, float z);
        int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};
}

#endif
