#include "Desenho.h"

/**
 ** Algoritmo de costura de pontos para formacao de uma superficie
 ** Recebe dois vetores com o mesmo tamanho
 **/
void makeCostura(vector< float* > v1, vector< float* > v2){

    int num_pontos = v1.size();

    glBegin(GL_TRIANGLE_STRIP);
        for(int k = 0; k < num_pontos-1; k++){
            float V1[3], V2[3], V3[3];

            V1[0] = v2[k][0]-v1[k][0];
            V1[1] = v2[k][1]-v1[k][1];
            V1[2] = v2[k][2]-v1[k][2];
            V2[0] = v1[k+1][0]-v1[k][0];
            V2[1] = v1[k+1][1]-v1[k][1];
            V2[2] = v1[k+1][2]-v1[k][2];
            crossNorm(V1,V2,V3);

            glNormal3fv(V3);
            glVertex3fv(v1[k]);
            glVertex3fv(v2[k]);
        }
        glVertex3fv(v1[num_pontos-1]);
        glVertex3fv(v2[num_pontos-1]);
    glEnd();
}

/**
 ** Desenha grid
 ** min_1, max_1  -> limites do eixo1
 ** min_2, max_2  -> limites do eixo2
 ** eixo1 e eixo2 -> eixos que definem o plano do grid
 ** num_subdiv    -> numero de subdivisoes do grid
 ** cor[4]        -> cor do grid
 **/
