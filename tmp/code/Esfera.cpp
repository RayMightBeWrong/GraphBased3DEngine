#include <GL/glut.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Modelo.cpp"



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
    void draw();
};

void Esfera::draw() {
    std::vector<Vertice> vertices;
	std::vector<std::vector<int>> indices;
	
	float sliceSize = 2 * M_PI/	slices;
	float stackSize = M_PI/stacks;

	for (int i = 0; i <= stacks;i++) {
		float stackAngle = M_PI_2 - i * stackSize;
		float y = raio * sinf(stackAngle);
		std::vector<int> verticesSlice;
		for (int s = 0; s < slices;s++) {
			float sliceAngle = s * sliceSize;
			float x = raio * cosf(stackAngle) * sinf(sliceAngle);
			float z = raio * cosf(stackAngle) * cosf(sliceAngle);
			Vertice v = Vertice(x,y,z);
			vertices.push_back(v);
			verticesSlice.push_back(vertices.size() - 1);
		}
		indices.push_back(verticesSlice);
	}

	for (GLuint i = 0; i < stacks; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (GLuint j = 0; j < slices; j++)
		{
			GLuint index = indices[i][j];
			glVertex3f(vertices[index].x,vertices[index].y,vertices[index].z);
			index = indices[i + 1][j];
			glVertex3f(vertices[index].x,vertices[index].y,vertices[index].z);
			if (j == slices - 1)
			{
				index = indices[i][0];
				glVertex3f(vertices[index].x,vertices[index].y,vertices[index].z);
				index = indices[i+1][0];
				glVertex3f(vertices[index].x,vertices[index].y,vertices[index].z);
			}
		}
	}
	glEnd();
}
