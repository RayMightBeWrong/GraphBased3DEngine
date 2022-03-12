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
    float alfa = 2 * M_PI / slices;
    float sliceAngle = alfa;

    for(int i = 0; i < slices; i++){
        // topo
        addVertex(this->vertices,this->indexes, 0,height,0);
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle),height,raio * cos(sliceAngle));
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle + alfa),height,raio * cos(sliceAngle + alfa));

        // base
        addVertex(this->vertices,this->indexes, 0,0,0);
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle),0,raio * cos(sliceAngle));
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle + alfa),0,raio * cos(sliceAngle + alfa));

        // corpo
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle),height,raio * cos(sliceAngle));
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle),0,raio * cos(sliceAngle));
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle + alfa),height,raio * cos(sliceAngle + alfa));

        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle + alfa),height,raio * cos(sliceAngle + alfa));
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle),0,raio * cos(sliceAngle));
        addVertex(this->vertices,this->indexes, raio * sin(sliceAngle + alfa),0,raio * cos(sliceAngle + alfa));

        sliceAngle += alfa;
    }
}


void Cilindro::addVertex(std::vector<float> &vertexs, 
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

int Cilindro::vertexInVector(std::vector<float> &vertexs, float x, float y, float z){
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