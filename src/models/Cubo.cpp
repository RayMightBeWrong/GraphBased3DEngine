#include "Cubo.h"
using namespace Modelos;

Cubo::Cubo(float tam,float sub){
	tamanho = tam;
	subDivisions = sub;
}

void Cubo::saveModel(std::ofstream &file){
	buildCubo();
	writeFile(file, this->vertices, this->indexes);
}

void Cubo::buildCubo(){
	buildPlaneTXZBack(-tamanho/2.0);
	buildPlaneTXZ(tamanho/2.0);
	buildPlaneTXYBack(-tamanho/2.0);
	buildPlaneTXY(tamanho/2.0);
	buildPlaneTYZBack(-tamanho/2.0);
	buildPlaneTYZ(tamanho/2.0);
}


void Cubo::buildPlaneTXY(float z){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = -tamanho/2; y < tamanho/2; y += step) {
			addVertex(this->vertices,this->indexes, x,y,z);
			addVertex(this->vertices,this->indexes, x+step,y,z);
			addVertex(this->vertices,this->indexes, x+step,y+step,z);

			addVertex(this->vertices,this->indexes, x+step,y+step,z);
			addVertex(this->vertices,this->indexes, x,y+step,z);
			addVertex(this->vertices,this->indexes, x,y,z);
        }
    }
}

void Cubo::buildPlaneTXYBack(float z){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = -tamanho/2; y < tamanho/2; y += step) {
			addVertex(this->vertices,this->indexes, x+step,y,z);
			addVertex(this->vertices,this->indexes, x,y,z);
			addVertex(this->vertices,this->indexes, x+step,y+step,z);
			
			addVertex(this->vertices,this->indexes, x,y+step,z);
			addVertex(this->vertices,this->indexes, x+step,y+step,z);
			addVertex(this->vertices,this->indexes, x,y,z);
        }
    }
}


void Cubo::buildPlaneTXZ(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			addVertex(this->vertices,this->indexes, x+step,y,z);
			addVertex(this->vertices,this->indexes, x,y,z);
			addVertex(this->vertices,this->indexes, x,y,z+step);

			addVertex(this->vertices,this->indexes, x,y,z+step);
			addVertex(this->vertices,this->indexes, x+step,y,z+step);
			addVertex(this->vertices,this->indexes, x+step,y,z);
    	}
    }
}

void Cubo::buildPlaneTXZBack(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			addVertex(this->vertices,this->indexes, x,y,z);
			addVertex(this->vertices,this->indexes, x+step,y,z);
			addVertex(this->vertices,this->indexes, x,y,z+step);

			addVertex(this->vertices,this->indexes, x+step,y,z+step);
			addVertex(this->vertices,this->indexes, x,y,z+step);
			addVertex(this->vertices,this->indexes, x+step,y,z); 
    	}
    }
}


void Cubo::buildPlaneTYZ(float x){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
    	for (float y = -tamanho/2; y < tamanho/2; y += step) {
			addVertex(this->vertices,this->indexes, x,y,z+step);
			addVertex(this->vertices,this->indexes, x,y,z);
			addVertex(this->vertices,this->indexes, x,y+step,z);

			addVertex(this->vertices,this->indexes, x,y+step,z);
			addVertex(this->vertices,this->indexes, x,y+step,z+step);
			addVertex(this->vertices,this->indexes, x,y,z+step);
    	}
    }	
}

void Cubo::buildPlaneTYZBack(float x){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
    	for (float y = -tamanho/2; y < tamanho/2; y += step) {
			addVertex(this->vertices,this->indexes, x,y,z);
			addVertex(this->vertices,this->indexes, x,y,z+step);
			addVertex(this->vertices,this->indexes, x,y+step,z);

			addVertex(this->vertices,this->indexes, x,y+step,z+step);
			addVertex(this->vertices,this->indexes, x,y+step,z);
			addVertex(this->vertices,this->indexes, x,y,z+step);
    	}
    }	
}

void Cubo::addVertex(std::vector<float> &vertexs, 
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

int Cubo::vertexInVector(std::vector<float> &vertexs, float x, float y, float z){
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

void Cubo::printSucess(std::string file){
	std::cout << "Cubo gerada com sucesso no ficheiro: " << file << std::endl;
}