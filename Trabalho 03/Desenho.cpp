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
    glutSolidSphere(e.raio,30,30);
}

void desenhaBloco(Bloco b, int num_sub, bool invertido){

    if(invertido) b.invert_normals();

    setMaterial_1side(b.luz_ambiente,b.luz_difusa,b.luz_especular,b.luz_emissao,b.luz_brilho);

    glNormal3fv(b.normais[0]);
    !b.texDef ? drawPlane(b.p1,b.p2,b.p2[2],num_sub,invertido ? PLANO_XY2 : PLANO_XY1) : drawPlane(b.p1,b.p2,b.p2[2],num_sub,invertido ? PLANO_XY2 : PLANO_XY1,b.textureManeger,b.face_tex_ids[0]);

    glNormal3fv(b.normais[1]);
    !b.texDef ? drawPlane(b.p1,b.p2,b.p2[0],num_sub,invertido ? PLANO_YZ2 : PLANO_YZ1) : drawPlane(b.p1,b.p2,b.p2[0],num_sub,invertido ? PLANO_YZ2 : PLANO_YZ1,b.textureManeger,b.face_tex_ids[1]);

    glNormal3fv(b.normais[2]);
    !b.texDef ? drawPlane(b.p1,b.p2,b.p2[1],num_sub,invertido ? PLANO_XZ2 : PLANO_XZ1) : drawPlane(b.p1,b.p2,b.p2[1],num_sub,invertido ? PLANO_XZ2 : PLANO_XZ1,b.textureManeger,b.face_tex_ids[2]);

    glNormal3fv(b.normais[3]);
    !b.texDef ? drawPlane(b.p1,b.p2,b.p1[0],num_sub,invertido ? PLANO_YZ1 : PLANO_YZ2) : drawPlane(b.p1,b.p2,b.p1[0],num_sub,invertido ? PLANO_YZ1 : PLANO_YZ2,b.textureManeger,b.face_tex_ids[3]);

    glNormal3fv(b.normais[4]);
    !b.texDef ? drawPlane(b.p1,b.p2,b.p1[1],num_sub,invertido ? PLANO_XZ1 : PLANO_XZ2) : drawPlane(b.p1,b.p2,b.p1[1],num_sub,invertido ? PLANO_XZ1 : PLANO_XZ2,b.textureManeger,b.face_tex_ids[4]);

    glNormal3fv(b.normais[5]);
    !b.texDef ? drawPlane(b.p1,b.p2,b.p1[2],num_sub,invertido ? PLANO_XY1 : PLANO_XY2) : drawPlane(b.p1,b.p2,b.p1[2],num_sub,invertido ? PLANO_XY1 : PLANO_XY2,b.textureManeger,b.face_tex_ids[5]);
}

void desenhaRebatedor(Rebatedor r){
    setMaterial_1side(r.luz_ambiente,r.luz_difusa,r.luz_especular,r.luz_emissao,r.luz_brilho);

    if(r.texDef){
        r.textureManeger->SetColorMode(GL_BLEND);
        r.textureManeger->Update();
        r.textureManeger->Bind(0);

        int c = 0;
        glBegin(GL_POLYGON);
            glNormal3fv(r.normais[0]);
            glTexCoord2f(0.0,0.0);
            for(int k = 0; k < r.num_pontos; k++){
                if     (c == 0) glTexCoord2f(0.0,0.0);
                else if(c == 1) glTexCoord2f(0.0,1.0);
                else if(c == 2) glTexCoord2f(1.0,1.0);
                else if(c == 3) glTexCoord2f(1.0,0.0);
                glVertex3fv(r.pontos[k]);

                c = c >= 3 ? 0 : c+1;
            }
        glEnd();
        c = 0;
        glBegin(GL_POLYGON);
            glNormal3fv(r.normais[1]);
            for(int k = r.num_pontos-1; k >= 0; k--){
                if     (c == 0) glTexCoord2f(0.0,0.0);
                else if(c == 1) glTexCoord2f(0.0,1.0);
                else if(c == 2) glTexCoord2f(1.0,1.0);
                else if(c == 3) glTexCoord2f(1.0,0.0);
                glVertex3f(r.pontos[k][0],r.pontos[k][1]+r.espessura,r.pontos[k][2]);

                c = c >= 3 ? 0 : c+1;
            }
        glEnd();

        r.textureManeger->SetColorMode(GL_MODULATE);
        r.textureManeger->Disable();

    }else{
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
    }

    makeCostura(r);
}

