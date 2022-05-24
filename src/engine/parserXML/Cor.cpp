#include "Cor.h"
#include <iostream>

Cor::Cor() {
    float corDifusa[4] = {200,200,200,1};
    float corAmbiente[4] = {50,50,50,1};
    float corEspecular[4] = {0,0,0,1};
    float corEmissiva[4] = {0,0,0,1};
    float shiny = 0;
    difusa = (float*) malloc(sizeof(float) * 4);
    difusa[0] = corDifusa[0]/255;difusa[1] = corDifusa[1]/255;difusa[2] = corDifusa[2]/255;difusa[3] = corDifusa[3]/255;
    ambiente = (float*) malloc(sizeof(float) * 4);
    ambiente[0] = corAmbiente[0]/255;ambiente[1] = corAmbiente[1]/255;ambiente[2] = corAmbiente[2]/255;ambiente[3] = corAmbiente[3]/255;
    especular = (float*) malloc(sizeof(float) * 4);
    especular[0] = corEspecular[0]/255;especular[1] = corEspecular[1]/255;especular[2] = corEspecular[2]/255;especular[3] = corEspecular[3]/255;
    emissive = (float*) malloc(sizeof(float) * 4);
    emissive[0] = corEmissiva[0]/255;emissive[1] = corEmissiva[1]/255;emissive[2] = corEmissiva[2]/255;emissive[3] = corEmissiva[3]/255;
    shininess = shiny;
}

Cor::Cor(float *corDifusa,
            float *corAmbiente,
            float *corEspecular,
            float *corEmissiva,
            float shiny) {

        difusa = (float*) malloc(sizeof(float) * 4);
        difusa[0] = corDifusa[0]/255;difusa[1] = corDifusa[1]/255;difusa[2] = corDifusa[2]/255;difusa[3] = corDifusa[3]/255;
        ambiente = (float*) malloc(sizeof(float) * 4);
        ambiente[0] = corAmbiente[0]/255;ambiente[1] = corAmbiente[1]/255;ambiente[2] = corAmbiente[2]/255;ambiente[3] = corAmbiente[3]/255;
        especular = (float*) malloc(sizeof(float) * 4);
        especular[0] = corEspecular[0]/255;especular[1] = corEspecular[1]/255;especular[2] = corEspecular[2]/255;especular[3] = corEspecular[3]/255;
        emissive = (float*) malloc(sizeof(float) * 4);
        emissive[0] = corEmissiva[0]/255;emissive[1] = corEmissiva[1]/255;emissive[2] = corEmissiva[2]/255;emissive[3] = corEmissiva[3]/255;
        shininess = shiny;
}

void Cor::apply() {
    glMaterialfv(GL_FRONT,GL_DIFFUSE,difusa);
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,especular);
    glMaterialfv(GL_FRONT,GL_EMISSION,emissive);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);
}