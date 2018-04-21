#include "Desenhos.h"

void desenhaElipse(Elipse *eli){
    glColor3f(eli->r,eli->g,eli->b);
    glBegin(GL_POLYGON);
        for(float theta = 0; theta < 2*M_PI; theta+=eli->prec)
            glVertex2f(eli->raio_maior*cos(theta) + eli->x, eli->raio_menor*sin(theta) + eli->y);
    glEnd();
}

void desenhaCirculo(Circulo *circ){
    glColor3f(circ->r,circ->g,circ->b);
    glBegin(GL_POLYGON);
        for(float theta = 0; theta < 2*M_PI; theta+=0.1)
            glVertex2f(circ->raio*cos(theta)+circ->x,circ->raio*sin(theta)+circ->y);
    glEnd();
}

void desenhaQuadrado(Quadrado *quad, float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glBegin(GL_QUADS);
        glColor3f(quad->r,quad->g,quad->b);
        glVertex3f(quad->x1, quad->y1, 0.0);
        glVertex3f(quad->x2, quad->y1, 0.0);
        glVertex3f(quad->x2, quad->y2, 0.0);
        glVertex3f(quad->x1, quad->y2, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);

        glVertex3f(quad->x2+ortho_diff_x*0.005, quad->y1-ortho_diff_y*0.01, 0.0);
        glVertex3f(quad->x2+ortho_diff_x*0.005, quad->y2-ortho_diff_y*0.01, 0.0);
        glVertex3f(quad->x1+ortho_diff_x*0.005, quad->y2-ortho_diff_y*0.01, 0.0);
    glEnd();


    glColor3f(0.0,0.0,0.0);
    glRasterPos2f(quad->x2-fabs(quad->x2-quad->x1)/2,quad->y1-fabs(quad->y1-quad->y2)/2);
    for(int i = 0; i < quad->nome.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , quad->nome[i]);
    }
}

void desenhaTitulo(float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glColor3f(1.0,1.0,0.0);
    glLineWidth(4);

    //P
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.175*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.175*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.300*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.300*ortho_diff_x+ortho[0],0.775*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.175*ortho_diff_x+ortho[0],0.775*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //O
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.350*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.350*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.475*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.475*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.350*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //N
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.525*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.525*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.650*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.650*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //G
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.825*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.700*ortho_diff_x+ortho[0],0.925*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.700*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.825*ortho_diff_x+ortho[0],0.625*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.825*ortho_diff_x+ortho[0],0.775*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.762*ortho_diff_x+ortho[0],0.775*ortho_diff_y+ortho[2],0.0);
    glEnd();

    glLineWidth(1);
}

void desenhaTitRanking(float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glColor3f(1.0,1.0,0.0);
    glLineWidth(3);

    //R
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.16*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.16*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.24*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.24*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.16*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0.20*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.24*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //A
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.26*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.26*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.34*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.34*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0.26*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.34*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //N
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.36*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.36*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.44*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.44*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //K
    glBegin(GL_LINES);
        glVertex3f(0.46*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.46*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.54*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.46*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.54*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //I
    glBegin(GL_LINES);
        glVertex3f(0.56*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.64*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.60*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.60*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.56*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.64*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //N
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.66*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.66*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.74*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.74*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
    glEnd();

    //G
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.84*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.76*ortho_diff_x+ortho[0],0.94*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.76*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.84*ortho_diff_x+ortho[0],0.86*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.84*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
        glVertex3f(0.80*ortho_diff_x+ortho[0],0.90*ortho_diff_y+ortho[2],0.0);
    glEnd();

    glLineWidth(1);
}

void desenhaLinha(float ortho[]){
    glColor3f(0.4,0.4,0.4);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(ortho[0],0);
        glVertex2f(ortho[1],0);
    glEnd();
}

void desenhaPlacar(int placar_one, int placar_two, float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glColor3f(0.4,0.4,0.4);
    glRasterPos2f(ortho[0]+ortho_diff_x*0.05,ortho_diff_y*0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+placar_one);
    glRasterPos2f(ortho[0]+ortho_diff_x*0.05,-ortho_diff_y*0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+placar_two);
}

void desenhaTimer(int tempo_vet[], float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glColor3f(0.4,0.4,0.4);
    glRasterPos2f(ortho[1]-ortho_diff_x*0.05,ortho_diff_y*0.1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , 48+tempo_vet[0]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , 48+tempo_vet[1]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , ':');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , 48+tempo_vet[2]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , 48+tempo_vet[3]);
}
