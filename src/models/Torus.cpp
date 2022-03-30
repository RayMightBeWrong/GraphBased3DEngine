#include "Torus.h"
using namespace Modelos;

Torus::Torus(float r,float dist,int rs,int sl){
    raio = r;
    distCentro = dist;
    rings = rs;
    slices = sl;
}

void Torus::saveModel(std::ofstream &file) {
    buildTorus();
    writeFile(file, this->vertices, this->indexes);
}

void Torus::buildTorus(){
    float alfa = 2 * M_PI / rings;
	float beta = 2 * M_PI / slices;
	float ringAngle = alfa;
	float sliceAngle;

	for(int i = 0; i < rings; i++){
		sliceAngle = beta;
		for(int j = 0; j < slices; j++){
			float r_ = abs(raio * cos(sliceAngle));
			float nextr_ = abs(raio * cos(sliceAngle + beta));

			float x = (r_ + distCentro) * cos(ringAngle);
			float y = raio * sin(sliceAngle);
			float z = (r_ + distCentro) * sin(ringAngle);
			float x2 = (r_ + distCentro) * cos(ringAngle + alfa);
			float y2 = raio * sin(sliceAngle); 
			float z2 = (r_ + distCentro) * sin(ringAngle + alfa);
			float x3 = (nextr_ + distCentro) * cos(ringAngle);
			float y3 = raio * sin(sliceAngle + beta);
			float z3 = (nextr_ + distCentro) * sin(ringAngle);
			float x4 = (nextr_ + distCentro) * cos(ringAngle + alfa);
			float y4 = raio * sin(sliceAngle + beta); 
			float z4 = (nextr_ + distCentro) * sin(ringAngle + alfa);

			addVertex(this->vertices, this->indexes, x, y, z);
			addVertex(this->vertices, this->indexes, x2, y2, z2);
			addVertex(this->vertices, this->indexes, x3, y3, z3);
				
			addVertex(this->vertices, this->indexes, x4, y4, z4);
			addVertex(this->vertices, this->indexes, x3, y3, z3);
			addVertex(this->vertices, this->indexes, x2, y2, z2);

			sliceAngle += beta;
		}
		ringAngle += alfa;
	}
}


void Torus::addVertex(std::vector<float> &vertexs, 
			            std::vector<unsigned int> &indexes, 
			            float x, float y, float z){
        int r;
		int verticeCount = vertexs.size() / 3;

        if((r = vertexInVector(vertexs, x, y, z)) == -1){
                vertexs.push_back(x);
                vertexs.push_back(y);
                vertexs.push_back(z);
                indexes.push_back(verticeCount);
                verticeCount++;
        }
        else
                indexes.push_back(r);
}

int Torus::vertexInVector(std::vector<float> &vertexs, float x, float y, float z){
        int r = -1;
		int verticeCount = vertexs.size() / 3;

        for(int i = 0; r == -1 && i < verticeCount; i++){
                if(x == vertexs[i*3])
                        if(y == vertexs[i*3 + 1])
                                if(z == vertexs[i*3 + 2])
                                        r = i;
        }

        return r;
}

void Torus::printSucess(std::string file){
	std::cout << "Torus gerada com sucesso no ficheiro: " << file << std::endl;
}