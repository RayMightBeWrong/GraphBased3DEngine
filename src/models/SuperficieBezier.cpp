#include "SuperficieBezier.h"
using namespace Modelos;


//Construtor da classe SuperficieBezier
SuperficieBezier::SuperficieBezier(std::vector<std::vector<int>> indices, std::vector<float> pontos,float tes) {
    for (int i = 0; i < indices.size();i++) {
        std::vector<int> indicesPatch = indices[i];
        std::vector<float> pontosControloPatch;
        for (int j = 0;j < indicesPatch.size();j++) {
            pontosControloPatch.push_back(pontos[indicesPatch[j] * 3]);
            pontosControloPatch.push_back(pontos[indicesPatch[j] * 3 + 1]);
            pontosControloPatch.push_back(pontos[indicesPatch[j] * 3 + 2]);
        }
        Patch p(pontosControloPatch,tes);
        patches.push_back(p);
    }
}

//Função que guarda no file os vertices e indices para desenhar o modelo
void SuperficieBezier::saveModel(std::ofstream &file) {
    int index = 0;
    // Para cada Patch vamos buscar os seus vertices e indices e acrescentar aos vectores gerais do modelo.
    for (int i = 0;i < patches.size();i++) {

        this->vertices.insert(this->vertices.end(),patches[i].vertices.begin(),patches[i].vertices.end());
        this->normals.insert(this->normals.end(),patches[i].normals.begin(),patches[i].normals.end());

        // Para cada valor dos indices ajustar para o indice global.
        for (int j = 0; j < patches[i].indices.size();j++) {
            patches[i].indices[j] += index;
        }
        
        this->indexes.insert(this->indexes.end(),patches[i].indices.begin(),patches[i].indices.end());
        
        // O index para o proximo patch sera o anterior mais o numero de pontos que foram adicionados na ultima patch.
        index += patches[i].vertices.size() / 3;
    }

    writeFile(file, this->vertices, this->indexes,this->normals);

}

void SuperficieBezier::printSucess(std::string file) {
    std::cout << "Modelo com as patches gerado com sucesso" << std::endl;
}