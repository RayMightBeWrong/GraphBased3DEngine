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
#include <unordered_map>
#include "parserXML/XMLDocReader.h"
#include "parserXML/tinyxml2.h"
using namespace std;
using namespace tinyxml2;

int nrModelos = 0;
vector<int> verticeCount;
vector<vector<float>> vertices;
vector<vector<float>> normals;
vector<vector<unsigned int>> indexes;
GLuint *verts, *indcs, *norms;
XMLParser parser;
unordered_map<string, int> filesIndex;

int startX, startY, tracking = 0;
float beta, alfa, radius;
float px, py, pz, angle;
float temp_x,temp_y,temp_z;

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
	gluPerspective(parser.camara.projFOV ,ratio, parser.camara.projNEAR ,parser.camara.projFAR);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void readVertices(fstream& myFile, int verticeCount){
	string line;
	vector<float> vs;
	vector<float> ns;
	for(int i = 0; i < verticeCount && getline(myFile, line); i++){
		float value;
		int posVert = 0,normalsVert = 0;
		stringstream ss(line);
		while (posVert < 3 && ss >> value ) {
			vs.push_back(value);
			posVert++;
		}
		while (normalsVert < 3 && ss >> value) {
			ns.push_back(value);
			normalsVert++;
		}
	}
	vertices.push_back(vs);
	normals.push_back(ns);
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

void initCamera(){
	radius = sqrt(pow(parser.camara.camPX, 2) + pow(parser.camara.camPY, 2) + pow(parser.camara.camPZ, 2));
	alfa = atan(parser.camara.camPZ / parser.camara.camPX);
	beta = atan((sqrt(pow(parser.camara.camPX, 2) + pow(parser.camara.camPZ, 2))) / parser.camara.camPY);
	px = parser.camara.camPX;
	py = parser.camara.camPY;
	pz = parser.camara.camPZ;
}

void updateCamera(){
	px = radius * cos(beta) * sin(alfa);
	py = radius * sin(beta);
	pz = radius * cos(beta) * cos(alfa);
}

void createVBOs(){
	// criar os VBOs
	verts = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	indcs = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	norms = (GLuint *) malloc(sizeof(GLuint) * nrModelos);

	for(int i = 0; i < nrModelos; i++){
		glGenBuffers(1, &verts[i]);
		glGenBuffers(1, &indcs[i]);
		glGenBuffers(1, &norms[i]);
	}

	// copiar o vector para a memória gráfica
	for(int i = 0; i < nrModelos; i++){
		glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices[i].size(), vertices[i].data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, norms[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals[i].size(), normals[i].data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indcs[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					sizeof(unsigned int) * indexes[i].size(), 
					indexes[i].data(), GL_STATIC_DRAW);
	}
}

bool prepareData(Grupo *g) {
	g->modelsIndex.reserve(g->modelos.size());
	for (int i = 0; i < g->modelos.size();i++) {
		fstream f;f.open(g->modelos[i].modelName,fstream::in);
		if (f.fail()) {
			return false;
		}
		
		if (filesIndex.find(g->modelos[i].modelName) == filesIndex.end()) {
			filesIndex[g->modelos[i].modelName] = nrModelos;
			g->modelsIndex.push_back(nrModelos);
			string line;
			getline(f, line);
			stringstream ss(line);
			int value;
			ss >> value;
			verticeCount.push_back(value);
			readVertices(f, value);
			readIndexes(f);
			nrModelos++;
		}
		else {
			g->modelsIndex.push_back(filesIndex.at(g->modelos[i].modelName));
		}
	}
	for (int i  = 0; i < g->subgrupos.size();i++) {
		if (!prepareData(&(g->subgrupos[i]))) return false;
	}
	return true;
}

void prepareLights() {
	int size = parser.luzes.size();
	glEnable(GL_LIGHTING);
	glEnable(GL_RESCALE_NORMAL);
	float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	if (size > 0 ) {
		glEnable(GL_LIGHT0);
	}
	if (size > 1 ) {
		glEnable(GL_LIGHT1);
	}
	if (size > 2 ) glEnable(GL_LIGHT2);
	if (size > 3 ) glEnable(GL_LIGHT3);
	if (size > 4 ) glEnable(GL_LIGHT4);
	if (size > 5 ) glEnable(GL_LIGHT5);
	if (size > 6 ) glEnable(GL_LIGHT6);
	if (size > 7 ) glEnable(GL_LIGHT7);
}

void desenhaGrupo(Grupo g, float time) {
	glPushMatrix();
	for (int i = 0; i < g.transformacoes.size();i++) {
		g.transformacoes[i]->apply(time);
	}
	for (int i = 0; i < g.modelsIndex.size();i++) {
		g.modelos[i].corModelo.apply();

		glBindBuffer(GL_ARRAY_BUFFER, norms[g.modelsIndex[i]]);
		glNormalPointer(GL_FLOAT,0,0);
		
		glBindBuffer(GL_ARRAY_BUFFER, verts[g.modelsIndex[i]]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indcs[g.modelsIndex[i]]);
		glDrawElements(GL_TRIANGLES, indexes[g.modelsIndex[i]].size(), GL_UNSIGNED_INT, 0);

	}

	for (int i = 0; i < g.subgrupos.size(); i++) {
		desenhaGrupo(g.subgrupos[i], time);
	}
	glPopMatrix();
}

void aplicaLuzes(std::vector<Luz*> luzes) {
	for(int i = 0;i < luzes.size();i++) {
		luzes[i]->apply(i);
	}
}

void renderScene(void) {
	// clear buffers
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(px, py, pz,
		      parser.camara.camLX,parser.camara.camLY,parser.camara.camLZ,
			  parser.camara.camUX,parser.camara.camUY,parser.camara.camUZ);
	desenhaGrupo(parser.grupo, glutGet(GLUT_ELAPSED_TIME) / 1000.f);

	aplicaLuzes(parser.luzes);
	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy){
	switch(key){
		case 115: // 'w'
			radius += 1; break;

		case 119: // 's'
			if (radius > 1.0)
				radius -= 1; 
			break;

		case 27: // ESCAPE
			exit(0); break;
	}
	updateCamera();
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy){
	switch(key){
		case GLUT_KEY_RIGHT:
			alfa -= 0.1; break;

		case GLUT_KEY_LEFT:
			alfa += 0.1; break;

		case GLUT_KEY_UP:
			if (beta < 1.45f)
				beta += 0.1f;
			break;

		case GLUT_KEY_DOWN:
			if (beta > -1.45f)
				beta -= 0.1f;
			break;
	}

	updateCamera();
	glutPostRedisplay();
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
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);


    // init GLEW
#ifndef __APPLE__
    glewInit();
#endif

//  OpenGL settings
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	if (argc == 2) {
		if (parser.loadXML(argv[1]) == XML_SUCCESS) {
			bool sucess = parser.parse();
			if (sucess) {
				if (prepareData(&parser.grupo)) {
					prepareLights();
					createVBOs();
					initCamera();
					glutMainLoop();
				}
				else std::cout << "Erro nos modelos pedidos para desenhar no cenário" << std::endl;
			}
			else {
				std::cout << "Erro no parsing do ficheiro de configuracao" << std::endl;
			}
		}
		else std::cerr << "Erro na abertura do ficheiro" << std::endl;
	}
	
	return 1;
}
