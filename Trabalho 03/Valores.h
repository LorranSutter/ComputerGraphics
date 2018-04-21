#ifndef VALORES_H_INCLUDED
#define VALORES_H_INCLUDED

#define NUM_SE 4
#define NUM_MS 3

const char **SoundEffect;
const char **MusicSounds;

ALuint Buffer_SoundEffect[NUM_SE];
ALuint Buffer_MusicSounds[NUM_MS];
ALuint Source_SoundEffect[NUM_SE];
ALuint Source_MusicSounds[NUM_MS];
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

bool fullscreen = false;
int width = 1200;
int height = 800;
float ortho_placar[6] = {0,10,0,10,-1,1};
float ortho_menu[6] = {-1,1,-1,1,-1,1};
float ortho_diff_x = 0;
float ortho_diff_y = 0;

float rotationX = 0.0, rotationY = 0.0;
float distOrigem = 20;
int   last_x, last_y;

float kc = 0.01f;
float kl = 0.01f;
float kq = 0.00025f;

float blocks_velocidade0 = 0.01;
float blocks_velocidade = 0.01;
float fator_aumenta_vel = 0.005;

int level_num   = 1;
bool venceu_2_players_p1 = false;
bool venceu_2_players_p2 = false;
bool venceu = false;
bool perdeu = false;
bool espera = true;
bool enable_tempo = false;
bool pressKeyboard = false;
float pos = 0;
float pos_placar = 0;
bool ponto = false;
bool pause = false;

bool colidiu_lat1 = false;
bool colidiu_lat2 = false;
bool colidiu_reb1 = false;
bool colidiu_reb2 = false;

int tempo = 0;

int placar_reb1 = 0;
int placar_reb2 = 0;

string venceu2p_VENCEU = "Vencedor: player ";
string perdeu_PERDEU = "PERDEU!";
string press_enter = "Pressione Enter para continuar";
string venceu_VENCEU = "VENCEU!";
string venceu_escreveNome = "Nome do vencedor: ";
string venceu_nome = "";
string level_LEVEL = "LEVEL";
string pause_PAUSE = "PAUSE";
string pause_jogo  = "Voltar ao jogo: space";
string pause_cam   = "Camera topo/perspectiva: m";
string pause_spot  = "Spotlight on/off: s";
string press_esc   = "Voltar ao menu inicial: ESC";

GLfloat cor_level[3] = {1,1,1};
GLfloat cor_venceu[3] = {1,1,1};
GLfloat cor_venceu2p[3] = {1,1,1};
GLfloat cor_perdeu[3] = {1,1,1};
GLfloat cor_pause[3] = {1,1,1};
GLfloat cor_tempo[3] = {1,1,1};
GLfloat cor_placar[3] = {1,1,1};
GLfloat cor_placar_reb1[3] = {1,1,0};
GLfloat cor_placar_reb2[3] = {1,0,1};

/// ---------- Rebatedores ---------- ///
float rebatedor_espessura = 1;

/// ---------- Rebatedor 1 - Jogador ---------- ///
GLfloat rebatedor1_ambient[]   = { 0.0, 0.0, 0.2, 1.0 };
GLfloat rebatedor1_difusa[]    = { 0.5, 0.0, 0.8, 1.0 };
GLfloat rebatedor1_especular[] = { 0.5, 0.0, 0.8, 1.0 };
GLfloat rebatedor1_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat rebatedor1_brilho      =   100.0;
float rebatedor1_c[3] = {0,0, 10};
float rebatedor1_velocidade = 0;

/// ---------- Rebatedor 2 - Computador ---------- ///
GLfloat rebatedor2_ambient[]   = { 0.0, 0.2, 0.0, 1.0 };
GLfloat rebatedor2_difusa[]    = { 0.5, 0.5, 0.0, 1.0 };
GLfloat rebatedor2_especular[] = { 0.5, 0.5, 0.0, 1.0 };
GLfloat rebatedor2_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat rebatedor2_brilho      =   100.0;
float rebatedor2_c[3] = {0,0,-10};
float rebatedor2_velocidade = 0.05;

