#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "Esfera.h"
#include "Rebatedor.h"
#include "Bloco.h"
#include "Desenho.h"
#include "Collision.h"
#include "Valores.h"
#include "Retangulo.h"
#include "Poste.h"

#define TELA_MENU 1
#define TELA_MODO_1P 2
#define TELA_MODO_2P 3
#define TELA_RANK 4
#define TELA_JOGO 5
#define MODO_1_PLAYER 6
#define MODO_2_PLAYERS 7
#define CRITERIO_VELOCIDADE 8
#define CRITERIO_REBATIDAS 9
#define NIVEL_1 10
#define NIVEL_2 11
#define NIVEL_3 12
#define LUZ_PONTUAL 13
#define LUZ_SPOTLIGHT 14
#define CAMERA_TOP 15
#define CAMERA_NORMAL 16

using namespace std;

string escreveNome = "Nome do vencedor";

int tela = TELA_MENU;
int modo = MODO_1_PLAYER;
int criterio = CRITERIO_VELOCIDADE;
int nivel = NIVEL_1;
int luz = LUZ_SPOTLIGHT;
int camera = CAMERA_NORMAL;

void setSpotlight(GLenum luz, GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *posicao, GLfloat *direcao, GLfloat cutoff, GLfloat expoente){
    glEnable(luz);                   // habilita luz

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightfv(luz, GL_AMBIENT, ambiente);
    glLightfv(luz, GL_DIFFUSE, difusa);
    glLightfv(luz, GL_SPECULAR, especular);
    glLightfv(luz, GL_POSITION, posicao);

    glLightf(luz, GL_SPOT_CUTOFF, cutoff);
    glLightf(luz, GL_SPOT_EXPONENT, expoente);
    glLightfv(luz, GL_SPOT_DIRECTION, direcao);

    glLightf(luz, GL_CONSTANT_ATTENUATION, kc);
    glLightf(luz, GL_LINEAR_ATTENUATION, kl);
    glLightf(luz, GL_QUADRATIC_ATTENUATION, kq);
}

bool eh_menor_Rankeados(int tempo, vector<Rankeados> r){
    if(r.size() < 10) return true;
    for(int k = 0; k < r.size(); k++){
        if(tempo < r[k].tempo) return true;
    }
}

bool menorRanking(Rankeados r1, Rankeados r2){
    return r1.tempo < r2.tempo;
}

void escreve_Arquivo_ranking(){
    ofstream arq("Ranking.txt");
    arq << rankeados_1.size() << endl;
    for(int k = 0; k < rankeados_1.size(); k++) arq << rankeados_1[k].nome << " " <<  rankeados_1[k].tempo/3600 << " " << rankeados_1[k].tempo/60%60 << " " << rankeados_1[k].tempo%60 << endl;
    arq << rankeados_2.size() << endl;
    for(int k = 0; k < rankeados_2.size(); k++) arq << rankeados_2[k].nome << " " <<  rankeados_2[k].tempo/3600 << " " << rankeados_2[k].tempo/60%60 << " " << rankeados_2[k].tempo%60 << endl;
    arq << rankeados_3.size() << endl;
    for(int k = 0; k < rankeados_3.size(); k++) arq << rankeados_3[k].nome << " " <<  rankeados_3[k].tempo/3600 << " " << rankeados_3[k].tempo/60%60 << " " << rankeados_3[k].tempo%60 << endl;
    arq.close();
}

void le_Arquivo_ranking(){
    string nome;
    int n = 0;
    int minuto, segundo, milesimo;
    ifstream arq("Ranking.txt");
    if(arq.is_open()){
        arq >> n;
        for(int k = 0; k < n; k++){
            arq >> nome;
            arq >> minuto;
            arq >> segundo;
            arq >> milesimo;
            Rankeados r = Rankeados(nome,minuto*3600 + segundo*60 + milesimo);
            rankeados_1.push_back(r);
        }
        arq >> n;
        for(int k = 0; k < n; k++){
            arq >> nome;
            arq >> minuto;
            arq >> segundo;
            arq >> milesimo;
            Rankeados r = Rankeados(nome,minuto*3600 + segundo*60 + milesimo);
            rankeados_2.push_back(r);
        }
        arq >> n;
        for(int k = 0; k < n; k++){
            arq >> nome;
            arq >> minuto;
            arq >> segundo;
            arq >> milesimo;
            Rankeados r = Rankeados(nome,minuto*3600 + segundo*60 + milesimo);
            rankeados_3.push_back(r);
        }
    }
    arq.close();
}

