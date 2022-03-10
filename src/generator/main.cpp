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
#include "../models/Modelo.h"
#include "../models/Esfera.h"
#include "../models/Cubo.h"
#include "../models/Plano.h"
#include "../models/Cone.h"
using namespace Modelos;
using namespace std;

ofstream file;
Modelo *m;

int handleInput(int argc, char **argv){
	if (argc == 5){
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
	}
	else if (argc == 6 && !strcmp(argv[1], "sphere")){
		int raio;
		sscanf(argv[2], "%d", &raio);
		int slices;
		sscanf(argv[3], "%d", &slices);
		int stacks;
		sscanf(argv[4], "%d", &stacks);
		m = new Esfera(raio,slices,stacks);
		file.open(argv[5]);
	}
	else if (argc == 7 && !strcmp(argv[1], "cone")){
		file.open(argv[6]);
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
	else return 0;
	return 1;
}



int main(int argc, char **argv) {
	if (handleInput(argc,argv) == 1) {
		m->saveModel(file);
		file.close();
	}
	return 1;
}
