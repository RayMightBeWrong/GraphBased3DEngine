#include "Modelo.h"
using namespace Modelos;

void Modelo::writeV(std::ofstream& myFile, float x, float y, float z){
	    myFile << x; myFile << " ";
	    myFile << y; myFile << " ";
	    myFile << z; myFile << "\n";
}
