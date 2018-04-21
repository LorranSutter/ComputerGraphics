#include "Bloco.h"

Bloco::Bloco(){
}

Bloco::Bloco(float *c, float tamx, float tamy, float tamz){
    this->c = c;
    this->tamx = tamx;
    this->tamy = tamy;
    this->tamz = tamz;
    this->p1[0] = c[0]-tamx/2;
    this->p2[0] = c[0]+tamx/2;
    this->p1[1] = c[1]-tamy/2;
    this->p2[1] = c[1]+tamy/2;
    this->p1[2] = c[2]-tamz/2;
    this->p2[2] = c[2]+tamz/2;

    this->texDef = false;

    this->calculaNormais();
}

Bloco::Bloco(float *c, float tamx, float tamy, float tamz, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho){
    this->c = c;
    this->tamx = tamx;
    this->tamy = tamy;
    this->tamz = tamz;
    this->p1[0] = c[0]-tamx/2;
    this->p2[0] = c[0]+tamx/2;
    this->p1[1] = c[1]-tamy/2;
    this->p2[1] = c[1]+tamy/2;
    this->p1[2] = c[2]-tamz/2;
    this->p2[2] = c[2]+tamz/2;
    this->luz_ambiente = luz_ambiente;
    this->luz_difusa = luz_difusa;
    this->luz_especular = luz_especular;
    this->luz_emissao = luz_emissao;
    this->luz_brilho = luz_brilho;

    this->texDef = false;

    this->calculaNormais();
}

Bloco::Bloco(float *c, float tamx, float tamy, float tamz, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, glcTexture *textureManeger){
    this->c = c;
    this->tamx = tamx;
    this->tamy = tamy;
    this->tamz = tamz;
    this->p1[0] = c[0]-tamx/2;
    this->p2[0] = c[0]+tamx/2;
    this->p1[1] = c[1]-tamy/2;
    this->p2[1] = c[1]+tamy/2;
    this->p1[2] = c[2]-tamz/2;
    this->p2[2] = c[2]+tamz/2;
    this->luz_ambiente = luz_ambiente;
    this->luz_difusa = luz_difusa;
    this->luz_especular = luz_especular;
    this->luz_emissao = luz_emissao;
    this->luz_brilho = luz_brilho;
    this->textureManeger = textureManeger;
    for(int k = 0; k < 6; k++) this->face_tex_ids[k] = 0;
    this->texDef = true;

    this->calculaNormais();
}

Bloco::Bloco(float *c, float tamx, float tamy, float tamz, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, glcTexture *textureManeger, int face_tex_ids[6]){
    this->c = c;
    this->tamx = tamx;
    this->tamy = tamy;
    this->tamz = tamz;
    this->p1[0] = c[0]-tamx/2;
    this->p2[0] = c[0]+tamx/2;
    this->p1[1] = c[1]-tamy/2;
    this->p2[1] = c[1]+tamy/2;
    this->p1[2] = c[2]-tamz/2;
    this->p2[2] = c[2]+tamz/2;
    this->luz_ambiente = luz_ambiente;
    this->luz_difusa = luz_difusa;
    this->luz_especular = luz_especular;
    this->luz_emissao = luz_emissao;
    this->luz_brilho = luz_brilho;
    this->textureManeger = textureManeger;
    for(int k = 0; k < 6; k++) this->face_tex_ids[k] = face_tex_ids[k];
    this->texDef = true;

    this->calculaNormais();
}

void Bloco::calculaNormais(){
    float v[3];
    crossNorm(this->p2[0]-this->p1[0],
              this->p1[1]-this->p1[1],
              this->p1[2]-this->p1[2],
              this->p2[0]-this->p1[0],
              this->p2[1]-this->p1[1],
              this->p1[2]-this->p1[2],
                                      v);
    normais[0][0] = v[0];
    normais[0][1] = v[1];
    normais[0][2] = v[2];

    crossNorm(this->p2[0]-this->p2[0],
              this->p1[1]-this->p1[1],
              this->p1[2]-this->p2[2],
              this->p2[0]-this->p2[0],
              this->p2[1]-this->p1[1],
              this->p1[2]-this->p2[2],
                                      v);
    normais[1][0] = v[0];
    normais[1][1] = v[1];
    normais[1][2] = v[2];

    crossNorm(this->p2[0]-this->p2[0],
              this->p2[1]-this->p2[1],
              this->p1[2]-this->p2[2],
              this->p1[0]-this->p2[0],
              this->p2[1]-this->p2[1],
              this->p1[2]-this->p2[2],
                                      v);
    normais[2][0] = v[0];
    normais[2][1] = v[1];
    normais[2][2] = v[2];

    crossNorm(this->p1[0]-this->p1[0],
              this->p2[1]-this->p2[1],
              this->p1[2]-this->p2[2],
              this->p1[0]-this->p1[0],
              this->p1[1]-this->p2[1],
              this->p1[2]-this->p2[2],
                                      v);
    normais[3][0] = v[0];
    normais[3][1] = v[1];
    normais[3][2] = v[2];

    crossNorm(this->p1[0]-this->p1[0],
              this->p1[1]-this->p1[1],
              this->p1[2]-this->p2[2],
              this->p2[0]-this->p1[0],
              this->p1[1]-this->p1[1],
              this->p1[2]-this->p2[2],
                                      v);
    normais[4][0] = v[0];
    normais[4][1] = v[1];
    normais[4][2] = v[2];

    crossNorm(this->p2[0]-this->p1[0],
              this->p2[1]-this->p2[1],
              this->p1[2]-this->p1[2],
              this->p2[0]-this->p1[0],
              this->p1[1]-this->p2[1],
              this->p1[2]-this->p1[2],
                                      v);
    normais[5][0] = v[0];
    normais[5][1] = v[1];
    normais[5][2] = v[2];
}

void Bloco::invert_normals(){
    for(int k = 0; k < 6; k++){
        this->normais[k][0] = -this->normais[k][0];
        this->normais[k][1] = -this->normais[k][1];
        this->normais[k][2] = -this->normais[k][2];
    }
}
