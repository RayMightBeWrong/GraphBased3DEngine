#ifndef CONE_H
#define CONE_H
#include "Modelo.h"
#include <fstream>
#include <math.h>
#define _USE_MATH_DEFINES

namespace Modelos
{
    class Cone : public Modelo {
    public:
        float raio;
        float stacks;
        float slices;
        float height;
        Cone(float r,float st,float sl,float h);
        void saveModel(std::ofstream &file);

    private:
    std::vector<float> vertices;
    std::vector<unsigned int> indexes;
    void buildCone();
    void addVertex(std::vector<float> &vertexs, std::vector<unsigned int> &indexes, float x, float y, float z);
    int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};

}

#endif