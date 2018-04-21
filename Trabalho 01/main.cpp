#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <vector>

#include "Collision.h"
#include "Auxiliares.h"
#include "Desenhos.h"

/**
    Referencias:
    http://www.emathzone.com/tutorials/math-results-and-formulas/equations-of-tangent-and-normal-to-a-ellipse.html
    https://en.wikipedia.org/wiki/Rotation_matrix
    https://www.physicsforums.com/threads/unit-vectors-for-ellipse.324153/
    https://www.algebra.com/algebra/homework/Quadratic-relations-and-conic-sections/Tangent-lines-to-an-ellipse.lesson
    https://www.experts-exchange.com/questions/23733731/OpenGL-Timer-Function.html
    http://cboard.cprogramming.com/c-programming/90175-how-build-timer-counts-seconds-elapsed.html
*/

using namespace std;

float screenWidth = 0;                              //Variaveis que arazenarao o as dimensoes da tela cheia do monitor em uso
float screenHeight = 0;
int windowSizeX = 680;                              //Tamanhos de tela iniciais
int windowSizeY = 680;
float ortho[6] = {-1.0,1.0,-1.0,1.0,-1.0,1.0};      //Variacao do Ortho
float ortho_diff_x = ortho[1]-ortho[0];             //Tamanho do Ortho no eixo x e eixo y cartesianos
float ortho_diff_y = ortho[3]-ortho[2];
float objectPosX = windowSizeX/2;                   //Posicao inicial da tela, no centro
float objectPosY = windowSizeY/2;

float background[4] = {1.0,1.0,1.0,0.0};            //fundo branco da tela do jogo

int lado = 1;                                       //define o lado do campo em que a bola está. 1: baixo; 2: cima

vector< float* > ranking_melhores;                  //vetor que guarda o ranking ordenado dos melhores tempos

bool time_started = false;                          //booleano que libera o timer
int segundos = 0;                                   //variavel que guarda o numero de segundos percorridos
int tempo_vet[4] = {0,0,0,0};                       //vetor que guarda as unidades de tempo separadamente. Dezena de minutos, unidade de minutos, dezena de segundos e unidade de segundos

int placar_one = 0;                                 //placares
int placar_two = 0;

bool ponto = false;                                 //verificador se a partida terminou

float fator_vel = 0.02;                             //fator de variacao da velocidade da bola
float velocidade_min = fator_vel;
float velocidade_max = 5*fator_vel;
float tolerancia = 0.0001;                          //tolerancia de proximidade

float circ_x      = 0;                              //posicao da bola no ortho
float circ_y      = 0;
float circ_raio   = 0.1;                            //raio da bola
float circ_vetX   = -0.8;                           //vetor posicao da bola
float circ_vetY   = -1;
float circ_rgb[3] = {1,0,0};                        //cor da bola

float eli_1_x          = 0;                         //posicao inicial do jogador 1
float eli_1_y          = -1;
float eli_1_raio_menor = 0.15;                      //raio maior da elipse 1
float eli_1_raio_maior = 0.5;                       //raio menor da elipse 1
float eli_1_prec       = 0.1;                       //precisao da suavidade da elipse 1
float eli_1_velocity   = 0;
float eli_1_rgb[3]     = {0.102,0.580,0.192};       //cor da elipse 1

float eli_2_x          = 0;                         //raio maior da elipse 2
float eli_2_y          = 1;                         //raio menor da elipse 2
float eli_2_raio_menor = 0.15;                      //precisao da suavidade da elipse 2
float eli_2_raio_maior = 0.5;                       //velocidade inicial da elipse 2
float eli_2_prec       = 0.1;                       //precisao da suavidade da elipse 2
float eli_2_velocity   = 0;                         //velocidade inicial da elipse 2
float eli_2_rgb[3]     = {0.031,0.376,0.659};       //cor da elipse 2

int moveX = 0;
int moveY = 0;
int sabaozim = 0;
bool inteligencia = false;

