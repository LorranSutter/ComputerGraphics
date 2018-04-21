#ifndef DESENHO_H_INCLUDED
#define DESENHO_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <vector>

#include "Funcoes.h"

#define EIXO_X 1
#define EIXO_Y 2
#define EIXO_Z 3

using namespace std;

/**
 ** Algoritmo de costura de pontos para formacao de uma superficie
 ** Recebe dois vetores com o mesmo tamanho
 **/
void makeCostura(vector< float* > v1, vector< float* > v2);

/**
 ** Algoritmo de costura de pontos para formacao de uma superficie
 ** Recebe dois vetores com o mesmo tamanho
 **/
void makeGrid(float min_1, float max_1, float min_2, float max_2, int eixo1, int eixo2, float num_subdiv, float cor[4]);

/**
 ** Desenha B-Spline
 ** v         -> vetor de pontos de controle
 ** precision -> refinamento da curva
 ** lineWidth -> espessura da curva
 ** cor       -> cor da curva
 **/
void desenhaB_Spline(vector< float* > v, float precision, float lineWidth, float cor_r, float cor_g, float cor_b);

/**
 ** Desenha Pontos de Controle
 ** v        -> vetor de pontos de controle
 ** tamPonto -> tamanho dos pontos de controle
 ** cor      -> cor do ponto de controle
 **/
void desenhaPontos_Controle(vector< float* > v, float tamPonto, float cor_r, float cor_g, float cor_b);

/**
 ** Desenha Poligono de Controle
 ** v         -> vetor de pontos de controle
 ** lineWidth -> espessura do poligono
 ** cor       -> cor do ponto de controle
 **/
void desenhaPoligono_Controle(vector< float* > v, float lineWidth, float cor_r, float cor_g, float cor_b);

/**
 ** Desenha Label dos Pontos de Controle
 ** v        -> vetor de pontos de controle
 ** cor      -> cor do ponto de controle
 **/
void desenhaLabel_Pontos_Controle(vector< float* > v, float cor_r, float cor_g, float cor_b);

#endif // DESENHO_H_INCLUDED
