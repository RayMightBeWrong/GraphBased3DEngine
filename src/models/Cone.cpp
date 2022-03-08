#include "Modelo.h"
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Esfera.h"
#include <vector>

using namespace Modelos;

class Cone : public Modelo {
    public:
        float raio;
        float stacks;
        float slices;
        float height;
        Cone(float r,float st,float sl,float h) {
            raio = r;
            stacks = st;
            slices = sl;
            height = h;
        }
        void saveModel(std::ofstream &file) {}
        void draw();
};


//TODO: Melhorar codigo para ficar mais legivel e escrever no ficheiro
void Cone::draw() {
    float sliceStep = 2 * M_PI / slices;
    float stackStep = height/stacks;
	glPointSize(2.5);
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);
    for (int i = 0; i < stacks;i++) {
        float stackAngle = i * stackStep;
		float stackAngle2 = (i+1) * stackStep;
        float xy = raio * (stacks-i)/stacks;
        float xy2 = raio * (stacks-i-1)/stacks;
        float y = i * stackStep;
		float y2 = (i + 1) * stackStep;

        for (int j = 0;j < slices;j++) {
            float sliceAngle = j * sliceStep;
            float sliceAngle2 = (j+1) * sliceStep;

			glVertex3f(xy * sin(sliceAngle),y,xy*cos(sliceAngle));
			glVertex3f(xy * sin(sliceAngle2),y,xy * cos(sliceAngle2));
			glVertex3f(xy2 * sin(sliceAngle2),y2,xy2 * cos(sliceAngle2));

			glVertex3f(xy2 * sin(sliceAngle2),y2,xy2 * cos(sliceAngle2));
			glVertex3f(xy2 * sin(sliceAngle),y2,xy2*cos(sliceAngle));
			glVertex3f(xy * sin(sliceAngle),y,xy * cos(sliceAngle));
        }
    }

	for (int i = 0; i < slices;i++) {
		float alphaAngle = i * sliceStep;
		float x = raio * sin(alphaAngle);
		float z = raio * cos(alphaAngle);
		float x2 = raio * sin(alphaAngle + sliceStep);
		float z2 = raio * cos(alphaAngle + sliceStep);
		
		glVertex3f(x2,0,z2);
		glVertex3f(x,0,z);
		glVertex3f(0,0,0);

	}
	glEnd();
}


