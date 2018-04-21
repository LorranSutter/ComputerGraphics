#include "Retangulo.h"

Retangulo::Retangulo(float x1, float y1, float x2, float y2, float r, float g, float b, string nome){
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->r = r;
    this->g = g;
    this->b = b;
    this->nome = nome;
}

bool Retangulo::isInside(float x, float y){
    return x > this->x1 and x < this->x2 and y < this->y1 and y > this->y2;
}

void Retangulo::setColor(float cor[3]){
    this->r = cor[0];
    this->g = cor[1];
    this->b = cor[2];
}
