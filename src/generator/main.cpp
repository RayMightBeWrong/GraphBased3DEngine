#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "../models/Modelo.h"
#include "../models/Cilindro.h"
#include "../models/Esfera.h"
#include "../models/Cubo.h"
#include "../models/Plano.h"
#include "../models/Cone.h"
#include "../models/Torus.h"
#include "../models/SuperficieBezier.h"

using namespace Modelos;
using namespace std;

int nrPatches = 0;
int nrPontosControlo = 0;
vector<vector<int>> indicesPatches;
vector<float> pontosControlo;
ofstream file;
string filename;
Modelo *m;

void getNumberPatches(std::ifstream &filePatch) {
	string line;
	getline(filePatch,line);
	stringstream ss(line);
	ss >> nrPatches;
}

void fillPatchesIndices(std::ifstream &filePatch) {
	for (int i = 0; i < nrPatches ; i++) {
		string line;
		getline(filePatch,line);
		stringstream ss(line);
		int indice;
		vector<int> indicesPatch;
		while (ss >> indice) {
			indicesPatch.push_back(indice);
			if (ss.peek() == ',')
            	ss.ignore();
		}
		indicesPatches.push_back(indicesPatch);
	}
}

void getNumberControlPoints(std::ifstream &filePatch) {
	string line;
	getline(filePatch,line);
	stringstream ss(line);
	ss >> nrPontosControlo;
}

void fillControlPoints(std::ifstream &filePatch) {
	for (int i = 0; i < nrPontosControlo ; i++) {
		string line;
		getline(filePatch,line);
		stringstream ss(line);
		float coordenada;
		while (ss >> coordenada)	 {
			pontosControlo.push_back(coordenada);
			if (ss.peek() == ',')
            	ss.ignore();
		}
	}
}

void getPatchInfo(std::ifstream &filePatch) {
	getNumberPatches(filePatch);
	fillPatchesIndices(filePatch);
	getNumberControlPoints(filePatch);
	fillControlPoints(filePatch);
}

int handleInput(int argc, char **argv){
	if (argc == 5){
		if(!strcmp(argv[1], "bezier")){
			ifstream filePatchs;
			filePatchs.open(argv[2]);
			if (filePatchs.fail()) {
				cerr << "Erro no ficheiro com os patchs" << endl;
				return 0;
			}
			else {
				float tesselation;
				sscanf(argv[3],"%f",&tesselation);
				getPatchInfo(filePatchs);
				m = new SuperficieBezier(indicesPatches,pontosControlo,tesselation);
			}

		}
		if(!strcmp(argv[1], "box")){
			float tamanho;
			sscanf(argv[2], "%f", &tamanho);
			float subDivisoes;
			sscanf(argv[3], "%f", &subDivisoes);
			m = new Cubo(tamanho,subDivisoes);
		}
		else if (!strcmp(argv[1], "plane")){
			float tamanho;
			sscanf(argv[2], "%f", &tamanho);
			float subDivisoes;
			sscanf(argv[3], "%f", &subDivisoes);
			m = new Plano(tamanho,subDivisoes);
		}
		file.open(argv[4]);
		filename = argv[4];
	}
	else if (argc == 6){
		if(!strcmp(argv[1], "sphere")){
			int raio;
			sscanf(argv[2], "%d", &raio);
			int slices;
			sscanf(argv[3], "%d", &slices);
			int stacks;
			sscanf(argv[4], "%d", &stacks);
			m = new Esfera(raio,slices,stacks);
		}
		else if (!strcmp(argv[1], "cylinder")){
			int raio;
			sscanf(argv[2], "%d", &raio);
			int altura;
			sscanf(argv[3], "%d", &altura);
			int slices;
			sscanf(argv[4], "%d", &slices);
			m = new Cilindro(raio,altura,slices);
		}
		file.open(argv[5]);
		filename = argv[5];
	}
	else if (argc == 7){
		if(!strcmp(argv[1], "cone")){
			int raio;
			sscanf(argv[2], "%d", &raio);
			int altura;
			sscanf(argv[3], "%d", &altura);
			int slices;
			sscanf(argv[4], "%d", &slices);
			int stacks;
			sscanf(argv[5], "%d", &stacks);
			m = new Cone(raio,altura,slices,stacks);
		}
		else if (!strcmp(argv[1], "torus")){
			int raio;
			sscanf(argv[2], "%d", &raio);
			int dist;
			sscanf(argv[3], "%d", &dist);
			int rings;
			sscanf(argv[5], "%d", &rings);
			int slices;
			sscanf(argv[5], "%d", &slices);

			m = new Torus(raio,dist,rings,slices);
		}
		file.open(argv[6]);
		filename = argv[6];
	}
	else return 0;
	return 1;
}



int main(int argc, char **argv) {
	if (handleInput(argc,argv) == 1) {
		m->saveModel(file);
		m->printSucess(filename);
		file.close();
	}
	return 1;
}
