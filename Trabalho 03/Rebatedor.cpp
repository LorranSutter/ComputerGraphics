#include "Rebatedor.h"

Rebatedor::Rebatedor(){
	this->num_pontos = 0;
	this->espessura = 0;
	this->luz_brilho = 0;
	this->raio_maior = 0;
	this->raio_menor = 0;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->velocidade = 0;

	this->texDef = false;
}

Rebatedor::Rebatedor(float *c){
	this->c = c;
	this->num_pontos = 0;
	this->espessura = 0;
	this->luz_brilho = 0;
	this->raio_maior = 0;
	this->raio_menor = 0;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->velocidade = 0;

	this->texDef = false;
}

Rebatedor::Rebatedor(float *c, float **pontos, int num_pontos, float espessura){
	this->c = c;
	this->pontos_origem = new float*[num_pontos];
	this->pontos = pontos;
	for(int k = 0; k < num_pontos; k++){
        this->pontos_origem[k] = new float[3];
        this->pontos_origem[k][0] = pontos[k][0];
        this->pontos_origem[k][1] = pontos[k][1];
        this->pontos_origem[k][2] = pontos[k][2];

        this->pontos[k][0] += this->c[0];
        this->pontos[k][1] += this->c[1];
        this->pontos[k][2] += this->c[2];
	}

	this->num_pontos = num_pontos;
	this->espessura = espessura;
	this->luz_brilho = 0;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->velocidade = 0;

	this->texDef = false;

    this->calculaPontosMedios();
	this->calculaNormais();
	this->calculaRaios();
}

Rebatedor::Rebatedor(float *c, float **pontos, int num_pontos, float espessura, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho){
	this->c = c;
	this->pontos_origem = new float*[num_pontos];
	this->pontos = pontos;
	for(int k = 0; k < num_pontos; k++){
        this->pontos_origem[k] = new float[3];
        this->pontos_origem[k][0] = pontos[k][0];
        this->pontos_origem[k][1] = pontos[k][1];
        this->pontos_origem[k][2] = pontos[k][2];

        this->pontos[k][0] += this->c[0];
        this->pontos[k][1] += this->c[1];
        this->pontos[k][2] += this->c[2];
	}

	this->num_pontos = num_pontos;
	this->espessura = espessura;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->luz_emissao = luz_emissao;
	this->luz_brilho = luz_brilho;
	this->vx = 0;
	this->vy = 0;
	this->vz = 0;
	this->velocidade = 0;

	this->texDef = false;

    this->calculaPontosMedios();
	this->calculaNormais();
	this->calculaRaios();
}

Rebatedor::Rebatedor(float *c, float **pontos, int num_pontos, float espessura, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, float vx, float vy, float vz, float velocidade){
	this->c = c;
	this->pontos_origem = new float*[num_pontos];
	this->pontos = pontos;
	for(int k = 0; k < num_pontos; k++){
        this->pontos_origem[k] = new float[3];
        this->pontos_origem[k][0] = pontos[k][0];
        this->pontos_origem[k][1] = pontos[k][1];
        this->pontos_origem[k][2] = pontos[k][2];

        this->pontos[k][0] += this->c[0];
        this->pontos[k][1] += this->c[1];
        this->pontos[k][2] += this->c[2];
	}

	this->num_pontos = num_pontos;
	this->espessura = espessura;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->luz_emissao = luz_emissao;
	this->luz_brilho = luz_brilho;
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
	this->velocidade = velocidade;

	this->texDef = false;

	this->calculaPontosMedios();
	this->calculaNormais();
	this->calculaRaios();
}

Rebatedor::Rebatedor(float *c, float **pontos, int num_pontos, float espessura, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, float vx, float vy, float vz, float velocidade, glcTexture *textureMagener){
    this->c = c;
	this->pontos_origem = new float*[num_pontos];
	this->pontos = pontos;
	for(int k = 0; k < num_pontos; k++){
        this->pontos_origem[k] = new float[3];
        this->pontos_origem[k][0] = pontos[k][0];
        this->pontos_origem[k][1] = pontos[k][1];
        this->pontos_origem[k][2] = pontos[k][2];

        this->pontos[k][0] += this->c[0];
        this->pontos[k][1] += this->c[1];
        this->pontos[k][2] += this->c[2];
	}

	this->num_pontos = num_pontos;
	this->espessura = espessura;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->luz_emissao = luz_emissao;
	this->luz_brilho = luz_brilho;
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
	this->velocidade = velocidade;

	this->textureManeger = textureMagener;
	this->texDef = true;

	this->calculaPontosMedios();
	this->calculaNormais();
	this->calculaRaios();
}

Rebatedor::~Rebatedor(){}

