#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include "Vertice.cpp"
#include "Esfera.cpp"
#include "Cubo.cpp"
#include "Plano.cpp"
#endif


Modelo *m;
int angle = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void axis_system(){
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glBegin(GL_LINES);
	
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(100.000, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100.000, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100.000);
    glEnd();
}

void drawCone(float radius, float height, int slices, int stacks){
	float ogAngle = 2 * M_PI / slices;
	float angle = 2 * M_PI / slices;

	glBegin(GL_TRIANGLES);

	for(int i = 0; i < slices; i++){
		glVertex3f(0,0,0);
		glVertex3f(radius * sin(angle),0,radius * cos(angle));
		glVertex3f(radius * sin(angle + ogAngle),0,radius * cos(angle + ogAngle));
		angle += 2 * M_PI / slices;
        }

	for(int i = 0; i < slices; i++){
		glVertex3f(0,height,0);
		glVertex3f(radius * sin(angle),0,radius * cos(angle));
		glVertex3f(radius * sin(angle + ogAngle),0,radius * cos(angle + ogAngle));
		angle += 2 * M_PI / slices;
	}

	glEnd();
}


void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glDisable(GL_CULL_FACE);
	axis_system();
	glRotatef(angle,0,1,0);
	angle++;
	m->draw();
	// End of frame
	glutSwapBuffers();
}

int handleInput(int argc, char **argv){
        if (argc == 4){
                if(!strcmp(argv[1], "box")){
					int tamanho;
					sscanf(argv[2], "%d", &tamanho);
					float subDivisoes;
					sscanf(argv[3], "%f", &subDivisoes);
					m = new Cubo(tamanho,subDivisoes);
                }
                else if (!strcmp(argv[1], "plane")){
					int tamanho;
					sscanf(argv[2], "%d", &tamanho);
					float subDivisoes;
					sscanf(argv[3], "%f", &subDivisoes);
					m = new Plano(tamanho,subDivisoes);
                }
        }
		else if (argc == 5 && !strcmp(argv[1],"sphere")) {
			int raio;
			sscanf(argv[2], "%d", &raio);
			int slices;
			sscanf(argv[3], "%d", &slices);
			int stacks;
			sscanf(argv[4], "%d", &stacks);
			m = new Esfera(raio,slices,stacks);
		}
		else if (argc == 6 && !strcmp(argv[1],"cone")) {
			//COdigo do cone;
		}
		else return 0;
        return 1;
}

int main(int argc, char **argv) {
	if(handleInput(argc, argv) == 1){
	// init GLUT and the window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowPosition(100,100);
		glutInitWindowSize(800,800);
		glutCreateWindow("CG@DI-UM");
		
	// Required callback registry 
		glutDisplayFunc(renderScene);
		glutIdleFunc(renderScene);
		glutReshapeFunc(changeSize);

	//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	
	// enter GLUT's main cycle
		glutMainLoop();
	}
	
	return 1;
}
