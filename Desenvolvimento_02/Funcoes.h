#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

using namespace std;

/**
 ** Funcao inspirada no codigo da curva de Bezier do link: https://rosettacode.org/wiki/Bitmap/B%C3%A9zier_curves/Cubic#C
 ** O embasamento matematico das funcoes bases foi inspirado nos slides da disciplina
 **/
float **cubic_Bspline(float x1, float y1,
                      float x2, float y2,
                      float x3, float y3,
                      float x4, float y4,
                      int num_seg);

/**
 ** Calcula a distancia entre dois pontos
 **/
float distancia(float x1, float y1, float x2, float y2);

/**
 ** Retorna o indice do ponto da lista_pontos mais proximo de (x,y) com tolerancia de distancia tol_dist
 ** Caso nao haja ponto proximo de acordo com a tolerancia, a funcao retona -1
 **/
int maisProximo(vector< float* > lista_pontos, float x, float y, float tol_dist);

/**
 ** Calcula quais os dois pontos mais proximos de (x,y) e, dentre esses, retorna o mais proximo ao inicio da lista
 ** Caso nao haja pontos o suficiente na lista, a funcao retona -1
 **/
int primeiroMaisProximo(vector< float* > lista_pontos, float x, float y);

vector< float* > obterPontos_B_Spline(vector< float* > v, float precision);
vector< float* > obterPontos_B_Spline_fechada(vector< float* > v, float precision);

/**
 ** Produto vetorial entre dois vetores
 ** v3 eh normalizado
 **/
void crossNorm(float *v1, float *v2, float (&v3)[3]);

/**
 ** Retorna um vetor rotacionado com angulo theta torno de um eixo arbitrario
 ** v        -> vetor a ser rotacionado
 ** theta    -> angulo de rotacao
 ** Ux,Uy,Uz -> componentes do eixo referencia para a rotacao
 **/
vector< float* > rotation_Axis_Points(vector< float* > v, float theta, float Ux, float Uy, float Uz);

/**
 ** Define material
 **/
void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *brilho, GLfloat *emissao);

/**
 ** Salva arquivo da curva
 **/
void salva_arquivo(const char* arq, vector< float* > v);

/**
 ** Le arquivo da curva
 **/
void le_arquivo(const char* arq, vector< float* > &v);

#endif // FUNCOES_H_INCLUDED
