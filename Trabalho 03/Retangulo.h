#ifndef RETANGULO_H_INCLUDED
#define RETANGULO_H_INCLUDED

#include <iostream>
#include <GL/glut.h>

#include "glcTexture.h"

using namespace std;

class Retangulo{
    public:
        float x1,y1,x2,y2;
        float r,g,b;
        string nome;

        glcTexture *textureManager;
        int currentBind;
        bool texDef;

        Retangulo(float x1, float y1, float x2, float y2, float r, float g, float b, string nome);
        ~Retangulo();
        Retangulo(float x1, float y1, float x2, float y2, float r, float g, float b, glcTexture *textureManager, string nome);

        bool isInside(float x, float y);
        void setColor(float cor[3]);
};

#endif // RETANGULO_H_INCLUDED
