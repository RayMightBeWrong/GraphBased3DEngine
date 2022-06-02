#include "Esfera.h"

using namespace Modelos;

Esfera::Esfera(int r,int sli,int sta){
        raio = r;
        slices = sli;
        stacks = sta;
}

void Esfera::saveModel(std::ofstream &file) {
	buildEsfera();
    writeFile(file, this->vertices, this->textCoords,this->indexes,this->normals);
}

void Esfera::buildEsfera(){
	float sliceStep = 2 * M_PI / slices;
    float stackStep = M_PI/stacks;
	float invRaio = 1.0f / raio;
	double textYstep = 1.0/stacks;
	double textXstep = 1.0/slices;

	vertices.push_back(0);vertices.push_back(raio);vertices.push_back(0);
	normals.push_back(0);normals.push_back(1);normals.push_back(0);
	textCoords.push_back(0);textCoords.push_back(1);

	vertices.push_back(0);vertices.push_back(-raio);vertices.push_back(0);
	normals.push_back(0);normals.push_back(-1);normals.push_back(0);
	textCoords.push_back(0);textCoords.push_back(0);

	int index = 2;
    for (float i = 1; i <= stacks;i++) {
		float stackAngle = M_PI_2 - i * stackStep;
        float xy = raio * cos(stackAngle);
        float y = raio * sin(stackAngle);
		float textureHeight = i*textYstep;

		int indexStackAnterior;
		if (i != 1) {
			indexStackAnterior = index - slices - 1;
		}
		vertices.push_back(0);vertices.push_back(y);vertices.push_back(xy);
		normals.push_back(0);normals.push_back(y*invRaio);normals.push_back(xy*invRaio);
		textCoords.push_back(0);textCoords.push_back(1 - textureHeight);
		index++;

        for (float j = 1;j <= slices;j++) {
			float alphaAngle = j * sliceStep;
			float x = xy * sin(alphaAngle);
			float z = xy * cos(alphaAngle);
			float textureWidth = j*textXstep;

			if (i == 1) {
				vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
				normals.push_back(x*invRaio);normals.push_back(y*invRaio);normals.push_back(z*invRaio);
				textCoords.push_back(textureWidth);textCoords.push_back(1 - textureHeight);

				indexes.push_back(0);
				indexes.push_back(index-1);
				indexes.push_back(index);
				index++;
			}
			else if (i == stacks) {
				vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
				normals.push_back(x*invRaio);normals.push_back(y*invRaio);normals.push_back(z*invRaio);
				textCoords.push_back(textureWidth);textCoords.push_back(1 - textureHeight);

				indexes.push_back(1);
				indexes.push_back(indexStackAnterior+1);
				indexes.push_back(indexStackAnterior);
				indexStackAnterior++;
			}
			else {
				vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
				normals.push_back(x*invRaio);normals.push_back(y*invRaio);normals.push_back(z*invRaio);
				textCoords.push_back(textureWidth);textCoords.push_back(1 - textureHeight);

				indexes.push_back(indexStackAnterior + 1);
				indexes.push_back(indexStackAnterior);
				indexes.push_back(index-1);

				indexes.push_back(index - 1);
				indexes.push_back(index);
				indexes.push_back(indexStackAnterior + 1);
				
				indexStackAnterior++;
				index++;
			}
        }
    }
}

void Esfera::printSucess(std::string file){
	std::cout << "Esfera gerada com sucesso no ficheiro: " << file << std::endl;
}