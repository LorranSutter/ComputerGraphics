#include "Desenho.h"

void setMaterial_1side(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *emissao, GLfloat brilho){
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
    glMaterialf (GL_FRONT, GL_SHININESS, brilho);
}

void setMaterial_2side(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *emissao, GLfloat brilho){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

void desenhaEsfera(Esfera e){
    setMaterial_1side(e.luz_ambiente,e.luz_difusa,e.luz_especular,e.luz_emissao,e.luz_brilho);
    glPushMatrix();
        glTranslatef(e.c[0],e.c[1],e.c[2]);
        glutSolidSphere(e.raio,30,30);
    glPopMatrix();
}

/*
void desenhaBloco(Bloco b){
    setMaterial_1side(b.luz_ambiente,b.luz_difusa,b.luz_especular,b.luz_emissao,b.luz_brilho);

    glBegin(GL_QUADS);
        glNormal3fv(b.normais[0]);
        glVertex3f(b.p1[0],b.p1[1],b.p2[2]);
        glVertex3f(b.p2[0],b.p1[1],b.p2[2]);
        glVertex3f(b.p2[0],b.p2[1],b.p2[2]);
        glVertex3f(b.p1[0],b.p2[1],b.p2[2]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3fv(b.normais[1]);
        glVertex3f(b.p2[0],b.p1[1],b.p2[2]);
        glVertex3f(b.p2[0],b.p1[1],b.p1[2]);
        glVertex3f(b.p2[0],b.p2[1],b.p1[2]);
        glVertex3f(b.p2[0],b.p2[1],b.p2[2]);
    glEnd();
    /*
    glBegin(GL_QUADS);
        glNormal3fv(b.normais[2]);
        glVertex3f(b.p2[0],b.p2[1],b.p2[2]);
        glVertex3f(b.p2[0],b.p2[1],b.p1[2]);
        glVertex3f(b.p1[0],b.p2[1],b.p1[2]);
        glVertex3f(b.p1[0],b.p2[1],b.p2[2]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3fv(b.normais[3]);
        glVertex3f(b.p1[0],b.p2[1],b.p2[2]);
        glVertex3f(b.p1[0],b.p2[1],b.p1[2]);
        glVertex3f(b.p1[0],b.p1[1],b.p1[2]);
        glVertex3f(b.p1[0],b.p1[1],b.p2[2]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3fv(b.normais[4]);
        glVertex3f(b.p1[0],b.p1[1],b.p2[2]);
        glVertex3f(b.p1[0],b.p1[1],b.p1[2]);
        glVertex3f(b.p2[0],b.p1[1],b.p1[2]);
        glVertex3f(b.p2[0],b.p1[1],b.p2[2]);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3fv(b.normais[5]);
        glVertex3f(b.p1[0],b.p2[1],b.p1[2]);
        glVertex3f(b.p2[0],b.p2[1],b.p1[2]);
        glVertex3f(b.p2[0],b.p1[1],b.p1[2]);
        glVertex3f(b.p1[0],b.p1[1],b.p1[2]);
    glEnd();

}
*/

void desenhaBloco(Bloco b){
    setMaterial_1side(b.luz_ambiente,b.luz_difusa,b.luz_especular,b.luz_emissao,b.luz_brilho);

    glNormal3fv(b.normais[0]);
    drawPlane(b.p1,b.p2,b.p2[2],30,PLANO_XY1);

    glNormal3fv(b.normais[1]);
    drawPlane(b.p1,b.p2,b.p2[0],30,PLANO_YZ1);

    glNormal3fv(b.normais[2]);
    drawPlane(b.p1,b.p2,b.p2[1],30,PLANO_XZ1);

    glNormal3fv(b.normais[3]);
    drawPlane(b.p1,b.p2,b.p1[0],30,PLANO_YZ2);

    glNormal3fv(b.normais[4]);
    drawPlane(b.p1,b.p2,b.p1[1],30,PLANO_XZ2);

    glNormal3fv(b.normais[5]);
    drawPlane(b.p1,b.p2,b.p1[2],30,PLANO_XY2);
}

void desenhaRebatedor(Rebatedor r){
    setMaterial_1side(r.luz_ambiente,r.luz_difusa,r.luz_especular,r.luz_emissao,r.luz_brilho);
    glBegin(GL_POLYGON);
        glNormal3fv(r.normais[0]);
        for(int k = 0; k < r.num_pontos; k++)
            glVertex3fv(r.pontos[k]);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3fv(r.normais[1]);
        for(int k = r.num_pontos-1; k >= 0; k--)
            glVertex3f(r.pontos[k][0],r.pontos[k][1]+r.espessura,r.pontos[k][2]);
    glEnd();

    makeCostura(r);
}

void makeCostura(Rebatedor r){
    int num = r.num_pontos;
    float esp = r.espessura;
    glBegin(GL_TRIANGLE_STRIP);
        for(int k = 0; k < num-1; k++){
            glNormal3fv(r.normais[k+2]);
            glVertex3fv(r.pontos[k]);
            glVertex3f (r.pontos[k][0],r.pontos[k][1]+esp,r.pontos[k][2]);
        }
        glVertex3fv(r.pontos[num-1]);
        glVertex3f (r.pontos[num-1][0],r.pontos[num-1][1]+esp,r.pontos[num-1][2]);
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
        glNormal3fv(r.normais[num+1]);
        glVertex3fv(r.pontos[num-1]);
        glVertex3f (r.pontos[num-1][0],r.pontos[num-1][1]+esp,r.pontos[num-1][2]);
        glVertex3fv(r.pontos[0]);
        glVertex3f (r.pontos[0][0],r.pontos[0][1]+esp,r.pontos[0][2]);
    glEnd();
}

void desenhaPoste(Poste p){
    setMaterial_1side(p.luz_ambiente,p.luz_difusa,p.luz_especular,p.luz_emissao,p.luz_brilho);

    glPushMatrix();

        glTranslatef(p.c_base[0],p.c_base[1],p.c_base[2]);
        glRotatef(p.angulo,0.0,1.0,0.0);

        glRotatef(-90.0,1.0,0.0,0.0);
        glutSolidCylinder(p.raio,p.altura,20.0,10.0);

        glRotatef(90.0,1.0,0.0,0.0);
        glTranslatef(0.0,p.altura,0.0);
        glRotatef(-15.0,1.0,0.0,0.0);

        //glDisable(GL_LIGHTING);
        //glEnable(GL_COLOR_MATERIAL);

        glBegin(GL_QUAD_STRIP);
            //parte interna da tampinha
            glVertex3f(-p.frente+p.raio, -p.raio, p.comprimento-p.raio);//1
            glVertex3f(-p.tras+p.raio,   -p.raio, -p.raio);//2
            glVertex3f(-p.frente+p.raio, 0.0,     p.comprimento-p.raio);//3
            glVertex3f(-p.tras+p.raio,   0.0,     -p.raio);//4
            glVertex3f(p.frente-p.raio,  0.0,     p.comprimento-p.raio);//5
            glVertex3f(p.tras-p.raio,    0.0,     -p.raio);//6
            glVertex3f(p.frente-p.raio,  -p.raio, p.comprimento-p.raio);//7
            glVertex3f(p.tras-p.raio,    -p.raio, -p.raio);//8
            //parte externa da tampinha
            glVertex3f(p.frente,         -p.raio, p.comprimento-p.raio);//9
            glVertex3f(p.tras,           -p.raio, -p.raio);//10
            glVertex3f(p.frente,         p.raio,  p.comprimento-p.raio);//11
            glVertex3f(p.tras,           p.raio,  -p.raio);//12
            glVertex3f(-p.frente,        p.raio,  p.comprimento-p.raio);//13
            glVertex3f(-p.tras,          p.raio,  -p.raio);//14
            glVertex3f(-p.frente,        -p.raio, p.comprimento-p.raio);//15
            glVertex3f(-p.tras,          -p.raio, -p.raio);//16
            glVertex3f(-p.frente+p.raio, -p.raio, p.comprimento-p.raio);//1
            glVertex3f(-p.tras+p.raio,   -p.raio, -p.raio);//2
        glEnd();

            //parte frontal da tampinha
        glBegin(GL_QUADS);
            glVertex3f(-p.frente+p.raio, -p.raio, p.comprimento-p.raio);
            glVertex3f(-p.frente+p.raio, 0.0,     p.comprimento-p.raio);
            glVertex3f(-p.frente,        0.0,     p.comprimento-p.raio);
            glVertex3f(-p.frente,        -p.raio, p.comprimento-p.raio);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-p.frente, 0.0,    p.comprimento-p.raio);
            glVertex3f(p.frente,  0.0,    p.comprimento-p.raio);
            glVertex3f(p.frente,  p.raio, p.comprimento-p.raio);
            glVertex3f(-p.frente, p.raio, p.comprimento-p.raio);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(p.frente,        -p.raio, p.comprimento-p.raio);
            glVertex3f(p.frente,        0.0,     p.comprimento-p.raio);
            glVertex3f(p.frente-p.raio, 0.0,     p.comprimento-p.raio);
            glVertex3f(p.frente-p.raio, -p.raio, p.comprimento-p.raio);
        glEnd();

            //parte traseira da tampinha
        glBegin(GL_QUADS);
            glVertex3f(-p.tras,        -p.raio, -p.raio);
            glVertex3f(-p.tras,        0.0,     -p.raio);
            glVertex3f(-p.tras+p.raio, 0.0,     -p.raio);
            glVertex3f(-p.tras+p.raio, -p.raio, -p.raio);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-p.tras, p.raio, -p.raio);
            glVertex3f(p.tras,  p.raio, -p.raio);
            glVertex3f(p.tras,  0.0,    -p.raio);
            glVertex3f(-p.tras, 0.0,    -p.raio);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(p.tras-p.raio, -p.raio, -p.raio);
            glVertex3f(p.tras-p.raio, 0.0,     -p.raio);
            glVertex3f(p.tras,        0.0,     -p.raio);
            glVertex3f(p.tras,        -p.raio, -p.raio);
        glEnd();

    glPopMatrix();

    //glEnable(GL_LIGHTING);
    //glDisable(GL_COLOR_MATERIAL);
}

