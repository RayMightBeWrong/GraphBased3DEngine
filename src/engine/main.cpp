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
#include "XMLDocReader.h"
#include "parserXML/tinyxml2.h"
using namespace std;
using namespace tinyxml2;

vector<vector<float>> vertices;
XMLParser parser;

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
	gluPerspective(parser.projFOV ,ratio, parser.projNEAR ,parser.projFAR);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawReadVertices(){
	for(int i = 0; i < vertices.size(); i++)
		glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
}


void readVertices(fstream& myFile){
	string line;
	while (getline(myFile, line)){
		float value;
		stringstream ss(line);
		vector<float> coords;
		while (ss >> value) {
			coords.push_back(value);
		}
		vertices.push_back(coords);
	}
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(parser.camPX,parser.camPY,parser.camPZ, 
		      parser.camLX,parser.camLY,parser.camLZ,
			  parser.camUX,parser.camUY,parser.camUZ);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLES);
	drawReadVertices();
	glEnd();

	// End of frame
	glutSwapBuffers();
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

	if (argc == 2) {
		if (parser.loadXML(argv[1]) == XML_SUCCESS) {
			bool sucess = parser.parse();
			if (sucess) {
				for (int i = 0; i < parser.modelos.size() && sucess;i++) {
					fstream f;f.open(parser.modelos[i],fstream::in);
					if (!f.fail()) {
						readVertices(f);
						f.close();
					}
					else sucess = false;
				}
			}
			if (sucess) glutMainLoop();
			else {
				std::cout << "Erro no parsing do ficheiro de configuracao" << std::endl;
			}
		}
		else std::cerr << "Erro na abertura do ficheiro" << std::endl;
	}
	
	return 1;
}
