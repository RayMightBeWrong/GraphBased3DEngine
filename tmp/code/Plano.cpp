#include <GL/glut.h>

class Plano : public Modelo
{
public:
    int length;
    float subDivisions;

    Plano(int l,float sub) {
        length = l;
        subDivisions = sub;
    }
    void draw();

private:
    void drawPlaneTXZ(float l1,float l2,float factor);
};

void Plano::draw() {
    glBegin(GL_TRIANGLES);
        for (float x = -length/2;x < length/2;x += length/subDivisions) {
                for (float z = -length/2;z < length/2;z += length/subDivisions) {
			        drawPlaneTXZ(x, z, 0);
                }
        }
	glEnd();
}

void Plano::drawPlaneTXZ(float l1, float l2, float factor){
	glVertex3f(l1+length/subDivisions,length*factor,l2);
	glVertex3f(l1,length*factor,l2);
	glVertex3f(l1,length*factor,l2+length/subDivisions);
		
	glVertex3f(l1,length*factor,l2+length/subDivisions);
	glVertex3f(l1+length/subDivisions,length*factor,l2+length/subDivisions);
	glVertex3f(l1+length/subDivisions,length*factor,l2);
}
