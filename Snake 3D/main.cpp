#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>

#include "luzes.h"
#include "controls.h"
#include "draw.h"
#include "point.h"

using namespace std;

//posicao cabeca snake
int xx=0, zz=0;
//angulo rotacao snake
int angle = 0;
//posicao tesouro
int treasure_x=0, treasure_y=0;
//pontos
int pontos = 0;

//tamanho cobra sem cabeca
int size=0;

//desenhar tesouro?
bool draw_treasure = true;

//direcao cobra
int UP=1, RIGTH=2, DOWN=3, LEFT=4;
int direcao=RIGTH;

//posicao cobra
int posicao_x[32];
int posicao_y[32];
int direcao_corpo[32];

bool pause = false;

void luzes() {
	//global
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//ligth0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

//activar luzes
void init_lights() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_COLOR_MATERIAL);
	luzes();
}

void drawScene() {
	glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //Change the background to sky blue
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity(); 

	// Viewing transformation.
	gluLookAt(0.0, 24.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 

	drawPontos();
	drawPalco();
	drawsnake();
	drawTesouro();

	glutSwapBuffers();
}

void setup(void) {
	init_lights();

	for(int i = 0; i<32; i++){
		posicao_x[i] = -10;
		posicao_y[i] = -10;
		direcao_corpo[i] = -1;
	}
}

// OpenGL window reshape routine
void resize(int w, int h) {
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1, 800);
	glMatrixMode(GL_MODELVIEW);
}

// Main routine
int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3); 
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("snake.cpp");

	glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(SpecialInput);

	glewExperimental = GL_TRUE; 
	glewInit(); 

	setup(); 

	glutTimerFunc(10, colide, 0);
	glutTimerFunc(10, moveSnake, 0);

	glutMainLoop(); 
}

