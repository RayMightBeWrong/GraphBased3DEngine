#include "Modelo.h"
using namespace Modelos;

void Modelo::writeNrVertices(std::ofstream& myFile, int nrVertices){
	myFile << nrVertices; 
	myFile << "\n";
}

void Modelo::writeV(std::ofstream& myFile, float x, float y, float z,float nx,float ny,float nz){
	myFile << x; myFile << " ";
	myFile << y; myFile << " ";
	myFile << z; myFile << " ";
	myFile << nx; myFile << " ";
	myFile << ny; myFile << " ";
	myFile << nz; myFile << "\n";
}

void Modelo::writeIndexes(std::ofstream& myFile, std::vector<unsigned int> &indexes){
	for(int i = 0; i < indexes.size(); i++){
		myFile << indexes[i]; myFile << " ";
	}
	myFile << "\n";
}

void Modelo::writeFile(std::ofstream& myFile, 
						std::vector<float> &vertexs, 
						std::vector<unsigned int> &indexes,
						std::vector<float> normals){

	int verticeCount = vertexs.size() / 3;
	
	writeNrVertices(myFile, verticeCount);
	for(int i = 0; i < verticeCount; i++)
		writeV(myFile, vertexs[i*3], vertexs[i*3+1], vertexs[i*3+2] , normals[i*3],normals[i*3+1],normals[i*3+2]);
	writeIndexes(myFile, indexes);
}

void Modelo::normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

