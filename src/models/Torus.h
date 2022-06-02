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
        float rings;
        float slices;
        Torus(float r,float dist,int rs,int sl);
        void saveModel(std::ofstream &file);
        void printSucess(std::string file);

    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indexes;
        std::vector<float> textCoords;
        std::vector<float> normals;
        void buildTorus();
        void addVertex(std::vector<float> &vertexs, std::vector<unsigned int> &indexes, float x, float y, float z, float normal[3],float texture[2]);
        int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};
}

#endif
