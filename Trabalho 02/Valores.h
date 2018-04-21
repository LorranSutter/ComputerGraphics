#ifndef VALORES_H_INCLUDED
#define VALORES_H_INCLUDED

int width = 800;
int height = 800;
float ortho_placar[6] = {0,10,0,10,-1,1};
float ortho_menu[6] = {-1,1,-1,1,-1,1};
float ortho_diff_x = 0;
float ortho_diff_y = 0;

float rotationX0 = 0.0, rotationY0 = 0.0;
float rotationX = 0.0, rotationY = 0.0;
float distOrigem = 20;
int   last_x, last_y;

float kc = 0.1f;
float kl = 0.02f;
float kq = 0.00025f;

float blocks_velocidade0 = 0.01;
float blocks_velocidade = 0.01;
float fator_aumenta_vel = 0.005;

int level_num   = 1;
bool venceu = false;
bool enable_tempo = false;
bool pressKeyboard = false;
float pos = 0;
bool ponto = false;
bool pause = false;

bool colidiu_lat1 = false;
bool colidiu_lat2 = false;
bool colidiu_reb1 = false;
bool colidiu_reb2 = false;

int tempo = 0;

int placar_reb1 = 0;
int placar_reb2 = 0;

string level_LEVEL = "LEVEL";
string pause_PAUSE = "PAUSE";
string pause_jogo  = "Voltar ao jogo: space";
string pause_cam   = "Camera topo/perspectiva: m";
string pause_spot  = "Spotlight on/off: s";
string pause_esc   = "Voltar ao menu inicial: ESC";

GLfloat cor_level[3] = {1,1,1};
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
float rebatedor2_velocidade = 0.15;

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
float esfera_velocidade_min_2 = 5;
float esfera_velocidade_min_3 = 7;
float esfera_velocidade_max_1 = 5;
float esfera_velocidade_max_2 = 7;
float esfera_velocidade_max_3 = 9;

/// ---------- Battle Field ---------- ///
GLfloat bf_ambient[]   = { 0.0, 0.1, 0.1, 1.0 };
GLfloat bf_difusa[]    = { 0.0, 0.5, 0.1, 1.0 };
GLfloat bf_especular[] = { 0.0, 0.5, 0.1, 1.0 };
GLfloat bf_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat bf_brilho      =   100.0;
float bf_c[3]         = {0,-1,0};
float bf_tamx = 10;
float bf_tamy = 1;
float bf_tamz = 20;

/// ---------- Laterais ---------- ///
GLfloat lateral_ambient[]   = { 0.0, 0.1, 0.2, 1.0 };
GLfloat lateral_difusa[]    = { 0.0, 0.5, 0.8, 1.0 };
GLfloat lateral_especular[] = { 0.0, 0.5, 0.8, 1.0 };
GLfloat lateral_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lateral_brilho      =   100.0;
float lateral1_c[3]   = {-5.25,0,0};
float lateral2_c[3]   = {5.25,0,0};
float lateral_tamx = 0.5;
float lateral_tamy = 3;
float lateral_tamz = 20;

/// ---------- Blocks ---------- ///
GLfloat blocks_ambient[]   = { 0.2, 0.0, 0.0, 1.0 };
GLfloat blocks_difusa[]    = { 0.0, 0.1, 0.4, 1.0 };
GLfloat blocks_especular[] = { 0.3, 0.0, 0.8, 1.0 };
GLfloat blocks_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat blocks_brilho      =   20.0;

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
float poste11_c[3]      = {-bf_tamx/2-lateral_tamx/2,lateral_tamy-2*bf_tamy,-bf_tamz/2+lateral_tamx/2};
float poste12_c[3]      = {bf_tamx/2+lateral_tamx/2,lateral_tamy-2*bf_tamy,-bf_tamz/2+lateral_tamx/2};
float poste21_c[3]      = {-bf_tamx/2-lateral_tamx/2,lateral_tamy-2*bf_tamy,0.0};
float poste22_c[3]      = {bf_tamx/2+lateral_tamx/2,lateral_tamy-2*bf_tamy,0.0};
float poste31_c[3]      = {-bf_tamx/2-lateral_tamx/2,lateral_tamy-2*bf_tamy,bf_tamz/2-lateral_tamx/2};
float poste32_c[3]      = {bf_tamx/2+lateral_tamx/2,lateral_tamy-2*bf_tamy,bf_tamz/2-lateral_tamx/2};

/// ---------- Luz 0 ---------- ///
GLfloat luz0_posicao[]	 = { 0.0, 30.0, 0.0, 1.0};
GLfloat luz0_ambiente[]	 = { 0.2, 0.2, 0.2, 1.0};
GLfloat luz0_difusa[]	 = { 0.7, 0.7, 0.7, 1.0};
GLfloat luz0_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz0_emissao[]   = { 0.9, 0.9, 0.9, 1.0};
GLfloat luz0_brilho      =   100.0;

