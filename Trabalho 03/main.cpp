#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <AL/alut.h>

#include "Esfera.h"
#include "Rebatedor.h"
#include "Bloco.h"
#include "Desenho.h"
#include "Collision.h"
#include "Valores.h"
#include "Retangulo.h"
#include "Poste.h"
#include "glcTexture.h"

#define TELA_MENU 1
#define TELA_MODO_1P 2
#define TELA_MODO_2P 3
#define TELA_RANK 4
#define TELA_JOGO 5
#define MODO_1_PLAYER 6
#define MODO_2_PLAYERS 7
#define NIVEL_1 8
#define NIVEL_2 9
#define NIVEL_3 10
#define LUZ_PONTUAL 11
#define LUZ_SPOTLIGHT 12
#define CAMERA_TOP 13
#define CAMERA_NORMAL 14

using namespace std;

bool playing_collision = true;

int tela = TELA_MENU;
int modo = MODO_1_PLAYER;
int nivel = NIVEL_1;
int luz = LUZ_SPOTLIGHT;
int camera = CAMERA_NORMAL;

void play_SoundEffect(int num_source){
    alSourcePlay(Source_SoundEffect[num_source]);
}

void play_MusicSound(int num_source){
    alSourcePlay(Source_MusicSounds[num_source]);
}

void stop_SoundEffect(int num_source){
    alSourceStop(Source_SoundEffect[num_source]);
}

void stop_MusicSound(int num_source){
    alSourceStop(Source_MusicSounds[num_source]);
}

void stop_all_SoundEffect(){
    for(int k = 0; k < NUM_SE; k++) alSourceStop(Source_SoundEffect[k]);
}

void stop_all_MusicSound(){
    for(int k = 0; k < NUM_MS; k++) alSourceStop(Source_MusicSounds[k]);
}

void setSpotlight(GLenum luz, GLfloat *ambiente, GLfloat *difusa, GLfloat *especular, GLfloat *posicao, GLfloat *direcao, GLfloat cutoff, GLfloat expoente){
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

    glEnable(luz);                   // habilita luz
}