void makeCostura(Rebatedor r){
    int num = r.num_pontos;
    float esp = r.espessura;

    if(r.texDef){
        r.textureManeger->Update();
        r.textureManeger->Bind(1);

        glBegin(GL_TRIANGLE_STRIP);
            int k;
            for(k = 0; k < num-1; k++){
                glNormal3fv(r.normais[k+2]);
                k%2 == 0 ? glTexCoord2f(0.0,0.0) : glTexCoord2f(0.0,1.0);
                glVertex3fv(r.pontos[k]);
                k%2 == 0 ? glTexCoord2f(1.0,0.0) : glTexCoord2f(1.0,1.0);
                glVertex3f (r.pontos[k][0],r.pontos[k][1]+esp,r.pontos[k][2]);
            }
            k%2 == 0 ? glTexCoord2f(0.0,0.0) : glTexCoord2f(0.0,1.0);
            glVertex3fv(r.pontos[num-1]);
            k%2 == 0 ? glTexCoord2f(1.0,0.0) : glTexCoord2f(1.0,1.0);
            glVertex3f (r.pontos[num-1][0],r.pontos[num-1][1]+esp,r.pontos[num-1][2]);
        glEnd();

        r.textureManeger->SetColorMode(GL_BLEND);
        r.textureManeger->Bind(2);
        r.textureManeger->Update();
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3fv(r.normais[num+1]);
            (k+1)%2 == 0 ? glTexCoord2f(0.0,0.0) : glTexCoord2f(0.0,2.0);
            glVertex3fv(r.pontos[num-1]);
            (k+1)%2 == 0 ? glTexCoord2f(2.0,0.0) : glTexCoord2f(2.0,2.0);
            glVertex3f (r.pontos[num-1][0],r.pontos[num-1][1]+esp,r.pontos[num-1][2]);
            k%2 == 0 ? glTexCoord2f(0.0,0.0) : glTexCoord2f(0.0,2.0);
            glVertex3fv(r.pontos[0]);
            k%2 == 0 ? glTexCoord2f(2.0,0.0) : glTexCoord2f(2.0,2.0);
            glVertex3f (r.pontos[0][0],r.pontos[0][1]+esp,r.pontos[0][2]);
        glEnd();

        r.textureManeger->SetColorMode(GL_BLEND);
        r.textureManeger->Disable();

    }else{
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
}

void desenhaRetangulo(Retangulo *ret, float ortho[]){
    float ortho_diff_x = ortho[1] - ortho[0];
    float ortho_diff_y = ortho[3] - ortho[2];

    glColor3f(0.0,0.0,0.0);
    glRasterPos2f(ret->x2-fabs(ret->x2-ret->x1)/2 - ret->nome.size()*0.017*fabs(ret->x2-ret->x1)/2,ret->y1-fabs(ret->y1-ret->y2)/2);
    for(int i = 0; i < ret->nome.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , ret->nome[i]);
    }

    if(ret->texDef){
        ret->textureManager->Update();
        ret->textureManager->Bind(ret->currentBind);

        glBegin(GL_QUADS);
            glColor3f(ret->r,ret->g,ret->b);
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(ret->x1, ret->y1, 0.0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(ret->x1, ret->y2, 0.0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(ret->x2, ret->y2, 0.0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(ret->x2, ret->y1, 0.0);
        glEnd();

        ret->textureManager->Disable();
    }else{
        glBegin(GL_QUADS);
            glColor3f(ret->r,ret->g,ret->b);
            glVertex3f(ret->x1, ret->y1, 0.0);
            glVertex3f(ret->x1, ret->y2, 0.0);
            glVertex3f(ret->x2, ret->y2, 0.0);
            glVertex3f(ret->x2, ret->y1, 0.0);
        glEnd();
    }

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 1.0);

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

void drawPlane(float *p1, float *p2, float dist, int num_sub, int plano, glcTexture *texture, int id_texture){
    float dx;
    float dy;

    float tex_pass = 1.0/num_sub;

    texture->Update();
    texture->Bind(id_texture);

    if(plano == PLANO_XY1){
        dx = fabs(p2[0]-p1[0]) / num_sub;
        dy = fabs(p2[1]-p1[1]) / num_sub;
        for(float i = 0; i < num_sub; i++) {
            glBegin(GL_QUADS);
            for(float j = 0; j < num_sub; j++) {
                glTexCoord2f(tex_pass*i, tex_pass*j);
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy   ,dist);
                glTexCoord2f(tex_pass*(i+1), tex_pass*j);
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy   ,dist);
                glTexCoord2f(tex_pass*(i+1), tex_pass*(j+1));
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy+dy,dist);
                glTexCoord2f(tex_pass*i, tex_pass*(j+1));
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
                glTexCoord2f(tex_pass*i, tex_pass*j);
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy   ,dist);
                glTexCoord2f(tex_pass*i, tex_pass*(j+1));
                glVertex3f(p1[0] + i*dx   , p1[1] + j*dy+dy,dist);
                glTexCoord2f(tex_pass*(i+1), tex_pass*(j+1));
                glVertex3f(p1[0] + i*dx+dx, p1[1] + j*dy+dy,dist);
                glTexCoord2f(tex_pass*(i+1), tex_pass*j);
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
                glTexCoord2f(tex_pass*i, tex_pass*j);
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy   );
                glTexCoord2f(tex_pass*i, tex_pass*(j+1));
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy+dy);
                glTexCoord2f(tex_pass*(i+1), tex_pass*(j+1));
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy+dy);
                glTexCoord2f(tex_pass*(i+1), tex_pass*j);
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
                glTexCoord2f(tex_pass*i, tex_pass*j);
                glVertex3f(p1[0] + i*dx   , dist, p1[2] + j*dy   );
                glTexCoord2f(tex_pass*(i+1), tex_pass*j);
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy   );
                glTexCoord2f(tex_pass*(i+1), tex_pass*(j+1));
                glVertex3f(p1[0] + i*dx+dx, dist, p1[2] + j*dy+dy);
                glTexCoord2f(tex_pass*i, tex_pass*(j+1));
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
                glTexCoord2f(tex_pass*i, tex_pass*j);
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy   );
                glTexCoord2f(tex_pass*(i+1), tex_pass*j);
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy   );
                glTexCoord2f(tex_pass*(i+1), tex_pass*(j+1));
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy+dy);
                glTexCoord2f(tex_pass*i, tex_pass*(j+1));
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
                glTexCoord2f(tex_pass*i, tex_pass*j);
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy   );
                glTexCoord2f(tex_pass*i, tex_pass*(j+1));
                glVertex3f(dist, p1[1] + i*dx   , p1[2] + j*dy+dy);
                glTexCoord2f(tex_pass*(i+1), tex_pass*(j+1));
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy+dy);
                glTexCoord2f(tex_pass*(i+1), tex_pass*j);
                glVertex3f(dist, p1[1] + i*dx+dx, p1[2] + j*dy   );
            }
            glEnd();
        }
    }

    texture->Disable();
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

