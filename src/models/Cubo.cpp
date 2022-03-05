#include <GL/glut.h>
class Cubo : public Modelo {
    public:
        int tamanho;
        float subDivisions;
        Cubo(int tam,float sub) : Modelo(){
            tamanho = tam;
            subDivisions = sub;
        }
		void saveModel(std::ofstream &file);
    private:
        void savePlaneTXY(float z,std::ofstream &file);
        void savePlaneTXZ(float y,std::ofstream &file);
        void savePlaneTYZ(float x,std::ofstream &file);
		void savePlaneTXYBack(float z,std::ofstream &file);
		void savePlaneTXZBack(float y,std::ofstream &file);
		void savePlaneTYZBack(float x,std::ofstream &file);

};

void Cubo::saveModel(std::ofstream &file){
	savePlaneTXZBack(0,file);
	savePlaneTXZ(tamanho,file);
	savePlaneTXYBack(-tamanho/2.0,file);
	savePlaneTXY(tamanho/2.0,file);
	savePlaneTYZBack(-tamanho/2.0,file);
	savePlaneTYZ(tamanho/2.0,file);
}


void Cubo::savePlaneTXY(float z,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = 0; y < tamanho; y += step) {
			writeV(file,x,y,z);
			writeV(file,x+step,y,z);
			writeV(file,x+step,y+step,z);
				
			writeV(file,x+step,y+step,z);
			writeV(file,x,y+step,z);
			writeV(file,x,y,z);  
        }
    }
}

void Cubo::savePlaneTXYBack(float z,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
        for (float y = 0; y < tamanho; y += step) {
			writeV(file,x+step,y,z);
			writeV(file,x,y,z);
			writeV(file,x+step,y+step,z);
				
			writeV(file,x,y+step,z);
			writeV(file,x+step,y+step,z);
			writeV(file,x,y,z);  
        }
    }
}


void Cubo::savePlaneTXZ(float y,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			writeV(file,x+step,y,z);
			writeV(file,x,y,z);
			writeV(file,x,y,z+step);

			writeV(file,x,y,z+step);
			writeV(file,x+step,y,z+step);
			writeV(file,x+step,y,z);   
    	}
    }
}

void Cubo::savePlaneTXZBack(float y,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float x = -tamanho/2; x < tamanho/2; x += step) {
    	for (float z = -tamanho/2; z < tamanho/2; z += step) {
			writeV(file,x,y,z);
			writeV(file,x+step,y,z);
			writeV(file,x,y,z+step);

			writeV(file,x+step,y,z+step);
			writeV(file,x,y,z+step);
			writeV(file,x+step,y,z);   
    	}
    }
}


void Cubo::savePlaneTYZ(float x,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
    	for (float y = 0; y < tamanho; y += step) {
			writeV(file,x,y,z+step);
			writeV(file,x,y,z);
			writeV(file,x,y+step,z);

			writeV(file,x,y+step,z); 
			writeV(file,x,y+step,z+step);
			writeV(file,x,y,	z+step);
    	}
    }	
}

void Cubo::savePlaneTYZBack(float x,std::ofstream &file){
	float step = tamanho/subDivisions;
	for (float z = -tamanho/2; z < tamanho/2; z += step) {
    	for (float y = 0; y < tamanho; y += step) {
			writeV(file,x,y,z);
			writeV(file,x,y,z+step);
			writeV(file,x,y+step,z);
				
			writeV(file,x,y+step,z+step);
			writeV(file,x,y+step,z); 
			writeV(file,x,y,	z+step);
    	}
    }	
}
