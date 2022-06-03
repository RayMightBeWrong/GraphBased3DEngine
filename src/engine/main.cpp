#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>
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

int nrModelos = 0,nrTexturas = 0;
vector<int> verticeCount;
vector<vector<float>> vertices;
vector<vector<float>> normals;
vector<vector<float>> textCoords;
vector<vector<unsigned int>> indexes;
GLuint *verts, *indcs,*texts, *norms;
XMLParser parser;
unordered_map<string, int> filesIndex;

int startX, startY, tracking = 0;
float teta, alfa, radius;
float px, py, pz;
float lx, ly, lz;
float dx, dy, dz;
float horizontal,vertical,frente;

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

void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void readVertices(fstream& myFile, int verticeCount){
	string line;
	vector<float> vs;
	vector<float> ns;
	vector<float> ts;
	for(int i = 0; i < verticeCount && getline(myFile, line); i++){
		float value;
		int posVert = 0,normalsVert = 0,textVert = 0;
		stringstream ss(line);
		while (posVert < 3 && ss >> value ) {
			vs.push_back(value);
			posVert++;
		}
		while (normalsVert < 3 && ss >> value) {
			ns.push_back(value);
			normalsVert++;
		}
		while (textVert < 2 && ss >> value) {
			ts.push_back(value);
			textVert++;
		}
	}
	vertices.push_back(vs);
	normals.push_back(ns);
	textCoords.push_back(ts);
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
	px = parser.camara.camPX;
	py = parser.camara.camPY;
	pz = parser.camara.camPZ;
	lx = parser.camara.camLX;
	ly = parser.camara.camLY;
	lz = parser.camara.camLZ;
	dx = lx - px;
	dy = ly-py;
	dz = lz-pz;
	
	

}

void reloadCamera() {
	radius = sqrt(pow(lx-px,2) + pow(ly-py,2) + pow(lz-pz,2));
	teta = asin((ly-py)/radius);
	alfa = atan2(lx-px,lz-pz);
	lx = px + radius * cosf(teta) * sinf(alfa);
	ly = py + radius * sinf(teta);
	lz = pz + radius * cosf(teta) * cosf(alfa);
	dx = lx-px;
	dy = ly-py;
	dz = lz-pz;
}

void updateCamera(){
	lx = px + radius * cosf(teta) * sinf(alfa);
	ly = py + radius * sinf(teta);
	lz = pz + radius * cosf(teta) * cosf(alfa);
	dx = lx-px;
	dy = ly-py;
	dz = lz-pz;
}


