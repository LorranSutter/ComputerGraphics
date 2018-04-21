#include "Funcoes.h"

/**
 ** Funcao inspirada no codigo da curva de Bezier do link: https://rosettacode.org/wiki/Bitmap/B%C3%A9zier_curves/Cubic#C
 ** O embasamento matematico das funcoes bases foi inspirado nos slides da disciplina
 **/
float **cubic_Bspline(float x1, float y1,
                      float x2, float y2,
                      float x3, float y3,
                      float x4, float y4,
                      int num_seg){

    float **pts = new float*[num_seg]; // Matriz com num_seg numero de pontos com 3 coordenadas cada
    for(int i = 0; i <= num_seg; i++){
        float t = (float)i / (float)num_seg;

        // Funcoes base da curva B-Spline
        float a = (1.0/6.0)*pow(t,3.0);
        float b = (1.0/6.0)*(-3*pow(t,3.0) + 3*pow(t,2.0) + 3*t + 1);
        float c = (1.0/6.0)*( 3*pow(t,3.0) - 6*pow(t,2.0) + 4);
        float d = (1.0/6.0)*(-pow(t,3.0) + 3*pow(t,2.0) - 3*t + 1);

        // Ponto obtido atraves das funcoes base
        pts[i] = new float[3];
        pts[i][0] = a * x1 + b * x2 + c * x3 + d * x4;
        pts[i][1] = a * y1 + b * y2 + c * y3 + d * y4;
        pts[i][2] = 0.0;
    }

    return pts;
}

/**
 ** Calcula a distancia entre dois pontos
 **/
float distancia(float x1, float y1, float x2, float y2){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

/**
 ** Retorna o indice do ponto da lista_pontos mais proximo de (x,y) com tolerancia de distancia tol_dist
 ** Caso nao haja ponto proximo de acordo com a tolerancia, a funcao retona -1
 **/
int maisProximo(vector< float* > lista_pontos, float x, float y, float tol_dist){
    int proximo = -1;
    float menor_d = tol_dist*10;
    float d = 0;

    for(int k = 0; k < lista_pontos.size() ; k++){
        d = distancia(lista_pontos[k][0],lista_pontos[k][1],x,y);
        if(d < menor_d and d < tol_dist){
            menor_d = d;
            proximo = k;
        }
    }
    return proximo;
}
