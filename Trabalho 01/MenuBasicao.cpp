#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

float screenWidth = 0;
float screenHeight = 0;
int windowSizeX = 680;
int windowSizeY = 680;
float ortho[6] = {-1.0,1.0,-1.0,1.0,-1.0,1.0};
float ortho_diff_x = ortho[1]-ortho[0];
float ortho_diff_y= ortho[3]-ortho[2];
float objectPosX = windowSizeX/2;
float objectPosY = windowSizeY/2;

float rgbzin1[3] = {0.0, 1.0, 0.0};
float rgbzin2[3] = {0.0, 1.0, 0.0};
float rgbzinr[3] = {0.0, 1.0, 0.0};
float rgbzins[3] = {0.0, 1.0, 0.0};

int moveX = 0;
int moveY = 0;
bool passiveMotion = false;

void menuzin()
{
    //TITULO
	glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(70.0, 650.0, 0.0);
        glVertex3f(610.0, 650.0, 0.0);
        glVertex3f(610.0, 400.0, 0.0);
        glVertex3f(70.0, 400.0, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(615.0, 645.0, 0.0);
        glVertex3f(615.0, 395.0, 0.0);
        glVertex3f(75.0, 395.0, 0.0);
    glEnd();

    //1 JOGADOR
    glBegin(GL_QUADS);
        glColor3f(rgbzin1[0],rgbzin1[1],rgbzin1[2]);
        glVertex3f(150.0, 350.0, 0.0);
        glVertex3f(530.0, 350.0, 0.0);
        glVertex3f(530.0, 250.0, 0.0);
        glVertex3f(150.0, 250.0, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(535.0, 345.0, 0.0);
        glVertex3f(535.0, 245.0, 0.0);
        glVertex3f(155.0, 245.0, 0.0);
    glEnd();

    //2 JOGADORES
    glBegin(GL_QUADS);
        glColor3f(rgbzin2[0],rgbzin2[1],rgbzin2[2]);
        glVertex3f(150.0, 230.0, 0.0);
        glVertex3f(530.0, 230.0, 0.0);
        glVertex3f(530.0, 130.0, 0.0);
        glVertex3f(150.0, 130.0, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(535.0, 225.0, 0.0);
        glVertex3f(535.0, 125.0, 0.0);
        glVertex3f(155.0, 125.0, 0.0);
    glEnd();

    //RANKING
    glBegin(GL_QUADS);
        glColor3f(rgbzinr[0],rgbzinr[1],rgbzinr[2]);
        glVertex3f(200.0, 110.0, 0.0);
        glVertex3f(480.0, 110.0, 0.0);
        glVertex3f(480.0, 80.0, 0.0);
        glVertex3f(200.0, 80.0, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(485.0, 105.0, 0.0);
        glVertex3f(485.0, 75.0, 0.0);
        glVertex3f(205.0, 75.0, 0.0);
    glEnd();

    //SAIR
    glBegin(GL_QUADS);
        glColor3f(rgbzins[0],rgbzins[1],rgbzins[2]);
        glVertex3f(300.0, 60.0, 0.0);
        glVertex3f(380.0, 60.0, 0.0);
        glVertex3f(380.0, 30.0, 0.0);
        glVertex3f(300.0, 30.0, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(385.0, 55.0, 0.0);
        glVertex3f(385.0, 25.0, 0.0);
        glVertex3f(305.0, 25.0, 0.0);
    glEnd();
}

void coloreQuadro(int qual, float r, float g, float b){
    if(qual == 1){
        rgbzin1[0] = r; rgbzin1[1] = g; rgbzin1[2] = b;
        glutPostRedisplay();
        return;
    }
    if(qual == 2){
        rgbzin2[0] = r; rgbzin2[1] = g; rgbzin2[2] = b;
        glutPostRedisplay();
        return;
    }
    if(qual == 3){
        rgbzinr[0] = r; rgbzinr[1] = g; rgbzinr[2] = b;
        glutPostRedisplay();
        return;
    }
    if(qual == 4){
        rgbzins[0] = r; rgbzins[1] = g; rgbzins[2] = b;
        glutPostRedisplay();
        return;
    }
    if(qual == -1){
        rgbzin1[0] = r; rgbzin1[1] = g; rgbzin1[2] = b;
        rgbzin2[0] = r; rgbzin2[1] = g; rgbzin2[2] = b;
        rgbzinr[0] = r; rgbzinr[1] = g; rgbzinr[2] = b;
        rgbzins[0] = r; rgbzins[1] = g; rgbzins[2] = b;
        glutPostRedisplay();
    }
}

// Special Keys callback
void specialKeysPress(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			moveY = 1;
		break;
		case GLUT_KEY_DOWN:
			moveY = -1;
		break;
		case GLUT_KEY_RIGHT:
			moveX = 1;
		break;
		case GLUT_KEY_LEFT:
			moveX = -1;
	break;
		default:
			printf("\nPressionou outra tecla especial não mapeada!");
	break;
	}
	glutPostRedisplay();
}

// Special Keys callback
void specialKeysRelease(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT :
			moveX = 0;
		break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN :
			moveY = 0;
		break;
	}
	glutPostRedisplay();
}

void passivo(int x, int y){
    y = windowSizeY - y;

	objectPosX = x;
	objectPosY = y;

	if(objectPosX > 150 and objectPosX < 530 and objectPosY < 350 and objectPosY > 250){
        coloreQuadro(1, 0.0, 0.0, 1.0);
    }else if(objectPosX > 150 and objectPosX < 530 and objectPosY < 230 and objectPosY > 130){
        coloreQuadro(2, 0.0, 0.0, 1.0);
    }else if(objectPosX > 200 and objectPosX < 480 and objectPosY < 110 and objectPosY > 80){
        coloreQuadro(3, 0.0, 0.0, 1.0);
    }else if(objectPosX > 300 and objectPosX < 380 and objectPosY < 60 and objectPosY > 30){
        coloreQuadro(4, 0.0, 0.0, 1.0);
    }else{
        coloreQuadro(-1, 0.0, 1.0, 0.0);
    }
}

// Motion callback
void motion(int x, int y )
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
	y = windowSizeY - y;

	objectPosX = x;
	objectPosY = y;

	if(objectPosX > 150 and objectPosX < 530 and objectPosY < 350 and objectPosY > 250){
        coloreQuadro(1, 1.0, 0.0, 0.0);
    }else if(objectPosX > 150 and objectPosX < 530 and objectPosY < 230 and objectPosY > 130){
        coloreQuadro(2, 1.0, 0.0, 0.0);
    }else if(objectPosX > 200 and objectPosX < 480 and objectPosY < 110 and objectPosY > 80){
        coloreQuadro(3, 1.0, 0.0, 0.0);
    }else if(objectPosX > 300 and objectPosX < 380 and objectPosY < 60 and objectPosY > 30){
        coloreQuadro(4, 1.0, 0.0, 0.0);
    }else{
        coloreQuadro(-1, 0.0, 1.0, 0.0);
    }
}

void noMotion(int x, int y )
{
	// Cancel passive motion
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
	y = windowSizeY - y;

	if ( button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			objectPosX = x;
			objectPosY = y;

			if(objectPosX > 150 and objectPosX < 530 and objectPosY < 350 and objectPosY > 250){
                coloreQuadro(1, 1.0, 0.0, 0.0);
            }else if(objectPosX > 150 and objectPosX < 530 and objectPosY < 230 and objectPosY > 130){
                coloreQuadro(2, 1.0, 0.0, 0.0);
            }else if(objectPosX > 200 and objectPosX < 480 and objectPosY < 110 and objectPosY > 80){
                coloreQuadro(3, 1.0, 0.0, 0.0);
            }else if(objectPosX > 300 and objectPosX < 380 and objectPosY < 60 and objectPosY > 30){
                coloreQuadro(4, 1.0, 0.0, 0.0);
            }else{
                coloreQuadro(-1, 0.0, 1.0, 0.0);
            }
		}else
			if(objectPosX > 150 and objectPosX < 530 and objectPosY < 350 and objectPosY > 250){
                cout << "Entrou no jogo para um jogador! OMG! T.G.I.F!!!" << endl;
            }else if(objectPosX > 150 and objectPosX < 530 and objectPosY < 230 and objectPosY > 130){
                cout << "Entrou no jogo para dois jogadores! OMG! T.G.I.F!!!" << endl;
            }else if(objectPosX > 200 and objectPosX < 480 and objectPosY < 110 and objectPosY > 80){
                cout << "Entrou no ranking! OMG! T.G.I.F!!!" << endl;
            }else if(objectPosX > 300 and objectPosX < 380 and objectPosY < 60 and objectPosY > 30){
                cout << "Saiu! OMG! T.G.I.F!!!" << endl;
            }// GLUT_UP
	}
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 27:
            exit(0);
        break;
    }
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Clean z-buffer

	// Change object position if some key is pressed
	objectPosX+=moveX;
	objectPosY+=moveY;

	menuzin();

	glutSwapBuffers ();  // Required when double buffer is initialized
	glutPostRedisplay();
}


void init (void)
{
	glClearColor (0.4, 0.4, 0.4, 0.0);

	// inicializar sistema de viz.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, windowSizeX, 0.0, windowSizeY, -500.0, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main Function
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (windowSizeX, windowSizeY);
	glutInitWindowPosition (500, 0);
	glutCreateWindow ("Pong");
	init ();

	// Modifique aqui para '0' para aumentar o delay
	glutIgnoreKeyRepeat(1);
	glutMouseFunc( mouse );

	glutSpecialFunc( specialKeysPress );
	glutSpecialUpFunc( specialKeysRelease );

	glutDisplayFunc(display);

	glutKeyboardFunc( keyboard );

	glutMotionFunc( motion );
	glutPassiveMotionFunc( passivo );

	glutMainLoop();

	return 0;
}
