#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>

#include "Funcoes.h"

using namespace std;

float windowSizeX = 800, windowSizeY = 800;
float ortho_x_min = -0.2, ortho_x_max = 1.2, ortho_y_min = -0.2, ortho_y_max = 1.2, ortho_z_min = -1.0, ortho_z_max = 1.0;

bool movendo = false;
int id_object;
float objectPosX, objectPosY;

int prec = 20;  // Total de pontos intermediários
float pontos[8][3] = {{0.0,0.0,0.0},{0.2,0.3,0.0},{0.3,1.0,0.0},{0.7,1.0,0.0},{1.0,0.0,0.0},{0.5,0.4,0.0},{0.3,0.3,0.0},{0.1,0.1,0.0}}; // Pontos de controle
int num_pontos = 8;
float tol_dist;

vector< float* > lista_pontos;

void init(void){
    glClearColor (0, 0, 0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ortho_x_min, ortho_x_max, ortho_y_min, ortho_y_max, ortho_z_min, ortho_z_max);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void display (void)
{
   float delta =1.0/(float)prec;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f(1,0,0);
   glPointSize(5);
   // Desenha os pontos de controle
   glBegin(GL_POINTS);
       for (int i=0; i<num_pontos; i++)
          glVertex3fv(lista_pontos[i]);
   glEnd();

   glLineWidth(1);
   glBegin(GL_LINE_STRIP);
       for (int i=0; i<num_pontos; i++)
          glVertex3fv(lista_pontos[i]);
   glEnd();

   glColor3f(0.102,0.580,0.192);
   for(int i = 0; i < num_pontos; i++){
        glRasterPos2f(lista_pontos[i][0]+0.01,lista_pontos[i][1]+0.01);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 'P');
        if(i < 10)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , 48+i);
        else{
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

    glColor3f(1,1,0);
    glBegin(GL_LINE_STRIP);
        for(int k = 0; k < num_pontos-3; k++){
            float **pts = cubic_Bspline(lista_pontos[k][0],lista_pontos[k][1],
                                        lista_pontos[k+1][0],lista_pontos[k+1][1],
                                        lista_pontos[k+2][0],lista_pontos[k+2][1],
                                        lista_pontos[k+3][0],lista_pontos[k+3][1],prec);
            for(int p = prec; p >= 0; p--) glVertex3fv(pts[p]);
            }
    glEnd();

   glutSwapBuffers();
}

// Mouse callback
void mouse(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            y = windowSizeY-y;
            float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0};

			printf("\nBotao esquerdo pressionado na posicao [%f, %f].", pos[0], pos[1]);

			int p = maisProximo(lista_pontos,pos[0],pos[1],tol_dist);

			if(p >= 0){
                printf("\nPonto mais proximo: %f [%f, %f].", p, lista_pontos[p][0], lista_pontos[p][1]);
                cout << endl << p << endl;
                id_object = p;
                movendo = true;

                for(int k = 0; k < num_pontos; k++) cout  << k << " " << lista_pontos[k][0] << " " << lista_pontos[k][1] << endl;
            }
            else{
                float *pos = new float[3];
                //float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0};
                pos[0] = x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min;
                pos[1] = y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min;
                pos[2] = 0.0;
                movendo = false;
                cout << endl << "Sem ponto" << endl;

                cout << "Ponto adicionado: [" << pos[0] << "," << pos[1] << "]" << endl;
                num_pontos++;
                lista_pontos.push_back(pos);
                cout << "Num pontos " << num_pontos << endl;

                for(int k = 0; k < num_pontos; k++) cout  << k << " " << lista_pontos[k][0] << " " << lista_pontos[k][1] << endl;
            }
		}

		if(state == GLUT_UP)
            movendo = false;
	}

	else if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN){
            y = windowSizeY-y;
            float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0};

			printf("\nBotao direito pressionado na posicao [%f, %f].", pos[0], pos[1]);

			int p = maisProximo(lista_pontos,pos[0],pos[1],tol_dist);

			if(p >= 0){
                printf("\nPonto mais proximo: %f [%f, %f].", p, lista_pontos[p][0], lista_pontos[p][1]);
                cout << endl << p << endl;
                lista_pontos.erase(lista_pontos.begin()+p);
                num_pontos--;

                for(int k = 0; k < num_pontos; k++) cout << k << " " << lista_pontos[k][0] << " " << lista_pontos[k][1] << endl;
            }
		}
	}

	glutPostRedisplay();
}

// Motion callback
void motion(int x, int y){

    if(movendo){
        y = windowSizeY-y;
        float pos[3] = {x*(ortho_x_max-ortho_x_min)/windowSizeX+ortho_x_min, y*(ortho_y_max-ortho_y_min)/windowSizeY+ortho_y_min,0.0};

        lista_pontos[id_object][0] = pos[0];
        lista_pontos[id_object][1] = pos[1];
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key){
        case 27:
            exit(0);
        break;
    }
}

int main(int argc, char** argv){

    tol_dist = ortho_x_max*0.02;

    //cout << endl << "Something is wrong with adding new control points!" << endl;

    for(int k = 0; k < num_pontos; k++) lista_pontos.push_back(pontos[k]);
    for(int k = 0; k < num_pontos; k++) cout << lista_pontos[k][0] << " " << lista_pontos[k][1] << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (windowSizeX, windowSizeY);
    glutInitWindowPosition (600, 100);
    glutCreateWindow ("Curvas Interativas - Bezier");
    init ();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
