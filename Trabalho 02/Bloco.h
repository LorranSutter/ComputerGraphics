#ifndef BLOCO_H_INCLUDED
#define BLOCO_H_INCLUDED

#include <iostream>
#include <GL/glut.h>

#include "Funcoes.h"

using namespace std;

class Bloco{
    private:
        void calculaNormais();

    public:
        float *c;
        float tamx, tamy, tamz;
        float p1[3], p2[3];
        float normais[6][3];
		GLfloat *luz_ambiente, *luz_difusa, *luz_especular, *luz_emissao;
		GLfloat luz_brilho;

		Bloco();
		Bloco(float *c, float tamx, float tamy, float tamz);
		Bloco(float *c, float tamx, float tamy, float tamz, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho);
};

#endif // BLOCO_H_INCLUDED
