#include <GL/glut.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

class Vertice
{
public:
    Vertice();
    Vertice(float x,float y,float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float x;
    float y;
    float z;
    
};

class Esfera : public Modelo {

public:
    int raio;
    int slices;
    int stacks;
    Esfera(int r,int sli,int sta) :Modelo(){
        raio = r;
        slices = sli;
        stacks = sta;
    }
	void saveModel(std::ofstream &file);
};

void Esfera::saveModel(std::ofstream &file) {
	
	std::vector<Vertice> vertices;
	float sectorStep = 2 * M_PI / slices;
    float stackStep = M_PI / stacks;

	for (int i = 0; i <= stacks; i++)
	{
		float stackAngle = M_PI_2 - i * stackStep;
		float xy = raio * cos(stackAngle);
		float y = raio * sin(stackAngle);
		
		for (int j = 0; j <= slices; j++)
		{
			float sliceAngle = j * sectorStep;
			float x = xy * sin(sliceAngle);
			float z = xy * cos(sliceAngle);
			
			Vertice v(x,y,z);
			vertices.push_back(v);
		}
	}

	for(int i = 0; i < stacks; ++i)
    {
        int vi1 = i * (slices + 1);           
        int vi2 = (i + 1) * (slices + 1);

        for(int j = 0; j < slices; ++j, ++vi1, ++vi2)
        {
            // get 4 vertices per sector
            //  v1--v3
            //  |    |
            //  v2--v4
            Vertice v1 = vertices[vi1];
            Vertice v2 = vertices[vi2];
            Vertice v3 = vertices[vi1 + 1];
            Vertice v4 = vertices[vi2 + 1];

			writeV(file,v1.x,v1.y,v1.z);
			writeV(file,v2.x,v2.y,v2.z);
			writeV(file,v3.x,v3.y,v3.z);

			writeV(file,v2.x,v2.y,v2.z);
			writeV(file,v4.x,v4.y,v4.z);
			writeV(file,v3.x,v3.y,v3.z);
		}
	}
}
