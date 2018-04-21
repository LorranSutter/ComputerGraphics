#include "Poste.h"

Poste::Poste(){
	this->raio = 0;
	this->altura = 0;
	this->angulo = 0;
	this->frente = 0;
	this->tras = 0;
	this->comprimento = 0;
	this->luz_brilho = 0;
}

Poste::Poste(float *c_base, float raio, float altura, float angulo, float frente, float tras, float comprimento){
    this->c_base = c_base;
    this->raio = raio;
    this->altura = altura;
    this->angulo = angulo;
    this->frente = frente;
	this->tras = tras;
	this->comprimento = comprimento;
    this->luz_brilho = 0;
}

Poste::Poste(float *c_base, float raio, float altura, float angulo, float frente, float tras, float comprimento, GLfloat *luz_ambiente, GLfloat *luz_difusa, GLfloat *luz_especular, GLfloat *luz_emissao, GLfloat luz_brilho){
    this->c_base = c_base;
    this->raio = raio;
    this->altura = altura;
    this->angulo = angulo;
    this->frente = frente;
	this->tras = tras;
	this->comprimento = comprimento;
    this->luz_ambiente = luz_ambiente;
    this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;
	this->luz_emissao = luz_emissao;
	this->luz_brilho = luz_brilho;
}

Poste::~Poste(){
}
