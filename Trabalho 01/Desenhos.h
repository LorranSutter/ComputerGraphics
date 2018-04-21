#ifndef DESENHOS_H_INCLUDED
#define DESENHOS_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <cmath>

#include "Auxiliares.h"

using namespace std;

void desenhaElipse(Elipse *eli);
void desenhaCirculo(Circulo *circ);
void desenhaQuadrado(Quadrado *quad, float ortho[]);
void desenhaTitulo(float ortho[]);
void desenhaTitRanking(float ortho[]);
void desenhaLinha(float ortho[]);
void desenhaTimer(int tempo_vet[], float ortho[]);
void desenhaPlacar(int placar_one, int placar_two, float ortho[]);

#endif // DESENHOS_H_INCLUDED