void reset_Jogo(){
    placar_reb1 = 0;
    placar_reb2 = 0;
    tempo = 0;
    enable_tempo = false;
    pause = false;
    camera = CAMERA_NORMAL;
    rebatedor2_c[0] = 0;
    rebatedor2.setCentro(rebatedor2_c);
    e.c[0] = 0;
    e.c[1] = 0;
    e.c[2] = 0;
    rotationX = rotationX0;
    rotationY = rotationY0;

    blocks_velocidade = blocks_velocidade0;

    colidiu_lat1 = false;
    colidiu_lat2 = false;
    colidiu_reb1 = false;
    colidiu_reb2 = false;

    nivel = NIVEL_1;
    level_num = 1;
    e.velocidade = esfera_velocidade_min_1;

    switch(rand()%4){
        case 0:
            esfera_v[0] = esfera_v01[0];
            esfera_v[1] = esfera_v01[1];
            esfera_v[2] = esfera_v01[2];
        break;
        case 1:
            esfera_v[0] = esfera_v02[0];
            esfera_v[1] = esfera_v02[1];
            esfera_v[2] = esfera_v02[2];
        break;
        case 2:
            esfera_v[0] = esfera_v03[0];
            esfera_v[1] = esfera_v03[1];
            esfera_v[2] = esfera_v03[2];
        break;
        case 3:
            esfera_v[0] = esfera_v04[0];
            esfera_v[1] = esfera_v04[1];
            esfera_v[2] = esfera_v04[2];
        break;
    }
    e.v = esfera_v;
}

void reset_ret_colors(){
    titulo->setColor(ret_cor_normal);
    de_1->setColor(ret_cor_normal);
    de_2->setColor(ret_cor_normal);
    ranking->setColor(ret_cor_normal);
    sair->setColor(ret_cor_normal);


    if(criterio == CRITERIO_REBATIDAS) modo_veloc->setColor(ret_cor_normal);
    if(criterio == CRITERIO_VELOCIDADE) modo_rebat->setColor(ret_cor_normal);
    choose_lv->setColor(ret_cor_normal);
    start->setColor(ret_cor_normal);
    voltar->setColor(ret_cor_normal);
    menu->setColor(ret_cor_normal);

}

void timer_func(int n){
    glutTimerFunc(n, timer_func, n); // recursivamente chama timer_func
    if(enable_tempo) tempo++;
    //cout << tempo/3600 << " " << tempo/60%60 << " " << tempo%60 << endl;
}

//Reshape Func
void reshape(int w, int h){
    width = w;
    height = h;
    glViewport(0,0,w,h);

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y){
    switch(key){
        case 'a':
            if(pressKeyboard) pressKeyboard = false;
        break;
        case 'd':
            if(pressKeyboard) pressKeyboard = false;
        break;
    }
}

void keyboard(unsigned char key, int x, int y){
    if(tela == TELA_JOGO){
        if(pause){
            switch(key){
                case 'm':
                    camera = camera == CAMERA_NORMAL ? CAMERA_TOP : CAMERA_NORMAL;
                break;
                case 's':
                    luz = luz == LUZ_PONTUAL ? LUZ_SPOTLIGHT : LUZ_PONTUAL;
                break;
                case 27:
                    tela = TELA_MENU;
                    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
                    reset_Jogo();
                    reset_ret_colors();
                break;
            }
        }
        if(modo == MODO_2_PLAYERS){
            switch(key){
                case 'a':
                    if(not pressKeyboard){
                        pressKeyboard = true;
                        rebatedor2.vx = -1;
                    }
                break;
                case 'd':
                    if(not pressKeyboard){
                        pressKeyboard = true;
                        rebatedor2.vx = 1;
                    }
                break;
            }
        }
        switch(key){
            case 32:
                pause = not pause;
                if(modo == MODO_1_PLAYER) enable_tempo = not enable_tempo;
            break;
        }
    }
    glutPostRedisplay();
}

void specialKeysPress(int button, int x, int y){
    switch(button){
        case GLUT_KEY_RIGHT:
            luz0_posicao[0] += 0.1;
            glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);
            spot2_posicao[0] += 0.1;
            glLightfv(GL_LIGHT2, GL_POSITION, spot2_posicao);
        break;
        case GLUT_KEY_LEFT:
            luz0_posicao[0] -= 0.1;
            glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);
            spot2_posicao[0] -= 0.1;
            glLightfv(GL_LIGHT2, GL_POSITION, spot2_posicao);
        break;
        case GLUT_KEY_UP:
            luz0_posicao[2] += 0.1;
            glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);
            spot2_posicao[2] += 0.1;
            glLightfv(GL_LIGHT2, GL_POSITION, spot2_posicao);
        break;
        case GLUT_KEY_DOWN:
            luz0_posicao[2] -= 0.1;
            glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);
            spot2_posicao[2] -= 0.1;
            glLightfv(GL_LIGHT2, GL_POSITION, spot2_posicao);
        break;
    }

    glutPostRedisplay();
}

void motionJogo(int x, int y){
    if(camera == CAMERA_TOP) camera = CAMERA_NORMAL;

    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    last_x = x;
    last_y = y;
}

// Motion callback
void motion(int x, int y){
    switch(tela){
        case TELA_MENU:
        break;
        case TELA_MODO_1P:
        break;
        case TELA_MODO_2P:
        break;
        case TELA_RANK:
        break;
        case TELA_JOGO:
            if(pause) motionJogo(x,y);
        break;
    }

    glutPostRedisplay();
}

