#include "Funcoes.h"

float norma(float *v){
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

float dot(float *v1, float *v2){
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

float angulo_vetores(float *v1, float *v2){
    //cout << "Angulo vetores funcao" << endl;
    //cout << dot(v1,v2) << " " << norma(v1) << " " << norma(v2) << endl;
    float res = dot(v1,v2)/(norma(v1)*norma(v2));
    res = res < -1 ? M_PI : res > 1 ? 0 : acos(res);
    //cout << res  << endl;
    return res;
}

float distancia(float *v1, float *v2){
    return sqrt((v2[0]-v1[0])*(v2[0]-v1[0]) + (v2[1]-v1[1])*(v2[1]-v1[1]) + (v2[2]-v1[2])*(v2[2]-v1[2]));
}

/// Referencia: https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
float distancia_point_line(float *p0, float *p1, float *p2){
    return fabs((p2[2]-p1[2])*p0[0] - (p2[0]-p1[0])*p0[2] + p2[0]*p1[2] - p2[2]*p1[0])/sqrt((p2[2]-p1[2])*(p2[2]-p1[2]) + (p2[0]-p1[0])*(p2[0]-p1[0]));
}

float *ponto_medio(float *v1, float *v2){
    float *v = new float[3];
    v[0] = (v2[0]+v1[0])/2;
    v[1] = (v2[1]+v1[1])/2;
    v[2] = (v2[2]+v1[2])/2;
    return v;
}

/**
 ** Produto vetorial entre dois vetores
 **/
void crossNorm(float x1, float y1, float z1, float x2, float y2, float z2, float (&v)[3]){
    v[0]  = y1*z2-z1*y2;
    v[1]  = z1*x2-x1*z2;
    v[2]  = x1*y2-y1*x2;

    float normal;
    normal  = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

    if(normal != 0){
        v[0] /= normal;
        v[1] /= normal;
        v[2] /= normal;
    }
}

/**
 ** Retorna um vetor rotacionado com angulo theta torno de um eixo arbitrario
 ** v        -> vetor a ser rotacionado
 ** theta    -> angulo de rotacao
 ** Ux,Uy,Uz -> componentes do eixo referencia para a rotacao
 **/
float *rotation_Axis_Vector(float *v, float theta, float Ux, float Uy, float Uz){
    float R_00 = cos(theta) + Ux*Ux*(1-cos(theta));
    float R_10 = Ux*Uy*(1-cos(theta)) + Uz*sin(theta);
    float R_20 = Ux*Uz*(1-cos(theta)) - Uy*sin(theta);
    float R_01 = Ux*Uy*(1-cos(theta)) - Uz*sin(theta);
    float R_11 = cos(theta) + Uy*Uy*(1-cos(theta));
    float R_21 = Uy*Uz*(1-cos(theta)) + Ux*sin(theta);
    float R_02 = Ux*Uz*(1-cos(theta)) + Uy*sin(theta);
    float R_12 = Uy*Uz*(1-cos(theta)) - Ux*sin(theta);
    float R_22 = cos(theta) + Uz*Uz*(1-cos(theta));

    float *v_rot = new float[3];
    v_rot[0] = v[0]*R_00 + v[1]*R_01 + v[2]*R_02;
    v_rot[1] = v[0]*R_10 + v[1]*R_11 + v[2]*R_12;
    v_rot[2] = v[0]*R_20 + v[1]*R_21 + v[2]*R_22;

    return v_rot;
}

void normalize(float (&v)[3]){
    float nor = norma(v);
    v[0] /= nor;
    v[1] /= nor;
    v[2] /= nor;
}

void normalize(float *v){
    float nor = norma(v);
    v[0] /= nor;
    v[1] /= nor;
    v[2] /= nor;
}

float *getMin(float v1[3], float v2[3]){
    if(v1[0] < v2[0]) return v1;
    if(v2[0] < v1[0]) return v2;
    if(v1[1] < v2[1]) return v1;
    if(v2[1] < v1[1]) return v2;
    if(v1[2] < v2[2]) return v1;
    if(v2[2] < v1[2]) return v2;
}

float *getMax(float v1[3], float v2[3]){
    if(v1[0] > v2[0]) return v1;
    if(v2[0] > v1[0]) return v2;
    if(v1[1] > v2[1]) return v1;
    if(v2[1] > v1[1]) return v2;
    if(v1[2] > v2[2]) return v1;
    if(v2[2] > v1[2]) return v2;
}

bool dentroConeSpot(float *ponto, float *fonte, float *direcao, float cutoff){
    float v_fonte_ponto[] = {ponto[0]-fonte[0],ponto[1]-fonte[1],ponto[2]-fonte[2]};
    return angulo_vetores(v_fonte_ponto,direcao) <= cutoff*M_PI/180 ? true : false;
}

int *convert_int_to_time(int time){
    static int tempo[6];
    tempo[0] = time/3600/10;
    tempo[1] = time/3600%10;
    tempo[2] = time/60%60/10;
    tempo[3] = time/60%60%10;
    tempo[4] = time%60/10;
    tempo[5] = time%60%10;
    return tempo;
}

string convert_int_to_time_string(int time){
    string str;
    stringstream m1;
    m1 << time/3600/10;
    str = m1.str();

    stringstream m2;
    m2 << time/3600%10;
    str += m2.str();
    str += ":";

    stringstream s1;
    s1 << time/60%60/10;
    str += s1.str();

    stringstream s2;
    s2 << time/60%60%10;
    str += s2.str();
    str += ":";

    stringstream m3;
    m3 << time%60/10;
    str += m3.str();

    stringstream m4;
    m4 << time%60%10;
    str += m4.str();

    return str;
}