Quadrado *titulo;
Quadrado *de_1;
Quadrado *de_2;
Quadrado *ranking;
Quadrado *sair;
Quadrado *titRanking;
Quadrado *posicao01;
Quadrado *posicao02;
Quadrado *posicao03;
Quadrado *posicao04;
Quadrado *posicao05;
Quadrado *posicao06;
Quadrado *posicao07;
Quadrado *posicao08;
Quadrado *posicao09;
Quadrado *posicao10;
Quadrado *menu;

Circulo *circ;
Elipse *bumper1, *bumper2;

void idle();
void init();
void mouse(int button, int state, int x, int y);
void display();
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);
void passivo(int x, int y);
void timer_func(int n);
bool compara_ranking(float *v1, float *v2);

// Main Function
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (windowSizeX, windowSizeY);
    glutInitWindowPosition (500, 0);

    glutCreateWindow ("Pong");

    glutMouseFunc( mouse );
    glutKeyboardFunc( keyboard );
    glutMotionFunc( motion );
    glutPassiveMotionFunc( passivo );
    glutDisplayFunc( display );
    glutIdleFunc( idle );

    init ();

    glutFullScreen();

    timer_func(1000);

    glutMainLoop();

	return 0;
}

void idle(){
    if(sabaozim == 1){
        fator_vel += fator_vel >= velocidade_max ? 0 : 0.00002;

        circ->x += circ->vetX*fator_vel/norma(circ->vetX,circ->vetY);
        circ->y += circ->vetY*fator_vel/norma(circ->vetX,circ->vetY);

        wall_collision(circ,ortho,lado,placar_one,placar_two,ponto);
        if(ponto){
            display();
            if(placar_one == 3 or placar_two == 3){
                float *vet = new float[5];
                vet[0] = placar_one == 3 ? 1 : 2;
                vet[1] = tempo_vet[0];
                vet[2] = tempo_vet[1];
                vet[3] = tempo_vet[2];
                vet[4] = tempo_vet[3];
                tempo_vet[0] = 0;
                tempo_vet[1] = 0;
                tempo_vet[2] = 0;
                tempo_vet[3] = 0;
                placar_one = 0;
                placar_two = 0;
                fator_vel = velocidade_min;
                ranking_melhores.push_back(vet);
                sort(ranking_melhores.begin(),ranking_melhores.end(),compara_ranking);
                if(ranking_melhores.size() > 10) ranking_melhores.pop_back();
                cout << endl;
                for(int k = 0; k < ranking_melhores.size(); k++)
                    cout << ranking_melhores[k][0] << " " << ranking_melhores[k][1] << " " << ranking_melhores[k][2] << " " << ranking_melhores[k][3] << " " << ranking_melhores[k][4] << endl;
            }
            time_t start, endd;
            int elapsed;
            time(&start);
            do{
                time(&endd);
                elapsed = difftime(endd, start);
            } while(elapsed < 2);
            ponto = false;
        }
        if(circ->y <= bumper1->raio_menor*1.05 or circ->y >= bumper2->raio_menor*1.05){
            if(lado == 1)
                bumper_collision_1(circ,bumper1,tolerancia,lado);
            else
                bumper_collision_2(circ,bumper2,tolerancia,lado);
        }
        if(inteligencia){
            if(circ->x < bumper2->x) bumper2->x -= bumper2->velocity;
            else if(circ->x > bumper2->x) bumper2->x += bumper2->velocity;
        }
    }

    glutPostRedisplay();
}

