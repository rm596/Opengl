#ifndef controls
/*MOVER RACKET*/
void keyboard(unsigned char key, int x, int y){
	switch(key)
	{
	case 'w':
		racket_left_y += racket_speed;
		break;
	case 'W':
		racket_left_y += racket_speed;
		break;
	case 's':
		racket_left_y -= racket_speed;
		break;
	case 'S':
		racket_left_y -= racket_speed;
		break;
	case 27: // Escape key
		//glutDestroyWindow ();
		exit (0);
		break;
	default : 
		break;
	}
	glutPostRedisplay();
}

void SpecialKeysUp(int key, int x, int y) {
	if (GLUT_KEY_UP == key){
		racket_right_y += racket_speed;
	} else if(GLUT_KEY_DOWN == key){
		racket_right_y -= racket_speed;
	}
	glutPostRedisplay();

}

#endif // !controls