/// ---------- Luz 1 ---------- ///
GLfloat luz1_posicao[]	 = { 5.0, 5.0, 0.0, 1.0};
GLfloat luz1_spot_dir[]	 = { 0.0,-1.0, 0.0, 1.0};
GLfloat luz1_ambiente[]	 = { 0.2, 0.2, 0.2, 1.0};
GLfloat luz1_difusa[]	 = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz1_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz1_emissao[]   = { 1.0, 1.0, 1.0, 1.0};
GLfloat luz1_brilho      =   100.0;

/// ---------- Spotlights ---------- ///
GLfloat spots_ambiente[]  = { 0.45, 0.45, 0.45, 1.0};
GLfloat spots_difusa[]	  = { 1.0, 1.0, 1.0, 1.0};
GLfloat spots_especular[] = { 1.0, 1.0, 1.0, 1.0};
GLfloat spots_emissao[]   = { 0.0, 0.0, 0.0, 1.0};
GLfloat spots_brilho      =   100.0;
GLfloat spots_cutoff      =    60.0;
GLfloat spots_expoente    =     8.0;

/// ---------- Spotlight 1 ---------- ///
GLfloat spot1_posicao[]	 = { poste11_c[0], 10, poste11_c[2], poste11_c[3]};
GLfloat spot1_dir[]	     = { 1.0, 0.0, 1.0, 1.0};

/// ---------- Spotlight 2 ---------- ///
GLfloat spot2_posicao[]	 = { poste12_c[0], 10, poste12_c[2], poste12_c[3]};
GLfloat spot2_dir[]	     = { -1.0, 0.0, 1.0, 1.0};

/// ---------- Spotlight 3 ---------- ///
GLfloat spot3_posicao[]	 = { poste21_c[0], 10, poste21_c[2], poste21_c[3]};
GLfloat spot3_dir[]	     = { 1.0, 0.0, 0.0, 1.0};

/// ---------- Spotlight 4 ---------- ///
GLfloat spot4_posicao[]	 = { poste22_c[0], 10, poste22_c[2], poste22_c[3]};
GLfloat spot4_dir[]	     = { -1.0, 0.0, 0.0, 1.0};

/// ---------- Spotlight 5 ---------- ///
GLfloat spot5_posicao[]	 = { poste31_c[0], 10, poste31_c[2], poste31_c[3]};
GLfloat spot5_dir[]	     = { 1.0, 0.0, -1.0, 1.0};

/// ---------- Spotlight 6 ---------- ///
GLfloat spot6_posicao[]	 = { poste32_c[0], 10, poste32_c[2], poste32_c[3]};
GLfloat spot6_dir[]	     = { -1.0, 0.0, -1.0, 1.0};

/// ---------- Spotlight 7 ---------- ///
GLfloat spot7_posicao[]	 = { 0, 50, 0, 1};
GLfloat spot7_dir[]	     = { 0.0, -1.0, 0.0, 1.0};

Rebatedor rebatedor1;
Rebatedor rebatedor2;
Esfera e = Esfera(esfera_c,esfera_raio,esfera_ambient,esfera_difusa,esfera_especular,esfera_emissao,esfera_brilho,esfera_v,esfera_velocidade);
Bloco battle_field = Bloco(bf_c,bf_tamx,bf_tamy,bf_tamz,bf_ambient,bf_difusa,bf_especular,bf_emissao,bf_brilho);
Bloco lateral1 = Bloco(lateral1_c,lateral_tamx,lateral_tamy,lateral_tamz,lateral_ambient,lateral_difusa,lateral_especular,lateral_emissao,lateral_brilho);
Bloco lateral2 = Bloco(lateral2_c,lateral_tamx,lateral_tamy,lateral_tamz,lateral_ambient,lateral_difusa,lateral_especular,lateral_emissao,lateral_brilho);
Poste poste11 = Poste(poste11_c,poste_r,poste_h,  45.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste12 = Poste(poste12_c,poste_r,poste_h, -45.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste21 = Poste(poste21_c,poste_r,poste_h,  90.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste22 = Poste(poste22_c,poste_r,poste_h, -90.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste31 = Poste(poste31_c,poste_r,poste_h, 135.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);
Poste poste32 = Poste(poste32_c,poste_r,poste_h,-135.0,poste_front, poste_back, poste_lenght, poste_ambient,poste_difusa,poste_especular,poste_emissao,poste_brilho);

float blocks_c[22][3];
Bloco blocks[22];

Retangulo *titulo;
Retangulo *de_1;
Retangulo *de_2;
Retangulo *ranking;
Retangulo *sair;
Retangulo *menu_modo;
Retangulo *modo_veloc;
Retangulo *modo_rebat;
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

class Rankeados{
    public:
        string nome;
        int tempo;

        Rankeados(string nome, int tempo) { this->nome = nome; this->tempo = tempo; }
};

vector<Rankeados> rankeados_1;
vector<Rankeados> rankeados_2;
vector<Rankeados> rankeados_3;

#endif // VALORES_H_INCLUDED
