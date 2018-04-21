#include <iostream>
#include <GL/glut.h>
#include <GL/glui.h>
#include <fstream>

#include "Funcoes.h"
#include "Desenho.h"

#define EIXO_X 1
#define EIXO_Y 2
#define EIXO_Z 3
#define MODO_2D 4
#define MODO_3D 5

using namespace std;

float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;

bool  rotacionando = false; // Habilita ou nao a rotacao da cena
int   modo = MODO_2D;       // Modo de visualizacao 2D/3D
float distOrigem = 2;       // Distancia da camera ate a origem

// Dimensionamentos do tamanho da janela e dos limites do ortho
float windowSizeX = 800, windowSizeY = 800;
float ortho[6] = {-1.2,1.2,-1.2,1.2,-1.2,1.2};
float ortho_x_min = ortho[0], ortho_x_max = ortho[1], ortho_y_min = ortho[2], ortho_y_max = ortho[3], ortho_z_min = ortho[4], ortho_z_max = ortho[5];
float cor_grid[4] = {0.2,0.2,0.2,1.0};

// Material da superficie de revolucao
GLfloat surf_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
GLfloat surf_difusa[]    = { 0.0, 0.8, 0.8, 1.0 };
GLfloat surf_especular[] = { 0.0, 0.8, 0.8, 1.0 };
GLfloat surf_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat surf_brilho[]    = { 128.0 };

// Define parametros da luz
GLfloat cor_luz[]		= { 0.5f, 0.5f, 0.5f, 1.0};
GLfloat cor_luz_amb[]	= { 0.02, 0.02, 0.02, 0.02};
GLfloat posicao_luz[]	= { 5.0, 5.0, 5.0, 1.0};

// Variaveis auxiliares
int poligono_controle = 1;  // Habilita exibicao do poligono de controle
int pontos_controle = 1;    // Habilita exibicao dos pontos de controle
int pode_mexer = 1;         // Habilita a movimentacao dos pontos pelo mouse
int pode_add_remov = 1;     // Habilita adicao e remocao de pontos de controle
bool movendo = false;       // Informa se um ponto esta sendo movido pelo mouse
int id_object;              // ID do ponto de controle sendo movido pelo mouse

int angulo = 10;                       // Angulo de precisao da rotacao da curva
int angulo_aux = 10;                   // Variavel auxiliar para o angulo de precisao
int prec = 20;                         // Total de pontos intermediarios (precisao)
int num_pontos = 0;                    // Numero de pontos de controle atuais
float tol_dist = ortho_x_max*0.02;     // Tolerancia de distancia para selecionar um ponto de controle e move-lo

// Vetor de pontos de controle
vector< float* > lista_pontos;

// Variavel que armazenara um ID para a window do glui
int main_window;

GLUI *glui;                   // Ponteiro para a window do glui
GLUI_Spinner *spinner_angulo; // Ponteiro para um spinner

// Definicoes das funcoes utilizadas
void init();
void change_angulo(int control);
void salva_curva(int control);
void carrega_curva(int control);
void change_modo_view(int control);
void clearListPoints(int control);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void reshape(int width, int height);
void display();

/**
 ** Funcao para inicializacoes necessarias do OpenGL e GLUT
 **/
void init(){
    glClearColor (0.3, 0.3, 0.3, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_LIGHT0);                   // habilita luz 0

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ortho_x_min, ortho_x_max, ortho_y_min, ortho_y_max, ortho_z_min, ortho_z_max);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    // Define parametros da luz 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
}

/**
 ** Callback para auxiliar o ajuste do angulo de rotacao da superficie
 **/
void change_angulo(int control){
    if(spinner_angulo->get_int_val() > angulo){
        angulo = angulo_aux;
        while(360%angulo != 0) angulo++;
    }
    else{
        angulo = angulo_aux;
        while(360%angulo != 0) angulo--;
    }
    angulo_aux = angulo;
    spinner_angulo->set_int_val(angulo);
}

/**
 ** Callback para salvar a curva no arquivo
 **/
void salva_curva(int control){
    if(num_pontos != 0) salva_arquivo("saida_curva.txt",lista_pontos);
}

/**
 ** Callback para ler a curva do arquivo
 **/
void carrega_curva(int control){
    le_arquivo("saida_curva.txt",lista_pontos);

    num_pontos = lista_pontos.size();

    glutPostRedisplay();
}

/**
 ** Alterna entre os modos de visualizacao 2D e 3D
 **/
void change_modo_view(int control){
    if(modo == MODO_2D){
        modo = MODO_3D;
        rotacionando = true;
        pode_add_remov = false;
        pode_mexer = 0;
    }else{
        modo = MODO_2D;
        rotacionando = false;
        pode_add_remov = true;
        pode_mexer = 1;
    }

    glutPostRedisplay();
}

/**
 ** Remove todos os pontos de controle atuais
 **/
void clearListPoints(int control){
    lista_pontos.clear(); // Limpa o vetor
    num_pontos = 0;       // Atualiza do numero de pontos de controle atuais

    glutPostRedisplay();
}

