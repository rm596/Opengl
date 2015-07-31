#include <string>
#include <windows.h>
#include <sstream> 

#include <GL\freeglut.h>  //texto
#include <GL/glut.h>

#include "extra.h"
#include "variables.h"
#include "controls.h"

//Called when the window is resized
void enable2D(int w, int h) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//Draws the 3D scene
void draw() {
	// clear (has to be done at the beginning)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// draw rackets
	drawRect(racket_left_x, racket_left_y, racket_width, racket_height);
	drawRect(racket_right_x, racket_right_y, racket_width, racket_height);

	// draw score
	drawText(width / 2 - 10, height - 15, int2str(score_left) + ":" + int2str(score_right)); 

	// draw ball
	drawRect(ball_pos_x - ball_size / 2, ball_pos_y - ball_size / 2, ball_size, ball_size);

	// swap buffers (has to be done at the end)
	glutSwapBuffers();
}

void updateBall() {
	// fly a bit
	ball_pos_x += ball_dir_x * ball_speed;
	ball_pos_y += ball_dir_y * ball_speed;

	// hit by left racket?
	if (ball_pos_x < racket_left_x + racket_width && 
		ball_pos_x > racket_left_x &&
		ball_pos_y < racket_left_y + racket_height &&
		ball_pos_y > racket_left_y) {
			// set fly direction depending on where it hit the racket
			// (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
			float t = ((ball_pos_y - racket_left_y) / racket_height) - 0.5f;
			ball_dir_x = fabs(ball_dir_x); // force it to be positive
			ball_dir_y = t;
	}

	// hit by right racket?
	if (ball_pos_x > racket_right_x && 
		ball_pos_x < racket_right_x + racket_width &&
		ball_pos_y < racket_right_y + racket_height &&
		ball_pos_y > racket_right_y) {
			// set fly direction depending on where it hit the racket
			// (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
			float t = ((ball_pos_y - racket_right_y) / racket_height) - 0.5f;
			ball_dir_x = -fabs(ball_dir_x); // force it to be negative
			ball_dir_y = t;
	}

	// hit left wall?
	if (ball_pos_x < 0) {
		++score_right;
		ball_pos_x = width / 2;
		ball_pos_y = height / 2;
		ball_dir_x = fabs(ball_dir_x); // force it to be positive
		ball_dir_y = 0;
	}

	// hit right wall?
	if (ball_pos_x > width) {
		++score_left;
		ball_pos_x = width / 2;
		ball_pos_y = height / 2;
		ball_dir_x = -fabs(ball_dir_x); // force it to be negative
		ball_dir_y = 0;
	}

	// hit top wall?
	if (ball_pos_y > height) {
		ball_dir_y = -fabs(ball_dir_y); // force it to be negative
	}

	// hit bottom wall?
	if (ball_pos_y < 0) {
		ball_dir_y = fabs(ball_dir_y); // force it to be positive
	}

	// make sure that length of dir stays at 1
	//vec2_norm(ball_dir_x, ball_dir_y);
}

void update(int value) {

	// update ball
	updateBall();

	// Call update() again in 'interval' milliseconds
	glutTimerFunc(interval, update, 0);

	// Redisplay frame
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);

	//Create the window
	glutCreateWindow("Pong");

	//display
	glutDisplayFunc(draw);
	glutReshapeFunc(enable2D);

	//CONTROLS
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeysUp);

	//update and colisions
	glutTimerFunc(interval, update, 0);

	glutMainLoop();
	return 0;
}
