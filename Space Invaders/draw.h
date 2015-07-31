#ifndef draw

#include <math.h>

extern int xx, zz, angle, index_missil, pontos;
extern int missil[2][50], rochas[2][10], enemys[2][50];
extern bool launch_missil[50], launch_rochas[10], launch_enemys[50];
int angle_rocha=0, index_rocha=0, index_enemy=0;
extern int animate_rochas [10];

using namespace std;

double distancia(int x1, int y1, int x2, int y2){
	return sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) );	
}

void draw_nave(){
	glPushMatrix();

	glTranslatef(xx, 0, zz);
	glScalef(4, 1, 5);
	glColor3f(0.1, 0.2, 1.0);
	glRotatef(180,1,0,0);
	glRotatef(angle, 0,0,1);
	glutSolidCone(2, 3, 10, 10);

	//right
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glColor3f(0.75, 0.8, 0.8);
	glScalef(0.45, 0.6, 0.5);	
	glutSolidCone(2, 3, 10, 10);
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glColor3f(0.75, 0.8, 0.8);
	glScalef(0.45, 0.6, 0.5);
	glutSolidCone(2, 3, 10, 10);
	glPopMatrix();

	//front
	glPushMatrix();
	glTranslatef(0, -1, 1);
	glColor3f(0.1, 0.1, 0.1);
	glScalef(1.5,1.5,1.5);
	glutSolidCube(1);
	glPopMatrix();

	//back
	glPushMatrix();
	glColor3f(0.9, 0.2, 0.3);
	glRotatef(180,1,0,0);
	glScalef(0.35,0.35,0.5);
	glutSolidCone(2, 3, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void scale_rochas(int index){
	animate_rochas[index]-=0.0001;
	if(animate_rochas[index] <= 0.001){
		launch_rochas[index]=false;
		rochas[1][index] = -105;
		animate_rochas[index] = 2;
	}
	glutTimerFunc(10000, scale_rochas, index);
}

void run_missil(int index){
	if(missil[1][index] >= -110){
		//vejo colisoes com rochas
		for(int i=0; i<10; i++){
			if(launch_rochas[i] == true && distancia(missil[0][index], missil[1][index], rochas[0][i], rochas[1][i]) < 7 && launch_missil[index] == true){
				//temos colisao
				//apagar missil

				//cout << "colisao" <<endl;

				launch_missil[index]=false;
				rochas[1][i] = -105;
				launch_rochas[i]=false;

				pontos+=20;

				//scale_rochas(i);
			}
		}
		if(launch_missil[index] == true){
			missil[1][index]-=1;
			glutTimerFunc(100, run_missil, index);
		}

	} else {
		launch_missil[index]=false;
	}
}

void draw_missil(int index){
	glPushMatrix();
	glColor3f(0.2, 1.0, 0.3);
	//desenhar missil
	glTranslatef(missil[0][index], 1, missil[1][index]);
	glScalef(0.7, 1, 1.2);
	glutSolidCylinder(1, 5, 10, 10);
	glPopMatrix();
	//launch missil
	glutTimerFunc(1, run_missil, index);
	glutPostRedisplay();

}

void check_missil(int n){
	for(int i=0; i<n; i++){
		if(launch_missil[i] == true){
			draw_missil(i);
		}
	}
}

void draw_barra(){
	glPushMatrix();
	glTranslatef(0, 0, 100);
	glRotatef(10,1,0,0);
	glScalef(180, 1, 1);
	glColor3f(0.9, 0.9, 0.9);
	glutSolidCube(1);
	glPopMatrix();
}

void run_rocha(int index){
	if(rochas[1][index] <= 110){
		if(launch_rochas[index] == true && distancia(xx, zz, rochas[0][index], rochas[1][index]) <=15 ){
			//colisao com nave
			launch_rochas[index] = false;
			rochas[1][index] = -105;
			pontos -=40;
		}
		if(launch_rochas[index] == true){
			rochas[1][index] += 1;
			angle_rocha++;
			glutTimerFunc(500, run_missil, index);
		}
	} else {
		rochas[1][index] = -105;
		launch_rochas[index] = false;
	}
}

void draw_rocha(int index){
	glPushMatrix();
	glTranslatef(rochas[0][index], 1, rochas[1][index]);
	glColor3f(0.5, 0.5, 0.5);
	glScalef(animate_rochas[index], animate_rochas[index], animate_rochas[index]);
	glRotatef(angle_rocha, 1, 0, 0);
	glutWireSphere(3, 15, 15);
	glPopMatrix();

	glutTimerFunc(1, run_rocha, index);

	glutPostRedisplay();
}

void check_rochas(int n){
	for(int i=0; i<n;i++){
		if(launch_rochas[i] == true){
			draw_rocha(i);
		}
	}
}

void launch_rocha(int x){
	launch_rochas[index_rocha] = true;

	if(index_rocha == 9){
		index_rocha = 0;
	} else {
		index_rocha++;
	}
	glutTimerFunc(1000, launch_rocha, 0);
}

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, const char * string) {  
	glDisable(GL_LIGHTING);
	const char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
	glEnable(GL_LIGHTING);
}

void drawPontos(){
	//escrever pontuacao
	string placeholder = "Pontos: " + to_string (pontos);
	const char * pontuacao = placeholder.c_str();

	glColor3f(1.0, 1.0, 1.0);

	glRasterPos3f(-10.0, 0.0, -90.0);
	writeBitmapString(GLUT_BITMAP_8_BY_13, pontuacao);
}

void run_enemy(int index){
	if(enemys[1][index] <= 110){
		if(launch_enemys[index] == true && distancia(xx, zz, enemys[0][index], enemys[1][index]) <=15 ){
			//colisao com nave
			launch_enemys[index] = false;
			enemys[1][index] = -105;
			pontos -=10;
		}
		if(launch_enemys[index] == true){
			enemys[1][index] += 1;
			glutTimerFunc(500, run_enemy, index);
		}
	} else {
		enemys[1][index] = -105;
		launch_enemys[index] = false;
	}
}

void draw_enemys(int index){
	glPushMatrix();
	glTranslatef(enemys[0][index], 0, enemys[1][index]);
	glColor3f(1.0, 0.2, 0.2);
	glScalef(0.9, 0.9, 0.9);
	glutWireSphere(3, 15, 15);
	glPopMatrix();

	glutTimerFunc(1, run_enemy, index);

	glutPostRedisplay();
}

void check_enemys(int n){
	for(int i=0; i<n;i++){
		if(launch_enemys[i] == true){
			draw_enemys(i);
		}
	}
}

void launch_enemy(int x){
	launch_enemys[index_enemy] = true;

	if(index_enemy == 49){
		index_enemy = 0;
	} else {
		index_enemy++;
	}
	glutTimerFunc(500, launch_enemy, 0);
}

#endif // !draw
