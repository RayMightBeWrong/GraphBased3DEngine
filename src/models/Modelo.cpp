#include "Modelo.h"
using namespace Modelos;

void Modelo::writeNrVertices(std::ofstream& myFile, int nrVertices){
	myFile << nrVertices; 
	myFile << "\n";
}

void Modelo::writeV(std::ofstream& myFile, float x, float y, float z){
	myFile << x; myFile << " ";
	myFile << y; myFile << " ";
	myFile << z; myFile << "\n";
}

void Modelo::writeIndexes(std::ofstream& myFile, std::vector<unsigned int> &indexes){
	for(int i = 0; i < indexes.size(); i++){
		myFile << indexes[i]; myFile << " ";
	}
	myFile << "\n";
}

void Modelo::writeFile(std::ofstream& myFile, 
						std::vector<float> &vertexs, 
						std::vector<unsigned int> &indexes){
	int verticeCount = vertexs.size() / 3;
	
	writeNrVertices(myFile, verticeCount);
	for(int i = 0; i < verticeCount; i++)
		writeV(myFile, vertexs[i*3], vertexs[i*3+1], vertexs[i*3+2]);
	writeIndexes(myFile, indexes);
}