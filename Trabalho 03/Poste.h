#ifndef POSTE_H_INCLUDED
#define POSTE_H_INCLUDED

#include <iostream>
#include <GL/glut.h>

#include "Funcoes.h"
#include "glcTexture.h"

using namespace std;

class Poste{
	public:
		float *c_base;
		float raio;
		float altura;
		float angulo;
		float frente;
		float tras;
		float comprimento;
		GLfloat *luz_ambiente, *luz_difusa, *luz_especular, *luz_emissao;
		GLfloat luz_brilho;

		Poste();
		Poste(float *c_base, float raio, float altura, float angulo, float frente, float tras, float comprimento);
		Poste(float *c_base, float raio, float altura, float angulo, float frente, float tras, float comprimento, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho);

		~Poste();
};

#endif // POSTE_H_INCLUDED
