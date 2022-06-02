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
    writeFile(file, this->vertices,this->textCoords, this->indexes,this->normals);
}

void Torus::buildTorus(){
    float alfa = 2 * M_PI / rings;
	float beta = 2 * M_PI / slices;
	float ringAngle = 0;
	float sliceAngle = 0;
	float sliceStep = 1.0/slices;
	float ringStep = 1.0/slices;

	for(int i = 0; i <= rings; i++){
		for(int j = 0; j <= slices; j++){
			float r_ = abs(raio * cos(sliceAngle));
			float nextr_ = abs(raio * cos(sliceAngle + beta));

			float x = (r_ + distCentro) * cos(ringAngle);
			float y = raio * sin(sliceAngle);
			float z = (r_ + distCentro) * sin(ringAngle);
			float t1[2] = {j * sliceStep,i*ringStep};
			float n1[3] = {r_ * cos(ringAngle),raio * sin(sliceAngle),r_*sin(ringAngle)};
			normalize(n1);

			float x2 = (r_ + distCentro) * cos(ringAngle + alfa);
			float y2 = raio * sin(sliceAngle); 
			float z2 = (r_ + distCentro) * sin(ringAngle + alfa);
			float t2[2] = {j * sliceStep,(i+1)*ringStep};
			float n2[3] = {r_ * cos(ringAngle + alfa),raio * sin(sliceAngle),r_*sin(ringAngle + alfa)};
			normalize(n2);

			float x3 = (nextr_ + distCentro) * cos(ringAngle);
			float y3 = raio * sin(sliceAngle + beta);
			float z3 = (nextr_ + distCentro) * sin(ringAngle);
			float t3[2] = {(j+1) * sliceStep,i*ringStep};
			float n3[3] = {r_ * cos(ringAngle),raio * sin(sliceAngle + beta),r_*sin(ringAngle)};
			normalize(n3);

			float x4 = (nextr_ + distCentro) * cos(ringAngle + alfa);
			float y4 = raio * sin(sliceAngle + beta); 
			float z4 = (nextr_ + distCentro) * sin(ringAngle + alfa);
			float t4[2] = {(j+1) * sliceStep,(i+1)*ringStep};
			float n4[3] = {r_ * cos(ringAngle + alfa),raio * sin(sliceAngle + beta),r_*sin(ringAngle + alfa)};
			normalize(n4);

			addVertex(this->vertices, this->indexes, x, y, z,n1,t1);
			addVertex(this->vertices, this->indexes, x2, y2, z2,n2,t2);
			addVertex(this->vertices, this->indexes, x3, y3, z3,n3,t3);
				
			addVertex(this->vertices, this->indexes, x2, y2, z2,n2,t2);
			addVertex(this->vertices, this->indexes, x4, y4, z4,n4,t4);
			addVertex(this->vertices, this->indexes, x3, y3, z3,n3,t3);

			sliceAngle += beta;
		}
		ringAngle += alfa;
	}
}


void Torus::addVertex(std::vector<float> &vertexs, 
			            std::vector<unsigned int> &indexes, 
			            float x, float y, float z, float normal[3],float texture[2]){
        int r;
		int verticeCount = vertexs.size() / 3;

        if((r = vertexInVector(vertexs, x, y, z)) == -1){
                vertexs.push_back(x);
                vertexs.push_back(y);
                vertexs.push_back(z);
				normals.push_back(normal[0]);
				normals.push_back(normal[1]);
				normals.push_back(normal[2]);
				textCoords.push_back(texture[0]);
				textCoords.push_back(texture[1]);
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