/// ---------- Bolinha ---------- ///
GLfloat esfera_ambient[]   = { 0.1, 0.0, 0.1, 1.0 };
GLfloat esfera_difusa[]    = { 0.7, 0.0, 0.1, 1.0 };
GLfloat esfera_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat esfera_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat esfera_brilho      =   100.0;
float esfera_c[3]     = {0,rebatedor_espessura/2,0};
float esfera_raio = 0.4;
float esfera_v[3] = {-1,0,-0.5};
float esfera_v01[3] = {1,0,0.5};
float esfera_v02[3] = {1,0,-0.5};
float esfera_v03[3] = {-1,0,0.5};
float esfera_v04[3] = {-1,0,-0.5};
float esfera_velocidade = 2;
float esfera_velocidade_min_1 = 2;
float esfera_velocidade_min_2 = 2.5;
float esfera_velocidade_min_3 = 3.5;
float esfera_velocidade_max_1 = 2.5;
float esfera_velocidade_max_2 = 3.5;
float esfera_velocidade_max_3 = 4.5;
//float esfera_velocidade = 2;
//float esfera_velocidade_min_1 = 2;
//float esfera_velocidade_min_2 = 5;
//float esfera_velocidade_min_3 = 7;
//float esfera_velocidade_max_1 = 5;
//float esfera_velocidade_max_2 = 7;
//float esfera_velocidade_max_3 = 9;

