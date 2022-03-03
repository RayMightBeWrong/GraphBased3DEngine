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

char *file;

float length = 0;
float subDivisions = 0;

int figure = 0;

void writeV(std::ofstream& myFile, float x, float y, float z){
	myFile << x; myFile << " ";
	myFile << y; myFile << " ";
	myFile << z; myFile << "\n";
}

void writePlaneTXY(std::ofstream& myFile, float l1, float l2, float factor){
        writeV(myFile, l1, l2, length*factor);
        writeV(myFile, l1+length/subDivisions, l2, length*factor);
        writeV(myFile, l1, l2+length/subDivisions, length*factor);
                
        writeV(myFile, l1+length/subDivisions, l2+length/subDivisions, length*factor);
        writeV(myFile, l1, l2+length/subDivisions, length*factor);
        writeV(myFile, l1+length/subDivisions, l2, length*factor);
}

void writePlaneTXZ(std::ofstream& myFile, float l1, float l2, float factor){
        writeV(myFile, l1+length/subDivisions, length*factor, l2);
        writeV(myFile, l1, length*factor, l2);
        writeV(myFile, l1, length*factor, l2+length/subDivisions);
                
        writeV(myFile, l1, length*factor, l2+length/subDivisions);
        writeV(myFile, l1+length/subDivisions, length*factor, l2+length/subDivisions);
        writeV(myFile, l1+length/subDivisions, length*factor, l2);
}

void writePlaneTYZ(std::ofstream& myFile, float l1, float l2, float factor){
        writeV(myFile, length*factor, l1, l2);
        writeV(myFile, length*factor, l1+length/subDivisions, l2);
        writeV(myFile, length*factor, l1, l2+length/subDivisions);
                
        writeV(myFile, length*factor, l1+length/subDivisions, l2+length/subDivisions);
        writeV(myFile, length*factor, l1, l2+length/subDivisions);
        writeV(myFile, length*factor, l1+length/subDivisions, l2);
}


void writePlane(std::ofstream& myFile){
	for (float x = -length/2; x < length/2; x += length/subDivisions) {
		for (float z = -length/2; z < length/2; z += length/subDivisions) {
			writePlaneTXZ(myFile, x, z, 0);
		}
	}
}

void writeCube(std::ofstream& myFile){
	for (float l1 = -length/2; l1 < length/2; l1 += length/subDivisions) {
		for (float l2 = -length/2; l2 < length/2; l2 += length/subDivisions) {
			writePlaneTXZ(myFile, l1, l2, 0.5);
			writePlaneTXY(myFile, l1, l2, 0.5);
			writePlaneTYZ(myFile, l1, l2, 0.5);
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
		}
		length = atoi(argv[2]);
		subDivisions = atoi(argv[3]);

		file = (char *) malloc(sizeof(char) * strlen(argv[4]));
		strcpy(file, argv[4]);
	}
	else if (argc == 6 && !strcmp(argv[1], "sphere")){
		figure = 1;
		file = (char *) malloc(sizeof(char) * strlen(argv[4]));
		strcpy(file, argv[4]);
	}
	else if (argc == 7 && !strcmp(argv[1], "cone")){
		figure = 3;
		file = (char *) malloc(sizeof(char) * strlen(argv[4]));
		strcpy(file, argv[4]);
	}
	else return 0;
	
	return 1;
}

int main(int argc, char **argv) {
	if(handleInput(argc, argv) == 1){
		std::ofstream myfile(file);
		switch(figure){
			case 2:
				writeCube(myfile); break;

			case 4:
				writePlane(myfile); break;

			default:
				printf("oof\n"); break;
		}
  		myfile.close();
	}

	return 1;
}