/**
 ** Callback keyboard
 **/
void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 'r':
            rotacionando = not rotacionando;
            if(rotacionando){
                pode_mexer = 0;
                movendo = false;
                pode_add_remov = 0;
            }else{
                pode_mexer = 1;
                pode_add_remov = 1;
            }
            break;
        // Saida do programa com esc ou q
        case 27:
        case 'q':
            exit(0);
            break;
    }
}

/**
 ** Callback mouse
 **/
void mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            last_x = x;
            last_y = y;

            y = windowSizeY-y; // Ajuste da orientacao da coordenada y de acordo com o ortho
            float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0}; // Converte a posicao do mouse para coordenadas cartesianas

			int p = maisProximo(lista_pontos,pos[0],pos[1],tol_dist); // Calcula o ponto mais proximo da posicao do mouse

            // Verifica se algum ponto proximo valido foi encontrado
			if(p >= 0){
                movendo = true; // Informa que o ponto sera movimentado
                id_object = p;  // Captura o ID do ponto a ser movimentado
            }
            else{
                // Caso contrario, verifica que a adicao e remocao de pontos esta habilitada
                if(pode_add_remov){
                    movendo = false; // Informa que nao ha pontos a serem movimentados

                    // Calcula as coordenadas do ponto a ser adicionado
                    float *pos = new float[3];
                    pos[0] = x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min;
                    pos[1] = y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min;
                    pos[2] = 0.0;

                    cout << "Ponto adicionado: [" << pos[0] << "," << pos[1] << "]" << endl << endl;

                    num_pontos++;                // Incrementa o numero de pontos de controle
                    lista_pontos.push_back(pos); // Adiciona novo ponto de controle ao fim do vetor
                }
            }
		}

		if(state == GLUT_UP)
            movendo = false; // Informa que nao ha pontos a serem movimentados
	}

	else if(button == GLUT_RIGHT_BUTTON){
        // Verifica se o botao direito do mouse foi pressionado e se a adicao e remocao de pontos esta habilitada
        if(state == GLUT_DOWN and pode_add_remov){
            y = windowSizeY-y; // Ajuste da orientacao da coordenada y de acordo com o ortho
            float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0}; // Converte a posicao do mouse para coordenadas cartesianas

			int p = maisProximo(lista_pontos,pos[0],pos[1],tol_dist); // Calcula o ponto mais proximo da posicao do mouse

            // Verifica se algum ponto proximo valido foi encontrado
			if(p >= 0){
                cout << "Ponto " << p << " removido: [" << lista_pontos[p][0] << "," << lista_pontos[p][1] << "]" << endl << endl;

                num_pontos--;                               // Incrementa o numero de pontos de controle
                lista_pontos.erase(lista_pontos.begin()+p); // Remove ponto de controle
            }
		}
	}
	else if(button == 3) distOrigem = distOrigem <= 0.5 ? 0.5 : distOrigem-0.1;
	else if(button == 4) distOrigem += 0.1;

	glutPostRedisplay();
}

/**
 ** Callback motion
 **/
void motion(int x, int y){
    // Verifica se a movimentacao esta habilitada e se algum ponto esta em condicoes de ser movimentado
    if(movendo and pode_mexer){
        y = windowSizeY-y; // Ajuste da orientacao da coordenada y de acordo com o ortho
        float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0}; // Converte a posicao do mouse para coordenadas cartesianas

        // Atualiza a posicao do ponto atual sendo movido para a posicao atual do mouse
        lista_pontos[id_object][0] = pos[0];
        lista_pontos[id_object][1] = pos[1];
    }
    if(rotacionando){
        rotationX += (float) (y - last_y);
        rotationY += (float) (x - last_x);
    }

    last_x = x;
    last_y = y;

    glutPostRedisplay();
}

/**
 ** Callback reshape
 **/
