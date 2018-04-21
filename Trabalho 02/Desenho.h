#ifndef DESENHO_H_INCLUDED
#define DESENHO_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "Funcoes.h"
#include "Esfera.h"
#include "Rebatedor.h"
#include "Bloco.h"
#include "Retangulo.h"
#include "Poste.h"

#define PLANO_XY1 1
#define PLANO_XY2 2
#define PLANO_XZ1 3
#define PLANO_XZ2 4
#define PLANO_YZ1 5
#define PLANO_YZ2 6

using namespace std;

void setMaterial_1side(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *emissao, GLfloat brilho);
void setMaterial_2side(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *emissao, GLfloat brilho);
void desenhaEsfera(Esfera e);
void desenhaBloco(Bloco b);
void desenhaRebatedor(Rebatedor r);
void makeCostura(Rebatedor r);
void desenhaPoste(Poste p);
void desenhaRetangulo(Retangulo *ret, float ortho[]);
void desenhaTitulo(float ortho[]);
void desenhaTitRanking(float ortho[]);
void drawPlane(float px1, float py1, float px2, float py2, int num_sub, int plano);
void drawPlane(float *p1, float *p2, int num_sub, int plano);
void drawPlane(float *p1, float *p2, float dist, int num_sub, int plano);
void desenhaLevel(string level_LEVEL, int level_num, float cor_level[3], float ortho[]);
void desenhaPause(string pause_PAUSE, string pause_jogo, string pause_cam, string pause_spot, string pause_esc, float cor_pause[3], float w, float h, float ortho[]);
void desenhaTempo(int tempo, float cor_tempo[3], float ortho[]);
void desenhaPlacar(int placar_reb1, int placar_reb2, float cor_placar_reb1[3], float cor_placar_reb2[3], float cor_placar[3], float ortho[]);

#endif // DESENHO_H_INCLUDED
