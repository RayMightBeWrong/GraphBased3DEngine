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

    for (int i = 0; i < stacks;i++) {
        float stackAngle = i * stackStep;
		float stackAngle2 = (i+1) * stackStep;
        float xy = raio * (stacks-i)/stacks; float xy2 = raio * (stacks-i-1)/stacks;
        float y = i * stackStep; float y2 = (i + 1) * stackStep;

        for (int j = 0;j < slices;j++) {
            float sliceAngle = j * sliceStep; float sliceAngle2 = (j+1) * sliceStep;
            // Coordenadas x da stack i
            float x1 = xy * sin(sliceAngle); float x2 = xy * sin(sliceAngle2);
            // Coordenadas x da stack i+1
            float x3 = xy2 * sin(sliceAngle); float x4 = xy2 * sin(sliceAngle2);
            // Coordenadas z da stack i
            float z1 = xy * cos(sliceAngle); float z2 = xy * cos(sliceAngle2);
            // Coordenadas z da stack i+1
            float z3 = xy2 * cos(sliceAngle); float z4 = xy2 * cos(sliceAngle2);

            addVertex(this->vertices,this->indexes, x1,y,z1);
            addVertex(this->vertices,this->indexes, x2,y,z2);
            addVertex(this->vertices,this->indexes, x4,y2,z4);

            addVertex(this->vertices,this->indexes, x4,y2,z4);
            addVertex(this->vertices,this->indexes, x3,y2,z3);
            addVertex(this->vertices,this->indexes, x1,y,z1);
        }
    }

    //BASE DO CONE
	for (int i = 0; i < slices;i++) {
		float alphaAngle = i * sliceStep;
		float x = raio * sin(alphaAngle);
		float z = raio * cos(alphaAngle);
		float x2 = raio * sin(alphaAngle + sliceStep);
		float z2 = raio * cos(alphaAngle + sliceStep);
		
        addVertex(this->vertices,this->indexes, x2,0,z2);
        addVertex(this->vertices,this->indexes, x,0,z);
        addVertex(this->vertices,this->indexes, 0,0,0);
	}
}

void Cone::addVertex(std::vector<float> &vertexs, 
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

int Cone::vertexInVector(std::vector<float> &vertexs, float x, float y, float z){
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