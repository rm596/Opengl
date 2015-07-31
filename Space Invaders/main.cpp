#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "light.h"
#include "draw.h"
#include "controls.h"
#include "getbmp.h"
#include "texture.h"

//nave
int xx = 0, zz = 90;
int pontos=0;
int angle=0;

//variaveis controlo
const int n_rochas = 10, n_missil=50, n_enemys=50;

//missies
int missil[2][n_missil];
bool launch_missil[n_missil];

//rochas
int rochas[2][n_rochas];
bool launch_rochas[n_rochas];
int animate_rochas [n_rochas];

//enimigos
int enemys[2][n_enemys];
bool launch_enemys[n_enemys];

// Array of texture ids.
unsigned int texture[1]; 
extern int index_rocha;

void drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity(); 

	// Viewing transformation.
	gluLookAt(0.0, 8.0, -2.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0); 

	//activar
	glEnable(GL_TEXTURE_2D);

	// Activate texture object.
	glBindTexture(GL_TEXTURE_2D, texture[0]);        

	// Map the texture onto a square polygon.
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-80.0, -5.0, -80.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(80.0, -5.0, -80.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(80.0, -5.0, 80.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-80.0, -5.0, 80.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	draw_nave();

	drawPontos();

	check_missil(n_missil);
	check_rochas(n_rochas);
	check_enemys(n_enemys);

	glutSwapBuffers();
}

void setup(void) {
	init_lights();

	//setup misseis
	for(int i=0; i<n_missil; i++){
		//x
		missil[0][i] = 0;
		//z
		missil[1][i] = 0;
		//false
		launch_missil[i] = false;

		int min= -80, max = 80;
		int cord_x = min + (rand() % (int)(max - min + 1));

		//inimigos
		enemys[0][i] = cord_x;
		enemys[1][i] = -105;
		launch_enemys[i] = false;
	}

	//setup rochas
	for(int i=0; i<n_rochas; i++){
		//xx
		int min= -80, max = 80;
		int cord_x = min + (rand() % (int)(max - min + 1));

		//rochas
		rochas[0][i] = cord_x;
		rochas[1][i] = -105;
		launch_rochas[i]=false;
		animate_rochas[i] = 2;
	}

	// Create texture ids.
	glGenTextures(1, texture); 

	// Load external texture. 
	loadExternalTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

// OpenGL window reshape routine
void resize(int w, int h) {
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

// Main routine
int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3); 
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("space.cpp");

	glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  

	//controlo
	glutSpecialFunc(SpecialInput);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE; 
	glewInit(); 

	//inicializacao misseis rochas luzes
	setup(); 

	//start rochas
	glutTimerFunc(100, launch_rocha, 0);
	glutTimerFunc(500, launch_enemy, 0);

	glutMainLoop(); 
}

