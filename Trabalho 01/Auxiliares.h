#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED

#include <iostream>
#include <cmath>

using namespace std;

class Circulo{
    public:
        float x,y;
        float raio;
        float vetX, vetY;
        float r,g,b;
        Circulo(float x, float y, float raio, float vetX, float vetY, float r, float g, float b);
};

class Elipse{
    public:
        float x, y;
        float raio_menor, raio_maior;
        float prec;
        float velocity;
        float r,g,b;
        Elipse(float x, float y, float raio_menor, float raio_maior, float prec, float velocity, float r, float g, float b);
};

class Quadrado{
    public:
        float x1,y1,x2,y2;
        float r,g,b;
        string nome;
        Quadrado(float x1, float y1, float x2, float y2, float r, float g, float b, string nome);
};

float dot(float x1, float y1, float x2, float y2);
float norma(float x, float y);
float distancia(float x1, float y1, float x2, float y2);

#endif // AUXILIARES_H_INCLUDED
