#ifndef draws
using namespace std;

extern bool draw_treasure;
extern int treasure_x, treasure_y, direcao;
extern int posicao_x[32];
extern int posicao_y[32];
extern int size;

void drawPalco(){
	glPushMatrix();
	glColor3f(0.1, 0.3, 0.2);
	glTranslatef(0, -1, 0);
	glScalef(18, 1.5, 18);

	glNormal3f(0, 1, 0);

	glutSolidCube(1);
	glPopMatrix();
}

void drawTesouro(){
	if(draw_treasure == true){

		int min= -9, max = 9;
		treasure_x = min + (rand() % (int)(max - min + 1));
		treasure_y = min + (rand() % (int)(max - min + 1));
		draw_treasure = false;
	} 

	glPushMatrix();
	glColor3f(1.0, 0.6, 0.3);
	glTranslatef(treasure_x, 0, treasure_y);
	glScalef(0.05, 0.05, 0.05);

	glutSolidSphere(7, 5, 5);
	glPopMatrix();
}

void drawCauda(){

}

void drawsnake(){ 
	glPushMatrix();
	glTranslatef(xx, 0, zz);
	glRotatef(angle, 0, 1, 0);

	glColor3f(1.0, 0.1, 0.1);

	//cabeca
	glPushMatrix();
	glScalef(0.05,0.05,0.05);
	glutSolidSphere(10,20,20);//Draw the head as a sphere a litle bit bigger than the body spheres
	glRotatef(90.0, 0.0, 1.0, 0.0);
	//nariz
	glColor3f(1.0, 0.1, 0.1);
	glTranslatef(0,0.0,8.0);
	glScalef(0.8, 1.0, 1.2);
	glutSolidCone(10,10,20,20);
	//olhos
	glColor3f(1,1,1);
	glTranslatef(-4.0,10.0,0.0);
	glScalef(0.4,0.4,0.4);

	glutSolidSphere(10,20,20);
	glTranslatef(26.0,0.0,0.0);
	glutSolidSphere(10,20,20);
	glPopMatrix();
	glPopMatrix();

	glColor3f(1.0, 0.1, 0.1);

	for(int i=0; i<size; i++){
		glPushMatrix();
		glTranslatef(posicao_x[i], 0, posicao_y[i]);
		glScalef(0.05,0.05,0.05);
		glutSolidSphere(10,20,20);
		glPopMatrix();
	}
	
}

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, const char * string) {  
	const char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawPontos(){
	//escrever pontuacao
	string placeholder = "Pontos: " + to_string (pontos);
	const char * pontuacao = placeholder.c_str();

	glRasterPos3f(-2.0, 0.0, -14.0);
	writeBitmapString(GLUT_BITMAP_8_BY_13, pontuacao);
}

#endif // !draws
