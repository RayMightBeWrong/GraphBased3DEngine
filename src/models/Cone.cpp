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
    writeFile(file, this->vertices, this->indexes,this->normals);
}

void Cone::buildCone(){
    float sliceStep = 2 * M_PI / slices;
    float stackStep = height/stacks;
	int index = 2;
	vertices.push_back(0);vertices.push_back(0);vertices.push_back(0);
	normals.push_back(0);normals.push_back(-1);normals.push_back(0);
	vertices.push_back(0);vertices.push_back(0);vertices.push_back(raio);
	normals.push_back(0);normals.push_back(-1);normals.push_back(0);

    //BASE DO CONE
	for (int i = 1; i <= slices;i++) {
		float alphaAngle = i * sliceStep;
		float x = raio * sin(alphaAngle);
		float z = raio * cos(alphaAngle);
		vertices.push_back(x);normals.push_back(0);
		vertices.push_back(0);normals.push_back(-1);
		vertices.push_back(z);normals.push_back(0);
		
		indexes.push_back(index);
		indexes.push_back(index-1);
		indexes.push_back(0);

		index++;
	}

	//Face lateral do cone
    for (int i = 0; i <= stacks;i++) {
        float xy = raio * (stacks-i)/stacks;
        float y = i * stackStep;

		int indexStackAnterior = index - slices - 1;
		float l = sqrt(height*height + raio*raio);
		float n[3] = {height*raio*sinf(0)/l,raio/l,height*raio*cosf(0)/l};
		normalize(n);

		vertices.push_back(0);vertices.push_back(y);vertices.push_back(xy);
		normals.push_back(n[0]);normals.push_back(n[1]);normals.push_back(n[2]);
		index++;
        for (int j = 1;j <= slices;j++) {
			float alphaAngle = j * sliceStep;
			float x = xy * sin(alphaAngle);
			float z = xy * cos(alphaAngle);
			float normal[3] = {height*raio*sinf(alphaAngle)/l,raio/l,height*raio*cosf(alphaAngle)/l};
			normalize(normal);

			vertices.push_back(x);vertices.push_back(y);vertices.push_back(z);
			normals.push_back(normal[0]);normals.push_back(normal[1]);normals.push_back(normal[2]);

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