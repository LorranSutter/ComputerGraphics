#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

float screenWidth = 0;
float screenHeight = 0;
int windowSizeX = 680;
int windowSizeY = 680;
float ortho[6] = {-1.0,1.0,-1.0,1.0,-1.0,1.0};
float ortho_diff_x = ortho[1]-ortho[0];
float ortho_diff_y = ortho[3]-ortho[2];
float objectPosX = windowSizeX/2;
float objectPosY = windowSizeY/2;

int moveX = 0;
int moveY = 0;
bool passiveMotion = false;
int sabaozim = 0;

class Quadrado{
    public:
        float x1,y1,x2,y2;
        float r,g,b;
        string nome;
        Quadrado(float x1, float y1, float x2, float y2, float r, float g, float b, string nome) {this->x1=x1; this->y1=y1; this->x2=x2; this->y2=y2; this->r=r; this->g=g; this->b=b; this->nome=nome;};
};

Quadrado *titulo;
Quadrado *de_1;
Quadrado *de_2;
Quadrado *ranking;
Quadrado *sair;

void desenhaQuadrado(Quadrado *quad);
void keyboard(unsigned char key, int x, int y);
void init();
void mouse(int button, int state, int x, int y);
void display();
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void passivo(int x, int y);

#endif // MENU_H_INCLUDED
