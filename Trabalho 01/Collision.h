#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Auxiliares.h"

using namespace std;

void wall_collision(Circulo *circ, float ortho[], int &lado, int &placar_one, int &placar_two, bool &ponto);
void bumper_collision_1(Circulo *circ, Elipse *bumper, float tol, int &lado);
void bumper_collision_2(Circulo *circ, Elipse *bumper, float tol, int &lado);

#endif // COLLISION_H_INCLUDED
