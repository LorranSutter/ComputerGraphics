#include "Auxiliares.h"

Circulo::Circulo(float x, float y, float raio, float vetX, float vetY, float r, float g, float b){
    this->x = x;
    this->y = y;
    this->raio = raio;
    this->vetX = vetX;
    this->vetY = vetY;
    this->r = r;
    this->g = g;
    this->b = b;
}

Elipse::Elipse(float x, float y, float raio_menor, float raio_maior, float prec, float velocity, float r, float g, float b){
    this->x = x;
    this->y = y;
    this->raio_menor = raio_menor;
    this->raio_maior = raio_maior;
    this->prec = prec;
    this->velocity = velocity;
    this->r = r;
    this->g = g;
    this->b = b;
}

Quadrado::Quadrado(float x1, float y1, float x2, float y2, float r, float g, float b, string nome){
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->r = r;
    this->g = g;
    this->b = b;
    this->nome = nome;
}

float dot(float x1, float y1, float x2, float y2){
    return x1*x2 + y1*y2;
}

float norma(float x, float y){
    return sqrt(x*x+y*y);
}

float distancia(float x1, float y1, float x2, float y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
