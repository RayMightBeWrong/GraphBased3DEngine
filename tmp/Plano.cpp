#include <GL/glut.h>

class Plano : public Modelo
{
public:
    int tamanho;
    float subDivisions;

    Plano(int l,float sub) {
        tamanho = l;
        subDivisions = sub;
    }
    void draw();

private:
    void drawPlaneTXZ(float y);
};

void Plano::draw() {
    glBegin(GL_TRIANGLES);
    drawPlaneTXZ(0);
	glEnd();
}

void Plano::drawPlaneTXZ(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			glVertex3f(x+step,y,z);
			glVertex3f(x,y,z);
			glVertex3f(x,y,z+step);

			glVertex3f(x,y,z+step);
			glVertex3f(x+step,y,z+step);
			glVertex3f(x+step,y,z);   
    	}
    }
}
