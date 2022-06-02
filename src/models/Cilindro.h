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
        void printSucess(std::string file);

    private:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textCoords;
    std::vector<unsigned int> indexes;
    void buildCilindro();
};

}

#endif