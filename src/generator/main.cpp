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
#include "../models/Modelo.cpp"
#include "../models/Esfera.cpp"
#include "../models/Cubo.cpp"
#include "../models/Plano.cpp"
using namespace std;

ofstream file;
Modelo *m;

int handleInput(int argc, char **argv){
	if (argc == 5){
		if(!strcmp(argv[1], "box")){
			int tamanho;
			sscanf(argv[2], "%d", &tamanho);
			float subDivisoes;
			sscanf(argv[3], "%f", &subDivisoes);
			m = new Cubo(tamanho,subDivisoes);
		}
		else if (!strcmp(argv[1], "plane")){
			int tamanho;
			sscanf(argv[2], "%d", &tamanho);
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
	}
	else return 0;
	return 1;
}

int main(int argc, char **argv) {
	if(handleInput(argc, argv) == 1){
		m->saveModel(file);
  		file.close();
	}

	return 1;
}