void createVBOs(){
	// criar os VBOs
	verts = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	indcs = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	norms = (GLuint *) malloc(sizeof(GLuint) * nrModelos);
	texts = (GLuint *) malloc(sizeof(GLuint) * nrModelos);

	for(int i = 0; i < nrModelos; i++){
		glGenBuffers(1, &verts[i]);
		glGenBuffers(1, &indcs[i]);
		glGenBuffers(1, &norms[i]);
		glGenBuffers(1, &texts[i]);
	}

	// copiar o vector para a memória gráfica
	for(int i = 0; i < nrModelos; i++){
		glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices[i].size(), vertices[i].data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, norms[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals[i].size(), normals[i].data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, texts[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textCoords[i].size(), textCoords[i].data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indcs[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					sizeof(unsigned int) * indexes[i].size(), 
					indexes[i].data(), GL_STATIC_DRAW);
	}
}

unsigned int loadTexture2D(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID = 0;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ILboolean file =  ilLoadImage((ILstring)s.c_str());
	if (!file) std::cout << "Textura " << s << " inexistente" << std::endl;
	else {
		tw = ilGetInteger(IL_IMAGE_WIDTH);
		th = ilGetInteger(IL_IMAGE_HEIGHT);
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		texData = ilGetData();

		glGenTextures(1,&texID);
		
		glBindTexture(GL_TEXTURE_2D,texID);
		glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,	GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,	GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return texID;

}

bool prepareData(Grupo *g) {
	g->modelsIndex.reserve(g->modelos.size());
	for (int i = 0; i < g->modelos.size();i++) {
		fstream f;f.open(g->modelos[i].modelName,fstream::in);
		if (f.fail()) {
			return false;
		}

		if (g->modelos[i].textureName.compare("NO TEXTURE") != 0){
			nrTexturas++;
			g->modelos[i].textureBuffer = loadTexture2D(g->modelos[i].textureName);
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

	if (size > 0 ) {
		glEnable(GL_LIGHTING);	
		glEnable(GL_RESCALE_NORMAL);
		float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
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
		g.modelos[i].corFigura.apply();

		glBindBuffer(GL_ARRAY_BUFFER, verts[g.modelsIndex[i]]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, norms[g.modelsIndex[i]]);
		glNormalPointer(GL_FLOAT,0,0);

		glBindBuffer(GL_ARRAY_BUFFER, texts[g.modelsIndex[i]]);
		glTexCoordPointer(2,GL_FLOAT,0,0);
		
		glBindTexture(GL_TEXTURE_2D,g.modelos[i].textureBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indcs[g.modelsIndex[i]]);
		glDrawElements(GL_TRIANGLES, indexes[g.modelsIndex[i]].size(), GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D,0);

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
		      lx,ly,lz,
			  parser.camara.camUX,parser.camara.camUY,parser.camara.camUZ);
	desenhaGrupo(parser.grupo, glutGet(GLUT_ELAPSED_TIME) / 1000.f);
	
	aplicaLuzes(parser.luzes);
	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy){
	switch(key){
		case 115: // 'w'
			px = px - 0.01 * dx;
			pz = pz - 0.01 * dz;
			lx = lx - 0.01 * dx;
			lz = lz - 0.01 * dz; 
			break;

		case 119: // 's'
			px = px + 0.01 * dx;
			pz = pz + 0.01 * dz;
			lx = lx + 0.01 * dx;
			lz = lz + 0.01 * dz; 
			break;

		case 100: // 'd'
		{
			float d[3] = {dx,dy,dz};
			float up[3] = {parser.camara.camUX,parser.camara.camUY,parser.camara.camUZ};
			float right[3];
			cross(d,up,right);
			px = px + 0.01 * right[0];
			pz = pz + 0.01 * right[2];
			lx = lx + 0.01 * right[0];
			lz = lz + 0.01 * right[2];
			break;
		}
		
		case 97: // 'a'
		{
			float d1[3] = {dx,dy,dz};
			float up1[3] = {parser.camara.camUX,parser.camara.camUY,parser.camara.camUZ};
			float right1[3];
			cross(d1,up1,right1);
			px = px - 0.01 * right1[0];
			pz = pz - 0.01 * right1[2];
			lx = lx - 0.01 * right1[0];
			lz = lz - 0.01 * right1[2];
			break;
		}

		case 122: // 'z'
		{
			py = py+0.01*radius;
			reloadCamera();
			break;
		}

		case 120: // 'x'
		{
			py = py-0.01 * radius;
			reloadCamera();
			break;
		}

		case 109: //'m'
		{
			px = px - 0.01 * dx;
			py = py - 0.01 * dy;
			pz = pz - 0.01 * dz;
			reloadCamera();
			break;
		}

		case 110: //'n'
		{
			px = px + 0.01 * dx;
			py = py + 0.01 * dy;
			pz = pz + 0.01 * dz;
			reloadCamera();
			break;
		}

		
		case 27: // ESCAPE
			exit(0); break;
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy){
	switch(key){
		case GLUT_KEY_RIGHT:
			alfa -= 0.1; 
			break;

		case GLUT_KEY_LEFT:
			alfa += 0.1;
			break;

		case GLUT_KEY_UP:
			teta += 0.1;
			break;

		case GLUT_KEY_DOWN:
			teta -= 0.1;
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
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	if (argc == 2) {
		if (parser.loadXML(argv[1]) == XML_SUCCESS) {
			bool sucess = parser.parse();
			if (sucess) {
				if (prepareData(&parser.grupo)) {
					prepareLights();
					createVBOs();
					initCamera();
					reloadCamera();
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
