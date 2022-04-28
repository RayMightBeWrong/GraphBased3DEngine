#include "Patch.h"

using namespace Modelos;

// Funçao que calcula a multiplicação da matriz da curva de bezier com a matrix das coordenadas dos pontos controlo
void multMatrix1(float m1[4][4],float m2[4][4][3],float res[4][4][3]) {
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 4;j++) {
                res[i][j][0] = 0;
                res[i][j][1] = 0;
                res[i][j][2] = 0;
            for (int k = 0;k < 4;k++) {
                res[i][j][0] += m1[i][k] * m2[k][j][0];
                res[i][j][1] += m1[i][k] * m2[k][j][1];
                res[i][j][2] += m1[i][k] * m2[k][j][2];
            }
        }
    }
}
// Funçao que calcula a multiplicação da matriz das coordenadas dos pontos controlo com a matriz da curva de bezier
void multMatrix2(float m1[4][4][3],float m2[4][4],float res[4][4][3]) {
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 4;j++) {
                res[i][j][0] = 0;
                res[i][j][1] = 0;
                res[i][j][2] = 0;
            for (int k = 0;k < 4;k++) {
                res[i][j][0] += m1[i][k][0] * m2[k][j];
                res[i][j][1] += m1[i][k][1] * m2[k][j];
                res[i][j][2] += m1[i][k][2] * m2[k][j];
            }
        }
    }
}

// Funçao que calcula a multiplicação da matriz resultado com o vetor V
void calculaVMatrix(float m1[4][4][3],float vector[4][1],float res[4][1][3]) {
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 1;j++) {
                res[i][j][0] = 0;
                res[i][j][1] = 0;
                res[i][j][2] = 0;
            for (int k = 0;k < 4;k++) {
                res[i][j][0] += m1[i][k][0] * vector[k][0];
                res[i][j][1] += m1[i][k][1] * vector[k][0];
                res[i][j][2] += m1[i][k][2] * vector[k][0];
            }
        }
    }
}

// Funçao que calcula a multiplicação da matriz resultado com o vetor U
void calculaUMatrix(float m1[4][1][3],float vector[4],float res[3]) {
    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
    for (int i = 0; i < 4;i++) {
        for (int j = 0;j < 1;j++) {
            res[0] += vector[i] * m1[i][j][0];
            res[1] += vector[i] * m1[i][j][1];
            res[2] += vector[i] * m1[i][j][2];
        }
    }
}

// Funçao que calcula as coordenadas de um ponto dado o valor de u e v e a matriz pré calculada
void calculaPonto(float matrixPre[4][4][3],float u,float v,float res[3]) {
    float uVector[4] = {powf(u,3),powf(u,2),u,1};
    float vVector[4][1] = {{powf(v,3)},{powf(v,2)},{v},{1}};

    float resVMatrix[4][1][3];
    calculaVMatrix(matrixPre,vVector,resVMatrix);
    calculaUMatrix(resVMatrix,uVector,res);
}

void Patch::preCalcularMatrix(float res[4][4][3]) {
    float matrizBezier[4][4] = {{-1,3,-3,1},
                                {3,-6,3,0},
                                {-3,3,0,0},
                                {1,0,0,0}};
    float matrizPontos[4][4][3];
    for (int i = 0;i < 4;i++) {
        for (int j = 0; j < 4;j++) {
            matrizPontos[i][j][0] = pontosControlo[i*12 + j*3];
            matrizPontos[i][j][1] = pontosControlo[i*12 + j*3 + 1];
            matrizPontos[i][j][2] = pontosControlo[i*12 + j*3 +2];
        }
    }

    float res1[4][4][3];

    multMatrix1(matrizBezier,matrizPontos,res1);
    multMatrix2(res1,matrizBezier,res);
}

// Construtor da classe Patch
Patch::Patch(std::vector<float> pontos,float tes) {
    for (int i = 0; i < pontos.size();i++) {
        pontosControlo.push_back(pontos[i]);
    }
    tesselation = tes;
    // Gerar vertices e indices para a patch
    buildPatch();
}

// Funçao que preenche os vectores dos vertices e dos indexes relativos a esta patch
void Patch::buildPatch() {

    float preCalcMatrix[4][4][3];
    preCalcularMatrix(preCalcMatrix);

    int index = 0;
    for (int i = 0;i < tesselation;i++) {
        for (int j = 0; j < tesselation;j++) {
            float coords1[3],coords2[3],coords3[3],coords4[3];
            float u1 = (1/tesselation) * i;
            float u2 = (1/tesselation) * (i+1);
            float v1 = (1/tesselation) * j;
            float v2 = (1/tesselation) * (j+1);

            //Calcular as coordenadas dos 4 vertices que utilizaremos para formar triangulos
            calculaPonto(preCalcMatrix,u1,v1,coords1);
            calculaPonto(preCalcMatrix,u1,v2,coords2);
            calculaPonto(preCalcMatrix,u2,v1,coords3);
            calculaPonto(preCalcMatrix,u2,v2,coords4);

            //Inserir os vertices no vector para depois escrever no ficheiro
            vertices.push_back(coords1[0]);vertices.push_back(coords1[1]);vertices.push_back(coords1[2]);
            vertices.push_back(coords2[0]);vertices.push_back(coords2[1]);vertices.push_back(coords2[2]);
            vertices.push_back(coords3[0]);vertices.push_back(coords3[1]);vertices.push_back(coords3[2]);
            vertices.push_back(coords4[0]);vertices.push_back(coords4[1]);vertices.push_back(coords4[2]);

            //Inserir os indices no vertice por ordem de forma a formar triangulos bem orientados.
            indices.push_back(index);
            indices.push_back(index+2);
            indices.push_back(index+1);
            indices.push_back(index+2);
            indices.push_back(index+3);
            indices.push_back(index+1);

            index += 4;
        }
    }
}
