#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>

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

#endif // FUNCOES_H_INCLUDED