void passiveMotion_MainMenu(int x, int y){
    y = height - y;

    float objPosX = x*ortho_diff_x/width+ortho_menu[0];
    float objPosY = y*ortho_diff_y/height+ortho_menu[2];

    if     (de_1->   isInside(objPosX,objPosY)) de_1->setColor(ret_cor_passivo);
    else if(de_2->   isInside(objPosX,objPosY)) de_2->setColor(ret_cor_passivo);
    else if(ranking->isInside(objPosX,objPosY)) ranking->setColor(ret_cor_passivo);
    else if(sair->   isInside(objPosX,objPosY)) sair->setColor(ret_cor_passivo);
    else reset_ret_colors();
}

void passiveMotion_MenuModo(int x, int y){
    y = height - y;

    float objPosX = x*ortho_diff_x/width+ortho_menu[0];
    float objPosY = y*ortho_diff_y/height+ortho_menu[2];

    if(criterio == CRITERIO_VELOCIDADE) modo_veloc->setColor(ret_cor_selecionado);
    else modo_rebat->setColor(ret_cor_selecionado);

    if(choose_lv->isInside(objPosX,objPosY)) choose_lv->setColor(ret_cor_passivo);
    else if(start->   isInside(objPosX,objPosY)) start->setColor(ret_cor_passivo);
    else if(voltar->   isInside(objPosX,objPosY)) voltar->setColor(ret_cor_passivo);
    else reset_ret_colors();
}

void passiveMotion_Ranking(int x, int y){
    y = height - y;

    float objPosX = x*ortho_diff_x/width+ortho_menu[0];
    float objPosY = y*ortho_diff_y/height+ortho_menu[2];

    if     (menu->isInside(objPosX,objPosY)){
            menu->setColor(ret_cor_passivo);
    }
    else reset_ret_colors();
}

void passiveMotion_Jogo(int x, int y){
    rebatedor1_c[0] = (float)x*bf_tamx/(float)width - bf_tamx/2;
    if(rebatedor1_c[0]+rebatedor1.raio_maior > bf_tamx/2)
        rebatedor1_c[0] = bf_tamx/2-rebatedor1.raio_maior;
    else if(rebatedor1_c[0]-rebatedor1.raio_maior < -bf_tamx/2.0)
        rebatedor1_c[0] = -bf_tamx/2+rebatedor1.raio_maior;
    rebatedor1.setCentro(rebatedor1_c);
}

// Passive Motion callback
void passiveMotion(int x, int y){
    switch(tela){
        case TELA_MENU:
            passiveMotion_MainMenu(x,y);
        break;
        case TELA_MODO_1P:
            passiveMotion_MenuModo(x,y);
        break;
        case TELA_MODO_2P:
            passiveMotion_MenuModo(x,y);
        break;
        case TELA_RANK:
            passiveMotion_Ranking(x,y);
        break;
        case TELA_JOGO:
            if(!pause) passiveMotion_Jogo(x,y);
        break;
    }

    glutPostRedisplay();
}

void mouseMainMenu(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        last_x = x;
        last_y = y;

        y = height - y;

        float objPosX = x*ortho_diff_x/width+ortho_menu[0];
        float objPosY = y*ortho_diff_y/height+ortho_menu[2];

        if(de_1->isInside(objPosX,objPosY)){
            tela = TELA_MODO_1P;
            modo = MODO_1_PLAYER;
            //enable_tempo = true;
            de_1->setColor(ret_cor_selecionado);
        }
        else if(de_2->isInside(objPosX,objPosY)){
            tela = TELA_MODO_2P;
            modo = MODO_2_PLAYERS;
            enable_tempo = false;
            de_2->setColor(ret_cor_selecionado);
        }
        else if(ranking->isInside(objPosX,objPosY)){
            tela = TELA_RANK;
            enable_tempo = false;
            ranking->setColor(ret_cor_selecionado);
        }
        else if(sair->isInside(objPosX,objPosY)){
            sair->setColor(ret_cor_selecionado);
            exit(0);
        }
        else reset_ret_colors();
    }
}

void mouseMenuModo(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        last_x = x;
        last_y = y;

        y = height - y;

        float objPosX = x*ortho_diff_x/width+ortho_menu[0];
        float objPosY = y*ortho_diff_y/height+ortho_menu[2];

        if(modo_veloc->isInside(objPosX,objPosY)){
            criterio = CRITERIO_VELOCIDADE;
            modo_veloc->setColor(ret_cor_selecionado);
        }
        else if(modo_rebat->isInside(objPosX,objPosY)){
            criterio = CRITERIO_REBATIDAS;
            modo_rebat->setColor(ret_cor_selecionado);
        }
        else if(choose_lv->isInside(objPosX,objPosY)){
            nivel = nivel < NIVEL_3 ? nivel+1 : NIVEL_1;
            if(nivel == NIVEL_1){
                choose_lv->nome = "Nivel 1";
                level_num = 1;
                e.velocidade = esfera_velocidade_min_1;
            }
            else if(nivel == NIVEL_2){
                choose_lv->nome = "Nivel 2";
                level_num = 2;
                e.velocidade = esfera_velocidade_min_2;
            }
            else if(nivel == NIVEL_3){
                choose_lv->nome = "Nivel 3";
                level_num = 3;
                e.velocidade = esfera_velocidade_min_3;
            }
            choose_lv->setColor(ret_cor_selecionado);
        }
        else if(start->isInside(objPosX,objPosY)){
            start->setColor(ret_cor_selecionado);
            if(tela == TELA_MODO_1P){
                modo = MODO_1_PLAYER;
                enable_tempo = true;
                tela = TELA_JOGO;
                glutSetCursor(GLUT_CURSOR_NONE);
            }else{
                modo = MODO_2_PLAYERS;
                enable_tempo = false;
                tela = TELA_JOGO;
                glutSetCursor(GLUT_CURSOR_NONE);
            }
        }else if(voltar->isInside(objPosX,objPosY)){
            tela = TELA_MENU;
            reset_ret_colors();
            reset_Jogo();
        }
        else reset_ret_colors();
    }
}