bool eh_menor_Rankeados(int tempo, vector<Rankeados> r){
    if(r.size() < 10) return true;
    for(int k = 0; k < r.size(); k++){
        if(tempo < r[k].tempo) return true;
    }
    return false;
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

void update_Menu_Rank(){
    for(int k = 0; k < rankeados_1.size(); k++)
        posicao[k]->nome = convert_int_to_time_string(rankeados_1[k].tempo) + " " + rankeados_1[k].nome;
    for(int k = 0; k < rankeados_2.size(); k++)
        posicao[k+10]->nome = convert_int_to_time_string(rankeados_2[k].tempo) + " " + rankeados_2[k].nome;
    for(int k = 0; k < rankeados_3.size(); k++)
        posicao[k+20]->nome = convert_int_to_time_string(rankeados_3[k].tempo) + " " + rankeados_3[k].nome;
}

void update_Score(){
    placar21.face_tex_ids[0] = placar_reb2;
    placar22.face_tex_ids[0] = placar_reb1;
    id_placarScore = createScore3d(placar21,placar22,20);
}

void update_Placar_Base(){
    placar1.face_tex_ids[0] = level_num - 1;
    id_placarBase = createPlacar3d(placar1,placar31,placar32,20);
}

void inclui_vencedor(){
    if(modo == MODO_1_PLAYER){
        switch(nivel){
            case NIVEL_1:
                if(eh_menor_Rankeados(tempo,rankeados_1)){
                    Rankeados r = Rankeados(venceu_nome,tempo);
                    rankeados_1.push_back(r);
                    sort(rankeados_1.begin(),rankeados_1.end(),menorRanking);
                    if(rankeados_1.size() > 10) rankeados_1.pop_back();
                }
            break;
            case NIVEL_2:
                if(eh_menor_Rankeados(tempo,rankeados_2)){
                    Rankeados r = Rankeados(venceu_nome,tempo);
                    rankeados_2.push_back(r);
                    sort(rankeados_2.begin(),rankeados_2.end(),menorRanking);
                    if(rankeados_2.size() > 10) rankeados_2.pop_back();
                }
            break;
            case NIVEL_3:
                if(eh_menor_Rankeados(tempo,rankeados_3)){
                    Rankeados r = Rankeados(venceu_nome,tempo);
                    rankeados_3.push_back(r);
                    sort(rankeados_3.begin(),rankeados_3.end(),menorRanking);
                    if(rankeados_3.size() > 10) rankeados_3.pop_back();
                }
            break;
        }
        update_Menu_Rank();
    }
}

void reset_Jogo(){
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    placar_reb1 = 0;
    placar_reb2 = 0;
    update_Score();
    tempo = 0;
    enable_tempo = false;
    pause = false;
    venceu = false;
    perdeu = false;
    espera = true;
    camera = CAMERA_NORMAL;
    rebatedor2_c[0] = 0;
    rebatedor2.setCentro(rebatedor2_c);
    e.c[0] = 0;
    e.c[1] = rebatedor_espessura/2;
    e.c[2] = 0;

    blocks_velocidade = blocks_velocidade0;

    venceu_nome = "";
    venceu_2_players_p1 = false;
    venceu_2_players_p2 = false;

    colidiu_lat1 = false;
    colidiu_lat2 = false;
    colidiu_reb1 = false;
    colidiu_reb2 = false;

    nivel = NIVEL_1;
    level_num = 1;
    e.velocidade = esfera_velocidade_min_1;

    luz = LUZ_SPOTLIGHT;

    rotationX = 0;
    rotationY = 0;

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

void reset_vel_pos_dir_esfera(){
    e.c[0] = 0;
    e.c[1] = rebatedor_espessura/2;
    e.c[2] = 0;

    switch(nivel){
        case NIVEL_1:
            e.velocidade = esfera_velocidade_min_1;
        break;
        case NIVEL_2:
            e.velocidade = esfera_velocidade_min_2;
        break;
        case NIVEL_3:
            e.velocidade = esfera_velocidade_min_3;
        break;
    }

    switch(rand()%4){
        case 0:
            esfera_v[0] = esfera_v01[0];
            esfera_v[1] = esfera_v01[1];
            esfera_v[2] = esfera_v01[2];
            colidiu_lat2 = false;
        break;
        case 1:
            esfera_v[0] = esfera_v02[0];
            esfera_v[1] = esfera_v02[1];
            esfera_v[2] = esfera_v02[2];
            colidiu_lat2 = false;
        break;
        case 2:
            esfera_v[0] = esfera_v03[0];
            esfera_v[1] = esfera_v03[1];
            esfera_v[2] = esfera_v03[2];
            colidiu_lat1 = false;
        break;
        case 3:
            esfera_v[0] = esfera_v04[0];
            esfera_v[1] = esfera_v04[1];
            esfera_v[2] = esfera_v04[2];
            colidiu_lat1 = false;
        break;
    }
    e.v = esfera_v;
}

void reset_Partida(){
    espera = true;
    placar_reb1 = 0;
    placar_reb2 = 0;
    update_Score();
    tempo = 0;
    enable_tempo = false;
    rebatedor2_c[0] = 0;
    rebatedor2.setCentro(rebatedor2_c);

    stop_all_MusicSound();
    play_MusicSound(0);

    venceu_nome = "";
    venceu_2_players_p1 = false;
    venceu_2_players_p2 = false;

    blocks_velocidade = blocks_velocidade0;

    reset_vel_pos_dir_esfera();

    pause = false;
    perdeu = false;
    venceu = false;
}

void reset_ret_colors(){
    titulo->setColor(ret_cor_normal);
    de_1->setColor(ret_cor_normal);
    de_2->setColor(ret_cor_normal);
    ranking->setColor(ret_cor_normal);
    sair->setColor(ret_cor_normal);

    choose_lv->currentBind = 0;
    start->setColor(ret_cor_normal);
    voltar->setColor(ret_cor_normal);
    menu->setColor(ret_cor_normal);
}

void reset_ret_textures(){
    fundo->currentBind = 0;
    titulo->currentBind = 0;
    de_1->currentBind = 0;
    de_2->currentBind = 0;
    ranking->currentBind = 0;
    sair->currentBind = 0;

    choose_lv->currentBind = nivel == NIVEL_1 ? 0 : nivel == NIVEL_2 ? 1 : 2;
    start->currentBind = 0;
    voltar->currentBind = 0;
    menu->currentBind = 0;
}

void timer_func(int n){
    glutTimerFunc(n, timer_func, n); // recursivamente chama timer_func
    if(enable_tempo) tempo++;
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
    if(key == 9){
        if(fullscreen){
            glutReshapeWindow(width,height);
            fullscreen = false;
        }else{
            glutFullScreen();
            fullscreen = true;
        }
    }
    if(tela == TELA_JOGO){
        if(venceu and modo == MODO_1_PLAYER){
            if((nivel == NIVEL_1 and eh_menor_Rankeados(tempo,rankeados_1)) or
               (nivel == NIVEL_2 and eh_menor_Rankeados(tempo,rankeados_2)) or
               (nivel == NIVEL_3 and eh_menor_Rankeados(tempo,rankeados_3))){
                if((key >= 65 and key <= 90) or (key >= 97 and key <= 122) and venceu_nome.size() <= 10){
                    stringstream ss;
                    ss << key;
                    venceu_nome += ss.str();
                }
                if((key == 127 or key == 8) and venceu_nome.size() >= 0)
                    venceu_nome = venceu_nome.substr(0, venceu_nome.size()-1);
                if(key == 13 and venceu_nome.size() > 0){
                    inclui_vencedor();
                    reset_Partida();
                }
            }else{
                if(key == 13)
                    reset_Partida();
                else if(key == 27){
                    tela = TELA_MENU;
                    stop_all_MusicSound();
                    stop_all_SoundEffect();
                    play_MusicSound(0);
                    reset_Jogo();
                    reset_ret_colors();
                    reset_ret_textures();
                }
            }
        }
        if(perdeu and modo == MODO_1_PLAYER){
            if(key == 13)
                reset_Partida();
            else if(key == 27){
                tela = TELA_MENU;
                stop_all_MusicSound();
                stop_all_SoundEffect();
                play_MusicSound(0);
                reset_Jogo();
                reset_ret_colors();
                reset_ret_textures();
            }
        }
        if((venceu_2_players_p1 or venceu_2_players_p2) and modo == MODO_2_PLAYERS){
            if(key == 13)
                reset_Partida();
            else if(key == 27){
                tela = TELA_MENU;
                stop_all_MusicSound();
                stop_all_SoundEffect();
                play_MusicSound(0);
                reset_Jogo();
                reset_ret_colors();
                reset_ret_textures();
            }
        }
        if(!pause and espera and !venceu and !perdeu){
            switch(key){
                case 13:
                    espera = not espera;
                    enable_tempo = not enable_tempo;
                break;
            }
        }
        if(pause and !venceu and !perdeu){
            switch(key){
                case 'm':
                    camera = camera == CAMERA_NORMAL ? CAMERA_TOP : CAMERA_NORMAL;
                break;
                case 's':
                    luz = luz == LUZ_PONTUAL ? LUZ_SPOTLIGHT : LUZ_PONTUAL;
                break;
                case 27:
                    tela = TELA_MENU;
                    stop_all_MusicSound();
                    stop_all_SoundEffect();
                    play_MusicSound(0);
                    reset_Jogo();
                    reset_ret_colors();
                    reset_ret_textures();
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
        if(!venceu and !perdeu){
            switch(key){
                case 32:
                    pause = not pause;
                    if(modo == MODO_1_PLAYER){
                        if(!espera) enable_tempo = pause ? false : true;
                    }
                break;
            }
        }
    }
    glutPostRedisplay();
}

void motionJogo(int x, int y){
    if(camera == CAMERA_TOP) camera = CAMERA_NORMAL;

    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    rotationX = rotationX >= 45 ? 45 : rotationX <= -45 ? -45 : rotationX;

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

    if     (de_1->   isInside(objPosX,objPosY)){
        de_1->setColor(ret_cor_passivo);
        de_1->currentBind = 1;
    }
    else if(de_2->   isInside(objPosX,objPosY)){
        de_2->setColor(ret_cor_passivo);
        de_2->currentBind = 1;
    }
    else if(ranking->isInside(objPosX,objPosY)){
        ranking->setColor(ret_cor_passivo);
        ranking->currentBind = 1;
    }
    else if(sair->   isInside(objPosX,objPosY)){
        sair->setColor(ret_cor_passivo);
        sair->currentBind = 1;
    }
    else{
        reset_ret_colors();
        reset_ret_textures();
    }
}

void passiveMotion_MenuModo(int x, int y){
    y = height - y;

    float objPosX = x*ortho_diff_x/width+ortho_menu[0];
    float objPosY = y*ortho_diff_y/height+ortho_menu[2];

    if(choose_lv->isInside(objPosX,objPosY)) choose_lv->currentBind = nivel == NIVEL_1 ? 3 : nivel == NIVEL_2 ? 4 : 5;
    else if(start->   isInside(objPosX,objPosY)) start->currentBind = 1;
    else if(voltar->   isInside(objPosX,objPosY)) voltar->currentBind = 1;
    else{
        reset_ret_colors();
        reset_ret_textures();
    }
}

void passiveMotion_Ranking(int x, int y){
    y = height - y;

    float objPosX = x*ortho_diff_x/width+ortho_menu[0];
    float objPosY = y*ortho_diff_y/height+ortho_menu[2];

    if     (menu->isInside(objPosX,objPosY)){
            menu->setColor(ret_cor_passivo);
            menu->currentBind = 1;
    }
    else{
        reset_ret_colors();
        reset_ret_textures();
    }
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
        }
        else if(de_2->isInside(objPosX,objPosY)){
            tela = TELA_MODO_2P;
            modo = MODO_2_PLAYERS;
            enable_tempo = false;
        }
        else if(ranking->isInside(objPosX,objPosY)){
            tela = TELA_RANK;
            enable_tempo = false;
        }
        else if(sair->isInside(objPosX,objPosY)){
            escreve_Arquivo_ranking();
            exit(0);
        }
        else{
            reset_ret_colors();
            reset_ret_textures();
        }
    }
}

void mouseMenuModo(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        last_x = x;
        last_y = y;

        y = height - y;

        float objPosX = x*ortho_diff_x/width+ortho_menu[0];
        float objPosY = y*ortho_diff_y/height+ortho_menu[2];

        if(choose_lv->isInside(objPosX,objPosY)){
            nivel = nivel < NIVEL_3 ? nivel+1 : NIVEL_1;
            if(nivel == NIVEL_1){
                choose_lv->currentBind = 0;
                level_num = 1;
                e.velocidade = esfera_velocidade_min_1;
            }
            else if(nivel == NIVEL_2){
                choose_lv->currentBind = 1;
                level_num = 2;
                e.velocidade = esfera_velocidade_min_2;
            }
            else if(nivel == NIVEL_3){
                choose_lv->currentBind = 2;
                level_num = 3;
                e.velocidade = esfera_velocidade_min_3;
            }
            update_Placar_Base();
        }
        else if(start->isInside(objPosX,objPosY)){
            if(tela == TELA_MODO_1P){
                modo = MODO_1_PLAYER;
                enable_tempo = false;
                tela = TELA_JOGO;
                stop_all_MusicSound();
                play_MusicSound(2);
                glutSetCursor(GLUT_CURSOR_NONE);
            }else{
                modo = MODO_2_PLAYERS;
                enable_tempo = false;
                tela = TELA_JOGO;
                stop_all_MusicSound();
                play_MusicSound(2);
                glutSetCursor(GLUT_CURSOR_NONE);
            }
        }else if(voltar->isInside(objPosX,objPosY)){
            tela = TELA_MENU;
            reset_ret_colors();
            reset_ret_textures();
            reset_Jogo();
        }
        else{
            reset_ret_colors();
            reset_ret_textures();
        }
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
            reset_ret_textures();
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
    if(button == 4) distOrigem = distOrigem >= sala_tamy/2 ? sala_tamy/2 : distOrigem+0.5;
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
    for(int k = 0; k < venceu_escreveNome.size(); k++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, venceu_escreveNome[k]);
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

    if(modo == MODO_1_PLAYER) desenhaTempo(tempo, cor_tempo, ortho);
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

    desenhaRetangulo(titulo,ortho_menu);
    desenhaRetangulo(de_1,ortho_menu);
    desenhaRetangulo(de_2,ortho_menu);
    desenhaRetangulo(ranking,ortho_menu);
    desenhaRetangulo(sair,ortho_menu);
    desenhaRetangulo(fundo,ortho_menu);
}

void display_menu_modo(float w, float h, float ortho[]){
    glClearColor (0.4, 0.4, 0.4, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    desenhaRetangulo(start,ortho_menu);
    desenhaRetangulo(voltar,ortho_menu);
    desenhaRetangulo(choose_lv,ortho_menu);
    desenhaRetangulo(fundo,ortho_menu);
}

void display_ranking(float w, float h, float ortho[]){
    glClearColor (0.4, 0.4, 0.4, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    desenhaRetangulo(titRanking,ortho_menu);
    desenhaRetangulo(rnk_lv1,ortho_menu);
    desenhaRetangulo(rnk_lv2,ortho_menu);
    desenhaRetangulo(rnk_lv3,ortho_menu);

    for(int k = 0; k < posicao.size(); k++)
        desenhaRetangulo(posicao[k],ortho_menu);

    desenhaRetangulo(menu,ortho_menu);
    desenhaRetangulo(fundo,ortho_menu);
}

void desenhaBlocks(){
    for(int k = 0; k < num_blocks/2-1; k++){
        glPushMatrix();
            glTranslatef(0,3*sin(pos+k*M_PI/3),0);
            glCallList(id_blocks[k]);
        glPopMatrix();
    }
    for(int k = 0; k < num_blocks/2-1; k++){
        glPushMatrix();
            glTranslatef(0,3*sin(-pos-k*M_PI/3),0);
            glCallList(id_blocks[k+num_blocks/2]);
        glPopMatrix();
    }
}

void desenhaLights(){
    if(luz == LUZ_PONTUAL){
        glEnable(GL_LIGHT0);

        for(int k = 0; k < num_spots; k++)
            glDisable(GL_LIGHT1+k);

        glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);

    }else{
        glDisable(GL_LIGHT0);

        for(int k = 0; k < num_spots; k++){
            glEnable(GL_LIGHT1+k);
            glLightfv(GL_LIGHT1+k, GL_POSITION, spots_posicao[k]);
            glLightfv(GL_LIGHT1+k, GL_SPOT_DIRECTION, spots_dir[k]);
        }
    }
}

void desenhaShadows(){
    float n_chao[] = {0,-1,0};
    float p_chao[] = {0,-(bf_c[1]/2+bf_tamy/2+perna1_c[1]/2+pernas_tamy)-pernas_tamy/2+1,0};
    float n_bf[] = {0,-1,0};
    float p_bf[] = {0,-.49,0};
    float n_lat1[] = {-1,0,0};
    float p_lat1[] = {-bf_tamx/2+0.01,0,0};
    float n_lat2[] = {1,0,0};
    float p_lat2[] = {bf_tamx/2-0.01,0,0};

    glDisable(GL_LIGHTING);

    glColor4fv(luz_shadow);
    for(int k = 0; k < num_blocks/2-1; k++){
        glPushMatrix();
            glShadowProjection(luz0_posicao,p_chao,n_chao);
            glTranslatef(0,3*sin(pos+k*M_PI/3),0);
            glCallList(id_blocks_shadow[k]);
        glPopMatrix();
    }
    for(int k = 0; k < num_blocks/2-1; k++){
        glPushMatrix();
            glShadowProjection(luz0_posicao,p_chao,n_chao);
            glTranslatef(0,3*sin(-pos-k*M_PI/3),0);
            glCallList(id_blocks_shadow[k+num_blocks/2]);
        glPopMatrix();
    }
    if(luz != LUZ_SPOTLIGHT){
        glColor4fv(luz_shadow);
        glPushMatrix();
            glShadowProjection(luz0_posicao,p_bf,n_bf);
            glTranslatef(e.c[0],e.c[1],e.c[2]);
            glCallList(id_esfera);
        glPopMatrix();
        glPushMatrix();
            glShadowProjection(luz0_posicao,p_lat1,n_lat1);
            glTranslatef(e.c[0],e.c[1],e.c[2]);
            glCallList(id_esfera);
        glPopMatrix();
        glPushMatrix();
            glShadowProjection(luz0_posicao,p_lat2,n_lat2);
            glTranslatef(e.c[0],e.c[1],e.c[2]);
            glCallList(id_esfera);
        glPopMatrix();
    }else{
        for(int k = 0; k < num_spots; k++){
            float v_fonte_ponto[] = {e.c[0]-spots_posicao[k][0],e.c[1]-spots_posicao[k][1],e.c[2]-spots_posicao[k][2]};
            float ang = angulo_vetores(v_fonte_ponto, spots_dir[k]);
            if(ang <= spots_cutoff[k]*M_PI/180){
                glColor4f(luz_shadow[0],luz_shadow[1],luz_shadow[2],1-ang/(spots_cutoff[k]*M_PI/180));
                glPushMatrix();
                    glShadowProjection(spots_posicao[k],p_bf,n_bf);
                    glTranslatef(e.c[0],e.c[1],e.c[2]);
                    glCallList(id_esfera);
                glPopMatrix();
                glPushMatrix();
                    glShadowProjection(spots_posicao[k],p_lat1,n_lat1);
                    glTranslatef(e.c[0],e.c[1],e.c[2]);
                    glCallList(id_esfera);
                glPopMatrix();
                glPushMatrix();
                    glShadowProjection(spots_posicao[k],p_lat2,n_lat2);
                    glTranslatef(e.c[0],e.c[1],e.c[2]);
                    glCallList(id_esfera);
                glPopMatrix();
            }
        }
    }
    glEnable(GL_LIGHTING);
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
        glRotatef( rotationX, 1.0, 0.0, 0.0 );

        for(int k = 0; k < 6; k++) glDisable(GL_LIGHT0+k);
        glEnable(GL_LIGHT7);
        glPushMatrix();
            glTranslatef(sala_c[0],sala_c[1],sala_c[2]);
            glCallList(id_sala);
        glPopMatrix();
        glDisable(GL_LIGHT7);

        desenhaLights();

        glPushMatrix();
            glTranslatef(e.c[0],e.c[1],e.c[2]);
            glCallList(id_esfera);
        glPopMatrix();
        glCallList(id_lateral1);
        glCallList(id_lateral2);
        glCallList(id_battle_field);
        glEnable(GL_LIGHT7);
        glCallList(id_perna1);
        glCallList(id_perna2);
        glCallList(id_perna3);
        glCallList(id_perna4);
        glDisable(GL_LIGHT7);
        glPushMatrix();
            glTranslatef(rebatedor1_c[0],rebatedor1_c[1],0);
            glCallList(id_rebatedor1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(rebatedor2_c[0],rebatedor2_c[1],0);
            glCallList(id_rebatedor2);
        glPopMatrix();

        desenhaShadows();

        if(luz == LUZ_SPOTLIGHT){
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);
        }
        desenhaBlocks();
        glCallList(id_poste11);
        glCallList(id_poste12);
        glCallList(id_poste31);
        glCallList(id_poste32);
        if(luz == LUZ_SPOTLIGHT) glDisable(GL_LIGHT0);

    glPopMatrix();

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);
    glEnable(GL_LIGHT7);
    glPushMatrix();
        glTranslatef(0,0.7*sin(pos_placar)+placar1_c[1]/3,0);
        glCallList(id_placarBase);
        glCallList(id_placarScore);
    glPopMatrix();
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT7);
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
            if(pause) desenhaPause(pause_PAUSE, pause_jogo, pause_cam, pause_spot, press_esc, cor_pause, width, height, ortho_placar);
            else if(venceu){
                    if(nivel == NIVEL_1 and eh_menor_Rankeados(tempo,rankeados_1))
                        desenhaVenceu(venceu_VENCEU, venceu_escreveNome, venceu_nome, cor_venceu, width, height, ortho_placar);
                    else if(nivel == NIVEL_2 and eh_menor_Rankeados(tempo,rankeados_2))
                        desenhaVenceu(venceu_VENCEU, venceu_escreveNome, venceu_nome, cor_venceu, width, height, ortho_placar);
                    else if(nivel == NIVEL_3 and eh_menor_Rankeados(tempo,rankeados_3))
                        desenhaVenceu(venceu_VENCEU, venceu_escreveNome, venceu_nome, cor_venceu, width, height, ortho_placar);
                    else
                        desenhaVenceuNoRank(venceu_VENCEU, press_enter, press_esc, cor_venceu, width, height, ortho_placar);
            }
            else if(perdeu) desenhaPerdeu(perdeu_PERDEU, press_enter, press_esc, cor_perdeu, width, height, ortho_placar);
            else if(venceu_2_players_p1) desenhaVenceu2p(venceu2p_VENCEU, press_enter, press_esc, 1, cor_venceu2p, width, height, ortho_placar);
            else if(venceu_2_players_p2) desenhaVenceu2p(venceu2p_VENCEU, press_enter, press_esc, 2, cor_venceu2p, width, height, ortho_placar);
            display_jogo();
        break;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void init_music(){
    SoundEffect = new const char*[NUM_SE];
    MusicSounds = new const char*[NUM_MS];

    for(int k = 0; k < NUM_SE; k++) SoundEffect[k] = new char[64];
    for(int k = 0; k < NUM_MS; k++) MusicSounds[k] = new char[64];

    SoundEffect[0] = "../musica/lat1.wav";    /// Colisao lateral
    SoundEffect[1] = "../musica/pt.wav";      /// Ponto
    SoundEffect[2] = "../musica/reb1.wav";    /// Colisao Lateral
    SoundEffect[3] = "../musica/reb2.wav";    /// Colisao Rebatedor
    MusicSounds[0] = "../musica/msx1.wav";    /// Musica do Menu
    MusicSounds[1] = "../musica/vct.wav";     /// Vitoria
    MusicSounds[2] = "../musica/msx2.wav";    /// Musica do jogo

    for(int k = 0; k < NUM_SE; k++){
        alGenBuffers(NUM_SE, &Buffer_SoundEffect[k]);
        Buffer_SoundEffect[k] = alutCreateBufferFromFile(SoundEffect[k]);
        alGenSources(NUM_SE, &Source_SoundEffect[k]);
        alSourcei  (Source_SoundEffect[k], AL_BUFFER, Buffer_SoundEffect[k]);
        alSourcei  (Source_SoundEffect[k], AL_LOOPING, false     );
        alSourcef  (Source_SoundEffect[k], AL_PITCH,    1.0f     );
        alSourcef  (Source_SoundEffect[k], AL_GAIN,     1.0f     );
        alSourcefv (Source_SoundEffect[k], AL_POSITION, SourcePos);
        alSourcefv (Source_SoundEffect[k], AL_VELOCITY, SourceVel);
    }
    for(int k = 0; k < NUM_MS; k++){
        alGenBuffers(NUM_MS, &Buffer_MusicSounds[k]);
        Buffer_MusicSounds[k] = alutCreateBufferFromFile(MusicSounds[k]);
        alGenSources(NUM_MS, &Source_MusicSounds[k]);
        alSourcei  (Source_MusicSounds[k], AL_BUFFER, Buffer_MusicSounds[k]);
        alSourcei  (Source_MusicSounds[k], AL_LOOPING, k == 1 ? false : true      );
        alSourcef  (Source_MusicSounds[k], AL_PITCH,    1.0f     );
        alSourcef  (Source_MusicSounds[k], AL_GAIN,     1.0f     );
        alSourcefv (Source_MusicSounds[k], AL_POSITION, SourcePos);
        alSourcefv (Source_MusicSounds[k], AL_VELOCITY, SourceVel);
    }

    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);

    play_MusicSound(0);
}

void init (void){

    init_music();

    le_Arquivo_ranking();

    sort(rankeados_1.begin(),rankeados_1.end(),menorRanking);
    sort(rankeados_2.begin(),rankeados_2.end(),menorRanking);
    sort(rankeados_3.begin(),rankeados_3.end(),menorRanking);

    ortho_menu[0] = -1.0*width/height;
    ortho_menu[1] =  1.0*width/height;

    ortho_diff_x = ortho_menu[1]-ortho_menu[0];
    ortho_diff_y = ortho_menu[3]-ortho_menu[2];

    TexBattleField = new glcTexture();
    TexLateral1    = new glcTexture();
    TexLateral2    = new glcTexture();
    TexPernas      = new glcTexture();
    TexBlocks      = new glcTexture();
    TexSala        = new glcTexture();
    TexRebatedor1  = new glcTexture();
    TexRebatedor2  = new glcTexture();
    TexPlacar1     = new glcTexture();
    TexPlacar21    = new glcTexture();
    TexPlacar22    = new glcTexture();
    TexPlacar31    = new glcTexture();
    TexPlacar32    = new glcTexture();

    TexBattleField ->SetNumberOfTextures(sizeof(img_bf)/32);
    TexLateral1    ->SetNumberOfTextures(sizeof(img_lat1)/32);
    TexLateral2    ->SetNumberOfTextures(sizeof(img_lat2)/32);
    TexPernas      ->SetNumberOfTextures(sizeof(img_pernas)/32);
    TexBlocks      ->SetNumberOfTextures(sizeof(img_blocks)/32);
    TexSala        ->SetNumberOfTextures(sizeof(img_sala)/32);
    TexRebatedor1  ->SetNumberOfTextures(sizeof(img_reb1)/32);
    TexRebatedor2  ->SetNumberOfTextures(sizeof(img_reb2)/32);
    TexPlacar1     ->SetNumberOfTextures(sizeof(img_placar1)/32);
    TexPlacar21    ->SetNumberOfTextures(sizeof(img_placar21)/32);
    TexPlacar22    ->SetNumberOfTextures(sizeof(img_placar22)/32);
    TexPlacar31    ->SetNumberOfTextures(sizeof(img_placar31)/32);
    TexPlacar32    ->SetNumberOfTextures(sizeof(img_placar32)/32);

    TexBattleField ->SetColorMode(GL_MODULATE);
    TexLateral1    ->SetColorMode(GL_MODULATE);
    TexLateral2    ->SetColorMode(GL_MODULATE);
    TexPernas      ->SetColorMode(GL_MODULATE);
    TexBlocks      ->SetColorMode(GL_MODULATE);
    TexSala        ->SetColorMode(GL_MODULATE);
    TexRebatedor1  ->SetColorMode(GL_MODULATE);
    TexRebatedor2  ->SetColorMode(GL_MODULATE);
    TexPlacar1     ->SetColorMode(GL_MODULATE);
    TexPlacar21    ->SetColorMode(GL_REPLACE);
    TexPlacar22    ->SetColorMode(GL_REPLACE);
    TexPlacar31    ->SetColorMode(GL_MODULATE);
    TexPlacar32    ->SetColorMode(GL_MODULATE);

    for(int k = 0; k < TexBattleField ->GetNumberOfTextures(); k++) TexBattleField ->CreateTexture(img_bf[k], k);
    for(int k = 0; k < TexLateral1    ->GetNumberOfTextures(); k++) TexLateral1    ->CreateTexture(img_lat1[k], k);
    for(int k = 0; k < TexLateral2    ->GetNumberOfTextures(); k++) TexLateral2    ->CreateTexture(img_lat2[k], k);
    for(int k = 0; k < TexPernas      ->GetNumberOfTextures(); k++) TexPernas      ->CreateTexture(img_pernas[k], k);
    for(int k = 0; k < TexBlocks      ->GetNumberOfTextures(); k++) TexBlocks      ->CreateTexture(img_blocks[k], k);
    for(int k = 0; k < TexSala        ->GetNumberOfTextures(); k++) TexSala        ->CreateTexture(img_sala[k], k);
    for(int k = 0; k < TexRebatedor1  ->GetNumberOfTextures(); k++) TexRebatedor1  ->CreateTexture(img_reb1[k], k);
    for(int k = 0; k < TexRebatedor2  ->GetNumberOfTextures(); k++) TexRebatedor2  ->CreateTexture(img_reb2[k], k);
    for(int k = 0; k < TexPlacar1     ->GetNumberOfTextures(); k++) TexPlacar1     ->CreateTexture(img_placar1[k], k);
    for(int k = 0; k < TexPlacar21    ->GetNumberOfTextures(); k++) TexPlacar21    ->CreateTexture(img_placar21[k], k);
    for(int k = 0; k < TexPlacar22    ->GetNumberOfTextures(); k++) TexPlacar22    ->CreateTexture(img_placar22[k], k);
    for(int k = 0; k < TexPlacar31    ->GetNumberOfTextures(); k++) TexPlacar31    ->CreateTexture(img_placar31[k], k);
    for(int k = 0; k < TexPlacar32    ->GetNumberOfTextures(); k++) TexPlacar32    ->CreateTexture(img_placar32[k], k);

    battle_field.textureManeger = TexBattleField;
    lateral1.textureManeger     = TexLateral1;
    lateral2.textureManeger     = TexLateral2;
    perna1.textureManeger       = TexPernas;
    perna2.textureManeger       = TexPernas;
    perna3.textureManeger       = TexPernas;
    perna4.textureManeger       = TexPernas;
    sala.textureManeger         = TexSala;
    placar1.textureManeger      = TexPlacar1;
    placar21.textureManeger     = TexPlacar21;
    placar22.textureManeger     = TexPlacar22;
    placar31.textureManeger     = TexPlacar31;
    placar32.textureManeger     = TexPlacar32;

    for(int k = 0; k < TexBattleField ->GetNumberOfTextures(); k++) battle_field.face_tex_ids[k] = bf_face_tex_ids[k];
    for(int k = 0; k < TexLateral1    ->GetNumberOfTextures(); k++) lateral1.face_tex_ids[k]     = lateral_face_tex_ids[k];
    for(int k = 0; k < TexLateral2    ->GetNumberOfTextures(); k++) lateral1.face_tex_ids[k]     = lateral_face_tex_ids[k];
    for(int k = 0; k < TexPernas      ->GetNumberOfTextures(); k++) perna1.face_tex_ids[k]       = pernas_face_tex_ids[k];
    for(int k = 0; k < TexPernas      ->GetNumberOfTextures(); k++) perna2.face_tex_ids[k]       = pernas_face_tex_ids[k];
    for(int k = 0; k < TexPernas      ->GetNumberOfTextures(); k++) perna3.face_tex_ids[k]       = pernas_face_tex_ids[k];
    for(int k = 0; k < TexPernas      ->GetNumberOfTextures(); k++) perna4.face_tex_ids[k]       = pernas_face_tex_ids[k];
    for(int k = 0; k < TexSala        ->GetNumberOfTextures(); k++) sala.face_tex_ids[k]         = sala_face_tex_ids[k];
    for(int k = 0; k < TexPlacar1     ->GetNumberOfTextures(); k++) placar1.face_tex_ids[k]      = placar1_face_tex_ids[k];
    for(int k = 0; k < TexPlacar21    ->GetNumberOfTextures(); k++) placar21.face_tex_ids[k]     = placar21_face_tex_ids[k];
    for(int k = 0; k < TexPlacar22    ->GetNumberOfTextures(); k++) placar22.face_tex_ids[k]     = placar22_face_tex_ids[k];
    for(int k = 0; k < TexPlacar31    ->GetNumberOfTextures(); k++) placar31.face_tex_ids[k]     = placar31_face_tex_ids[k];
    for(int k = 0; k < TexPlacar32    ->GetNumberOfTextures(); k++) placar32.face_tex_ids[k]     = placar32_face_tex_ids[k];

    battle_field.texDef = true;
    lateral1.texDef     = true;
    lateral2.texDef     = true;
    sala.texDef         = true;
    perna1.texDef       = true;
    perna2.texDef       = true;
    perna3.texDef       = true;
    perna4.texDef       = true;
    placar1.texDef      = true;
    placar21.texDef     = true;
    placar22.texDef     = true;
    placar31.texDef     = true;
    placar32.texDef     = true;

    id_lateral1     = createBlock(lateral1,10,false);
    id_lateral2     = createBlock(lateral2,10,false);
    id_battle_field = createBlock(battle_field,30,false);
    id_sala         = createBlock(sala,30,true);
    id_esfera       = createSphere(e);
    id_perna1       = createBlock(perna1,10,false);
    id_perna2       = createBlock(perna2,10,false);
    id_perna3       = createBlock(perna3,10,false);
    id_perna4       = createBlock(perna4,10,false);
    id_placarBase   = createPlacar3d(placar1,placar31,placar32,20);
    id_placarScore  = createScore3d(placar21,placar22,20);

    id_poste11 = createPoste(poste11);
    id_poste12 = createPoste(poste12);
    id_poste31 = createPoste(poste31);
    id_poste32 = createPoste(poste32);

    int num_pontos = 20;
    float **pontos;
    pontos = new float*[num_pontos];
    int k = 0;
    for(float theta = 0; theta <= M_PI+M_PI/num_pontos; theta += M_PI/(num_pontos-1)){
        pontos[k] = new float[3];
        pontos[k][0] = 1.0*(theta-M_PI_2);
        pontos[k][1] = 0;
        pontos[k][2] = -1.0*sin(theta);
        k++;
    }

    rebatedor1 = Rebatedor(rebatedor1_c,pontos,num_pontos,rebatedor_espessura,rebatedor1_ambient,rebatedor1_difusa,rebatedor1_especular,rebatedor1_emissao,rebatedor1_brilho,1,0,0,rebatedor1_velocidade);
    rebatedor1.textureManeger   = TexRebatedor1;
    rebatedor1.texDef   = true;

    float **pontos2;
    pontos2 = new float*[num_pontos];
    k = 0;
    for(float theta = M_PI; theta > -M_PI/(num_pontos-1); theta -= M_PI/(num_pontos-1)){
        pontos2[k] = new float[3];
        pontos2[k][0] = 1.0*(theta-M_PI_2);
        pontos2[k][1] = 0;
        pontos2[k][2] = 1.0*sin(theta);
        k++;
    }

    rebatedor2 = Rebatedor(rebatedor2_c,pontos2,num_pontos,rebatedor_espessura,rebatedor2_ambient,rebatedor2_difusa,rebatedor2_especular,rebatedor2_emissao,rebatedor2_brilho,1,0,0,rebatedor2_velocidade);
    rebatedor2.textureManeger   = TexRebatedor2;
    rebatedor2.texDef   = true;

    id_rebatedor1 = createRebatedor(rebatedor1);
    id_rebatedor2 = createRebatedor(rebatedor2);

    for(int k = 0; k < num_blocks; k++){
        blocks_c[k][0] = k < 10 ? 7.25 : -7.25;
        blocks_c[k][1] = pos;
        blocks_c[k][2] = k < 10 ? 2*k-9 : 2*(k-11)-9;

        blocks[k] = Bloco(blocks_c[k],2,2,2,blocks_ambient,blocks_difusa,blocks_especular,blocks_emissao,blocks_brilho,TexBlocks);
        blocks[k].texDef = true;
        for(int w = 0; w < 6; w++) blocks[k].face_tex_ids[w] = blocks_face_tex_ids[w];
        id_blocks[k] = createBlock(blocks[k],10,false);

        blocks[k].texDef = false;
        id_blocks_shadow[k] = createBlock(blocks[k],10,false);
    }

    TexFundo      = new glcTexture();
    TexTitulo     = new glcTexture();
    TexDe_1       = new glcTexture();
    TexDe_2       = new glcTexture();
    TexRanking    = new glcTexture();
    TexSair       = new glcTexture();
    TexChoose_lv  = new glcTexture();
    TexStart      = new glcTexture();
    TexVoltar     = new glcTexture();
    TexTitRanking = new glcTexture();
    TexRnk_lv1    = new glcTexture();
    TexRnk_lv2    = new glcTexture();
    TexRnk_lv3    = new glcTexture();
    TexPosicao    = new glcTexture();
    TexMenu       = new glcTexture();

    TexFundo      ->SetNumberOfTextures(sizeof(img_fundo)/32);
    TexTitulo     ->SetNumberOfTextures(sizeof(img_titulo)/32);
    TexDe_1       ->SetNumberOfTextures(sizeof(img_de_1)/32);
    TexDe_2       ->SetNumberOfTextures(sizeof(img_de_2)/32);
    TexRanking    ->SetNumberOfTextures(sizeof(img_ranking)/32);
    TexSair       ->SetNumberOfTextures(sizeof(img_sair)/32);
    TexChoose_lv  ->SetNumberOfTextures(sizeof(img_choose_lv)/32);
    TexStart      ->SetNumberOfTextures(sizeof(img_start)/32);
    TexVoltar     ->SetNumberOfTextures(sizeof(img_voltar)/32);
    TexTitRanking ->SetNumberOfTextures(sizeof(img_titRanking)/32);
    TexRnk_lv1    ->SetNumberOfTextures(sizeof(img_rnk_lv1)/32);
    TexRnk_lv2    ->SetNumberOfTextures(sizeof(img_rnk_lv2)/32);
    TexRnk_lv3    ->SetNumberOfTextures(sizeof(img_rnk_lv3)/32);
    TexPosicao    ->SetNumberOfTextures(sizeof(img_posicao)/32);
    TexMenu       ->SetNumberOfTextures(sizeof(img_menu)/32);

    for(int k = 0; k < TexFundo     ->GetNumberOfTextures(); k++) TexFundo      ->CreateTexture(img_fundo[k], k);
    for(int k = 0; k < TexTitulo    ->GetNumberOfTextures(); k++) TexTitulo     ->CreateTexture(img_titulo[k], k);
    for(int k = 0; k < TexDe_1      ->GetNumberOfTextures(); k++) TexDe_1       ->CreateTexture(img_de_1[k], k);
    for(int k = 0; k < TexDe_2      ->GetNumberOfTextures(); k++) TexDe_2       ->CreateTexture(img_de_2[k], k);
    for(int k = 0; k < TexRanking   ->GetNumberOfTextures(); k++) TexRanking    ->CreateTexture(img_ranking[k], k);
    for(int k = 0; k < TexSair      ->GetNumberOfTextures(); k++) TexSair       ->CreateTexture(img_sair[k], k);
    for(int k = 0; k < TexChoose_lv ->GetNumberOfTextures(); k++) TexChoose_lv  ->CreateTexture(img_choose_lv[k], k);
    for(int k = 0; k < TexStart     ->GetNumberOfTextures(); k++) TexStart      ->CreateTexture(img_start[k], k);
    for(int k = 0; k < TexVoltar    ->GetNumberOfTextures(); k++) TexVoltar     ->CreateTexture(img_voltar[k], k);
    for(int k = 0; k < TexTitRanking->GetNumberOfTextures(); k++) TexTitRanking ->CreateTexture(img_titRanking[k], k);
    for(int k = 0; k < TexRnk_lv1   ->GetNumberOfTextures(); k++) TexRnk_lv1    ->CreateTexture(img_rnk_lv1[k], k);
    for(int k = 0; k < TexRnk_lv2   ->GetNumberOfTextures(); k++) TexRnk_lv2    ->CreateTexture(img_rnk_lv2[k], k);
    for(int k = 0; k < TexRnk_lv3   ->GetNumberOfTextures(); k++) TexRnk_lv3    ->CreateTexture(img_rnk_lv3[k], k);
    for(int k = 0; k < TexPosicao   ->GetNumberOfTextures(); k++) TexPosicao    ->CreateTexture(img_posicao[k], k);
    for(int k = 0; k < TexMenu      ->GetNumberOfTextures(); k++) TexMenu       ->CreateTexture(img_menu[k], k);

    fundo   = new Retangulo(0.00*ortho_diff_x+ortho_menu[1],0.00*ortho_diff_y+ortho_menu[2],0.00*ortho_diff_x+ortho_menu[0],0.00*ortho_diff_y+ortho_menu[3],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexFundo,"");
    titulo  = new Retangulo(0.15*ortho_diff_x+ortho_menu[0],0.95*ortho_diff_y+ortho_menu[2],0.85*ortho_diff_x+ortho_menu[0],0.60*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexTitulo,"");
    de_1    = new Retangulo(0.25*ortho_diff_x+ortho_menu[0],0.50*ortho_diff_y+ortho_menu[2],0.75*ortho_diff_x+ortho_menu[0],0.40*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexDe_1,"");
    de_2    = new Retangulo(0.25*ortho_diff_x+ortho_menu[0],0.35*ortho_diff_y+ortho_menu[2],0.75*ortho_diff_x+ortho_menu[0],0.25*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexDe_2,"");
    ranking = new Retangulo(0.35*ortho_diff_x+ortho_menu[0],0.20*ortho_diff_y+ortho_menu[2],0.65*ortho_diff_x+ortho_menu[0],0.15*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexRanking,"");
    sair    = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.10*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.06*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexSair,"");

    choose_lv  = new Retangulo(0.40*ortho_diff_x+ortho_menu[0],0.50*ortho_diff_y+ortho_menu[2],0.60*ortho_diff_x+ortho_menu[0],0.40*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexChoose_lv,"");
    start      = new Retangulo(0.25*ortho_diff_x+ortho_menu[0],0.30*ortho_diff_y+ortho_menu[2],0.75*ortho_diff_x+ortho_menu[0],0.15*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexStart,"");
    voltar     = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.10*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.06*ortho_diff_y+ortho_menu[2],ret_cor_normal[0],ret_cor_normal[1],ret_cor_normal[2],TexVoltar,"");

    titRanking = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.95*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.85*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexTitRanking,"");
    rnk_lv1    = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.815*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.765*ortho_diff_y+ortho_menu[2],0.0,1.0,1.0,TexRnk_lv1,"");
    posicao00  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.752*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.702*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao01  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.689*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.639*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao02  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.626*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.576*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao03  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.563*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.513*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao04  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.500*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.450*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao05  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.437*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.387*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao06  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.374*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.324*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao07  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.311*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.261*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao08  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.248*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.198*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao09  = new Retangulo(0.12*ortho_diff_x+ortho_menu[0],0.185*ortho_diff_y+ortho_menu[2],0.35*ortho_diff_x+ortho_menu[0],0.135*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");

    rnk_lv2    = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.815*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.765*ortho_diff_y+ortho_menu[2],0.0,1.0,1.0,TexRnk_lv2,"");
    posicao10  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.752*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.702*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao11  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.689*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.639*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao12  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.626*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.576*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao13  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.563*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.513*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao14  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.500*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.450*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao15  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.437*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.387*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao16  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.374*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.324*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao17  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.311*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.261*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao18  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.248*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.198*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao19  = new Retangulo(0.385*ortho_diff_x+ortho_menu[0],0.185*ortho_diff_y+ortho_menu[2],0.615*ortho_diff_x+ortho_menu[0],0.135*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");

    rnk_lv3    = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.815*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.765*ortho_diff_y+ortho_menu[2],0.0,1.0,1.0,TexRnk_lv3,"");
    posicao20  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.752*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.702*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao21  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.689*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.639*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao22  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.626*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.576*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao23  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.563*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.513*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao24  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.500*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.450*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao25  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.437*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.387*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao26  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.374*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.324*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao27  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.311*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.261*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao28  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.248*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.198*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");
    posicao29  = new Retangulo(0.65*ortho_diff_x+ortho_menu[0],0.185*ortho_diff_y+ortho_menu[2],0.88*ortho_diff_x+ortho_menu[0],0.135*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexPosicao,"");

    menu       = new Retangulo(0.45*ortho_diff_x+ortho_menu[0],0.100*ortho_diff_y+ortho_menu[2],0.55*ortho_diff_x+ortho_menu[0],0.060*ortho_diff_y+ortho_menu[2],0.0,1.0,0.0,TexMenu,"");

    posicao.push_back(posicao00);
    posicao.push_back(posicao01);
    posicao.push_back(posicao02);
    posicao.push_back(posicao03);
    posicao.push_back(posicao04);
    posicao.push_back(posicao05);
    posicao.push_back(posicao06);
    posicao.push_back(posicao07);
    posicao.push_back(posicao08);
    posicao.push_back(posicao09);
    posicao.push_back(posicao10);
    posicao.push_back(posicao11);
    posicao.push_back(posicao12);
    posicao.push_back(posicao13);
    posicao.push_back(posicao14);
    posicao.push_back(posicao15);
    posicao.push_back(posicao16);
    posicao.push_back(posicao17);
    posicao.push_back(posicao18);
    posicao.push_back(posicao19);
    posicao.push_back(posicao20);
    posicao.push_back(posicao21);
    posicao.push_back(posicao22);
    posicao.push_back(posicao23);
    posicao.push_back(posicao24);
    posicao.push_back(posicao25);
    posicao.push_back(posicao26);
    posicao.push_back(posicao27);
    posicao.push_back(posicao28);
    posicao.push_back(posicao29);

    update_Menu_Rank();

    spots_posicao.push_back(spot1_posicao);
    spots_posicao.push_back(spot2_posicao);
    spots_posicao.push_back(spot3_posicao);
    spots_posicao.push_back(spot4_posicao);
    spots_posicao.push_back(spot5_posicao);

    spots_dir.push_back(spot1_dir);
    spots_dir.push_back(spot2_dir);
    spots_dir.push_back(spot3_dir);
    spots_dir.push_back(spot4_dir);
    spots_dir.push_back(spot5_dir);

    spots_cutoff.push_back(spot1_cutoff);
    spots_cutoff.push_back(spot2_cutoff);
    spots_cutoff.push_back(spot3_cutoff);
    spots_cutoff.push_back(spot4_cutoff);
    spots_cutoff.push_back(spot5_cutoff);

    spots_expoente.push_back(spot1_expoente);
    spots_expoente.push_back(spot2_expoente);
    spots_expoente.push_back(spot3_expoente);
    spots_expoente.push_back(spot4_expoente);
    spots_expoente.push_back(spot5_expoente);

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    glEnable(GL_CULL_FACE);                // Habilita Backface-Culling

    glLightfv(GL_LIGHT0, GL_AMBIENT, luz0_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz0_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz0_posicao);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

    glLightfv(GL_LIGHT7, GL_AMBIENT, luz7_ambiente);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, luz7_difusa);
    glLightfv(GL_LIGHT7, GL_SPECULAR, luz7_especular);
    glLightfv(GL_LIGHT7, GL_POSITION, luz7_posicao);

    for(int k = 0; k < num_spots; k++)
        setSpotlight(GL_LIGHT1+k,spots_ambiente,spots_difusa,spots_especular, spots_posicao[k],spots_dir[k],spots_cutoff[k],spots_expoente[k]);
    setSpotlight(GL_LIGHT6,luz6_ambiente,luz6_difusa,luz6_especular,luz6_posicao,luz6_spot_dir,luz6_cutoff,luz6_expoente);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void idle(){
    if(!espera and !pause and tela == TELA_JOGO){
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
            update_Score();
            if(placar_reb1 == 3){
                stop_all_MusicSound();
                play_MusicSound(1);
                if(modo == MODO_1_PLAYER) perdeu = true;
                if(modo == MODO_2_PLAYERS) venceu_2_players_p2 = true;
            }else play_SoundEffect(1);
            reset_vel_pos_dir_esfera();
            espera = true;
            enable_tempo = false;
        }
        else if(e.c[2] <= -bf_tamz/2){
            ponto = true;
            placar_reb2++;
            update_Score();
            if(placar_reb2 == 3){
                stop_all_MusicSound();
                play_MusicSound(1);
                if(modo == MODO_1_PLAYER) venceu = true;
                if(modo == MODO_2_PLAYERS) venceu_2_players_p1 = true;
            }else play_SoundEffect(1);
            espera = true;
            enable_tempo = false;
            reset_vel_pos_dir_esfera();
        }
        if(!colidiu_lat1){
            if(block_collision(e,lateral1)){
                play_SoundEffect(2);
                e.v[0] = - e.v[0];
                colidiu_lat1 = true;
                colidiu_lat2 = false;
                colidiu_reb1 = false;
                colidiu_reb2 = false;
            }
        }
        if(!colidiu_lat2){
            if(block_collision(e,lateral2)){
                play_SoundEffect(2);
                e.v[0] = - e.v[0];
                colidiu_lat1 = false;
                colidiu_lat2 = true;
                colidiu_reb1 = false;
                colidiu_reb2 = false;
            }
        }
        if(!colidiu_reb1){
            if(bumper_collision(e,rebatedor1)){
                play_SoundEffect(3);
                colidiu_lat1 = false;
                colidiu_lat2 = false;
                colidiu_reb1 = true;
                colidiu_reb2 = false;
            }
        }
        if(!colidiu_reb2){
            if(bumper_collision(e,rebatedor2)){
                play_SoundEffect(3);
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
                    blocks_velocidade += fator_aumenta_vel/100;
                }
            break;
            case NIVEL_2:
                if(e.velocidade >= esfera_velocidade_max_2) e.velocidade = esfera_velocidade_max_2;
                else{
                    e.velocidade += fator_aumenta_vel;
                    blocks_velocidade += fator_aumenta_vel/100;
                }
            break;
            case NIVEL_3:
                if(e.velocidade >= esfera_velocidade_max_3) e.velocidade = esfera_velocidade_max_3;
                else{
                    e.velocidade += fator_aumenta_vel;
                    blocks_velocidade += fator_aumenta_vel/100;
                }
            break;
        }
    }

    if(tela == TELA_JOGO){
        pos = pos >= 2*M_PI ? 0 : pos+blocks_velocidade;
        pos_placar = pos_placar >= 2*M_PI ? 0 : pos_placar+0.01;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv){
    srand(time(0));

    cout << endl;
    cout << "Pressione tab para ligar/desligar fullscreen" << endl << endl;

    glutInit(&argc, argv);

    width = glutGet(GLUT_SCREEN_WIDTH);
    height = glutGet(GLUT_SCREEN_HEIGHT);

    alutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (width/1.5, height/1.5);
    glutInitWindowPosition (width/1.5, 0);
    glutCreateWindow ("PONG 3D");
    init ();
    glutMouseFunc( mouse );
    glutKeyboardFunc( keyboard );
    glutKeyboardUpFunc( keyboardUp );
    glutMotionFunc( motion );
    glutPassiveMotionFunc( passiveMotion );
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutIdleFunc( idle );

    timer_func(10);

    //glutFullScreen();

    glutMainLoop();
    for(int k = 0; k < NUM_SE; k++){
        alDeleteBuffers(NUM_SE, &Buffer_SoundEffect[k]);
        alDeleteSources(NUM_SE, &Source_SoundEffect[k]);
    }
    for(int k = 0; k < NUM_MS; k++){
        alDeleteBuffers(NUM_MS, &Buffer_MusicSounds[k]);
        alDeleteSources(NUM_MS, &Source_MusicSounds[k]);
    }
    alutExit();

    return 0;
}
