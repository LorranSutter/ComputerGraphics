#include "Collision.h"

/// Referencia: http://stackoverflow.com/questions/4578967/cube-sphere-intersection-test
bool block_collision(Esfera &e, Bloco &b){
    float dist_squared = e.raio * e.raio;

    /* assume C1 and C2 are element-wise sorted, if not, do that now */
    if      (e.c[0] < b.p1[0]) dist_squared -= pow(e.c[0] - b.p1[0],2);
    else if (e.c[0] > b.p2[0]) dist_squared -= pow(e.c[0] - b.p2[0],2);
    if      (e.c[1] < b.p1[1]) dist_squared -= pow(e.c[1] - b.p1[1],2);
    else if (e.c[1] > b.p2[1]) dist_squared -= pow(e.c[1] - b.p2[1],2);
    if      (e.c[2] < b.p1[2]) dist_squared -= pow(e.c[2] - b.p1[2],2);
    else if (e.c[2] > b.p2[2]) dist_squared -= pow(e.c[2] - b.p2[2],2);
    return dist_squared > 0;
}

bool bumper_collision(Esfera &e, Rebatedor &r){
    if(distancia(e.c,r.getCentro()) > r.raio_maior+e.raio)
		return false;

	float *centro = e.c;
	float raio = e.raio;
	for(int k = 0; k < r.num_pontos-1; k++){
	    float d = distancia_point_line(centro,r.pontos[k],r.pontos[k+1]);
		if(d <= raio){
            if(is_dist_min_pontos_medios(centro,k,r)){
                int num = k+2;
                //cout << "Normal colidida" << endl;
                //cout << num << endl;
                //cout << r.normais[num][0] << " " << r.normais[num][1] << " " << r.normais[num][2] << endl;
                e.v = bumper_collision_aux(r.normais[k+2],e.v);
                return true;
            }
		}
	}
	return false;
}

float *bumper_collision_aux(float *normal, float *v){
    float theta = angulo_vetores(normal,v);
    if(theta <= M_PI_2) theta = M_PI_2+theta;

    theta = M_PI-theta;

    float *normal_rot = rotation_Axis_Vector(normal,theta,0,1,0);
    //cout << "theta  " << theta*180/M_PI << endl;
    //cout << "angulo " << angulo_vetores(normal_rot,v)*180/M_PI << endl;
    return M_PI-angulo_vetores(normal_rot,v) < theta ? rotation_Axis_Vector(normal,-theta,0,1,0) : normal_rot;
}

bool is_dist_min_pontos_medios(float *centro, int id_pMedio, Rebatedor &r){
    float dist = distancia(centro,r.pontos_medios[id_pMedio]);
    for(int k = 0; k < r.num_pontos; k++){
        if(k != id_pMedio and distancia(centro,r.pontos_medios[k]) < dist)
            return false;
    }
    return true;
}

/*
float *bumper_collision(Esfera &e, Rebatedor &r){
	float *n0 = new float[3];
	n0[0] = 0;
	n0[1] = 0;
	n0[2] = 0;
    if(distancia(e.c,r.getCentro()) > r.raio_maior+e.raio)
		return n0;

	float *centro = e.c;
	float raio = e.raio;
	for(int k = 0; k < r.num_pontos-1; k++){
	    float d = distancia_point_line(centro,r.pontos[k],r.pontos[k+1]);
	    //cout << k << " " << d << endl;
		if(d <= raio){
            if(is_dist_min_pontos_medios(centro,k,r)){
                int num = k+2;
                cout << "Normal colidida" << endl;
                cout << num << endl;
                cout << r.normais[num][0] << " " << r.normais[num][1] << " " << r.normais[num][2] << endl;
                return bumper_collision_aux(r.normais[k+2],e.v);
            }
		}
	}
	return n0;
}
*/