void passivo(int x, int y){
    if(sabaozim == 0){
        y = screenHeight - y;

        objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
        objectPosY = y*ortho_diff_y/screenHeight+ortho[2];

        if(objectPosX > de_1->x1         and objectPosX < de_1->x2    and objectPosY < de_1->y1    and objectPosY > de_1->y2){
            de_1->r = 0.0;
            de_1->b = 1.0;
            de_1->g = 0.0;
        }
        else if(objectPosX > de_2->x1    and objectPosX < de_2->x2    and objectPosY < de_2->y1    and objectPosY > de_2->y2){
            de_2->r = 0.0;
            de_2->b = 1.0;
            de_2->g = 0.0;
        }
        else if(objectPosX > ranking->x1 and objectPosX < ranking->x2 and objectPosY < ranking->y1 and objectPosY > ranking->y2){
            ranking->r = 0.0;
            ranking->b = 1.0;
            ranking->g = 0.0;
        }
        else if(objectPosX > sair->x1    and objectPosX < sair->x2    and objectPosY < sair->y1    and objectPosY > sair->y2){
            sair->r = 0.0;
            sair->b = 1.0;
            sair->g = 0.0;
        }
        else{
            titulo->r = 0.0;
            titulo->g = 1.0;
            titulo->b = 0.0;
            de_1->r = 0.0;
            de_1->g = 1.0;
            de_1->b = 0.0;
            de_2->r = 0.0;
            de_2->g = 1.0;
            de_2->b = 0.0;
            ranking->r = 0.0;
            ranking->g = 1.0;
            ranking->b = 0.0;
            sair->r = 0.0;
            sair->g = 1.0;
            sair->b = 0.0;
        }
    }
    else if(sabaozim == 1) bumper1->x = x*(ortho[1]-ortho[0])/screenWidth+ortho[0];
    else if(sabaozim == 2){
        y = screenHeight - y;

        objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
        objectPosY = y*ortho_diff_y/screenHeight+ortho[2];
        if(objectPosX > menu->x1    and objectPosX < menu->x2    and objectPosY < menu->y1    and objectPosY > menu->y2){
            menu->r = 0.0;
            menu->b = 1.0;
            menu->g = 0.0;
        }
        else{
            menu->r = 0.0;
            menu->g = 1.0;
            menu->b = 0.0;
        }
    }
    glutPostRedisplay();
}

// Motion callback
void motion(int x, int y ){
    if(sabaozim == 0){
        y = screenHeight - y;

        objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
        objectPosY = y*ortho_diff_y/screenHeight+ortho[2];

        if(objectPosX > de_1->x1         and objectPosX < de_1->x2    and objectPosY < de_1->y1    and objectPosY > de_1->y2){
            de_1->r = 1.0;
            de_1->g = 0.0;
            de_1->b = 0.0;
        }
        else if(objectPosX > de_2->x1    and objectPosX < de_2->x2    and objectPosY < de_2->y1    and objectPosY > de_2->y2){
            de_2->r = 1.0;
            de_2->g = 0.0;
            de_2->b = 0.0;
        }
        else if(objectPosX > ranking->x1 and objectPosX < ranking->x2 and objectPosY < ranking->y1 and objectPosY > ranking->y2){
            ranking->r = 1.0;
            ranking->g = 0.0;
            ranking->b = 0.0;
        }
        else if(objectPosX > sair->x1    and objectPosX < sair->x2    and objectPosY < sair->y1    and objectPosY > sair->y2){
            sair->r = 1.0;
            sair->g = 0.0;
            sair->b = 0.0;
        }
        else{
            titulo->r = 0.0;
            titulo->g = 1.0;
            titulo->b = 0.0;
            de_1->r = 0.0;
            de_1->g = 1.0;
            de_1->b = 0.0;
            de_2->r = 0.0;
            de_2->g = 1.0;
            de_2->b = 0.0;
            ranking->r = 0.0;
            ranking->g = 1.0;
            ranking->b = 0.0;
            sair->r = 0.0;
            sair->g = 1.0;
            sair->b = 0.0;
        }
    }else if(sabaozim = 2){
        y = screenHeight - y;

        objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
        objectPosY = y*ortho_diff_y/screenHeight+ortho[2];
        if(objectPosX > menu->x1    and objectPosX < menu->x2    and objectPosY < menu->y1    and objectPosY > menu->y2){
            menu->r = 1.0;
            menu->g = 0.0;
            menu->b = 0.0;
        }
        else{
            menu->r = 0.0;
            menu->g = 1.0;
            menu->b = 0.0;
        }
    }
    glutPostRedisplay();
}