void mouseRanking(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        last_x = x;
        last_y = y;

        y = height - y;

        float objPosX = x*ortho_diff_x/width+ortho_menu[0];
        float objPosY = y*ortho_diff_y/height+ortho_menu[2];

        if(menu->isInside(objPosX,objPosY)){
            tela = TELA_MENU;
            modo = MODO_1_PLAYER;
            //enable_tempo = false;
            de_1->setColor(ret_cor_selecionado);
            reset_ret_colors();
            reset_Jogo();
        }
    }
}

void mouseJogo(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        last_x = x;
        last_y = y;
    }
    if(button == 3) distOrigem = distOrigem <= 1 ? 1 : distOrigem-0.5;
    if(button == 4) distOrigem = distOrigem >= 50 ? 50 : distOrigem+0.5;
}

// Mouse callback
void mouse(int button, int state, int x, int y){
    switch(tela){
        case TELA_MENU:
            mouseMainMenu(button,state,x,y);
        break;
        case TELA_MODO_1P:
            mouseMenuModo(button,state,x,y);
        break;
        case TELA_MODO_2P:
            mouseMenuModo(button,state,x,y);
        break;
        case TELA_RANK:
            mouseRanking(button,state,x,y);
        break;
        case TELA_JOGO:
            if(pause) mouseJogo(button,state,x,y);
        break;
    }
}

void desenhaNomeVencedor(int tempo, float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w*0.3,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glColor3fv(cor_placar);
    glRasterPos2f(ortho[1]*0.435,ortho[3]*0.9);
    for(int k = 0; k < escreveNome.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, escreveNome[k]);
}

void desenhaLateral_Info(int tempo, float w, float h, float ortho[]){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w*0.3,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    if(modo == MODO_1_PLAYER){
        desenhaPlacar(placar_reb1, placar_reb2, cor_placar_reb1, cor_placar_reb2, cor_placar, ortho);
        desenhaTempo(tempo, cor_tempo, ortho);
        desenhaLevel(level_LEVEL, level_num, cor_level, ortho);
    }
}

