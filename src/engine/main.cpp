#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
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

int nrModelos = 0;
vector<int> verticeCount;
vector<vector<float>> vertices;
vector<vector<unsigned int>> indexes;
GLuint *verts, *indcs;
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

void readVertices(fstream& myFile, int verticeCount){
	string line;
	vector<float> vs;
	for(int i = 0; i < verticeCount && getline(myFile, line); i++){
		float value;
		stringstream ss(line);
		while (ss >> value) {
			vs.push_back(value);
		}
	}
	vertices.push_back(vs);
}

void readIndexes(fstream& myFile){
	string line;
	unsigned int value;
	vector<unsigned int> ids;
	getline(myFile, line);
	stringstream ss(line);
	while (ss >> value) {
		ids.push_back(value);
	}
	indexes.push_back(ids);
}

void prepareData(fstream& myFile){
	// preencher o vector com as coordenadas dos pontos
	string line;
	getline(myFile, line);
	stringstream ss(line);
	int value;
	ss >> value;
	verticeCount.push_back(value);
	readVertices(myFile, value);
	readIndexes(myFile);
}

void createVBOs(){
	// criar os VBOs
	verts = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	indcs = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	for(int i = 0; i < nrModelos; i++){
		glGenBuffers(1, &verts[i]);
		glGenBuffers(1, &indcs[i]);
	}

	// copiar o vector para a memória gráfica
	for(int i = 0; i < nrModelos; i++){
		glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices[i].size(), vertices[i].data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indcs[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					sizeof(unsigned int) * indexes[i].size(), 
					indexes[i].data(), GL_STATIC_DRAW);
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

	for(int i = 0; i < nrModelos; i++){
		glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indcs[i]);
		glDrawElements(GL_TRIANGLES, indexes[i].size(), GL_UNSIGNED_INT, 0);
	}

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
	glEnableClientState(GL_VERTEX_ARRAY);

		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


    // init GLEW
#ifndef __APPLE__
    glewInit();
#endif

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);	

	if (argc == 2) {
		if (parser.loadXML(argv[1]) == XML_SUCCESS) {
			bool sucess = parser.parse();
			if (sucess) {
				nrModelos = parser.modelos.size();
				for (int i = 0; i < parser.modelos.size() && sucess;i++) {
					fstream f;f.open(parser.modelos[i],fstream::in);
					if (!f.fail()) {
						prepareData(f);
						f.close();
					}
					else sucess = false;
				}
				createVBOs();
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
