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

/**
 ** Calcula quais os dois pontos mais proximos de (x,y) e, dentre esses, retorna o mais proximo ao inicio da lista
 ** Caso nao haja pontos o suficiente na lista, a funcao retona -1
 **/
int primeiroMaisProximo(vector< float* > lista_pontos, float x, float y){

    /* Tem que terminar, tava com sono e sem paciencia
    if(lista_pontos.size() == 0) return -1;
    if(lista_pontos.size() == 1) return 0;

    float menor_d_ante = distancia(lista_pontos[0][0],lista_pontos[0][1],x,y);
    float menor_d_pont = distancia(lista_pontos[1][0],lista_pontos[1][1],x,y);

    if(lista_pontos.size() == 2) return menor_d_ante < menor_d_pont ? 0 : 1;

    //float menor_d_prox = distancia(lista_pontos[2][0],lista_pontos[2][1],x,y);

    int proximo = 1;
    //float menor_d = distancia(lista_pontos[0][0],lista_pontos[0][1],x,y);
    float d = 0;

    for(int k = 2; k < lista_pontos.size() ; k++){
        menor_d_ante = menor_d_pont;
        d = distancia(lista_pontos[k][0],lista_pontos[k][1],x,y);
        if(d < menor_d_pont){
            menor_d_pont = d;
            proximo = k;
        }
    }
    return distancia(lista_pontos[proximo-1][0],lista_pontos[proximo-1][1],x,y) < distancia(lista_pontos[proximo+1][0],lista_pontos[proximo+1][1],x,y) ? proximo-1 : proximo;
    */
    return -1;
}

vector< float* > obterPontos_B_Spline(vector< float* > v, float precision){
    vector< float* > res;
    int num_points = v.size();
    for(int k = 0; k < num_points-3; k++){
        float **pts = cubic_Bspline(v[k][0],v[k][1],
                                    v[k+1][0],v[k+1][1],
                                    v[k+2][0],v[k+2][1],
                                    v[k+3][0],v[k+3][1],precision);
        // Os pontos calculados sao desenhados
        for(int p = precision; p > 0; p--) res.push_back(pts[p]);
        //if(k%2 != 0) for(int p = precision; p >= 0; p--) res.push_back(pts[p]);
        //else         for(int p = 0; p <= precision; p++) res.push_back(pts[p]);
    }

    return res;
}

vector< float* > obterPontos_B_Spline_fechada(vector< float* > v, float precision){
    vector< float* > res;
    int num_points = v.size();
    for(int k = 0; k < num_points-3; k++){
        float **pts = cubic_Bspline(v[k][0],v[k][1],
                                    v[k+1][0],v[k+1][1],
                                    v[k+2][0],v[k+2][1],
                                    v[k+3][0],v[k+3][1],precision);
        // Os pontos calculados sao desenhados
        for(int p = precision; p >= 0; p--) res.push_back(pts[p]);
        if(num_points >= 4){
            float **pts = cubic_Bspline(v[num_points-3][0],v[num_points-3][1],
                                        v[num_points-2][0],v[num_points-2][1],
                                        v[num_points-1][0],v[num_points-1][1],
                                        v[0           ][0],v[0           ][1],precision);
            for(int p = precision; p >= 0; p--) res.push_back(pts[p]);
                    pts = cubic_Bspline(v[num_points-2][0],v[num_points-2][1],
                                        v[num_points-1][0],v[num_points-1][1],
                                        v[0           ][0],v[0           ][1],
                                        v[1           ][0],v[1           ][1],precision);
            for(int p = precision; p >= 0; p--) res.push_back(pts[p]);
                    pts = cubic_Bspline(v[num_points-1][0],v[num_points-1][1],
                                        v[0           ][0],v[0           ][1],
                                        v[1           ][0],v[1           ][1],
                                        v[2           ][0],v[2           ][1],precision);
            for(int p = precision; p >= 0; p--) res.push_back(pts[p]);
        }
    }

    return res;
}

/**
 ** Produto vetorial entre dois vetores
 **/
void crossNorm(float *v1, float *v2, float (&v3)[3]){
    v3[0]  = v1[1]*v2[2]-v1[2]*v2[1];
    v3[1]  = v1[2]*v2[0]-v1[0]*v2[2];
    v3[2]  = v1[0]*v2[1]-v1[1]*v2[0];

    float normal;
    normal  = sqrt(v3[0]*v3[0]+v3[1]*v3[1]+v3[2]*v3[2]);

    v3[0] /= normal;
    v3[1] /= normal;
    v3[2] /= normal;
}

/**
 ** Retorna um vetor rotacionado com angulo theta torno de um eixo arbitrario
 ** v        -> vetor a ser rotacionado
 ** theta    -> angulo de rotacao
 ** Ux,Uy,Uz -> componentes do eixo referencia para a rotacao
 **/
vector< float* > rotation_Axis_Points(vector< float* > v, float theta, float Ux, float Uy, float Uz){
    float R_00 = cos(theta) + Ux*Ux*(1-cos(theta));
    float R_10 = Ux*Uy*(1-cos(theta)) + Uz*sin(theta);
    float R_20 = Ux*Uz*(1-cos(theta)) - Uy*sin(theta);
    float R_01 = Ux*Uy*(1-cos(theta)) - Uz*sin(theta);
    float R_11 = cos(theta) + Uy*Uy*(1-cos(theta));
    float R_21 = Uy*Uz*(1-cos(theta)) + Ux*sin(theta);
    float R_02 = Ux*Uz*(1-cos(theta)) + Uy*sin(theta);
    float R_12 = Uy*Uz*(1-cos(theta)) - Ux*sin(theta);
    float R_22 = cos(theta) + Uz*Uz*(1-cos(theta));

    vector< float* > v_rot;

    for(int k = 0; k < v.size(); k++){
        float *p = new float[3];
        p[0] = v[k][0]*R_00 + v[k][1]*R_01 + v[k][2]*R_02;
        p[1] = v[k][0]*R_10 + v[k][1]*R_11 + v[k][2]*R_12;
        p[2] = v[k][0]*R_20 + v[k][1]*R_21 + v[k][2]*R_22;
        v_rot.push_back(p);
    }

    return v_rot;
}

/**
 ** Define material
 **/
void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *brilho, GLfloat *emissao){
    // Define os parametros da superficie a ser iluminada
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
}

/**
 ** Salva arquivo da curva
 **/
void salva_arquivo(const char* arq, vector< float* > v){
    ofstream arquivo;
    arquivo.open(arq);

    arquivo << v.size() << endl;
    for(int k = 0; k < v.size(); k++)
        arquivo << v[k][0] << " " << v[k][1] << " " << v[k][2] << endl;

    arquivo.close();
}

/**
 ** Le arquivo da curva
 **/
void le_arquivo(const char* arq, vector< float* > &v){
    ifstream arquivo(arq);

    if(arquivo.good()){
        v.clear();
        int num_pontos;
        arquivo >> num_pontos;
        for(int k = 0; k < num_pontos; k++){
            float *p = new float[3];
            arquivo >> p[0] >> p[1] >> p[2];

            v.push_back(p);
        }

        arquivo.close();
    }else
        cout << "Arquivo inexistente!" << endl;
}
