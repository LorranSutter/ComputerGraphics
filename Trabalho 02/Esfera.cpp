#include "Esfera.h"

Esfera::Esfera(){
	this->raio = 0;
	this->luz_brilho = 0;
	this->velocidade = 0;
}

Esfera::Esfera(float *c, float raio){
	this->c = c;
	this->raio = raio;
	this->luz_brilho = 0;
	this->velocidade = 0;
}

Esfera::Esfera(float *c, float raio, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho){
	this->c = c;
	this->raio = raio;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->luz_emissao = luz_emissao;
	this->luz_brilho = luz_brilho;
	this->velocidade = 0;
}

Esfera::Esfera(float *c, float raio, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho, float *v, float velocidade){
	this->c = c;
	this->raio = raio;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->luz_emissao = luz_emissao;
	this->luz_brilho = luz_brilho;
	this->v = v;
	normalize(this->v);
	this->velocidade = velocidade;
}

Esfera::~Esfera(){
}