void Rebatedor::calculaNormais(){
    this->normais = new float*[this->num_pontos+2];
	for(int k = 0; k < this->num_pontos+2; k++) this->normais[k] = new float[3];

    float v[3];
    crossNorm(this->pontos[1][0]-this->pontos[0][0],
              this->pontos[1][1]-this->pontos[0][1],
              this->pontos[1][2]-this->pontos[0][2],
              this->pontos[2][0]-this->pontos[0][0],
              this->pontos[2][1]-this->pontos[0][1],
              this->pontos[2][2]-this->pontos[0][2],
                                                    v);
    this->normais[0][0] = v[0];
    this->normais[0][1] = v[1];
    this->normais[0][2] = v[2];
    this->normais[1][0] = -v[0];
    this->normais[1][1] = -v[1];
    this->normais[1][2] = -v[2];

    for(int k = 0; k < this->num_pontos-1; k++){
        crossNorm(this->pontos[k  ][0]-this->pontos[k][0],
                  this->pontos[k  ][1]-this->pontos[k][1]+this->espessura,
                  this->pontos[k  ][2]-this->pontos[k][2],
                  this->pontos[k+1][0]-this->pontos[k][0],
                  this->pontos[k+1][1]-this->pontos[k][1],
                  this->pontos[k+1][2]-this->pontos[k][2],
                                                          v);
        this->normais[k+2][0] = v[0];
        this->normais[k+2][1] = v[1];
        this->normais[k+2][2] = v[2];
    }

    crossNorm(this->pontos[this->num_pontos-1][0]-this->pontos[this->num_pontos-1][0],
              this->pontos[this->num_pontos-1][1]-this->pontos[this->num_pontos-1][1]+this->espessura,
              this->pontos[this->num_pontos-1][2]-this->pontos[this->num_pontos-1][2],
              this->pontos[0                 ][0]-this->pontos[this->num_pontos-1][0],
              this->pontos[0                 ][1]-this->pontos[this->num_pontos-1][1],
              this->pontos[0                 ][2]-this->pontos[this->num_pontos-1][2],
                                                                                      v);
    this->normais[this->num_pontos+1][0] = v[0];
    this->normais[this->num_pontos+1][1] = v[1];
    this->normais[this->num_pontos+1][2] = v[2];
}

float *Rebatedor::getCentro(){
    return this->c;
}

float **Rebatedor::getPontos_origem(){
    return this->pontos_origem;
}

void Rebatedor::setCentro(float *centro){
    this->c = centro;
    for(int k = 0; k < this->num_pontos; k++){
        this->pontos[k][0] = this->pontos_origem[k][0] + this->c[0];
        this->pontos[k][1] = this->pontos_origem[k][1] + this->c[1];
        this->pontos[k][2] = this->pontos_origem[k][2] + this->c[2];

        this->pontos_medios[k][0] = this->pontos_medios_origem[k][0] + this->c[0];
        this->pontos_medios[k][1] = this->pontos_medios_origem[k][1] + this->c[1];
        this->pontos_medios[k][2] = this->pontos_medios_origem[k][2] + this->c[2];
	}
}

void Rebatedor::calculaPontosMedios(){
    this->pontos_medios_origem = new float*[this->num_pontos];
    this->pontos_medios = new float*[this->num_pontos];

    for(int k = 0; k < this->num_pontos; k++) this->pontos_medios_origem[k] = new float[3];
    for(int k = 0; k < this->num_pontos; k++) this->pontos_medios[k] = new float[3];

    for(int k = 0; k < this->num_pontos-1; k++){
            this->pontos_medios_origem[k] = ponto_medio(this->pontos_origem[k],this->pontos_origem[k+1]);
            this->pontos_medios[k][0] = this->pontos_medios_origem[k][0] + this->c[0];
            this->pontos_medios[k][1] = this->pontos_medios_origem[k][1] + this->c[1];
            this->pontos_medios[k][2] = this->pontos_medios_origem[k][2] + this->c[2];
    }
	this->pontos_medios_origem[this->num_pontos-1] = ponto_medio(this->pontos_origem[this->num_pontos-1],this->pontos_origem[0]);
	this->pontos_medios[this->num_pontos-1][0] = this->pontos_medios_origem[this->num_pontos-1][0] + this->c[0];
    this->pontos_medios[this->num_pontos-1][1] = this->pontos_medios_origem[this->num_pontos-1][1] + this->c[1];
    this->pontos_medios[this->num_pontos-1][2] = this->pontos_medios_origem[this->num_pontos-1][2] + this->c[2];
}

void Rebatedor::calculaRaios(){
    float aux_maior = fabs(this->pontos[0][0]-this->c[0]);
    float aux_menor = fabs(this->pontos[0][2]-this->c[2]);

    this->raio_maior = aux_maior;
    this->raio_menor = aux_menor;

    for(int k = 1; k < this->num_pontos; k++){
        aux_maior = fabs(this->pontos[k][0]-this->c[0]);
        aux_menor = fabs(this->pontos[k][2]-this->c[2]);

        if(aux_maior > this->raio_maior) this->raio_maior = aux_maior;
        if(aux_menor > this->raio_menor) this->raio_menor = aux_menor;
    }
}
