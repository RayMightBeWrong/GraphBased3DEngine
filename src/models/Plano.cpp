#include "Plano.h"
using namespace Modelos;

Plano::Plano(float l,float sub){
        tamanho = l;
        subDivisions = sub;
}

void Plano::saveModel(std::ofstream &file) {
        buildPlaneTXZ(0);
        writeFile(file, this->vertices, this->indexes);
}

void Plano::buildPlaneTXZ(float y){
	float step = tamanho/subDivisions;

	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	        for (float z = -tamanho/2; z < tamanho/2; z += step) {
                        addVertex(this->vertices,this->indexes,x+step,y,z);
			addVertex(this->vertices,this->indexes,x,y,z);
			addVertex(this->vertices,this->indexes,x,y,z+step);

			addVertex(this->vertices,this->indexes,x,y,z+step);
			addVertex(this->vertices,this->indexes,x+step,y,z+step);
			addVertex(this->vertices,this->indexes,x+step,y,z); 
    	        }
        }
}


void Plano::addVertex(std::vector<float> &vertexs, 
			std::vector<unsigned int> &indexes, 
			float x, float y, float z){
        int r;
		int verticeCount = vertexs.size() / 3;

        if((r = vertexInVector(vertexs, x, y, z)) == -1){
                vertexs.push_back(x);
                vertexs.push_back(y);
                vertexs.push_back(z);
                indexes.push_back(verticeCount);
                verticeCount++;
        }
        else
                indexes.push_back(r);
}

int Plano::vertexInVector(std::vector<float> &vertexs, float x, float y, float z){
        int r = -1;
		int verticeCount = vertexs.size() / 3;

        for(int i = 0; r == -1 && i < verticeCount; i++){
                if(x == vertexs[i*3])
                        if(y == vertexs[i*3 + 1])
                                if(z == vertexs[i*3 + 2])
                                        r = i;
        }

        return r;
}