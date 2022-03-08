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
#include <sstream>
#include <vector>
#include "parserXML/tinyxml2.h"

float length = 2;
float subDivisions = 10;

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


std::vector<std::vector<float>> vertices;

void drawReadVertices(){
	for(int i = 0; i < vertices.size(); i++)
		glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5,5,5, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glPolygonMode(GL_FRONT,GL_LINE);

	glBegin(GL_TRIANGLES);
	drawReadVertices();
	glEnd();

	// End of frame
	glutSwapBuffers();
}

void readVertices(std::ifstream& myFile){
	int i = 0;
	std::string line;
	while (std::getline(myFile, line)){
		float value;
		std::stringstream ss(line);
		vertices.push_back(std::vector<float>());
		while (ss >> value)
			vertices[i].push_back(value);
	       	++i;
	}
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@ENGINE");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
