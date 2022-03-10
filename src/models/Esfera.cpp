#include "Esfera.h"

using namespace Modelos;

Vertice::Vertice(float x,float y,float z) {
        this->x = x;
        this->y = y;
        this->z = z;
}

Esfera::Esfera(int r,int sli,int sta){
        raio = r;
        slices = sli;
        stacks = sta;
}

void Esfera::saveModel(std::ofstream &file) {
	
	float sliceStep = 2 * M_PI / slices;
    float stackStep = M_PI / stacks;

	for (int i = 0; i < stacks; i++)
	{
		float stackAngle = M_PI_2 - i * stackStep;
		float stackAngle2 = M_PI_2 - (i + 1) * stackStep;
		float xy = raio * cos(stackAngle); float xy2 = raio * cos(stackAngle2);
		float y = raio * sin(stackAngle); float y2 = raio * sin(stackAngle2);
		
		for (int j = 0; j < slices; j++)
		{
			float sliceAngle = j * sliceStep;
			float sliceAngle2 = (j+1) * sliceStep;
			float x1 = xy * sin(sliceAngle);float x2 = xy * sin(sliceAngle2);
			float z1 = xy * cos(sliceAngle);float z2 = xy * cos(sliceAngle2);

			float x3 = xy2 * sin(sliceAngle); float x4 = xy2 * sin(sliceAngle2);
			float z3 = xy2 * cos(sliceAngle); float z4 = xy2 * cos(sliceAngle2);

/*           Stack entre as slides j e j+1
			Para desenhar cada stack basta ligar os vertices formando um quadrado
			(x1,z1) ------------- (x2,z2)
			   |                     |
			   |                     |
			   |                     | 
			   |                     |
			   |                     |
			(x3,z3) ------------- (x4,z4)   */
			
			writeV(file,x1,y,z1);
			writeV(file,x3,y2,z3);
			writeV(file,x4,y2,z4);

			writeV(file,x4,y2,z4);
			writeV(file,x2,y,z2);
			writeV(file,x1,y,z1);

		}
	}
}