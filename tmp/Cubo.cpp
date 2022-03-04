#include <GL/glut.h>

class Cubo : public Modelo {
    public:
        int tamanho;
        float subDivisions;
        Cubo(int tam,float sub) : Modelo(){
            tamanho = tam;
            subDivisions = sub;
        }
        void draw();
    private:
        void drawPlaneTXY(float z);
        void drawPlaneTXZ(float y);
        void drawPlaneTYZ(float x);
		void drawPlaneTXYBack(float z);
		void drawPlaneTXZBack(float y);
		void drawPlaneTYZBack(float x);

};

void Cubo::draw(){
	glBegin(GL_TRIANGLES);
	drawPlaneTXZBack(0);
	drawPlaneTXZ(tamanho);
	drawPlaneTXYBack(-tamanho/2.0);
	drawPlaneTXY(tamanho/2.0);
	drawPlaneTYZBack(-tamanho/2.0);
	drawPlaneTYZ(tamanho/2.0);
	glEnd();	
}


void Cubo::drawPlaneTXY(float z){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = 0; y < tamanho; y += step) {
			glVertex3f(x,y,z);
			glVertex3f(x+step,y,z);
			glVertex3f(x+step,y+step,z);
				
			glVertex3f(x+step,y+step,z);
			glVertex3f(x,y+step,z);
			glVertex3f(x,y,z);  
        }
    }
}

void Cubo::drawPlaneTXYBack(float z){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = 0; y < tamanho; y += step) {
			glVertex3f(x+step,y,z);
			glVertex3f(x,y,z);
			glVertex3f(x+step,y+step,z);
				
			glVertex3f(x,y+step,z);
			glVertex3f(x+step,y+step,z);
			glVertex3f(x,y,z);  
        }
    }
}


void Cubo::drawPlaneTXZ(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			glVertex3f(x+step,y,z);
			glVertex3f(x,y,z);
			glVertex3f(x,y,z+step);

			glVertex3f(x,y,z+step);
			glVertex3f(x+step,y,z+step);
			glVertex3f(x+step,y,z);   
    	}
    }
}

void Cubo::drawPlaneTXZBack(float y){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			glVertex3f(x,y,z);
			glVertex3f(x+step,y,z);
			glVertex3f(x,y,z+step);

			glVertex3f(x+step,y,z+step);
			glVertex3f(x,y,z+step);
			glVertex3f(x+step,y,z);   
    	}
    }
}


void Cubo::drawPlaneTYZ(float x){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
    	for (float y = 0; y < tamanho; y += step) {
			glVertex3f(x,y,z+step);
			glVertex3f(x,y,z);
			glVertex3f(x,y+step,z);
				
			glVertex3f(x,y+step,z); 
			glVertex3f(x,y+step,z+step);
			glVertex3f(x,y,	z+step);
    	}
    }	
}

void Cubo::drawPlaneTYZBack(float x){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
    	for (float y = 0; y < tamanho; y += step) {
			glVertex3f(x,y,z);
			glVertex3f(x,y,z+step);
			glVertex3f(x,y+step,z);
				
			glVertex3f(x,y+step,z+step);
			glVertex3f(x,y+step,z); 
			glVertex3f(x,y,	z+step);
    	}
    }	
}