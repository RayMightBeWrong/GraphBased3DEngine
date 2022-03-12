#ifndef CILINDRO_H
#define CILINDRO_H
#include "Modelo.h"
#include <fstream>
#include <math.h>
#define _USE_MATH_DEFINES

namespace Modelos
{
    class Cilindro : public Modelo {
    public:
        float raio;
        float height;
        float slices;
        Cilindro(float r,float h,float sl);
        void saveModel(std::ofstream &file);

    private:
    std::vector<float> vertices;
    std::vector<unsigned int> indexes;
    void buildCilindro();
    void addVertex(std::vector<float> &vertexs, std::vector<unsigned int> &indexes, float x, float y, float z);
    int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};

}

#endif