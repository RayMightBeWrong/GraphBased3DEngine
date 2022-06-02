#ifndef ESFERA_H
#define ESFERA_H
#include "Modelo.h"
#include <vector>
#include <math.h>
#define _USE_MATH_DEFINES


namespace Modelos
{
class Esfera : public Modelo 
{
public:
    int raio;
    float slices;
    float stacks;
    Esfera(int r,int sli,int sta);
	void saveModel(std::ofstream &file);
    void printSucess(std::string file);

private:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textCoords;
    std::vector<unsigned int> indexes;
    void buildEsfera();
    void addVertex(std::vector<float> &vertexs, 
						std::vector<unsigned int> &indexes, 
							float x, float y, float z);
    int vertexInVector(std::vector<float> &vertexs, float x, float y, float z);
};
}

#endif