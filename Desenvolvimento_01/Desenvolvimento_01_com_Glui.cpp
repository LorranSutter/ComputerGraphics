#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>

#include "Funcoes.h"

using namespace std;

// Dimensionamentos do tamanho da janela e dos limites do ortho
float windowSizeX = 800, windowSizeY = 800;
float ortho_x_min = 0.0, ortho_x_max = 1.2, ortho_y_min = 0.0, ortho_y_max = 1.2, ortho_z_min = -1.0, ortho_z_max = 1.0;

// Variaveis auxiliares
int poligono_controle = 1;  // Habilita exibicao do poligono de controle
int pontos_controle = 1;    // Habilita exibicao dos pontos de controle
int pode_mexer = 1;         // Habilita a movimentacao dos pontos pelo mouse
int pode_add_remov = 1;     // Habilita adicao e remocao de pontos de controle
bool movendo = false;       // Informa se um ponto esta sendo movido pelo mouse
int id_object;              // ID do ponto de controle sendo movido pelo mouse

int prec = 20;                         // Total de pontos intermediarios (precisao)
int num_pontos = 0;                    // Numero de pontos de controle atuais
float tol_dist = ortho_x_max*0.02;     // Tolerancia de distancia para selecionar um ponto de controle e move-lo

// Vetor de pontos de controle
vector< float* > lista_pontos;

// Variavel que armazenara um ID para a window do glui
int main_window;

// Ponteiro para a window do glui
GLUI *glui;

/**
 ** Funcao para inicializacoes necessarias do OpenGL e GLUT
 **/
void init(void){
    glClearColor (0, 0, 0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ortho_x_min, ortho_x_max, ortho_y_min, ortho_y_max, ortho_z_min, ortho_z_max);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

    glutPostRedisplay();
}

/**
 ** Callback display
 **/
void display (void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Desenha a curva B-Spline
    glColor3f(1,1,0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
        for(int k = 0; k < num_pontos-3; k++){
            // Calcula os pontos da curva a cada 4 pontos de controle
            float **pts = cubic_Bspline(lista_pontos[k][0],lista_pontos[k][1],
                                        lista_pontos[k+1][0],lista_pontos[k+1][1],
                                        lista_pontos[k+2][0],lista_pontos[k+2][1],
                                        lista_pontos[k+3][0],lista_pontos[k+3][1],prec);
            // Os pontos calculados sao desenhados
            for(int p = prec; p >= 0; p--) glVertex3fv(pts[p]);
            }
    glEnd();

    // Desenha os pontos de controle
    if(pontos_controle){
        glColor3f(1,0,0);
        glPointSize(5);
        glBegin(GL_POINTS);
            for (int i=0; i<num_pontos; i++)
                glVertex3fv(lista_pontos[i]);
        glEnd();
    }

    // Desenha poligono de controle
    if(poligono_controle){
        glColor3f(1,0,0);
        glLineWidth(1);
        glBegin(GL_LINE_STRIP);
            for (int i=0; i<num_pontos; i++)
                glVertex3fv(lista_pontos[i]);
        glEnd();
    }

    // Desenha identificacao dos pontos
    if(pontos_controle){
        glColor3f(0.102,0.580,0.192);
        for(int i = 0; i < num_pontos; i++){
            glRasterPos2f(lista_pontos[i][0]+0.01,lista_pontos[i][1]+0.01);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 'P'); // Caracter P
            if(i < 10) // Caso simples em que o indice do ponto eh menor que 10
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+i);
            else{ // Procedimento para numeracao de pontos com indice maior que 10
                int num = i;
                vector<int> num_v;
                while(num >= 10){
                    num_v.insert(num_v.begin(),num%10);
                    num /= 10;
                }
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+num);
                for(int k = 0; k < num_v.size(); k++)
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+num_v[k]);
            }
        }
    }

    glutSwapBuffers();

}

/**
 ** Main
 **/
int main(int argc, char* argv[]){
    // Menu inicial
    cout << "Botao direito do mouse:  adiciona e move pontos" << endl;
    cout << "Botao esquerdo do mouse: remove ponto na posicao do cursor" << endl << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize( windowSizeX, windowSizeY );
    glutInitWindowPosition( 600, 100 );

    main_window = glutCreateWindow( "Trabai" );

    init();
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );
    glutMotionFunc( motion );

    glui = GLUI_Master.create_glui( "Window" ); // Cria subwindow com as especificoes abaixo

    new GLUI_Checkbox(glui,"Mostrar poligono de controle", &poligono_controle);   // Checkbox para habilitar e desabilitar a exibicao do poligono de controle
    new GLUI_Checkbox(glui,"Mostrar pontos de controle", &pontos_controle);       // Checkbox para habilitar e desabilitar a exibicao dos pontos de controle
    new GLUI_Checkbox(glui,"Pode mexer", &pode_mexer);                            // Checkbox para habilitar e desabilitar a movimentacao dos pontos pelo mouse
    new GLUI_Checkbox(glui,"Pode add/remover pontos", &pode_add_remov);           // Checkbox para habilitar e desabilitar adicao e remocao de pontos

    new GLUI_StaticText( glui, ""); // Espaco entre as Checkboxes e os botoes

    new GLUI_Button( glui, "Clear screen", 0, clearListPoints); // Botao para limpar a tela de todos os pontos de controle
    new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );    // Botao Quit

    glui->set_main_gfx_window( main_window );

    glutMainLoop();

    return 0;
}