void desenhaPause(string pause_PAUSE, string pause_jogo, string pause_cam, string pause_spot, string press_esc, float cor_pause[3], float w, float h, float ortho[]){
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
    for(int k = 0; k < press_esc.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_esc[k]);
}

void desenhaVenceu(string venceu_VENCEU, string venceu_escreveNome, string venceu_nome, float cor_venceu[3], float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor3fv(cor_venceu);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.9);
    for(int k = 0; k < venceu_VENCEU.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, venceu_VENCEU[k]);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.5);
    for(int k = 0; k < venceu_escreveNome.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, venceu_escreveNome[k]);
    for(int k = 0; k < venceu_nome.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, venceu_nome[k]);
}

void desenhaVenceuNoRank(string venceu_VENCEU, string press_enter, string press_esc, float cor_venceu[3], float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor3fv(cor_venceu);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.9);
    for(int k = 0; k < venceu_VENCEU.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, venceu_VENCEU[k]);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.5);
    for(int k = 0; k < press_enter.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_enter[k]);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.45);
    for(int k = 0; k < press_esc.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_esc[k]);
}

void desenhaPerdeu(string perdeu_PERDEU, string press_enter, string press_esc, float cor_perdeu[3], float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor3fv(cor_perdeu);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.9);
    for(int k = 0; k < perdeu_PERDEU.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, perdeu_PERDEU[k]);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.5);
    for(int k = 0; k < press_enter.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_enter[k]);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.45);
    for(int k = 0; k < press_esc.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_esc[k]);
}