/// ---------- Battle Field ---------- ///
GLfloat bf_ambient[]   = { 0.0, 0.1, 0.1, 1.0 };
GLfloat bf_difusa[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat bf_especular[] = { 0.0, 0.5, 0.1, 1.0 };
GLfloat bf_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat bf_brilho      =   100.0;
float bf_c[3]          = {0,-1,0};
float bf_tamx = 10;
float bf_tamy = 1;
float bf_tamz = 20;
int bf_face_tex_ids[] = {0,1,2,3,4,5};

/// ---------- Laterais ---------- ///
GLfloat lateral_ambient[]   = { 0.0, 0.1, 0.2, 1.0 };
GLfloat lateral_difusa[]    = { 1.0, 0.75, 0.8, 1.0 };
GLfloat lateral_especular[] = { 0.0, 0.5, 0.8, 1.0 };
GLfloat lateral_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lateral_brilho      =   100.0;
float lateral1_c[3]   = {-5.25,0,0};
float lateral2_c[3]   = {5.25,0,0};
float lateral_tamx = 0.5;
float lateral_tamy = 3;
float lateral_tamz = 20;
int lateral_face_tex_ids[6] = {0,1,2,3,4,5};

/// ---------- Placar ---------- ///
GLfloat placar1_ambient[]   = { 0.2, 0.2, 0.2, 1.0 };
GLfloat placar1_difusa[]    = { 0.1, 0.1, 0.1, 1.0 };
GLfloat placar1_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat placar1_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat placar1_brilho      =   100.0;
float placar1_c[3] = {0,4.0*bf_tamy,-bf_tamz/1.5};
float placar1_tamx = {2.5*bf_tamx};
float placar1_tamy = {9.0*bf_tamy};
float placar1_tamz = {0.01*bf_tamz};
int placar1_face_tex_ids[6] = {0,4,4,4,4,4};

GLfloat placar2_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
GLfloat placar2_difusa[]    = { 0.1, 0.1, 0.1, 1.0 };
GLfloat placar2_especular[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat placar2_emissao[]   = { 1.0, 1.0, 1.0, 1.0 };
GLfloat placar2_brilho      =   100.0;
float placar21_c[3] = {-0.35*placar1_tamx+placar1_tamy*0.05,4.0*bf_tamy,-bf_tamz/1.5+placar1_tamz};
float placar22_c[3] = {0.35*placar1_tamx-placar1_tamy*0.05,4.0*bf_tamy,-bf_tamz/1.5+placar1_tamz};
float placar2_tamx = {0.3*placar1_tamx};
float placar2_tamy = {0.9*placar1_tamy};
float placar2_tamz = {placar1_tamz};
int placar21_face_tex_ids[6] = {0,5,4,5,5,5};
int placar22_face_tex_ids[6] = {0,5,4,5,5,5};

float placar31_c[3] = {placar21_c[0]+0.5*placar2_tamx+0.0375*placar1_tamx+0.0375*placar1_tamy,4.0*bf_tamy,-bf_tamz/1.5+placar1_tamz};
float placar32_c[3] = {placar22_c[0]-0.5*placar2_tamx-0.0375*placar1_tamx-0.0375*placar1_tamy,4.0*bf_tamy,-bf_tamz/1.5+placar1_tamz};
float placar3_tamx = {0.075*placar1_tamx};
float placar3_tamy = {0.9*placar1_tamy};
float placar3_tamz = {placar1_tamz};
int placar31_face_tex_ids[6] = {0,5,4,5,5,5};
int placar32_face_tex_ids[6] = {0,5,4,5,5,5};

/// ---------- Pernas ---------- ///
GLfloat pernas_ambient[]   = { 0.0, 0.1, 0.2, 1.0 };
GLfloat pernas_difusa[]    = { 0.0, 0.5, 0.8, 1.0 };
GLfloat pernas_especular[] = { 0.0, 0.5, 0.8, 1.0 };
GLfloat pernas_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat pernas_brilho      =   100.0;
float pernas_tamx = bf_tamx/6;
float pernas_tamy = bf_tamx*1.2;
float pernas_tamz = bf_tamx/6;
float perna1_c[3]   = {bf_c[0]+bf_tamx/3,bf_c[1]-pernas_tamy/2-bf_tamy/2,bf_c[2]+bf_tamz/3};
float perna2_c[3]   = {bf_c[0]+bf_tamx/3,bf_c[1]-pernas_tamy/2-bf_tamy/2,bf_c[2]-bf_tamz/3};
float perna3_c[3]   = {bf_c[0]-bf_tamx/3,bf_c[1]-pernas_tamy/2-bf_tamy/2,bf_c[2]+bf_tamz/3};
float perna4_c[3]   = {bf_c[0]-bf_tamx/3,bf_c[1]-pernas_tamy/2-bf_tamy/2,bf_c[2]-bf_tamz/3};
int pernas_face_tex_ids[6] = {0,1,2,3,4,5};

/// ---------- Blocks ---------- ///
GLfloat blocks_ambient[]   = { 0.2, 0.0, 0.0, 1.0 };
GLfloat blocks_difusa[]    = { 0.0, 0.1, 0.4, 1.0 };
GLfloat blocks_especular[] = { 0.3, 0.0, 0.8, 1.0 };
GLfloat blocks_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat blocks_brilho      =   20.0;

/// ---------- Blockquinhos laterais ---------- ///
const int num_blocks = 22;
float blocks_c[num_blocks][3];
Bloco blocks[num_blocks];
int id_blocks[num_blocks];
int id_blocks_shadow[num_blocks];
int blocks_face_tex_ids[6] = {0,1,2,3,4,5};

/// ---------- Sala ---------- ///
GLfloat sala_ambient[]   = { 0.0, 0.1, 0.1, 1.0 };
GLfloat sala_difusa[]    = { 0.9, 0.9, 0.9, 1.0 };
GLfloat sala_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat sala_emissao[]   = { 0.0, 1.0, 1.0, 1.0 };
GLfloat sala_brilho      =   100.0;
float sala_c[3]   = {bf_c[0],bf_c[1]/2+bf_tamy/2+perna1_c[1]/2+pernas_tamy,bf_c[2]};
float sala_tamx = 3*bf_tamz*1.5;
float sala_tamy = 2*bf_tamz*1.5;
float sala_tamz = 3*bf_tamz*1.5;
int sala_face_tex_ids[6] = {0,1,2,3,4,5};

/// ---------- Retangulo ---------- ///
float ret_cor_normal[3] = {0,0.9,0};
float ret_cor_passivo[3] = {0,0,0.9};
float ret_cor_selecionado[3] = {0.9,0.0,0.0};

/// ---------- Postezins ---------- ///
GLfloat poste_ambient[]   = { 0.2, 0.2, 0.3, 1.0 };
GLfloat poste_difusa[]    = { 0.1, 0.4, 0.4, 1.0 };
GLfloat poste_especular[] = { 0.2, 0.1, 0.1, 1.0 };
GLfloat poste_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat poste_brilho      =   45.0;
float poste_r = bf_tamx/200.0;
float poste_h = bf_tamx/2.0;
float poste_front = bf_tamx/40.0;
float poste_back = 3.0*bf_tamx/200.0;
float poste_lenght = bf_tamx/10.0;

/// ---------- Postezins centros ---------- ///
float poste11_c[3] = {-bf_tamx/2-lateral_tamx/2,lateral_tamy-2*bf_tamy,-bf_tamz/2+lateral_tamx/2};
float poste12_c[3] = {bf_tamx/2+lateral_tamx/2,lateral_tamy-2*bf_tamy,-bf_tamz/2+lateral_tamx/2};
float poste21_c[3] = {-bf_tamx/2-lateral_tamx/2,lateral_tamy-2*bf_tamy,0.0};
float poste22_c[3] = {bf_tamx/2+lateral_tamx/2,lateral_tamy-2*bf_tamy,0.0};
float poste31_c[3] = {-bf_tamx/2-lateral_tamx/2,lateral_tamy-2*bf_tamy,bf_tamz/2-lateral_tamx/2};
float poste32_c[3] = {bf_tamx/2+lateral_tamx/2,lateral_tamy-2*bf_tamy,bf_tamz/2-lateral_tamx/2};

/// ---------- Luz 0 ---------- ///
GLfloat luz0_posicao[]	 = { 0.0, 20.0, 0.0, 1.0};
GLfloat luz0_ambiente[]	 = { 0.2, 0.2, 0.2, 1.0};
GLfloat luz0_difusa[]	 = { 0.7, 0.7, 0.7, 1.0};
GLfloat luz0_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz0_emissao[]   = { 0.9, 0.9, 0.9, 1.0};
GLfloat luz0_brilho      =   100.0;

/// ---------- Luz 6 ---------- ///
GLfloat luz6_posicao[]	 = { 0, 5.0, 0.0, 1.0};
GLfloat luz6_spot_dir[]	 = { -luz6_posicao[0], -luz6_posicao[1], -luz6_posicao[2], 1.0};
GLfloat luz6_ambiente[]	 = { 0.2, 0.2, 0.2, 1.0};
GLfloat luz6_difusa[]	 = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz6_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz6_emissao[]   = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz6_brilho      =   100.0;
GLfloat luz6_cutoff      =   30.0;
GLfloat luz6_expoente    =   50.0;

/*
/// ---------- Luz 7 ---------- ///
GLfloat luz7_posicao[]	 = { -bf_tamx/2, 5.0, 0.0, 1.0};
GLfloat luz7_spot_dir[]	 = { -luz7_posicao[0], -luz7_posicao[1], -luz7_posicao[2], 1.0};
GLfloat luz7_ambiente[]	 = { 0.2, 0.2, 0.2, 1.0};
GLfloat luz7_difusa[]	 = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz7_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz7_emissao[]   = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz7_brilho      =   100.0;
GLfloat luz7_cutoff      =   30.0;
GLfloat luz7_expoente    =   50.0;
*/

/// ---------- Luz 7 ---------- ///
GLfloat luz7_posicao[]	 = { 0.0, 0.0, 0.0, 1.0};
GLfloat luz7_ambiente[]	 = { 0.2, 0.2, 0.2, 1.0};
GLfloat luz7_difusa[]	 = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz7_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz7_emissao[]   = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz7_brilho      =   100.0;

/// ---------- Spotlights ---------- ///
GLfloat spots_ambiente[]  = { 0.45, 0.45, 0.45, 1.0};
GLfloat spots_difusa[]	  = { 1.0, 1.0, 1.0, 1.0};
GLfloat spots_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat spots_emissao[]   = { 0.0, 0.0, 0.0, 1.0};
GLfloat spots_brilho      =   100.0;
GLfloat spots_cutoff_padrao      =    30.0;
GLfloat spots_expoente_padrao    =    50.0;

vector< GLfloat* > spots_posicao;
vector< GLfloat* > spots_dir;
vector< GLfloat  > spots_cutoff;
vector< GLfloat  > spots_expoente;

int num_spots = 5;

/// ---------- Spotlight 1 ---------- ///
GLfloat spot1_posicao[]	 = { poste11_c[0], poste11_c[1]+5, poste11_c[2], 1.0};
GLfloat spot1_dir[]	     = { -poste11_c[0], -poste11_c[1]-10, -poste11_c[2], 1.0};
//GLfloat spot1_dir[]	     = { poste32_c[0]-poste11_c[0], -poste11_c[1], poste32_c[2]-poste11_c[2], 1.0};
GLfloat spot1_cutoff = spots_cutoff_padrao;
GLfloat spot1_expoente = spots_expoente_padrao;

/// ---------- Spotlight 2 ---------- ///
GLfloat spot2_posicao[]	 = { poste12_c[0], poste12_c[1]+5, poste12_c[2], 1.0};
GLfloat spot2_dir[]	     = { -poste12_c[0], -poste12_c[1]-10, -poste12_c[2], 1.0};
//GLfloat spot2_dir[]	     = { poste31_c[0]-poste12_c[0], -poste12_c[1], poste31_c[2]-poste12_c[2], 1.0};
GLfloat spot2_cutoff = spots_cutoff_padrao;
GLfloat spot2_expoente = spots_expoente_padrao;

/// ---------- Spotlight 3 ---------- ///
GLfloat spot3_posicao[]	 = { poste31_c[0], poste31_c[1]+5, poste31_c[2], 1.0};
GLfloat spot3_dir[]	     = { -poste31_c[0], -poste31_c[1]-10, -poste31_c[2], 1.0};
//GLfloat spot3_dir[]	     = { poste12_c[0]-poste31_c[0], -poste31_c[1], poste12_c[2]-poste31_c[2], 1.0};
GLfloat spot3_cutoff = spots_cutoff_padrao;
GLfloat spot3_expoente = spots_expoente_padrao;

/// ---------- Spotlight 4 ---------- ///
GLfloat spot4_posicao[]	 = { poste32_c[0], poste32_c[1]+5, poste32_c[2], 1.0};
GLfloat spot4_dir[]	     = { -poste32_c[0], -poste32_c[1]-10, -poste32_c[2], 1.0};
//GLfloat spot6_dir[]	     = { poste11_c[0]-poste32_c[0], -poste32_c[1], poste12_c[2]-poste32_c[2], 1.0};
GLfloat spot4_cutoff = spots_cutoff_padrao;
GLfloat spot4_expoente = spots_expoente_padrao;

/// ---------- Spotlight 5 ---------- ///
GLfloat spot5_posicao[]	 = { 0, 50, 0, 1};
GLfloat spot5_dir[]	     = { 0.0, -1.0, 0.0, 1.0};
GLfloat spot5_cutoff = 90;
GLfloat spot5_expoente = 50;

GLfloat luz_shadow[] = {0.0,0.0,0.0,1.0};

Rebatedor rebatedor1;
Rebatedor rebatedor2;
Esfera e = Esfera(esfera_c,esfera_raio,esfera_ambient,esfera_difusa,esfera_especular,esfera_emissao,esfera_brilho,esfera_v,esfera_velocidade);
Bloco battle_field = Bloco(bf_c,bf_tamx,bf_tamy,bf_tamz,bf_ambient,bf_difusa,bf_especular,bf_emissao,bf_brilho);
Bloco lateral1 = Bloco(lateral1_c,lateral_tamx,lateral_tamy,lateral_tamz,lateral_ambient,lateral_difusa,lateral_especular,lateral_emissao,lateral_brilho);
Bloco lateral2 = Bloco(lateral2_c,lateral_tamx,lateral_tamy,lateral_tamz,lateral_ambient,lateral_difusa,lateral_especular,lateral_emissao,lateral_brilho);
Bloco perna1 = Bloco(perna1_c,pernas_tamx,pernas_tamy,pernas_tamz,pernas_ambient,pernas_difusa,pernas_especular,pernas_emissao,pernas_brilho);
Bloco perna2 = Bloco(perna2_c,pernas_tamx,pernas_tamy,pernas_tamz,pernas_ambient,pernas_difusa,pernas_especular,pernas_emissao,pernas_brilho);
Bloco perna3 = Bloco(perna3_c,pernas_tamx,pernas_tamy,pernas_tamz,pernas_ambient,pernas_difusa,pernas_especular,pernas_emissao,pernas_brilho);
Bloco perna4 = Bloco(perna4_c,pernas_tamx,pernas_tamy,pernas_tamz,pernas_ambient,pernas_difusa,pernas_especular,pernas_emissao,pernas_brilho);
Bloco sala = Bloco(sala_c,sala_tamx,sala_tamy,sala_tamz,sala_ambient,sala_difusa,sala_especular,sala_emissao,sala_brilho);
Bloco placar1 = Bloco(placar1_c,placar1_tamx,placar1_tamy,placar1_tamz,placar1_ambient,placar1_difusa,placar1_especular,placar1_emissao,placar1_brilho);
Bloco placar21 = Bloco(placar21_c,placar2_tamx,placar2_tamy,placar2_tamz,placar2_ambient,placar2_difusa,placar2_especular,placar2_emissao,placar2_brilho);
Bloco placar22 = Bloco(placar22_c,placar2_tamx,placar2_tamy,placar2_tamz,placar2_ambient,placar2_difusa,placar2_especular,placar2_emissao,placar2_brilho);
Bloco placar31 = Bloco(placar31_c,placar3_tamx,placar3_tamy,placar3_tamz,rebatedor1_ambient,rebatedor1_difusa,rebatedor1_especular,rebatedor1_emissao,rebatedor1_brilho);
Bloco placar32 = Bloco(placar32_c,placar3_tamx,placar3_tamy,placar3_tamz,rebatedor2_ambient,rebatedor2_difusa,rebatedor2_especular,rebatedor2_emissao,rebatedor2_brilho);
Poste poste11 = Poste(poste11_c,poste_r,poste_h,  45.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste12 = Poste(poste12_c,poste_r,poste_h, -45.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
//Poste poste21 = Poste(poste21_c,poste_r,poste_h,  90.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
//Poste poste22 = Poste(poste22_c,poste_r,poste_h, -90.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste31 = Poste(poste31_c,poste_r,poste_h, 135.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste32 = Poste(poste32_c,poste_r,poste_h,-135.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);

Retangulo *fundo;
Retangulo *titulo;
Retangulo *de_1;
Retangulo *de_2;
Retangulo *ranking;
Retangulo *sair;
Retangulo *choose_lv;
Retangulo *start;
Retangulo *voltar;

Retangulo *titRanking;
Retangulo *rnk_lv1;
Retangulo *rnk_lv2;
Retangulo *rnk_lv3;
Retangulo *posicao00;
Retangulo *posicao01;
Retangulo *posicao02;
Retangulo *posicao03;
Retangulo *posicao04;
Retangulo *posicao05;
Retangulo *posicao06;
Retangulo *posicao07;
Retangulo *posicao08;
Retangulo *posicao09;
Retangulo *posicao10;
Retangulo *posicao11;
Retangulo *posicao12;
Retangulo *posicao13;
Retangulo *posicao14;
Retangulo *posicao15;
Retangulo *posicao16;
Retangulo *posicao17;
Retangulo *posicao18;
Retangulo *posicao19;
Retangulo *posicao20;
Retangulo *posicao21;
Retangulo *posicao22;
Retangulo *posicao23;
Retangulo *posicao24;
Retangulo *posicao25;
Retangulo *posicao26;
Retangulo *posicao27;
Retangulo *posicao28;
Retangulo *posicao29;
Retangulo *menu;

vector< Retangulo* > posicao;

string img_fundo[]      = {"../data/Fundo.png","../data/granite.png","../data/imagem1.png"};
string img_titulo[]     = {"../data/PongLogo.png","../data/granite.png","../data/imagem1.png"};
string img_de_1[]       = {"../data/1Jogador.png","../data/1JogadorON.png","../data/imagem1.png"};
string img_de_2[]       = {"../data/2Jogadores.png","../data/2JogadoresON.png","../data/imagem1.png"};
string img_ranking[]    = {"../data/Ranking.png","../data/RankingON.png","../data/imagem1.png"};
string img_sair[]       = {"../data/Sair.png","../data/SairON.png","../data/imagem1.png"};
string img_choose_lv[]  = {"../data/Nivel01.png","../data/Nivel02.png","../data/Nivel03.png","../data/Nivel01ON.png","../data/Nivel02ON.png","../data/Nivel03ON.png"};
string img_start[]      = {"../data/Start.png","../data/StartON.png","../data/imagem1.png"};
string img_voltar[]     = {"../data/VoltarOFF.png","../data/VoltarON.png","../data/imagem1.png"};
string img_titRanking[] = {"../data/RankingTop.png","../data/granite.png","../data/imagem1.png"};
string img_rnk_lv1[]    = {"../data/Nivel1.png","../data/granite.png","../data/imagem1.png"};
string img_rnk_lv2[]    = {"../data/Nivel2.png","../data/granite.png","../data/imagem1.png"};
string img_rnk_lv3[]    = {"../data/Nivel3.png","../data/granite.png","../data/imagem1.png"};
string img_posicao[]    = {"../data/Records.png","../data/granite.png","../data/imagem1.png"};
string img_menu[]       = {"../data/VoltarOFF.png","../data/VoltarON.png","../data/imagem1.png"};

string img_bf[]         = {"../data/Chao.png","../data/Chao.png","../data/Chao.png","../data/Chao.png","../data/Chao.png","../data/Chao.png"};
string img_lat1[]       = {"../data/paper.png","../data/paper.png","../data/paper.png","../data/paper.png","../data/paper.png","../data/paper.png"};
string img_lat2[]       = {"../data/paper.png","../data/paper.png","../data/paper.png","../data/paper.png","../data/paper.png","../data/paper.png"};
string img_pernas[]     = {"../data/circuitos0.png","../data/circuitos1.png","../data/circuitos0.png","../data/circuitos3.png","../data/circuitos0.png","../data/circuitos5.png"};
string img_blocks[]     = {"../data/Blocos02.png","../data/Blocos02.png","../data/Blocos02.png","../data/Blocos02.png","../data/Blocos02.png","../data/Blocos02.png"};

string img_reb1[]       = {"../data/Roxo01.png","../data/Roxo02.png","../data/Roxo02.png"};
string img_reb2[]       = {"../data/Amarelo01.png","../data/Amarelo02.png","../data/Amarelo02.png"};

string img_sala[]       = {"../data/Lateral_sala05.png","../data/Lateral_sala05.png","../data/Lateral_sala05.png","../data/Lateral_sala05.png","../data/Floor03.png","../data/Lateral_sala05.png"};

string img_placar1[]    = {"../data/Cinza01.png","../data/Cinza02.png","../data/Cinza03.png","../data/Branco01.png","../data/Branco01.png","../data/Branco01.png"};
string img_placar21[]   = {"../data/Placar0cinza.png","../data/Placar1cinza.png","../data/Placar2cinza.png","../data/Placar3cinza.png","../data/Branco01.png","../data/Cinza04.png"};
string img_placar22[]   = {"../data/Placar0cinza.png","../data/Placar1cinza.png","../data/Placar2cinza.png","../data/Placar3cinza.png","../data/Branco01.png","../data/Cinza04.png"};
string img_placar31[]   = {"../data/Roxo04.png","../data/Roxo01.png","../data/Roxo01.png","../data/Roxo01.png","../data/Branco01.png","../data/Cinza04.png"};
string img_placar32[]   = {"../data/Amarelo03.png","../data/Amarelo01.png","../data/Amarelo01.png","../data/Amarelo01.png","../data/Branco01.png","../data/Cinza04.png"};

glcTexture *TexFundo;
glcTexture *TexTitulo;
glcTexture *TexDe_1;
glcTexture *TexDe_2;
glcTexture *TexRanking;
glcTexture *TexSair;
glcTexture *TexChoose_lv;
glcTexture *TexStart;
glcTexture *TexVoltar;
glcTexture *TexTitRanking;
glcTexture *TexRnk_lv1;
glcTexture *TexRnk_lv2;
glcTexture *TexRnk_lv3;
glcTexture *TexPosicao;
glcTexture *TexMenu;

glcTexture *TexBattleField;
glcTexture *TexLateral1;
glcTexture *TexLateral2;
glcTexture *TexPernas;
glcTexture *TexBlocks;
glcTexture *TexSala;

glcTexture *TexRebatedor1;
glcTexture *TexRebatedor2;

glcTexture *TexPlacar1;
glcTexture *TexPlacar21;
glcTexture *TexPlacar22;
glcTexture *TexPlacar31;
glcTexture *TexPlacar32;

class Rankeados{
    public:
        string nome;
        int tempo;

        Rankeados(string nome, int tempo) { this->nome = nome; this->tempo = tempo; }
};

vector<Rankeados> rankeados_1;
vector<Rankeados> rankeados_2;
vector<Rankeados> rankeados_3;

int id_lateral1;
int id_lateral2;
int id_battle_field;
int id_esfera;
int id_perna1;
int id_perna2;
int id_perna3;
int id_perna4;
int id_sala;
int id_rebatedor1;
int id_rebatedor2;
int id_poste11;
int id_poste12;
int id_poste21;
int id_poste22;
int id_poste31;
int id_poste32;
int id_placarBase;
int id_placarScore;

#endif // VALORES_H_INCLUDED
