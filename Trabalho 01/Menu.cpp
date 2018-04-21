#include "Menu.h"

void desenhaQuadrado(Quadrado *quad){
    glBegin(GL_QUADS);
        glColor3f(quad->r,quad->g,quad->b);
        glVertex3f(quad->x1, quad->y1, 0.0);
        glVertex3f(quad->x2, quad->y1, 0.0);
        glVertex3f(quad->x2, quad->y2, 0.0);
        glVertex3f(quad->x1, quad->y2, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 1.0, 0.0);

        glVertex3f(quad->x2+ortho_diff_x*0.005, quad->y1-ortho_diff_y*0.01, 0.0);
        glVertex3f(quad->x2+ortho_diff_x*0.005, quad->y2-ortho_diff_y*0.01, 0.0);
        glVertex3f(quad->x1+ortho_diff_x*0.005, quad->y2-ortho_diff_y*0.01, 0.0);
    glEnd();


    glColor3f(0.0,0.0,0.0);
    glRasterPos2f(quad->x2-fabs(quad->x2-quad->x1)/2,quad->y1-fabs(quad->y1-quad->y2)/2);
    for(int i = 0; i < quad->nome.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , quad->nome[i]);
    }
}


void passivo(int x, int y){
    if(sabaozim == 0){
        y = windowSizeY - y;

        objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
        objectPosY = y*ortho_diff_y/screenHeight+ortho[2]*0.5;

        cout << objectPosX << " " << objectPosY << endl;
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
    glutPostRedisplay();
}

// Motion callback
void motion(int x, int y ){
    if(sabaozim == 0){
        y = windowSizeY - y;

        objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
        objectPosY = y*ortho_diff_y/screenHeight+ortho[2]*0.5;

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
    }
    glutPostRedisplay();
}

// Mouse callback
void mouse(int button, int state, int x, int y){
    if(sabaozim == 0){
        if(button == GLUT_LEFT_BUTTON){
            if(state == GLUT_DOWN){
                y = windowSizeY - y;

                objectPosX = x*ortho_diff_x/screenWidth+ortho[0];
                objectPosY = y*ortho_diff_y/screenHeight+ortho[2]*0.5;

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
                if(objectPosX > de_1->x1         and objectPosX < de_1->x2    and objectPosY < de_1->y1    and objectPosY > de_1->y2)
                    cout << "Entrou no jogo para um jogador! OMG! T.G.I.F!!!" << endl;
                else if(objectPosX > de_2->x1    and objectPosX < de_2->x2    and objectPosY < de_2->y1    and objectPosY > de_2->y2)
                    cout << "Entrou no jogo para dois jogadores! OMG! T.G.I.F!!!" << endl;
                else if(objectPosX > ranking->x1 and objectPosX < ranking->x2 and objectPosY < ranking->y1 and objectPosY > ranking->y2)
                    cout << "Entrou no ranking! OMG! T.G.I.F!!!" << endl;
                else if(objectPosX > sair->x1    and objectPosX < sair->x2    and objectPosY < sair->y1    and objectPosY > sair->y2){
                    cout << "Saiu! OMG! T.G.I.F!!!" << endl;
                    exit(0);
                }
            }
        }
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 32:
            sabaozim == 1 ? sabaozim-- : sabaozim++;
            cout << "Trocou" << endl;
            break;
        case 27:
            exit(0);
        break;
    }
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Clean z-buffer

    if(sabaozim == 0){
        // Change object position if some key is pressed
        objectPosX+=moveX;
        objectPosY+=moveY;

        //menuzin();

        desenhaQuadrado(titulo);
        desenhaQuadrado(de_1);
        desenhaQuadrado(de_2);
        desenhaQuadrado(ranking);
        desenhaQuadrado(sair);
    }

	glutSwapBuffers ();  // Required when double buffer is initialized
	glutPostRedisplay();
}

void init (void){
    glClearColor (0.4, 0.4, 0.4, 0.0);

    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    if(sabaozim == 0){
        ortho[0] = -1.0*screenWidth/screenHeight;
        ortho[1] =  1.0*screenWidth/screenHeight;
    //    ortho[2] = -1.0*screenWidth/screenHeight;
    //    ortho[3] =  1.0*screenWidth/screenHeight;

        ortho_diff_x = ortho[1]-ortho[0];
    //    ortho_diff_y = ortho[3]-ortho[2];

        titulo  = new Quadrado(0.15*ortho_diff_x+ortho[0],0.95*ortho_diff_y+ortho[2],0.85*ortho_diff_x+ortho[0],0.60*ortho_diff_y+ortho[2],0.0,1.0,0.0,"");
        de_1    = new Quadrado(0.25*ortho_diff_x+ortho[0],0.50*ortho_diff_y+ortho[2],0.75*ortho_diff_x+ortho[0],0.40*ortho_diff_y+ortho[2],0.0,1.0,0.0,"1 Jogador");
        de_2    = new Quadrado(0.25*ortho_diff_x+ortho[0],0.35*ortho_diff_y+ortho[2],0.75*ortho_diff_x+ortho[0],0.25*ortho_diff_y+ortho[2],0.0,1.0,0.0,"2 Jogadores");
        ranking = new Quadrado(0.35*ortho_diff_x+ortho[0],0.20*ortho_diff_y+ortho[2],0.65*ortho_diff_x+ortho[0],0.15*ortho_diff_y+ortho[2],0.0,1.0,0.0,"Ranking");
        sair    = new Quadrado(0.45*ortho_diff_x+ortho[0],0.10*ortho_diff_y+ortho[2],0.55*ortho_diff_x+ortho[0],0.06*ortho_diff_y+ortho[2],0.0,1.0,0.0,"Sair");

        cout << titulo->x1 << " " << titulo->y1 << " " << titulo->x2 << " " << titulo->y2 << " " << titulo->r << " " << titulo->g << " " << titulo->b << endl;
    }

	// inicializar sistema de viz.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ortho[0],ortho[1],ortho[2],ortho[3],ortho[4],ortho[5]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
