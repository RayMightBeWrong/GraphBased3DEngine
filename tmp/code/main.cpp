#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>
#include <cstring>

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
        glVertex3f(3, 0, 0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 3, 0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 3);

        glEnd();
}

int figure = 0;
float length, subDivisions;

void drawPlaneTXY(float l1, float l2, float factor){
	glVertex3f(l1,l2,length*factor);
	glVertex3f(l1+length/subDivisions,l2,length*factor);
	glVertex3f(l1,l2+length/subDivisions,length*factor);
		
	glVertex3f(l1+length/subDivisions,l2+length/subDivisions,length*factor);
	glVertex3f(l1,l2+length/subDivisions,length*factor);
	glVertex3f(l1+length/subDivisions,l2,length*factor);
}


void drawPlaneTXZ(float l1, float l2, float factor){
	glVertex3f(l1+length/subDivisions,length*factor,l2);
	glVertex3f(l1,length*factor,l2);
	glVertex3f(l1,length*factor,l2+length/subDivisions);
		
	glVertex3f(l1,length*factor,l2+length/subDivisions);
	glVertex3f(l1+length/subDivisions,length*factor,l2+length/subDivisions);
	glVertex3f(l1+length/subDivisions,length*factor,l2);
}


void drawPlaneTYZ(float l1, float l2, float factor){
	glVertex3f(length*factor,l1,l2);
	glVertex3f(length*factor,l1+length/subDivisions,l2);
	glVertex3f(length*factor,l1,l2+length/subDivisions);
		
	glVertex3f(length*factor,l1+length/subDivisions,l2+length/subDivisions);
	glVertex3f(length*factor,l1,l2+length/subDivisions);
	glVertex3f(length*factor,l1+length/subDivisions,l2);
}

void drawPlane(){
	glBegin(GL_TRIANGLES);
        for (float x = -length/2;x < length/2;x += length/subDivisions) {
                for (float z = -length/2;z < length/2;z += length/subDivisions) {
			drawPlaneTXZ(x, z, 0);
                }
        }
	glEnd();
}

void drawCube(){
	glBegin(GL_TRIANGLES);
        for (float l1 = -length/2; l1 < length/2; l1 += length/subDivisions) {
                for (float l2 = -length/2; l2 < length/2; l2 += length/subDivisions) {
			drawPlaneTXY(l1, l2, 0.5);
			//drawPlaneXY(l1, l2, -0.5);
			drawPlaneTXZ(l1, l2, 0.5);
			//drawPlaneXZ(l1, l2, -0.5);
			drawPlaneTYZ(l1, l2, 0.5);
			//drawPlaneYZ(l1, l2, -0.5);
                }
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

	glPolygonMode(GL_FRONT, GL_LINE);
	axis_system();
	glColor3f(1,1,1);
	switch(figure){
		case 2:
			drawCube(); break;

		case 4:
			drawPlane(); break;

		default:
			printf("oof\n"); break;
	}

	// End of frame
	glutSwapBuffers();
}

int handleInput(int argc, char **argv){
        if (argc == 4){
                if(!strcmp(argv[1], "box")){
                        figure = 2;
                }
                else if (!strcmp(argv[1], "plane")){
                        //tratar dos erros
                        figure = 4;
                }
		length = atoi(argv[2]);
		subDivisions = atoi(argv[3]);
        }
        else if (argc == 5 && !strcmp(argv[1], "sphere"))
                figure = 1;
        else if (argc == 6 && !strcmp(argv[1], "cone"))
                figure = 3;
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
		glutReshapeFunc(changeSize);

	//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	
	// enter GLUT's main cycle
		glutMainLoop();
	}
	
	return 1;
}