void makeGrid(float min_1, float max_1, float min_2, float max_2, int eixo1, int eixo2, float num_subdiv, float cor[4]){
    float tam1 = max_1-min_1;
    float tam2 = max_2-min_2;
    float meio1 = min_1+tam1/2;
    float meio2 = min_2+tam2/2;

    bool light = glIsEnabled(GL_LIGHTING);

    if(light) glDisable(GL_LIGHTING);
    glLineWidth(2);
    glColor4fv(cor);
    float k1,k2;
    int cont = 0;
    if(eixo1 == EIXO_X and eixo2 == EIXO_Y){
        glColor4f(1,1,1,1);
        glBegin(GL_LINES);
            glVertex3f(meio1,min_2,0);
            glVertex3f(meio1,max_2,0);
            glVertex3f(min_1,meio2,0);
            glVertex3f(max_1,meio2,0);
        glEnd();
        glColor4fv(cor);
        for(k1 = min_1, k2 = min_2; k1 <= max_1; k1+=tam1/num_subdiv, k2+=tam2/num_subdiv){
            if(cont%5 == 0){
                glLineWidth(2);
                glBegin(GL_LINES);
                    glVertex3f(k1,min_2,0);
                    glVertex3f(k1,max_2,0);
                    glVertex3f(min_1,k2,0);
                    glVertex3f(max_1,k2,0);
                glEnd();
            }
            else{
                glLineWidth(1);
                glBegin(GL_LINES);
                    glVertex3f(k1,min_2,0);
                    glVertex3f(k1,max_2,0);
                    glVertex3f(min_1,k2,0);
                    glVertex3f(max_1,k2,0);
                glEnd();
            }
            cont++;
        }
    }
    else if(eixo1 == EIXO_X and eixo2 == EIXO_Z){
        glColor4f(1,1,1,1);
        glBegin(GL_LINES);
            glVertex3f(meio1,0,min_2);
            glVertex3f(meio1,0,max_2);
            glVertex3f(min_1,0,meio2);
            glVertex3f(max_1,0,meio2);
        glEnd();
        glColor4fv(cor);
        for(k1 = min_1, k2 = min_2; k1 <= max_1, k2 <= max_2; k1+=tam1/num_subdiv, k2+=tam2/num_subdiv){
            if(cont%5 == 0){
                glLineWidth(2);
                glBegin(GL_LINES);
                    glVertex3f(k1,0,min_2);
                    glVertex3f(k1,0,max_2);
                    glVertex3f(min_1,0,k2);
                    glVertex3f(max_1,0,k2);
                glEnd();
            }
            else{
                glLineWidth(1);
                glBegin(GL_LINES);
                    glVertex3f(k1,0,min_2);
                    glVertex3f(k1,0,max_2);
                    glVertex3f(min_1,0,k2);
                    glVertex3f(max_1,0,k2);
                glEnd();
            }
            cont++;
        }
    }
    else if(eixo1 == EIXO_Y and eixo2 == EIXO_Z){
        glColor4f(1,1,1,1);
        glBegin(GL_LINES);
            glVertex3f(0,meio1,min_2);
            glVertex3f(0,meio1,max_2);
            glVertex3f(0,min_1,meio2);
            glVertex3f(0,max_1,meio2);
        glEnd();
        glColor4fv(cor);
        for(k1 = min_1, k2 = min_2; k1 <= max_1, k2 <= max_2; k1+=tam1/num_subdiv, k2+=tam2/num_subdiv){
            if(cont%5 == 0){
                glLineWidth(2);
                glBegin(GL_LINES);
                    glVertex3f(0,k1,min_2);
                    glVertex3f(0,k1,max_2);
                    glVertex3f(0,min_1,k2);
                    glVertex3f(0,max_1,k2);
                glEnd();
            }
            else{
                glLineWidth(1);
                glBegin(GL_LINES);
                    glVertex3f(0,k1,min_2);
                    glVertex3f(0,k1,max_2);
                    glVertex3f(0,min_1,k2);
                    glVertex3f(0,max_1,k2);
                glEnd();
            }
            cont++;
        }
    }
    else if(eixo1 == EIXO_Y and eixo2 == EIXO_X){
        glColor4f(1,1,1,1);
        glBegin(GL_LINES);
            glVertex3f(min_2,meio1,0);
            glVertex3f(max_2,meio1,0);
            glVertex3f(meio2,min_1,0);
            glVertex3f(meio2,max_1,0);
        glEnd();
        glColor4fv(cor);
        for(k1 = min_1, k2 = min_2; k1 <= max_1, k2 <= max_2; k1+=tam1/num_subdiv, k2+=tam2/num_subdiv){
            if(cont%5 == 0){
                glLineWidth(2);
                glBegin(GL_LINES);
                    glVertex3f(min_2,k1,0);
                    glVertex3f(max_2,k1,0);
                    glVertex3f(k2,min_1,0);
                    glVertex3f(k2,max_1,0);
                glEnd();
            }
            else{
                glLineWidth(1);
                glBegin(GL_LINES);
                    glVertex3f(min_2,k1,0);
                    glVertex3f(max_2,k1,0);
                    glVertex3f(k2,min_1,0);
                    glVertex3f(k2,max_1,0);
                glEnd();
            }
            cont++;
        }
    }
    else if(eixo1 == EIXO_Z and eixo2 == EIXO_X){
        glColor4f(1,1,1,1);
        glBegin(GL_LINES);
            glVertex3f(min_2,0,meio1);
            glVertex3f(max_2,0,meio1);
            glVertex3f(meio2,0,min_1);
            glVertex3f(meio2,0,max_1);
        glEnd();
        glColor4fv(cor);
        for(k1 = min_1, k2 = min_2; k1 <= max_1, k2 <= max_2; k1+=tam1/num_subdiv, k2+=tam2/num_subdiv){
            if(cont%5 == 0){
                glLineWidth(2);
                glBegin(GL_LINES);
                    glVertex3f(min_2,0,k1);
                    glVertex3f(max_2,0,k1);
                    glVertex3f(k2,0,min_1);
                    glVertex3f(k2,0,max_1);
                glEnd();
            }
            else{
                glLineWidth(1);
                glBegin(GL_LINES);
                    glVertex3f(min_2,0,k1);
                    glVertex3f(max_2,0,k1);
                    glVertex3f(k2,0,min_1);
                    glVertex3f(k2,0,max_1);
                glEnd();
            }
            cont++;
        }
    }
    else if(eixo1 == EIXO_Z and eixo2 == EIXO_Y){
        glColor4f(1,1,1,1);
        glBegin(GL_LINES);
            glVertex3f(0,min_2,meio1);
            glVertex3f(0,max_2,meio1);
            glVertex3f(0,meio2,min_1);
            glVertex3f(0,meio2,max_1);
        glEnd();
        glColor4fv(cor);
        for(k1 = min_1, k2 = min_2; k1 <= max_1, k2 <= max_2; k1+=tam1/num_subdiv, k2+=tam2/num_subdiv){
            if(cont%5 == 0){
                glLineWidth(2);
                glBegin(GL_LINES);
                    glVertex3f(0,min_2,k1);
                    glVertex3f(0,max_2,k1);
                    glVertex3f(0,k2,min_1);
                    glVertex3f(0,k2,max_1);
                glEnd();
            }
            else{
                glLineWidth(1);
                glBegin(GL_LINES);
                    glVertex3f(0,min_2,k1);
                    glVertex3f(0,max_2,k1);
                    glVertex3f(0,k2,min_1);
                    glVertex3f(0,k2,max_1);
                glEnd();
            }
            cont++;
        }
    }

    if(light) glEnable(GL_LIGHTING);
}

