#ifndef REBATEDOR_H_INCLUDED
#define REBATEDOR_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <cmath>

#include "Funcoes.h"
#include "glcTexture.h"

using namespace std;

class Rebatedor{
    private:
        float *c;
        float **pontos_origem;
        float **pontos_medios_origem;

        void calculaPontosMedios();
        void calculaNormais();
        void calculaRaios();

	public:
		float **pontos;
		int num_pontos;
		float espessura;
		float **pontos_medios;
		float **normais;
		GLfloat *luz_ambiente, *luz_difusa, *luz_especular, *luz_emissao;
		GLfloat luz_brilho;
		float raio_maior, raio_menor;
		float vx, vy, vz;
		float velocidade;

		glcTexture *textureManeger;
		bool texDef;

		Rebatedor();
		Rebatedor(float *c);
		Rebatedor(float *c, float **pontos, int num_pontos, float espessura);
		Rebatedor(float *c, float **pontos, int num_pontos, float espessura, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho);
		Rebatedor(float *c, float **pontos, int num_pontos, float espessura, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, float vx, float vy, float vz, float velocidade);
		Rebatedor(float *c, float **pontos, int num_pontos, float espessura, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, float vx, float vy, float vz, float velocidade, glcTexture *textureMagener);

		float *getCentro();
		float **getPontos_origem();

		void setCentro(float *centro);

		~Rebatedor();
};

#endif // REBATEDOR_H_INCLUDED
