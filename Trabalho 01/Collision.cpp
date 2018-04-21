#include "Collision.h"

void wall_collision(Circulo *circ, float ortho[], int &lado, int &placar_one, int &placar_two, bool &ponto){
    srand(time(0));
    if(circ->x+circ->raio >= ortho[1]){
        circ->vetX = -circ->vetX;
        return;
    }
    if(circ->x-circ->raio <= ortho[0]){
        circ->vetX = -circ->vetX;
        return;
    }
    if(circ->y+circ->raio >= ortho[3]){
        ponto = true;
        placar_two++;
        circ->x = 0;
        circ->y = 0;
        circ->vetX = ((float(rand()) / float(RAND_MAX)) * 2) - 1;
        circ->vetY =  (float(rand()) / float(RAND_MAX)) - 1;
        while(circ->vetX == 0 and circ->vetY == 0){
            circ->vetX = ((float(rand()) / float(RAND_MAX)) * 2) - 1;
            circ->vetY =  (float(rand()) / float(RAND_MAX)) - 1;
        }
        lado = circ->vetY > 0 ? 2 : 1;
        return;
    }
    if(circ->y-circ->raio <= ortho[2]){
        ponto = true;
        placar_one++;
        circ->x = 0;
        circ->y = 0;
        circ->vetX = ((float(rand()) / float(RAND_MAX)) * 2) - 1;
        circ->vetY =  (float(rand()) / float(RAND_MAX)) + 1;
        while(circ->vetX == 0 and circ->vetY == 0){
            circ->vetX = ((float(rand()) / float(RAND_MAX)) * 2) - 1;
            circ->vetY =  (float(rand()) / float(RAND_MAX)) + 1;
        }
        lado = circ->vetY > 0 ? 2 : 1;
        return;
    }
}

void bumper_collision_1(Circulo *circ, Elipse *bumper, float tol, int &lado){
    float d_l = distancia(circ->x,circ->y,bumper->x-bumper->raio_maior,bumper->y);
    float d_r = distancia(circ->x,circ->y,bumper->x+bumper->raio_maior,bumper->y);

    if(d_l < d_r){
        if(d_l <= bumper->raio_maior+bumper->raio_menor){
            float d_old = d_l;
            float d_new;
            for(float theta = M_PI-tol; theta >= M_PI_2; theta -= tol){
                d_new = distancia(circ->x,circ->y,bumper->raio_maior*cos(theta)+bumper->x,bumper->raio_menor*sin(theta)+bumper->y);
                float* p = new float[2];
                if(d_new <= d_old){
                    if(d_new <= fabs(circ->raio+tol)){
                        p[0] = (bumper->raio_maior*cos(theta)+bumper->x)/(bumper->raio_maior*bumper->raio_maior);
                        p[1] = (bumper->raio_menor*sin(theta)+bumper->y)/(bumper->raio_menor*bumper->raio_menor);
                        float angulo = acos(dot(circ->vetX,circ->vetY,p[0],p[1])/(norma(circ->vetX,circ->vetY)*norma(p[0],p[1])));

                        if(circ->vetX <= 0){
                            circ->vetX = cos(angulo)*p[0] + sin(angulo)*p[1];
                            circ->vetY = sin(angulo)*p[0] - cos(angulo)*p[1];
                        }else{
                            circ->vetX = cos(-angulo)*p[0] + sin(-angulo)*p[1];
                            circ->vetY = sin(-angulo)*p[0] - cos(-angulo)*p[1];
                        }

                        lado = 2;

                        return;
                    }
                    d_old = d_new;
                }
                else
                    return;
            }
        }
    }
    if(d_r <= bumper->raio_maior+bumper->raio_menor){
        float d_old = d_r;
        float d_new;
        for(float theta = tol; theta <= M_PI_2; theta += tol){
            d_new = distancia(circ->x,circ->y,bumper->raio_maior*cos(theta)+bumper->x,bumper->raio_menor*sin(theta)+bumper->y);
            float* p = new float[2];
            if(d_new <= d_old){
                if(d_new <= fabs(circ->raio+tol)){
                    p[0] = (bumper->raio_maior*cos(theta)+bumper->x)/(bumper->raio_maior*bumper->raio_maior);
                    p[1] = (bumper->raio_menor*sin(theta)+bumper->y)/(bumper->raio_menor*bumper->raio_menor);
                    float angulo = acos(dot(circ->vetX,circ->vetY,p[0],p[1])/(norma(circ->vetX,circ->vetY)*norma(p[0],p[1])));

                    if(circ->vetX <= 0){
                        circ->vetX = cos(angulo)*p[0] + sin(angulo)*p[1];
                        circ->vetY = sin(angulo)*p[0] - cos(angulo)*p[1];
                    }else{
                        circ->vetX = cos(-angulo)*p[0] + sin(-angulo)*p[1];
                        circ->vetY = sin(-angulo)*p[0] - cos(-angulo)*p[1];
                    }

                    lado = 2;

                    return;
                }
                d_old = d_new;
            }
            else
                return;
        }
    }
}