void desenhaRetangulo(Retangulo *ret, float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glColor3f(0.0,0.0,0.0);
    glRasterPos2f(ret->x2-fabs(ret->x2-ret->x1)/2,ret->y1-fabs(ret->y1-ret->y2)/2);
    for(int i = 0; i < ret->nome.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , ret->nome[i]);
    }

    glBegin(GL_QUADS);
        glColor3f(ret->r,ret->g,ret->b);
        glVertex3f(ret->x1, ret->y1, 0.0);
        glVertex3f(ret->x1, ret->y2, 0.0);
        glVertex3f(ret->x2, ret->y2, 0.0);
        glVertex3f(ret->x2, ret->y1, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);

        glVertex3f(ret->x2+ortho_diff_x*0.005, ret->y1-ortho_diff_y*0.01, 0.0);
        glVertex3f(ret->x2+ortho_diff_x*0.005, ret->y2-ortho_diff_y*0.01, 0.0);
        glVertex3f(ret->x1+ortho_diff_x*0.005, ret->y2-ortho_diff_y*0.01, 0.0);
    glEnd();
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

void drawPlane(float px1, float py1, float px2, float py2, int num_sub, int plano){
    float dx = fabs(px2-px1) / num_sub;
    float dy = fabs(py2-py1) / num_sub;

    if(plano == PLANO_XY1){
        glNormal3f(0.0, 0.0, 1.0);
        for(float i = px1; i < px2; i += dx) {
            glBegin(GL_QUADS);
            for(float j = py1; j < py2; j += dy) {
                glVertex3f(i, j,0);
                glVertex3f(i, j+dx,0);
                glVertex3f(i+dy, j+dx,0);
                glVertex3f(i+dy, j,0);
            }
            glEnd();
        }
    }
    if(plano == PLANO_XZ1){
        glNormal3f(0.0, 1.0, 0.0);
        for(float i = px1; i < px2; i += dx) {
            glBegin(GL_QUADS);
            for(float j = py1; j < py2; j += dy) {
                glVertex3f(i, 0, j);
                glVertex3f(i, 0, j+dx);
                glVertex3f(i+dy, 0, j+dx);
                glVertex3f(i+dy, 0, j);
            }
            glEnd();
        }
    }
    else if(plano == PLANO_YZ1){
        glNormal3f(1.0, 0.0, 0.0);
        for(float i = px1; i < px2; i += dx) {
            glBegin(GL_QUADS);
            for(float j = py1; j < py2; j += dy) {
                glVertex3f(0,i, j);
                glVertex3f(0,i, j+dx);
                glVertex3f(0,i+dy, j+dx);
                glVertex3f(0,i+dy, j);
            }
            glEnd();
        }
    }
}

