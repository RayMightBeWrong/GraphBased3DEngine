#include "Cone.h"
using namespace Modelos;

Cone::Cone(float r,float h,float sli,float sta) {
    raio = r;
    height = h;
    slices = sli;
    stacks = sta;
}

void Cone::saveModel(std::ofstream &file) {
    buildCone();
    writeFile(file, this->vertices, this->indexes);
}

void Cone::buildCone(){
    float sliceStep = 2 * M_PI / slices;
    float stackStep = height/stacks;
	int index = 2;
	vertices.push_back(0);vertices.push_back(0);vertices.push_back(0);
	vertices.push_back(0);vertices.push_back(0);vertices.push_back(raio);

    //BASE DO CONE
	for (int i = 1; i <= slices;i++) {
		float alphaAngle = i * sliceStep;
		float x = raio * sin(alphaAngle);
		float z = raio * cos(alphaAngle);
		vertices.push_back(x);vertices.push_back(0);vertices.push_back(z);
		
		indexes.push_back(index);
		indexes.push_back(index-1);
		indexes.push_back(0);

		index++;
	}

    for (int i = 1; i <= stacks;i++) {
        float xy = raio * (stacks-i)/stacks;
        float y = i * stackStep;

		int indexStackAnterior = index - slices - 1;
		vertices.push_back(0);vertices.push_back(y);vertices.push_back(xy);
		index++;
        for (int j = 1;j <= slices;j++) {
			float alphaAngle = j * sliceStep;
			float x = xy * sin(alphaAngle);
			float z = xy * cos(alphaAngle);
			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);

			indexes.push_back(indexStackAnterior);
			indexes.push_back(indexStackAnterior + 1);
			indexes.push_back(index-1);

			indexes.push_back(index);
			indexes.push_back(index - 1);
			indexes.push_back(indexStackAnterior + 1);
			
			indexStackAnterior++;
			index++;
        }
    }
}

void Cone::printSucess(std::string file){
	std::cout << "Cone gerada com sucesso no ficheiro: " << file << std::endl;
}