void display_main_menu(float w, float h, float ortho[]){
    glClearColor (0.4, 0.4, 0.4, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    desenhaTitulo(ortho_menu);
    desenhaRetangulo(titulo,ortho_menu);
    desenhaRetangulo(de_1,ortho_menu);
    desenhaRetangulo(de_2,ortho_menu);
    desenhaRetangulo(ranking,ortho_menu);
    desenhaRetangulo(sair,ortho_menu);
}

void display_menu_modo(float w, float h, float ortho[]){
    glClearColor (0.4, 0.4, 0.4, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //glOrtho(ortho_menu[0],ortho_menu[1],ortho_menu[2],ortho_menu[3],ortho_menu[4],ortho_menu[5]);
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    desenhaRetangulo(modo_veloc,ortho_menu);
    desenhaRetangulo(modo_rebat,ortho_menu);
    desenhaRetangulo(start,ortho_menu);
    desenhaRetangulo(voltar,ortho_menu);
    if(tela == TELA_MODO_1P) desenhaRetangulo(choose_lv,ortho_menu);
}

void display_ranking(float w, float h, float ortho[]){
    glClearColor (0.4, 0.4, 0.4, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //glOrtho(ortho_menu[0],ortho_menu[1],ortho_menu[2],ortho_menu[3],ortho_menu[4],ortho_menu[5]);
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    desenhaTitRanking(ortho_menu);
    desenhaRetangulo(titRanking,ortho_menu);
    desenhaRetangulo(rnk_lv1,ortho_menu);
    desenhaRetangulo(rnk_lv2,ortho_menu);
    desenhaRetangulo(rnk_lv3,ortho_menu);
    desenhaRetangulo(posicao00,ortho_menu);
    desenhaRetangulo(posicao01,ortho_menu);
    desenhaRetangulo(posicao02,ortho_menu);
    desenhaRetangulo(posicao03,ortho_menu);
    desenhaRetangulo(posicao04,ortho_menu);
    desenhaRetangulo(posicao05,ortho_menu);
    desenhaRetangulo(posicao06,ortho_menu);
    desenhaRetangulo(posicao07,ortho_menu);
    desenhaRetangulo(posicao08,ortho_menu);
    desenhaRetangulo(posicao09,ortho_menu);
    desenhaRetangulo(posicao10,ortho_menu);
    desenhaRetangulo(posicao11,ortho_menu);
    desenhaRetangulo(posicao12,ortho_menu);
    desenhaRetangulo(posicao13,ortho_menu);
    desenhaRetangulo(posicao14,ortho_menu);
    desenhaRetangulo(posicao15,ortho_menu);
    desenhaRetangulo(posicao16,ortho_menu);
    desenhaRetangulo(posicao17,ortho_menu);
    desenhaRetangulo(posicao18,ortho_menu);
    desenhaRetangulo(posicao19,ortho_menu);
    desenhaRetangulo(posicao20,ortho_menu);
    desenhaRetangulo(posicao21,ortho_menu);
    desenhaRetangulo(posicao22,ortho_menu);
    desenhaRetangulo(posicao23,ortho_menu);
    desenhaRetangulo(posicao24,ortho_menu);
    desenhaRetangulo(posicao25,ortho_menu);
    desenhaRetangulo(posicao26,ortho_menu);
    desenhaRetangulo(posicao27,ortho_menu);
    desenhaRetangulo(posicao28,ortho_menu);
    desenhaRetangulo(posicao29,ortho_menu);
    //if(rnk1 == true) desenhaRetangulo(proximo,ortho_menu);
    //else
    desenhaRetangulo(menu,ortho_menu);
}

void desenhaBlocks(){
    for(int k = 0; k < 10; k++){
        glPushMatrix();
            glTranslatef(0,3*sin(pos+k*M_PI/3),0);
            desenhaBloco(blocks[k]);
        glPopMatrix();
    }
    for(int k = 0; k < 10; k++){
        glPushMatrix();
            glTranslatef(0,3*sin(-pos-k*M_PI/3),0);
            desenhaBloco(blocks[k+11]);
        glPopMatrix();
    }
}

void desenhaLights(){
    if(luz == LUZ_PONTUAL){
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
        glDisable(GL_LIGHT6);
        glDisable(GL_LIGHT7);

        glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);

    }else{
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
        glEnable(GL_LIGHT5);
        glEnable(GL_LIGHT6);
        glEnable(GL_LIGHT7);

        glLightfv(GL_LIGHT1, GL_POSITION, spot1_posicao);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot1_dir);
        glLightfv(GL_LIGHT2, GL_POSITION, spot2_posicao);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot2_dir);
        glLightfv(GL_LIGHT3, GL_POSITION, spot3_posicao);
        glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot3_dir);
        glLightfv(GL_LIGHT4, GL_POSITION, spot4_posicao);
        glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot4_dir);
        glLightfv(GL_LIGHT5, GL_POSITION, spot5_posicao);
        glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot5_dir);
        glLightfv(GL_LIGHT6, GL_POSITION, spot6_posicao);
        glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot6_dir);
        glLightfv(GL_LIGHT7, GL_POSITION, spot7_posicao);
        glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spot7_dir);
    }

    //setMaterial_1side(spots_ambiente,spots_difusa,spots_especular,spots_emissao,spots_brilho);
    /*
    glPushMatrix();
        glTranslatef(spot1_posicao[0],spot1_posicao[1],spot1_posicao[2]);
        glutSolidSphere(0.1,20,20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(spot2_posicao[0],spot2_posicao[1],spot2_posicao[2]);
        glutSolidSphere(0.1,20,20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(spot3_posicao[0],spot3_posicao[1],spot3_posicao[2]);
        glutSolidSphere(0.1,20,20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(spot4_posicao[0],spot4_posicao[1],spot4_posicao[2]);
        glutSolidSphere(0.1,20,20);
    glPopMatrix();

    glPushMatrix();
    glPushMatrix();
        glTranslatef(spot5_posicao[0],spot5_posicao[1],spot5_posicao[2]);
        glutSolidSphere(0.1,20,20);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(spot6_posicao[0],spot6_posicao[1],spot6_posicao[2]);
        glutSolidSphere(0.1,20,20);
    glPopMatrix();
    */

    /*
    glPushMatrix();
        glTranslatef(luz0_posicao[0],luz0_posicao[1],luz0_posicao[2]);
        setMaterial_1side(luz0_ambiente,luz0_difusa,luz0_emissao,luz0_emissao,luz0_brilho);
        glutSolidSphere(0.2,20,20);
    glPopMatrix();
    */
}

