#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <iostream>
#include <cmath>

#include "Funcoes.h"
#include "Esfera.h"
#include "Bloco.h"
#include "Rebatedor.h"

using namespace std;

bool block_collision(Esfera &e, Bloco &b);
bool bumper_collision(Esfera &e, Rebatedor &r);
//float *bumper_collision(Esfera &e, Rebatedor &r);
float *bumper_collision_aux(float *normal, float *v);
bool is_dist_min_pontos_medios(float *centro, int id_pMedio, Rebatedor &r);
//void bumper_collision(Esfera &e, Rebatedor &r, float tol, int &lado);
//void wall_collision(Esfera *e, int &lado, int &placar_one, int &placar_two, bool &ponto);
//void bumper_collision_2(Circulo *circ, Elipse *bumper, float tol, int &lado);

#endif // COLLISION_H_INCLUDED
