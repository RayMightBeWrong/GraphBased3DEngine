#include "Cilindro.h"
using namespace Modelos;

Cilindro::Cilindro(float r,float h,float sl){
    raio = r;
    height = h;
    slices = sl;
}

void Cilindro::saveModel(std::ofstream &file) {
    buildCilindro();
    writeFile(file, this->vertices, this->indexes);
}

void Cilindro::buildCilindro(){
    float alfa = 2 * M_PI;

    vertices.push_back(0);vertices.push_back(0);vertices.push_back(0);
	vertices.push_back(0);vertices.push_back(height);vertices.push_back(0);
	vertices.push_back(raio*sin(alfa));vertices.push_back(0);vertices.push_back(raio*cos(alfa));
	vertices.push_back(raio*sin(alfa));vertices.push_back(height);vertices.push_back(raio*cos(alfa));

    int index = 4;
	float sliceStep = alfa/slices;

	for (int i = 0; i < slices;i++) {
		float alfaAngle = alfa - i * sliceStep;
		float alfaAngle2 = alfa - (i+1) * sliceStep;
		float x2 = raio * sin(alfaAngle2);
		float z2 = raio * cos(alfaAngle2);
		indexes.push_back(index-2);
		vertices.push_back(x2);
		vertices.push_back(0);
		vertices.push_back(z2);
		indexes.push_back(index);
		indexes.push_back(0);

		indexes.push_back(index-1);
		indexes.push_back(1);
		vertices.push_back(x2);
		vertices.push_back(height);
		vertices.push_back(z2);
		indexes.push_back(index+1);

		indexes.push_back(index-2);
		indexes.push_back(index-1);
		indexes.push_back(index+1);

		indexes.push_back(index+1);
		indexes.push_back(index);
		indexes.push_back(index-2);

		index +=2;
	}
}

void Cilindro::printSucess(std::string file){
	std::cout << "Cilindro gerada com sucesso no ficheiro: " << file << std::endl;
}