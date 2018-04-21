#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include <iostream>
#include <GL/glut.h>

#include "Funcoes.h"
#include "glcTexture.h"

using namespace std;

class Esfera{
	public:
		float *c;
		float raio;
		GLfloat *luz_ambiente, *luz_difusa, *luz_especular, *luz_emissao;
		GLfloat luz_brilho;
		float *v;
		float velocidade;

		Esfera();
		Esfera(float *c, float raio);
		Esfera(float *c, float raio, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho);
		Esfera(float *c, float raio, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, float *v, float velocidade);

		~Esfera();
};

#endif // ESFERA_H_INCLUDED
