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

void writeV(ofstream& myFile, float x, float y, float z){
	myFile << x; myFile << " ";
	myFile << y; myFile << " ";
	myFile << z; myFile << "\n";
}

void drawPlane(ofstream& myFile){
	for (float x = -length/2;x < length/2;x += length/subDivisions) {
		for (float z = -length/2;z < length/2;z += length/subDivisions) {
			writeV(myFile,x+length/subDivisions,0,z);
			writeV(myFile,x,0,z);
			writeV(myFile,x,0,z+length/subDivisions);
			
			writeV(myFile,x,0,z+length/subDivisions);
			writeV(myFile,x+length/subDivisions,0,z+length/subDivisions);
			writeV(myFile,x+length/subDivisions,0,z);
		}
	}
}


int handleInput(int argc, char **argv){
	if (argc == 5){
		if(!strcmp(argv[1], "box")){
			figure = 2;
		}
		else if (!strcmp(argv[1], "plane")){
			//tratar dos erros
			figure = 4;
			length = atoi(argv[2]);
			subDivisions = atoi(argv[3]);
		}
		file = (char *) malloc(sizeof(char) * strlen(argv[4]));
		strcpy(file, argv[4]);
	}
	else if (argc == 6 && !strcmp(argv[1], "sphere"))
		figure = 1;
	else if (argc == 7 && !strcmp(argv[1], "cone"))
		figure = 3;
	else return 0;
	
	return 1;
}

int main(int argc, char **argv) {
	if(handleInput(argc, argv) == 1){
		ofstream myfile(file);
		switch(figure){
			case 4:
				drawPlane(myfile); break;

			default:
				printf("oof\n"); break;
		}
  		myfile.close();
	}

	return 1;
}