// Mouse callback
void mouse(int button, int state, int x, int y){
    if(sabaozim == 0){
        if(button == GLUT_LEFT_BUTTON){
            if(state == GLUT_DOWN){
                y = screenHeight - y;

                objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
                objectPosY = y*ortho_diff_y/screenHeight+ortho[2];

                if(objectPosX > de_1->x1         and objectPosX < de_1->x2    and objectPosY < de_1->y1    and objectPosY > de_1->y2){
                    de_1->r = 1.0;
                    de_1->g = 0.0;
                    de_1->b = 0.0;
                }
                else if(objectPosX > de_2->x1    and objectPosX < de_2->x2    and objectPosY < de_2->y1    and objectPosY > de_2->y2){
                    de_2->r = 1.0;
                    de_2->g = 0.0;
                    de_2->b = 0.0;
                }
                else if(objectPosX > ranking->x1 and objectPosX < ranking->x2 and objectPosY < ranking->y1 and objectPosY > ranking->y2){
                    ranking->r = 1.0;
                    ranking->g = 0.0;
                    ranking->b = 0.0;
                }
                else if(objectPosX > sair->x1    and objectPosX < sair->x2    and objectPosY < sair->y1    and objectPosY > sair->y2){
                    sair->r = 1.0;
                    sair->g = 0.0;
                    sair->b = 0.0;
                }
                else{
                    titulo->r = 0.0;
                    titulo->g = 1.0;
                    titulo->b = 0.0;
                    de_1->r = 0.0;
                    de_1->g = 1.0;
                    de_1->b = 0.0;
                    de_2->r = 0.0;
                    de_2->g = 1.0;
                    de_2->b = 0.0;
                    ranking->r = 0.0;
                    ranking->g = 1.0;
                    ranking->b = 0.0;
                    sair->r = 0.0;
                    sair->g = 1.0;
                    sair->b = 0.0;
                }
            }else{
                if(objectPosX > de_1->x1         and objectPosX < de_1->x2    and objectPosY < de_1->y1    and objectPosY > de_1->y2){
                    cout << "Entrou no jogo para um jogador! OMG! T.G.I.F!!!" << endl;
                    time_started = true;
                    inteligencia = true;
                    bumper2->velocity = velocidade_min;
                    sabaozim = 1;
                    glClearColor (background[0],background[1],background[2],background[3]);
                    glutSetCursor(GLUT_CURSOR_NONE);
                }
                else if(objectPosX > de_2->x1    and objectPosX < de_2->x2    and objectPosY < de_2->y1    and objectPosY > de_2->y2){
                    cout << "Entrou no jogo para dois jogadores! OMG! T.G.I.F!!!" << endl;
                    time_started = true;
                    inteligencia = false;
                    sabaozim = 1;
                    glClearColor (background[0],background[1],background[2],background[3]);
                    glutSetCursor(GLUT_CURSOR_NONE);
                }
                else if(objectPosX > ranking->x1 and objectPosX < ranking->x2 and objectPosY < ranking->y1 and objectPosY > ranking->y2){
                    cout << "Entrou no ranking! OMG! T.G.I.F!!!" << endl;
                    time_started = false;
                    sabaozim = 2;
                }
                else if(objectPosX > sair->x1    and objectPosX < sair->x2    and objectPosY < sair->y1    and objectPosY > sair->y2){
                    cout << "Saiu! OMG! T.G.I.F!!!" << endl;
                    time_started = false;
                    exit(0);
                }
            }
        }
    }else if(sabaozim == 2){
        if(button == GLUT_LEFT_BUTTON){
            if(state == GLUT_DOWN){
                y = screenHeight - y;

                objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
                objectPosY = y*ortho_diff_y/screenHeight+ortho[2];

                if(objectPosX > menu->x1    and objectPosX < menu->x2    and objectPosY < menu->y1    and objectPosY > menu->y2){
                    menu->r = 1.0;
                    menu->b = 0.0;
                    menu->g = 0.0;
                }
                else{
                    menu->r = 0.0;
                    menu->g = 1.0;
                    menu->b = 0.0;
                }
            }else if(objectPosX > menu->x1    and objectPosX < menu->x2    and objectPosY < menu->y1    and objectPosY > menu->y2) sabaozim = 0;
        }
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    if(sabaozim == 0){
        switch (key){
            case 32:
                sabaozim == 1 ? sabaozim-- : sabaozim++;
                sabaozim == 0 ? glClearColor (0.4, 0.4, 0.4, 0.0) : glClearColor (background[0],background[1],background[2],background[3]);
                break;
            case 27:
                exit(0);
            break;
        }
    }
    else if(sabaozim == 1){
        switch (key){
            case 32:
                sabaozim == 1 ? sabaozim-- : sabaozim++;
                sabaozim == 0 ? glClearColor (0.4, 0.4, 0.4, 0.0) : glClearColor (background[0],background[1],background[2],background[3]);
                if(sabaozim == 0) glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
                break;
            case 97:
                if(bumper2->x-0.1 <= ortho[0]) bumper2->x = ortho[0];
                else bumper2->x -= 0.1;
                break;
            case 100:
                if(bumper2->x+0.1 >= ortho[1]) bumper2->x = ortho[1];
                else bumper2->x += 0.1;
                break;
            case 27:
                exit(0);
            break;
        }
    }
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Clean z-buffer

    if(sabaozim == 0){
        // Change object position if some key is pressed
        objectPosX+=moveX;
        objectPosY+=moveY;

        desenhaQuadrado(titulo,ortho);
        desenhaTitulo(ortho);
        desenhaQuadrado(de_1,ortho);
        desenhaQuadrado(de_2,ortho);
        desenhaQuadrado(ranking,ortho);
        desenhaQuadrado(sair,ortho);
    }
    else if(sabaozim == 1){
        desenhaLinha(ortho);
        desenhaPlacar(placar_one,placar_two,ortho);
        desenhaTimer(tempo_vet, ortho);
        desenhaElipse(bumper1);
        desenhaElipse(bumper2);
        desenhaCirculo(circ);
    }
    else if(sabaozim == 2){
        desenhaQuadrado(titRanking,ortho);
        desenhaTitRanking(ortho);
        desenhaQuadrado(posicao01,ortho);
        desenhaQuadrado(posicao02,ortho);
        desenhaQuadrado(posicao03,ortho);
        desenhaQuadrado(posicao04,ortho);
        desenhaQuadrado(posicao05,ortho);
        desenhaQuadrado(posicao06,ortho);
        desenhaQuadrado(posicao07,ortho);
        desenhaQuadrado(posicao08,ortho);
        desenhaQuadrado(posicao09,ortho);
        desenhaQuadrado(posicao10,ortho);
        desenhaQuadrado(menu,ortho);
    }

	glutSwapBuffers ();  // Required when double buffer is initialized
	glutPostRedisplay();
}

void init (void){
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    ortho[0] = -1.0*screenWidth/screenHeight;
    ortho[1] =  1.0*screenWidth/screenHeight;

    glClearColor (0.4, 0.4, 0.4, 0.0);

    ortho_diff_x = ortho[1]-ortho[0];
    ortho_diff_y = ortho[3]-ortho[2];

    titulo  = new Quadrado(0.15*ortho_diff_x+ortho[0],0.95*ortho_diff_y+ortho[2],0.85*ortho_diff_x+ortho[0],0.60*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    de_1    = new Quadrado(0.25*ortho_diff_x+ortho[0],0.50*ortho_diff_y+ortho[2],0.75*ortho_diff_x+ortho[0],0.40*ortho_diff_y+ortho[2],0.0,1.0,0.0,"1 Jogador");
    de_2    = new Quadrado(0.25*ortho_diff_x+ortho[0],0.35*ortho_diff_y+ortho[2],0.75*ortho_diff_x+ortho[0],0.25*ortho_diff_y+ortho[2],0.0,1.0,0.0,"2 Jogadores");
    ranking = new Quadrado(0.35*ortho_diff_x+ortho[0],0.20*ortho_diff_y+ortho[2],0.65*ortho_diff_x+ortho[0],0.15*ortho_diff_y+ortho[2],0.0,1.0,0.0,"Ranking");
    sair    = new Quadrado(0.45*ortho_diff_x+ortho[0],0.10*ortho_diff_y+ortho[2],0.55*ortho_diff_x+ortho[0],0.06*ortho_diff_y+ortho[2],0.0,1.0,0.0,"Sair");

    circ = new Circulo(circ_x,circ_y,circ_raio,circ_vetX,circ_vetY,circ_rgb[0],circ_rgb[1],circ_rgb[2]);

    bumper1 = new Elipse(eli_1_x,eli_1_y,eli_1_raio_menor,eli_1_raio_maior,eli_1_prec,eli_1_velocity,eli_1_rgb[0],eli_1_rgb[1],eli_1_rgb[2]);
    bumper2 = new Elipse(eli_2_x,eli_2_y,eli_2_raio_menor,eli_2_raio_maior,eli_2_prec,eli_2_velocity,eli_2_rgb[0],eli_2_rgb[1],eli_2_rgb[2]);

    titRanking = new Quadrado(0.12*ortho_diff_x+ortho[0],0.95*ortho_diff_y+ortho[2],0.88*ortho_diff_x+ortho[0],0.85*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
	posicao01  = new Quadrado(0.12*ortho_diff_x+ortho[0],0.815*ortho_diff_y+ortho[2],0.48*ortho_diff_x+ortho[0],0.695*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao02  = new Quadrado(0.12*ortho_diff_x+ortho[0],0.675*ortho_diff_y+ortho[2],0.48*ortho_diff_x+ortho[0],0.555*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao03  = new Quadrado(0.12*ortho_diff_x+ortho[0],0.535*ortho_diff_y+ortho[2],0.48*ortho_diff_x+ortho[0],0.415*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao04  = new Quadrado(0.12*ortho_diff_x+ortho[0],0.395*ortho_diff_y+ortho[2],0.48*ortho_diff_x+ortho[0],0.275*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao05  = new Quadrado(0.12*ortho_diff_x+ortho[0],0.255*ortho_diff_y+ortho[2],0.48*ortho_diff_x+ortho[0],0.135*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao06  = new Quadrado(0.52*ortho_diff_x+ortho[0],0.815*ortho_diff_y+ortho[2],0.88*ortho_diff_x+ortho[0],0.695*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao07  = new Quadrado(0.52*ortho_diff_x+ortho[0],0.675*ortho_diff_y+ortho[2],0.88*ortho_diff_x+ortho[0],0.555*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao08  = new Quadrado(0.52*ortho_diff_x+ortho[0],0.535*ortho_diff_y+ortho[2],0.88*ortho_diff_x+ortho[0],0.415*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao09  = new Quadrado(0.52*ortho_diff_x+ortho[0],0.395*ortho_diff_y+ortho[2],0.88*ortho_diff_x+ortho[0],0.275*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    posicao10  = new Quadrado(0.52*ortho_diff_x+ortho[0],0.255*ortho_diff_y+ortho[2],0.88*ortho_diff_x+ortho[0],0.135*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
    menu       = new Quadrado(0.45*ortho_diff_x+ortho[0],0.100*ortho_diff_y+ortho[2],0.55*ortho_diff_x+ortho[0],0.060*ortho_diff_y+ortho[2],0.0,1.0,0.0,"Menu");

	// inicializar sistema de viz.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void timer_func(int n){
    glutTimerFunc(n, timer_func, n); // recursivamente chama timer_func
    if(time_started){
        segundos++;
        if(segundos > 9){
            tempo_vet[3] = 0;
            segundos = 0;
            if(tempo_vet[2] == 5){
                tempo_vet[2] = 0;
                if(tempo_vet[1] > 9){
                    tempo_vet[1] = 0;
                    tempo_vet[0]++;
                }else tempo_vet[1]++;
            }else tempo_vet[2]++;
        }else tempo_vet[3]++;
    }
}

bool compara_ranking(float *v1, float *v2){
    return v1[1] < v2[1] and v1[2] < v2[2] and v1[3] < v2[3] and v1[4] < v2[4];
}