void reshape(int width, int height){
    windowSizeX = width;
    windowSizeY = height;
    glViewport(0,0,(GLsizei)width,(GLsizei)height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    if(width <= height){
        ortho_y_min = ortho[2]*(float)height/(float)width;
        ortho_y_max = ortho[3]*(float)height/(float)width;
        ortho_z_min = ortho[4]*(float)height/(float)width;
        ortho_z_max = ortho[5]*(float)height/(float)width;
    }
    else{
        ortho_x_min = ortho[0]*(float)width/(float)height;
        ortho_x_max = ortho[1]*(float)width/(float)height;
        ortho_z_min = ortho[4]*(float)width/(float)height;
        ortho_z_max = ortho[5]*(float)width/(float)height;
    }

    glOrtho(ortho_x_min, ortho_x_max, ortho_y_min, ortho_y_max, ortho_z_min, ortho_z_max);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 ** Callback display
 **/
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(modo == MODO_2D) glDisable(GL_LIGHTING);
    else                glEnable(GL_LIGHTING);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if(modo == MODO_2D) glOrtho(ortho_x_min, ortho_x_max, ortho_y_min, ortho_y_max, ortho_z_min, ortho_z_max);
    else                gluPerspective(60.0, (GLfloat) windowSizeX/(GLfloat) windowSizeY, 0.1, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    if(modo == MODO_3D) gluLookAt (distOrigem, distOrigem, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    if(modo == MODO_3D){ // Rotacao da cena
        glRotatef( rotationY, 0.0, 1.0, 0.0 );
        glRotatef( rotationX, 1.0, 0.0, 0.0 );
    }

    if(modo == MODO_2D){
        desenhaB_Spline(lista_pontos,prec,2,1,1,0);

        // Desenha Pontos de controle
        if(pontos_controle) desenhaPontos_Controle(lista_pontos,5,1,0,0);

        // Desenha poligono de controle
        if(poligono_controle) desenhaPoligono_Controle(lista_pontos,1,1,0,0);

        // Desenha identificacao dos pontos
        if(pontos_controle) desenhaLabel_Pontos_Controle(lista_pontos,0.102,0.580,0.192);

        makeGrid(ortho_x_min,ortho_x_max,ortho_y_min,ortho_y_max,EIXO_X,EIXO_Y,50,cor_grid);

    }else{ // Modo 3D
        vector< float* > v;

        v = obterPontos_B_Spline(lista_pontos,prec);

        if(num_pontos >= 4){ // Realiza a costura caso haja ao menos 4 pontos de controle
            vector< float* > v_rot; // Vetor de pontos da curva inicial rotacionada
            setMaterial(surf_ambient,surf_difusa,surf_especular,surf_brilho,surf_emissao);
            for(int theta = angulo; theta <= 360; theta+=angulo){
                v_rot = rotation_Axis_Points(v,angulo*M_PI/180,0,1,0);

                // Realiza costura em dois sentidos para que os dois lados da superficie sejam visiveis
                makeCostura(v,v_rot); // Realiza a costura em um sentido
                makeCostura(v_rot,v); // Realiza a costura no sentido oposto

                v = v_rot;
            }
        }
        makeGrid(ortho_x_min,ortho_x_max,ortho_z_min,ortho_z_max,EIXO_X,EIXO_Z,50,cor_grid);
    }

    glutSwapBuffers();
}

/**
 ** Main
 **/
int main(int argc, char* argv[]){
    // Menu inicial
    cout << "------------------------ Modo 2D ------------------------" << endl;
    cout << "Botao direito do mouse:  adiciona e move pontos" << endl;
    cout << "Botao esquerdo do mouse: remove ponto na posicao do cursor" << endl << endl;
    cout << "------------------------ Modo 3D ------------------------" << endl;
    cout << "Botao direito do mouse:  rotaciona a cena" << endl;
    cout << "Scroll do mouse:  Zoom" << endl << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
    glutInitWindowSize( windowSizeX, windowSizeY );
    glutInitWindowPosition( 600, 100 );

    main_window = glutCreateWindow( "Trabai" );

    init();
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutReshapeFunc( reshape );

    glui = GLUI_Master.create_glui( "Window" ); // Cria subwindow com as especificoes abaixo

    new GLUI_Checkbox(glui,"Mostrar poligono de controle", &poligono_controle);   // Checkbox para habilitar e desabilitar a exibicao do poligono de controle
    new GLUI_Checkbox(glui,"Mostrar pontos de controle", &pontos_controle);       // Checkbox para habilitar e desabilitar a exibicao dos pontos de controle
    new GLUI_Checkbox(glui,"Pode mexer", &pode_mexer);                            // Checkbox para habilitar e desabilitar a movimentacao dos pontos pelo mouse
    new GLUI_Checkbox(glui,"Pode add/remover pontos", &pode_add_remov);           // Checkbox para habilitar e desabilitar adicao e remocao de pontos

    new GLUI_Separator(glui);

    spinner_angulo = new GLUI_Spinner(glui,"Angulo",&angulo_aux,0,change_angulo); // Spinner para alterar o angulo de precisao de rotacao da curva
    spinner_angulo->set_int_limits(1,120);                                        // Define limites de angulo
    spinner_angulo->set_speed(0.5);                                               // Velocidade com que o Spinner varia

    new GLUI_Separator(glui);

    new GLUI_Button(glui, "Revolution / Curva", 0, change_modo_view);    // Botao para alterar entre os modos de vizualizacao 2D e 3D
    new GLUI_Button(glui, "Clear screen", 0, clearListPoints);           // Botao para limpar a tela de todos os pontos de controle

    new GLUI_Separator(glui);

    new GLUI_Button(glui, "Salvar curva", 0, salva_curva);               // Botao para salvar a curva corrente
    new GLUI_Button(glui, "Carregar curva", 0, carrega_curva);           // Botao para carregar a curva do arquivo

    new GLUI_Separator(glui);

    new GLUI_Button(glui, "Quit", 0,(GLUI_Update_CB)exit );              // Botao Quit

    glui->set_main_gfx_window( main_window );

    glutMainLoop();

    return 0;
}
