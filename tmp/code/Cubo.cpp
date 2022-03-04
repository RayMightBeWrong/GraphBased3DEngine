#include <GL/glut.h>

class Cubo : public Modelo {
    public:
        int tamanho;
        float subDivisions;
        Cubo(int tam,float sub) : Modelo(){
            tamanho = tam;
            subDivisions = sub;
        }
        void draw();
    private:
        void drawPlaneTXY(float l1,float l2,float factor);
        void drawPlaneTXZ(float l1,float l2,float factor);
        void drawPlaneTYZ(float l1,float l2,float factor);

};

void Cubo::draw(){
	glBegin(GL_TRIANGLES);
        for (float l1 = -tamanho/2; l1 < tamanho/2; l1 += tamanho/subDivisions) {
                for (float l2 = -tamanho/2; l2 < tamanho/2; l2 += tamanho/subDivisions) {
                    drawPlaneTXY(l1, l2, 0.5);
                    drawPlaneTXZ(l1, l2, 0.5);
                    drawPlaneTYZ(l1, l2, 0.5);
                }
        }
	glEnd();
}


void Cubo::drawPlaneTXY(float l1, float l2, float factor){
	glVertex3f(l1,l2,tamanho*factor);
	glVertex3f(l1+tamanho/subDivisions,l2,tamanho*factor);
	glVertex3f(l1,l2+tamanho/subDivisions,tamanho*factor);
		
	glVertex3f(l1+tamanho/subDivisions,l2+tamanho/subDivisions,tamanho*factor);
	glVertex3f(l1,l2+tamanho/subDivisions,tamanho*factor);
	glVertex3f(l1+tamanho/subDivisions,l2,tamanho*factor);
}


void Cubo::drawPlaneTXZ(float l1, float l2, float factor){
	glVertex3f(l1+tamanho/subDivisions,tamanho*factor,l2);
	glVertex3f(l1,tamanho*factor,l2);
	glVertex3f(l1,tamanho*factor,l2+tamanho/subDivisions);
		
	glVertex3f(l1,tamanho*factor,l2+tamanho/subDivisions);
	glVertex3f(l1+tamanho/subDivisions,tamanho*factor,l2+tamanho/subDivisions);
	glVertex3f(l1+tamanho/subDivisions,tamanho*factor,l2);
}


void Cubo::drawPlaneTYZ(float l1, float l2, float factor){
	glVertex3f(tamanho*factor,l1,l2);
	glVertex3f(tamanho*factor,l1+tamanho/subDivisions,l2);
	glVertex3f(tamanho*factor,l1,l2+tamanho/subDivisions);
		
	glVertex3f(tamanho*factor,l1+tamanho/subDivisions,l2+tamanho/subDivisions);
	glVertex3f(tamanho*factor,l1,l2+tamanho/subDivisions);
	glVertex3f(tamanho*factor,l1+tamanho/subDivisions,l2);
}