void drawPlane(float *p1, float *p2, int num_sub, int plano){
    float dx;
    float dy;

    if(plano == PLANO_XY1){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[1]-p1[1]) / num_sub;
        //glNormal3f(0.0, 0.0, 1.0);
        for(float i = p1[0]; i < p2[0]; i += dx) {
            glBegin(GL_QUADS);
            for(float j = p1[1]; j < p2[1]; j += dy) {
                glVertex3f(i, j,p2[2]);
                glVertex3f(i+dx, j,p2[2]);
                glVertex3f(i+dx, j+dy,p2[2]);
                glVertex3f(i, j+dy,p2[2]);
            }
            glEnd();
        }
    }
    if(plano == PLANO_XZ1){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[2]-p1[2]) / num_sub;
        //glNormal3f(0.0, 1.0, 0.0);
        for(float i = p1[0]; i < p2[0]; i += dx) {
            glBegin(GL_QUADS);
            for(float j = p1[2]; j < p2[2]; j += dy) {
                glVertex3f(i, p2[1], j);
                glVertex3f(i+dx, p2[1], j);
                glVertex3f(i+dx, p2[1], j+dy);
                glVertex3f(i, p2[1], j+dy);
            }
            glEnd();
        }
    }
    else if(plano == PLANO_YZ1){
        dx = fabs(p2[1]-p1[1]) / num_sub;
        dy = fabs(p2[2]-p1[2]) / num_sub;
        //glNormal3f(1.0, 0.0, 0.0);
        for(float i = p1[1]; i < p2[1]; i += dx) {
            glBegin(GL_QUADS);
            for(float j = p1[2]; j < p2[2]; j += dy) {
                glVertex3f(0,i, j);
                glVertex3f(0,i, j+dx);
                glVertex3f(0,i+dy, j+dx);
                glVertex3f(0,i+dy, j);
            }
            glEnd();
        }
    }
}

