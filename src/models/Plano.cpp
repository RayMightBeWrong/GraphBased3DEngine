#include "Plano.h"
using namespace Modelos;

Plano::Plano(int l,float sub){
        tamanho = l;
        subDivisions = sub;
}

void Plano::saveModel(std::ofstream &file) {
    savePlaneTXZ(0,file);
}

void Plano::savePlaneTXZ(float y,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			writeV(file,x+step,y,z);
			writeV(file,x,y,z);
			writeV(file,x,y,z+step);

			writeV(file,x,y,z+step);
			writeV(file,x+step,y,z+step);
			writeV(file,x+step,y,z);   
    	}
    }
}
