#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

char *file;

float length = 0;
float subDivisions = 0;

int figure = 0;

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

void drawAndWriteV(fstream& myFile, float x, float y, float z){
//	glVertex3f(x, y, z);
	myFile.write((char *) &x, sizeof(float));
	myFile.write((char *) &y, sizeof(float));
	myFile.write((char *) &z, sizeof(float));
	myFile.write("\n", 1);
}

void drawPlane(fstream& myFile){
	for (float x = -length/2;x < length/2;x += length/subDivisions) {
		for (float z = -length/2;z < length/2;z += length/subDivisions) {
			drawAndWriteV(myFile,x+length/subDivisions,0,z);
			drawAndWriteV(myFile,x,0,z);
			drawAndWriteV(myFile,x,0,z+length/subDivisions);
			
			drawAndWriteV(myFile,x,0,z+length/subDivisions);
			drawAndWriteV(myFile,x+length/subDivisions,0,z+length/subDivisions);
			drawAndWriteV(myFile,x+length/subDivisions,0,z);
		}
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glPolygonMode(GL_FRONT,GL_LINE);

	glBegin(GL_TRIANGLES);
	glEnd();
	

	// End of frame
	glutSwapBuffers();
}


int main(int argc, char **argv) {
	if (argc == 5){
		if(strcmp(argv[1], "box")){
			figure = 2;
		}
		else if (strcmp(argv[1], "plane")){
			//tratar dos erros
			figure = 4;
			length = atoi(argv[2]);
			subDivisions = atoi(argv[3]);
		}
		file = (char *) malloc(sizeof(char) * strlen(argv[4]));
		strcpy(file, argv[4]);
		printf("%ld %s\n", strlen(argv[4]), file);
	}
	else if (argc == 6 && strcmp(argv[1], "sphere"))
		figure = 1;
	else if (argc == 7 && strcmp(argv[1], "cone"))
		figure = 3;
	else return 0;

	fstream myFile(file, ios::binary | ios::out | ios::trunc); 
	drawPlane(myFile);
/*
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@GENERATOR");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	*/
	myFile.close();
	
	return 1;
}