void drawPlane(float *p1, float *p2, float dist, int num_sub, int plano){
    float dx;
    float dy;

    if(plano == PLANO_XY1){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[1]-p1[1]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy   ,dist);
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy   ,dist);
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy+dy,dist);
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy+dy,dist);
            }
            glEnd();
        }
    }
    else if(plano == PLANO_XY2){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[1]-p1[1]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy   ,dist);
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy+dy,dist);
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy+dy,dist);
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy   ,dist);
            }
            glEnd();
        }
    }
    else if(plano == PLANO_XZ1){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[2]-p1[2]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy   );
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy+dy);
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy+dy);
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy   );
            }
            glEnd();
        }
    }
    else if(plano == PLANO_XZ2){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[2]-p1[2]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy   );
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy   );
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy+dy);
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy+dy);
            }
            glEnd();
        }
    }
    else if(plano == PLANO_YZ1){
        dx = fabs(p2[1]-p1[1]) / num_sub;
        dy = fabs(p2[2]-p1[2]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy   );
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy   );
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy+dy);
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy+dy);
            }
            glEnd();
        }
    }
    else if(plano == PLANO_YZ2){
        dx = fabs(p2[1]-p1[1]) / num_sub;
        dy = fabs(p2[2]-p1[2]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy   );
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy+dy);
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy+dy);
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy   );
            }
            glEnd();
        }
    }
}

void desenhaLevel(string level_LEVEL, int level_num, float cor_level[3], float ortho[]){
    glColor3fv(cor_level);
    glRasterPos2f(ortho[1]*0.1,ortho[3]*0.7);
    for(int k = 0; k < level_LEVEL.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, level_LEVEL[k]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+level_num);
}

void desenhaPause(string pause_PAUSE, string pause_jogo, string pause_cam, string pause_spot, string pause_esc, float cor_pause[3], float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor3fv(cor_pause);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.9);
    for(int k = 0; k < pause_PAUSE.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pause_PAUSE[k]);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.2);
    for(int k = 0; k < pause_jogo.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pause_jogo[k]);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.15);
    for(int k = 0; k < pause_cam.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pause_cam[k]);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.1);
    for(int k = 0; k < pause_spot.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pause_spot[k]);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.05);
    for(int k = 0; k < pause_esc.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pause_esc[k]);
}

void desenhaTempo(int tempo, float cor_tempo[3], float ortho[]){
    int minuto1 = tempo/3600;
    int minuto2 = minuto1%10;
    minuto1 = minuto1/10%6;
    int seg1 = tempo/60;
    int seg2 = seg1%10;
    seg1 = seg1/10%6;
    int mili1 = tempo%60;
    int mili2 = mili1%10;
    mili1 /= 10;

    glColor3fv(cor_tempo);
    glRasterPos2f(ortho[1]*0.1,ortho[3]*0.9);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+minuto1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+minuto2);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+seg1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+seg2);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+mili1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+mili2);
}

void desenhaPlacar(int placar_reb1, int placar_reb2, float cor_placar_reb1[3], float cor_placar_reb2[3], float cor_placar[3], float ortho[]){
    glColor3fv(cor_placar_reb1);
    glRasterPos2f(ortho[1]*0.1,ortho[3]*0.8);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+placar_reb1);
    glColor3fv(cor_placar);
    glRasterPos2f(ortho[1]*0.3,ortho[3]*0.8);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
    glColor3fv(cor_placar_reb2);
    glRasterPos2f(ortho[1]*0.5,ortho[3]*0.8);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+placar_reb2);
}
