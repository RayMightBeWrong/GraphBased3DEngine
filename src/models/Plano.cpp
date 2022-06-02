#include "Plano.h"
using namespace Modelos;

Plano::Plano(float l,float sub){
        tamanho = l;
        subDivisions = sub;
}

void Plano::saveModel(std::ofstream &file) {
    buildPlaneTXZ(0);
	writeFile(file, this->vertices, this->textCoords,this->indexes,this->normals);
}

void Plano::buildPlaneTXZ(float y){
	float step = (2*tamanho)/subDivisions;
	int index = 0;
	for (float x = -tamanho; x < tamanho; x += step) {
                for (float z = -tamanho; z < tamanho; z += step) {
	                vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
	                normals.push_back(0);normals.push_back(1);normals.push_back(0);
					textCoords.push_back((x + tamanho/2)/tamanho);textCoords.push_back((z + tamanho/2)/tamanho);
					
	                vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z);
	                normals.push_back(0);normals.push_back(1);normals.push_back(0);
					textCoords.push_back((x + step + tamanho/2)/tamanho);textCoords.push_back((z + tamanho/2)/tamanho);

	                vertices.push_back(x);vertices.push_back(y);vertices.push_back(z+step);
	                normals.push_back(0);normals.push_back(1);normals.push_back(0);
					textCoords.push_back((x + tamanho/2)/tamanho);textCoords.push_back((z + step + tamanho/2)/tamanho);
                        
	                vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z+step);
	                normals.push_back(0);normals.push_back(1);normals.push_back(0);
					textCoords.push_back((x + step + tamanho/2)/tamanho);textCoords.push_back((z + step + tamanho/2)/tamanho);

	                indexes.push_back(index+1);indexes.push_back(index);indexes.push_back(index+3);
	                indexes.push_back(index+2);indexes.push_back(index+3);indexes.push_back(index);

	                index +=4;
        }
    }
}


void Plano::printSucess(std::string file){
	std::cout << "Plano gerada com sucesso no ficheiro: " << file << std::endl;
}