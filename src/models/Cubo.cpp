#include "Cubo.h"
using namespace Modelos;

Cubo::Cubo(float tam,float sub){
	tamanho = tam;
	subDivisions = sub;
}

void Cubo::saveModel(std::ofstream &file){
	index = 0;
	buildCubo();
    writeFile(file, this->vertices, this->indexes,this->normals);
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
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(1);
			vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(1);
			vertices.push_back(x);vertices.push_back(y+step);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(1);
			vertices.push_back(x+step);vertices.push_back(y+step);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(1);
			
			indexes.push_back(index);indexes.push_back(index+1);indexes.push_back(index+3);
			indexes.push_back(index+3);indexes.push_back(index+2);indexes.push_back(index);

			index +=4;
        }
    }
}

void Cubo::buildPlaneTXYBack(float z){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = -tamanho/2; y < tamanho/2; y += step) {
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(-1);
			vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(-1);
			vertices.push_back(x);vertices.push_back(y+step);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(-1);
			vertices.push_back(x+step);vertices.push_back(y+step);vertices.push_back(z);
			normals.push_back(0);normals.push_back(0);normals.push_back(-1);
			
			indexes.push_back(index+1);indexes.push_back(index);indexes.push_back(index+3);
			indexes.push_back(index+2);indexes.push_back(index+3);indexes.push_back(index);
			
			index +=4;
        }
    }
}


void Cubo::buildPlaneTXZ(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float z = -tamanho/2; z < tamanho/2; z += step) {
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(1);normals.push_back(0);
			vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(1);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z+step);
			normals.push_back(0);normals.push_back(1);normals.push_back(0);
			vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z+step);
			normals.push_back(0);normals.push_back(1);normals.push_back(0);
			
			indexes.push_back(index+1);indexes.push_back(index);indexes.push_back(index+3);
			indexes.push_back(index+2);indexes.push_back(index+3);indexes.push_back(index);
			
			index +=4;
        }
    }
}

void Cubo::buildPlaneTXZBack(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float z = -tamanho/2; z < tamanho/2; z += step) {
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(-1);normals.push_back(0);
			vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(0);normals.push_back(-1);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z+step);
			normals.push_back(0);normals.push_back(-1);normals.push_back(0);
			vertices.push_back(x+step);vertices.push_back(y);vertices.push_back(z+step);
			normals.push_back(0);normals.push_back(-1);normals.push_back(0);
			
			indexes.push_back(index);indexes.push_back(index+1);indexes.push_back(index+3);
			indexes.push_back(index+3);indexes.push_back(index+2);indexes.push_back(index);
			
			index +=4;
        }
    }
}


void Cubo::buildPlaneTYZ(float x){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
        for (float y = -tamanho/2; y < tamanho/2; y += step) {
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(1);normals.push_back(0);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y+step);vertices.push_back(z);
			normals.push_back(1);normals.push_back(0);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z+step);
			normals.push_back(1);normals.push_back(0);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y+step);vertices.push_back(z+step);
			normals.push_back(1);normals.push_back(0);normals.push_back(0);
			
			indexes.push_back(index);indexes.push_back(index+1);indexes.push_back(index+3);
			indexes.push_back(index+3);indexes.push_back(index+2);indexes.push_back(index);
			
			index +=4;
        }
    }	
}

void Cubo::buildPlaneTYZBack(float x){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
        for (float y = -tamanho/2; y < tamanho/2; y += step) {
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(-1);normals.push_back(0);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y+step);vertices.push_back(z);
			normals.push_back(-1);normals.push_back(0);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z+step);
			normals.push_back(-1);normals.push_back(0);normals.push_back(0);
			vertices.push_back(x);vertices.push_back(y+step);vertices.push_back(z+step);
			normals.push_back(-1);normals.push_back(0);normals.push_back(0);
			
			indexes.push_back(index+1);indexes.push_back(index);indexes.push_back(index+3);
			indexes.push_back(index+2);indexes.push_back(index+3);indexes.push_back(index);
			
			index +=4;
        }
    }		
}


void Cubo::printSucess(std::string file){
	std::cout << "Cubo gerada com sucesso no ficheiro: " << file << std::endl;
}