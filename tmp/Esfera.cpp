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
	
	float sliceCounter = 2 * M_PI/	slices;
	float stackCounter = M_PI/stacks;

	// Calcular os vertices atraves da funçoes parametricas
	for (int i = 0; i <= stacks;i++) {
		//Calcular angulo da stack atual(phi)
		float stackAngle = M_PI_2 - i * stackCounter;

		//Calcular o y com o angulo. y = r * sin(phi)
		float y = raio * sinf(stackAngle);

		// Vector com a posicao de todos os vertices do slice
		std::vector<int> verticesSlice;
		for (int s = 0; s < slices;s++) {
			// Calcular angulo da slice (theta)
			float sliceAngle = s * sliceCounter;
			//Calcular x. x = r * cos(phi) * sin(theta)
			float x = raio * cosf(stackAngle) * sinf(sliceAngle);
			//Calcular z. z = r * cos(phi) * cos(theta)
			float z = raio * cosf(stackAngle) * cosf(sliceAngle);

			Vertice v = Vertice(x,y,z);
			vertices.push_back(v);
			verticesSlice.push_back(vertices.size() - 1);
		}
		indices.push_back(verticesSlice);
	}

	// Percorrer todos os vertices de forma a formar os triangulos
	// Posicao [i][j] do vector dos indices corresponde aos vertices do stack i no slice j
	for (int i = 0; i < stacks; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < slices; j++)
		{
			int index = indices[i][j];
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
