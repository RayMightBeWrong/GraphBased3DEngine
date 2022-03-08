#ifndef ESFERA_H
#define ESFERA_H
#include "Modelo.h"
#include <vector>
#include <math.h>
#define _USE_MATH_DEFINES


namespace Modelos
{
    class Vertice
{
public:
    Vertice();
    Vertice(float x,float y,float z);

    float x;
    float y;
    float z;
    
};

class Esfera : public Modelo {

public:
    int raio;
    int slices;
    int stacks;
    Esfera(int r,int sli,int sta);
	void saveModel(std::ofstream &file);
};
}

#endif