/**
 ** Desenha B-Spline
 ** v         -> vetor de pontos de controle
 ** precision -> refinamento da curva
 ** lineWidth -> espessura da curva
 ** cor       -> cor da curva
 **/
void desenhaB_Spline(vector< float* > v, float precision, float lineWidth, float cor_r, float cor_g, float cor_b){

    int num_points = v.size();

    glColor3f(cor_r,cor_g,cor_b);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_STRIP);
        for(int k = 0; k < num_points-3; k++){
            // Calcula os pontos da curva a cada 4 pontos de controle
            float **pts = cubic_Bspline(v[k][0],v[k][1],
                                        v[k+1][0],v[k+1][1],
                                        v[k+2][0],v[k+2][1],
                                        v[k+3][0],v[k+3][1],precision);
            // Os pontos calculados sao desenhados
            for(int p = precision; p > 0; p--) glVertex3fv(pts[p]);
        }
    glEnd();
}

/**
 ** Desenha Pontos de Controle
 ** v        -> vetor de pontos de controle
 ** tamPonto -> tamanho dos pontos de controle
 ** cor      -> cor do ponto de controle
 **/
void desenhaPontos_Controle(vector< float* > v, float tamPonto, float cor_r, float cor_g, float cor_b){
    glColor3f(cor_r,cor_g,cor_b);
    glPointSize(tamPonto);
    glBegin(GL_POINTS);
        for(int k = 0; k < v.size(); k++)
            glVertex3fv(v[k]);
    glEnd();
}

/**
 ** Desenha Poligono de Controle
 ** v         -> vetor de pontos de controle
 ** lineWidth -> espessura do poligono
 ** cor       -> cor do ponto de controle
 **/
void desenhaPoligono_Controle(vector< float* > v, float lineWidth, float cor_r, float cor_g, float cor_b){
    glColor3f(cor_r,cor_g,cor_b);
    glLineWidth(lineWidth);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0xF0F0);
    glBegin(GL_LINE_STRIP);
        for(int k = 0; k < v.size(); k++)
            glVertex3fv(v[k]);
        if(v.size() >= 3) glVertex3fv(v[0]);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

/**
 ** Desenha Label dos Pontos de Controle
 ** v        -> vetor de pontos de controle
 ** cor      -> cor do ponto de controle
 **/
void desenhaLabel_Pontos_Controle(vector< float* > v, float cor_r, float cor_g, float cor_b){
    glColor3f(cor_r,cor_g,cor_b);
    for(int k = 0; k < v.size(); k++){
        glRasterPos2f(v[k][0]+0.01,v[k][1]+0.01);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 'P'); // Caracter P
        if(k < 10) // Caso simples em que o indice do ponto eh menor que 10
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+k);
        else{ // Procedimento para numeracao de pontos com indice maior que 10
            int num = k;
            vector<int> num_v;
            while(num >= 10){
                num_v.insert(num_v.begin(),num%10);
                num /= 10;
            }
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+num);
            for(int w = 0; w < num_v.size(); w++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+num_v[w]);
        }
    }
}
