#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

float norma(float *v);
float dot(float *v1, float *v2);
float angulo_vetores(float *v1, float *v2);
float distancia(float *v1, float *v2);
float distancia_point_line(float *p0, float *p1, float *p2);

float *ponto_medio(float *v1, float *v2);

/**
 ** Produto vetorial entre dois vetores
 ** v3 eh normalizado
 **/
void crossNorm(float x1, float y1, float z1, float x2, float y2, float z2, float (&v)[3]);
float *rotation_Axis_Vector(float *v, float theta, float Ux, float Uy, float Uz);

void normalize(float (&v)[3]);
void normalize(float *v);

float *getMin(float v1[3], float v2[3]);
float *getMax(float v1[3], float v2[3]);

bool dentroConeSpot(float *ponto, float *fonte, float *direcao, float cutoff);

int *convert_int_to_time(int time);
string convert_int_to_time_string(int time);

#endif // FUNCOES_H_INCLUDED
