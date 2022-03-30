#include "Esfera.h"

using namespace Modelos;

Esfera::Esfera(int r,int sli,int sta){
        raio = r;
        slices = sli;
        stacks = sta;
}

void Esfera::saveModel(std::ofstream &file) {
	buildEsfera();
    writeFile(file, this->vertices, this->indexes);
}

void Esfera::buildEsfera(){
	float sliceStep = 2 * M_PI / slices;
    float stackStep = M_PI / stacks;

	this->vertices.push_back(0);this->vertices.push_back(raio);this->vertices.push_back(0);
	this->vertices.push_back(0);this->vertices.push_back(-raio);this->vertices.push_back(0);
	unsigned int index = 2,indexstackAnterior = 2 ;
	for (int i = 0; i < stacks; i++)
	{
		float stackAngle2 = M_PI_2 - (i + 1) * stackStep;
		float xy2 = raio * cos(stackAngle2);
		float y2 = raio * sin(stackAngle2);

		float sliceAngle = 0;
		float x3 = xy2 * sin(sliceAngle);
		float z3 = xy2 * cos(sliceAngle);
		vertices.push_back(x3);vertices.push_back(y2);vertices.push_back(z3);
		index++;
		
		for (int j = 0; j < slices; j++){
			float sliceAngle2 = (j+1) * sliceStep;

			float x4 = xy2 * sin(sliceAngle2);
			float z4 = xy2 * cos(sliceAngle2);
			
			if (i == 0) {
				vertices.push_back(x4);vertices.push_back(y2);vertices.push_back(z4);
				indexes.push_back(0);
				indexes.push_back(index-1);
				indexes.push_back(index);
				index ++;
			}
			else if (i == stacks-1){
				indexes.push_back(indexstackAnterior + 1);
				indexes.push_back(indexstackAnterior);
				indexes.push_back(1);
				indexstackAnterior++;
			}
			else {
				indexes.push_back(indexstackAnterior + 1);
				indexes.push_back(indexstackAnterior);
				indexes.push_back(index-1);

				vertices.push_back(x4);vertices.push_back(y2);vertices.push_back(z4);
				indexes.push_back(index-1);
				indexes.push_back(index);
				indexes.push_back(indexstackAnterior + 1);
				indexstackAnterior++;
			}
		}
	}
}