void bumper_collision_2(Circulo *circ, Elipse *bumper, float tol, int &lado){
    float d_l = distancia(circ->x,circ->y,bumper->x-bumper->raio_maior,bumper->y);
    float d_r = distancia(circ->x,circ->y,bumper->x+bumper->raio_maior,bumper->y);

    if(d_l < d_r){
        if(d_l <= bumper->raio_maior+bumper->raio_menor){
            float d_old = d_l;
            float d_new;
            for(float theta = M_PI+tol; theta <= 3*M_PI_2; theta += tol){
                d_new = distancia(circ->x,circ->y,bumper->raio_maior*cos(theta)+bumper->x,bumper->raio_menor*sin(theta)+bumper->y);
                float* p = new float[2];
                if(d_new <= d_old){
                    if(d_new <= fabs(circ->raio+tol)){
                        p[0] = (bumper->raio_maior*cos(theta)+bumper->x)/(bumper->raio_maior*bumper->raio_maior);
                        p[1] = (bumper->raio_menor*sin(theta)+bumper->y)/(bumper->raio_menor*bumper->raio_menor);
                        float angulo = acos(dot(circ->vetX,circ->vetY,p[0],p[1])/(norma(circ->vetX,circ->vetY)*norma(p[0],p[1])));

                        if(circ->vetX <= 0){
                            circ->vetX = cos(-angulo)*p[0] + sin(-angulo)*p[1];
                            circ->vetY = sin(-angulo)*p[0] - cos(-angulo)*p[1];
                        }else{
                            circ->vetX = cos(angulo)*p[0] + sin(angulo)*p[1];
                            circ->vetY = sin(angulo)*p[0] - cos(angulo)*p[1];
                        }

                        lado = 1;

                        return;
                    }
                    d_old = d_new;
                }
                else
                    return;
            }
        }
    }
    if(d_r <= bumper->raio_maior+bumper->raio_menor){
        float d_old = d_r;
        float d_new;
        for(float theta = -tol; theta >= -M_PI_2; theta -= tol){
            d_new = distancia(circ->x,circ->y,bumper->raio_maior*cos(theta)+bumper->x,bumper->raio_menor*sin(theta)+bumper->y);
            float* p = new float[2];
            if(d_new <= d_old){
                if(d_new <= fabs(circ->raio+tol)){
                    p[0] = (bumper->raio_maior*cos(theta)+bumper->x)/(bumper->raio_maior*bumper->raio_maior);
                    p[1] = (bumper->raio_menor*sin(theta)+bumper->y)/(bumper->raio_menor*bumper->raio_menor);
                    float angulo = acos(dot(circ->vetX,circ->vetY,p[0],p[1])/(norma(circ->vetX,circ->vetY)*norma(p[0],p[1])));

                    if(circ->vetX <= 0){
                        circ->vetX = cos(-angulo)*p[0] + sin(-angulo)*p[1];
                        circ->vetY = sin(-angulo)*p[0] - cos(-angulo)*p[1];
                    }else{
                        circ->vetX = cos(angulo)*p[0] + sin(angulo)*p[1];
                        circ->vetY = sin(angulo)*p[0] - cos(angulo)*p[1];
                    }

                    lado = 1;

                    return;
                }
                d_old = d_new;
            }
            else
                return;
        }
    }
}