void display_jogo(){
    glClearColor(0,0,0,0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,width,height);
    if(camera == CAMERA_TOP){
            gluLookAt(0.0, distOrigem, 0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
            rotationX = 0;
            rotationY = 0;
    }
    else if(camera == CAMERA_NORMAL) gluLookAt(0.0, distOrigem, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    glPushMatrix();
        glRotatef( rotationY, 0.0, 1.0, 0.0 );
        //glRotatef( rotationX, 1.0, 0.0, 0.0 );

        desenhaLights();

        desenhaEsfera(e);
        desenhaBloco(battle_field);
        desenhaBloco(lateral1);
        desenhaBloco(lateral2);
        desenhaRebatedor(rebatedor1);
        desenhaRebatedor(rebatedor2);
        desenhaPoste(poste11);
        desenhaPoste(poste12);
        desenhaPoste(poste21);
        desenhaPoste(poste22);
        desenhaPoste(poste31);
        desenhaPoste(poste32);

        if(luz == LUZ_SPOTLIGHT) glEnable(GL_LIGHT0);
        desenhaBlocks();
        if(luz == LUZ_SPOTLIGHT) glDisable(GL_LIGHT0);

    glPopMatrix();
}

void display(){
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    switch(tela){
        case TELA_MENU:
            display_main_menu(width,height,ortho_menu);
        break;
        case TELA_MODO_1P:
            display_menu_modo(width,height,ortho_menu);
        break;
        case TELA_MODO_2P:
            display_menu_modo(width,height,ortho_menu);
        break;
        case TELA_RANK:
            display_ranking(width,height,ortho_menu);
        break;
        case TELA_JOGO:
            desenhaLateral_Info(tempo,width,height,ortho_placar);
            if(pause) desenhaPause(pause_PAUSE, pause_jogo, pause_cam, pause_spot, pause_esc, cor_pause, width, height, ortho_placar);
            display_jogo();
        break;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}


void init (void){
    width = glutGet(GLUT_SCREEN_WIDTH);
    height = glutGet(GLUT_SCREEN_HEIGHT);

    ortho_menu[0] = -1.0*width/height;
    ortho_menu[1] =  1.0*width/height;

    ortho_diff_x = ortho_menu[1]-ortho_menu[0];
    ortho_diff_y = ortho_menu[3]-ortho_menu[2];

    int num_pontos = 20;
	float **pontos;
	pontos = new float*[num_pontos];
	int k = 0;
	for(float theta = 0; theta <= M_PI+M_PI/num_pontos; theta += M_PI/(num_pontos-1)){
        pontos[k] = new float[3];
        //cout << theta << endl;
        pontos[k][0] = 1.3*(theta-M_PI_2);
        pontos[k][1] = 0;
        pontos[k][2] = -1.3*sin(theta);
        k++;
    }

	rebatedor1 = Rebatedor(rebatedor1_c,pontos,num_pontos,rebatedor_espessura,rebatedor1_ambient,rebatedor1_difusa,rebatedor1_especular,rebatedor1_emissao,rebatedor1_brilho,1,0,0,rebatedor1_velocidade);

	float **pontos2;
	pontos2 = new float*[num_pontos];
	k = 0;
	for(float theta = M_PI; theta > -M_PI/(num_pontos-1); theta -= M_PI/(num_pontos-1)){
        pontos2[k] = new float[3];
        pontos2[k][0] = 1.3*(theta-M_PI_2);
        pontos2[k][1] = 0;
        pontos2[k][2] = 1.3*sin(theta);
        k++;
    }

	rebatedor2 = Rebatedor(rebatedor2_c,pontos2,num_pontos,rebatedor_espessura,rebatedor2_ambient,rebatedor2_difusa,rebatedor2_especular,rebatedor2_emissao,rebatedor2_brilho,1,0,0,rebatedor2_velocidade);

	for(int k = 0; k < 22; k++){
        blocks_c[k][0] = k < 10 ? 7.25 : -7.25;
        blocks_c[k][1] = pos;
        blocks_c[k][2] = k < 10 ? 2*k-9 : 2*(k-11)-9;

        blocks[k] = Bloco(blocks_c[k],2,2,2,blocks_ambient,blocks_difusa,blocks_especular,blocks_emissao,blocks_brilho);
    }

    titulo  = new Retangulo(0.15*ortho_diff_x+ortho_menu[0],0.95*ortho_diff_y+ortho_menu[2],0.85*ortho_diff_x+ortho_menu[0],0.60*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"");
    de_1    = new Retangulo(0.25*ortho_diff_x+ortho_menu[0],0.50*ortho_diff_y+ortho_menu[2],0.75*ortho_diff_x+ortho_menu[0],0.40*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"1 Jogador");
    de_2    = new Retangulo(0.25*ortho_diff_x+ortho_menu[0],0.35*ortho_diff_y+ortho_menu[2],0.75*ortho_diff_x+ortho_menu[0],0.25*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"2 Jogadores");
    ranking = new Retangulo(0.35*ortho_diff_x+ortho_menu[0],0.20*ortho_diff_y+ortho_menu[2],0.65*ortho_diff_x+ortho_menu[0],0.15*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"Ranking");
    sair    = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.10*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.06*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"Sair");

    modo_veloc = new Retangulo(0.125*ortho_diff_x+ortho_menu[0],0.6875*ortho_diff_y+ortho_menu[2],0.45*ortho_diff_x+ortho_menu[0],0.5625*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"Modo Velocidade");
    modo_rebat = new Retangulo(0.55*ortho_diff_x+ortho_menu[0],0.6875*ortho_diff_y+ortho_menu[2],0.875*ortho_diff_x+ortho_menu[0],0.5625*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],1.0,"Modo Rebatidas");
    choose_lv  = new Retangulo(0.40*ortho_diff_x+ortho_menu[0],0.50*ortho_diff_y+ortho_menu[2],0.60*ortho_diff_x+ortho_menu[0],0.40*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"Nivel 1");
    start      = new Retangulo(0.25*ortho_diff_x+ortho_menu[0],0.30*ortho_diff_y+ortho_menu[2],0.75*ortho_diff_x+ortho_menu[0],0.15*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"Start!");
    voltar     = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.10*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.06*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],"Voltar");

    titRanking = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.95*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.85*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
	rnk_lv1    = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.815*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.765*ortho_diff_y+ortho_menu[2],0.0,1.0,1.0,"Nivel 1");
    posicao00  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.752*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.702*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao01  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.689*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.639*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao02  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.626*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.576*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao03  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.563*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.513*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao04  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.500*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.450*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao05  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.437*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.387*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao06  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.374*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.324*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao07  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.311*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.261*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao08  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.248*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.198*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao09  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.185*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.135*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");

    rnk_lv2    = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.815*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.765*ortho_diff_y+ortho_menu[2],0.0,1.0,1.0,"Nivel 2");
    posicao10  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.752*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.702*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao11  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.689*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.639*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao12  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.626*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.576*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao13  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.563*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.513*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao14  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.500*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.450*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao15  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.437*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.387*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao16  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.374*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.324*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao17  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.311*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.261*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao18  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.248*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.198*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao19  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.185*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.135*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");

    rnk_lv3    = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.815*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.765*ortho_diff_y+ortho_menu[2],0.0,1.0,1.0,"Nivel 2");
    posicao20  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.752*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.702*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao21  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.689*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.639*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao22  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.626*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.576*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao23  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.563*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.513*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao24  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.500*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.450*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao25  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.437*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.387*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao26  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.374*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.324*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao27  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.311*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.261*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao28  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.248*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.198*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");
    posicao29  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.185*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.135*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"");

    //proximo    = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.100*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.060*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"Proximo");
    menu       = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.100*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.060*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,"Menu");

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling

    //glEnable(GL_LIGHT0);                   // habilita luz 0

    glLightfv(GL_LIGHT0, GL_AMBIENT, luz0_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz0_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

    setSpotlight(GL_LIGHT1,spots_ambiente,spots_difusa,spots_especular,spot1_posicao,spot1_dir,spots_cutoff,spots_expoente);
    setSpotlight(GL_LIGHT2,spots_ambiente,spots_difusa,spots_especular,spot2_posicao,spot2_dir,spots_cutoff,spots_expoente);
    setSpotlight(GL_LIGHT3,spots_ambiente,spots_difusa,spots_especular,spot3_posicao,spot3_dir,spots_cutoff,spots_expoente);
    setSpotlight(GL_LIGHT4,spots_ambiente,spots_difusa,spots_especular,spot4_posicao,spot4_dir,spots_cutoff,spots_expoente);
    setSpotlight(GL_LIGHT5,spots_ambiente,spots_difusa,spots_especular,spot5_posicao,spot5_dir,spots_cutoff,spots_expoente);
    setSpotlight(GL_LIGHT6,spots_ambiente,spots_difusa,spots_especular,spot6_posicao,spot6_dir,spots_cutoff,spots_expoente);
    setSpotlight(GL_LIGHT7,spots_ambiente,spots_difusa,spots_especular,spot7_posicao,spot7_dir,spots_cutoff,spots_expoente);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void idle(){
    if(!pause and tela == TELA_JOGO){
        if(modo == MODO_1_PLAYER){
            if     (e.c[0] > rebatedor2_c[0]) rebatedor2.vx = 1;
            else if(e.c[0] < rebatedor2_c[0]) rebatedor2.vx = -1;
            else                              rebatedor2.vx = 0;

            rebatedor2_c[0] += rebatedor2.vx*rebatedor2.velocidade;

            if     (rebatedor2.vx ==  1 and e.c[0] < rebatedor2_c[0])    rebatedor2_c[0] = e.c[0];
            else if(rebatedor2.vx == -1 and e.c[0] > rebatedor2_c[0])   rebatedor2_c[0] = e.c[0];
            if     (rebatedor2_c[0]+rebatedor2.raio_maior >  bf_tamx/2) rebatedor2_c[0] = bf_tamx/2-rebatedor2.raio_maior;
            else if(rebatedor2_c[0]-rebatedor2.raio_maior < -bf_tamx/2) rebatedor2_c[0] = -bf_tamx/2+rebatedor2.raio_maior;

            rebatedor2.setCentro(rebatedor2_c);
        }
        else if(modo == MODO_2_PLAYERS){
            if(pressKeyboard){
                rebatedor2_c[0] += rebatedor2.vx*rebatedor2.velocidade;
                if     (rebatedor2_c[0]+rebatedor2.raio_maior >  bf_tamx/2) rebatedor2_c[0] = bf_tamx/2-rebatedor2.raio_maior;
                else if(rebatedor2_c[0]-rebatedor2.raio_maior < -bf_tamx/2) rebatedor2_c[0] = -bf_tamx/2+rebatedor2.raio_maior;
                rebatedor2.setCentro(rebatedor2_c);
            }
        }
        if(e.c[2] >= bf_tamz/2){
            ponto = true;
            placar_reb1++;
            if(placar_reb1 == 3){
                venceu = true;
                tempo = 0;
                placar_reb1 = 0;
                placar_reb2 = 0;
            }
            e.c[0] = 0;
            e.c[1] = 0;
            e.c[2] = 0;
        }
        else if(e.c[2] <= -bf_tamz/2){
            ponto = true;
            placar_reb2++;
            if(placar_reb2 == 3){
                venceu = true;
                if(modo == MODO_1_PLAYER){
                    switch(nivel){
                        case NIVEL_1:
                            if(eh_menor_Rankeados(tempo,rankeados_1)){
                                Rankeados r = Rankeados("Jogador",tempo);
                                rankeados_1.push_back(r);
                                sort(rankeados_1.begin(),rankeados_1.end(),menorRanking);
                                if(rankeados_1.size() > 10) rankeados_1.pop_back();
                            }
                        break;
                        case NIVEL_2:
                            if(eh_menor_Rankeados(tempo,rankeados_2)){
                                Rankeados r = Rankeados("Jogador",tempo);
                                rankeados_2.push_back(r);
                                sort(rankeados_2.begin(),rankeados_2.end(),menorRanking);
                                if(rankeados_2.size() > 10) rankeados_2.pop_back();
                            }
                        break;
                        case NIVEL_3:
                            if(eh_menor_Rankeados(tempo,rankeados_3)){
                                Rankeados r = Rankeados("Jogador",tempo);
                                rankeados_3.push_back(r);
                                sort(rankeados_3.begin(),rankeados_3.end(),menorRanking);
                                if(rankeados_3.size() > 10) rankeados_3.pop_back();
                            }
                        break;
                    }
                    escreve_Arquivo_ranking();
                }
                tempo = 0;
                placar_reb1 = 0;
                placar_reb2 = 0;
            }
            e.c[0] = 0;
            e.c[1] = 0;
            e.c[2] = 0;
        }
        if(!colidiu_lat1){
            if(block_collision(e,lateral1)){
                e.v[0] = - e.v[0];
                colidiu_lat1 = true;
                colidiu_lat2 = false;
                colidiu_reb1 = false;
                colidiu_reb2 = false;
            }
        }
        if(!colidiu_lat2){
            if(block_collision(e,lateral2)){
                e.v[0] = - e.v[0];
                colidiu_lat1 = false;
                colidiu_lat2 = true;
                colidiu_reb1 = false;
                colidiu_reb2 = false;
            }
        }
        if(!colidiu_reb1){
            if(bumper_collision(e,rebatedor1)){
                colidiu_lat1 = false;
                colidiu_lat2 = false;
                colidiu_reb1 = true;
                colidiu_reb2 = false;
            }
        }
        if(!colidiu_reb2){
            if(bumper_collision(e,rebatedor2)){
                colidiu_lat1 = false;
                colidiu_lat2 = false;
                colidiu_reb1 = false;
                colidiu_reb2 = true;
            }
        }

        e.c[0] += e.v[0]*0.05*e.velocidade;
        e.c[1] += e.v[1]*0.05*e.velocidade;
        e.c[2] += e.v[2]*0.05*e.velocidade;

        switch(nivel){
            case NIVEL_1:
                if(e.velocidade >= esfera_velocidade_max_1) e.velocidade = esfera_velocidade_max_1;
                else{
                    e.velocidade += fator_aumenta_vel;
                    blocks_velocidade += fator_aumenta_vel/75;
                }
            break;
            case NIVEL_2:
                if(e.velocidade >= esfera_velocidade_max_2) e.velocidade = esfera_velocidade_max_2;
                else{
                    e.velocidade += fator_aumenta_vel;
                    blocks_velocidade += fator_aumenta_vel/75;
                }
            break;
            case NIVEL_3:
                if(e.velocidade >= esfera_velocidade_max_3) e.velocidade = esfera_velocidade_max_3;
                else{
                    e.velocidade += fator_aumenta_vel;
                    blocks_velocidade += fator_aumenta_vel/75;
                }
            break;
        }
        //cout << e.velocidade << endl;
    }

    if(tela == TELA_JOGO) pos = pos >= 2*M_PI ? 0 : pos+blocks_velocidade;

    glutPostRedisplay();
}

int main(int argc, char** argv){
    //escreve_Arquivo_ranking();
    le_Arquivo_ranking();

    sort(rankeados_1.begin(),rankeados_1.end(),menorRanking);
    sort(rankeados_2.begin(),rankeados_2.end(),menorRanking);
    sort(rankeados_3.begin(),rankeados_3.end(),menorRanking);

    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (300, 100);
    glutCreateWindow ("PONG 3D");
    init ();
    glutMouseFunc( mouse );
    glutKeyboardFunc( keyboard );
    glutKeyboardUpFunc( keyboardUp );
    glutSpecialFunc( specialKeysPress );
    glutMotionFunc( motion );
    glutPassiveMotionFunc( passiveMotion );
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutIdleFunc( idle );

    timer_func(10);

    glutFullScreen();

    glutMainLoop();

    return 0;
}
