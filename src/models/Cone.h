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
};

}

#endif