void desenhaVenceu2p(string venceu2p_VENCEU, string press_enter, string press_esc, int venceu2p_vencedor, float cor_venceu2p[3], float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor3fv(cor_venceu2p);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.9);
    for(int k = 0; k < venceu2p_VENCEU.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, venceu2p_VENCEU[k]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48+venceu2p_vencedor);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.5);
    for(int k = 0; k < press_enter.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_enter[k]);
    glRasterPos2f(ortho[1]*0.335,ortho[3]*0.45);
    for(int k = 0; k < press_esc.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, press_esc[k]);
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

void desenhaPlacar2d(int placar_reb1, int placar_reb2, float cor_placar_reb1[3], float cor_placar_reb2[3], float cor_placar[3], float ortho[]){
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

int createBlock(Bloco b, int num_sub, bool invertido){
    GLuint id;
	id = glGenLists(1);
	if(!id) return id;

	glNewList(id, GL_COMPILE);
        desenhaBloco(b,num_sub,invertido);
	glEndList();

	return id;
}

int createSphere(Esfera e){
    GLuint id;
	id = glGenLists(1);
	if(!id) return id;

	glNewList(id, GL_COMPILE);
        desenhaEsfera(e);
	glEndList();

	return id;
}

int createRebatedor(Rebatedor r){
    GLuint id;
	id = glGenLists(1);
	if(!id) return id;

	glNewList(id, GL_COMPILE);
        desenhaRebatedor(r);
	glEndList();

	return id;
}

int createPoste(Poste p){
    GLuint id;
	id = glGenLists(1);
	if(!id) return id;

	glNewList(id, GL_COMPILE);
        desenhaPoste(p);
	glEndList();

	return id;
}

int createPlacar3d(Bloco placar1, Bloco placar31, Bloco placar32, int num_sub){
    GLuint id;
	id = glGenLists(1);
	if(!id) return id;

	glNewList(id, GL_COMPILE);
        desenhaBloco(placar1 ,num_sub,false);
        desenhaBloco(placar31,num_sub,false);
        desenhaBloco(placar32,num_sub,false);
	glEndList();

	return id;
}

int createScore3d(Bloco placar21, Bloco placar22, int num_sub){
GLuint id;
	id = glGenLists(1);
	if(!id) return id;

	glNewList(id, GL_COMPILE);
        desenhaBloco(placar21,num_sub,false);
        desenhaBloco(placar22,num_sub,false);
	glEndList();

	return id;
}

void glShadowProjection(float * l, float * e, float * n){
    float d, c;
  	float mat[16];

  	// These are c and d (corresponding to the tutorial)
  	d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
  	c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

  	// Create the matrix. OpenGL uses column by column ordering
  	mat[0]  = l[0]*n[0]+c;
  	mat[4]  = n[1]*l[0];
  	mat[8]  = n[2]*l[0];
  	mat[12] = -l[0]*c-l[0]*d;

  	mat[1]  = n[0]*l[1];
  	mat[5]  = l[1]*n[1]+c;
  	mat[9]  = n[2]*l[1];
  	mat[13] = -l[1]*c-l[1]*d;

  	mat[2]  = n[0]*l[2];
  	mat[6]  = n[1]*l[2];
  	mat[10] = l[2]*n[2]+c;
  	mat[14] = -l[2]*c-l[2]*d;

  	mat[3]  = n[0];
  	mat[7]  = n[1];
  	mat[11] = n[2];
  	mat[15] = -d;

  	// Finally multiply the matrices together *plonk*
  	glMultMatrixf(mat);
}
