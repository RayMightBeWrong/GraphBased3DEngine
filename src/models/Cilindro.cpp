#include "Cilindro.h"
using namespace Modelos;

Cilindro::Cilindro(float r,float h,float sl){
    raio = r;
    height = h;
    slices = sl;
}

void Cilindro::saveModel(std::ofstream &file) {
    buildCilindro();
    writeFile(file, this->vertices, this->indexes,this->normals);
}

void Cilindro::buildCilindro(){
    float alfa = 2 * M_PI;

    vertices.push_back(0);vertices.push_back(0);vertices.push_back(0);
	normals.push_back(0);normals.push_back(-1);normals.push_back(0);
	vertices.push_back(0);vertices.push_back(height);vertices.push_back(0);
	normals.push_back(0);normals.push_back(1);normals.push_back(0);
	vertices.push_back(raio*sinf(alfa));vertices.push_back(0);vertices.push_back(raio*cosf(alfa));
	normals.push_back(0);normals.push_back(-1);normals.push_back(0);
	vertices.push_back(raio*sinf(alfa));vertices.push_back(height);vertices.push_back(raio*cosf(alfa));
	normals.push_back(0);normals.push_back(1);normals.push_back(0);
    int index = 4;

	// Adicionar vértices da base
	float sliceStep = alfa/slices;

	for (int i = 0; i < slices;i++) {
		float alphaAngle = alfa - (i+1) * sliceStep;
		float x2 = raio * sinf(alphaAngle);
		float z2 = raio * cosf(alphaAngle);

		vertices.push_back(x2);normals.push_back(0);
		vertices.push_back(0);normals.push_back(-1);
		vertices.push_back(z2);normals.push_back(0);
		indexes.push_back(index-2);
		indexes.push_back(index);
		indexes.push_back(0);

		vertices.push_back(x2);normals.push_back(0);
		vertices.push_back(height);normals.push_back(1);
		vertices.push_back(z2);normals.push_back(0);
		indexes.push_back(1);
		indexes.push_back(index+1);
		indexes.push_back(index-1);

		index +=2;

	}

	// Adicionar vértices da lateral
	float n[3] = {sinf(alfa),0,cosf(alfa)};
	normalize(n);
	vertices.push_back(raio * sinf(alfa));vertices.push_back(0);vertices.push_back(raio*cosf(alfa));
	normals.push_back(n[0]);normals.push_back(n[1]);normals.push_back(n[2]);
	vertices.push_back(raio * sinf(alfa));vertices.push_back(height);vertices.push_back(raio*cosf(alfa));
	normals.push_back(n[0]);normals.push_back(n[1]);normals.push_back(n[2]);

	index+=2;
	for (int i = 0; i < slices;i++) {
		float alphaAngle = alfa - (i+1) * sliceStep;
		float x2 = raio * sinf(alphaAngle);
		float z2 = raio * cosf(alphaAngle);
		float n[3] = {sinf(alphaAngle),0,cosf(alphaAngle)};
		normalize(n);
		vertices.push_back(x2);normals.push_back(n[0]);
		vertices.push_back(0);normals.push_back(n[1]);
		vertices.push_back(z2);normals.push_back(n[2]);
		indexes.push_back(index-2);
		indexes.push_back(index-1);
		indexes.push_back(index+1);

		vertices.push_back(x2);normals.push_back(n[0]);
		vertices.push_back(height);normals.push_back(n[1]);
		vertices.push_back(z2);normals.push_back(n[2]);
		indexes.push_back(index+1);
		indexes.push_back(index);
		indexes.push_back(index-2);

		index +=2;
	}
}

void Cilindro::printSucess(std::string file){
	std::cout << "Cilindro gerada com sucesso no ficheiro: " << file << std::endl;
}