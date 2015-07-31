#ifndef controls

using namespace std;

extern int xx, zz, angle, treasure_x, treasure_y, pontos, size;
extern bool draw_treasure;
extern int direcao;
extern int posicao_x[32];
extern int posicao_y[32];
extern int direcao_corpo[32];
extern bool pause;

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
	switch(key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void SpecialInput(int key, int x, int y) {
	switch(key){
	case GLUT_KEY_UP:
		direcao = 1;
		break;	
	case GLUT_KEY_DOWN:
		direcao = 3;
		break;
	case GLUT_KEY_LEFT:
		direcao = 4;
		break;
	case GLUT_KEY_RIGHT:
		direcao = 2;
		break;
	default:
		break;
	}
	direcao_corpo[0] = direcao;
	glutPostRedisplay();
}

void actualizar_corpo(){
	for(int i=size; i>=1; i--){
		posicao_x[i] = posicao_x[i-1];
		posicao_y[i] = posicao_y[i-1];
	}
	posicao_x[0] = xx;
	posicao_y[0] = zz;
}

void colidi(){
	for(int i=0; i<size; i++){
		if(xx == posicao_x[i] && zz == posicao_y[i]){
			pause = true;
		}
	}
}

void moveSnake(int x) {
	if(pause == false){
		actualizar_corpo();
		switch (direcao) {
			//up
		case 1:
			if(zz == -9){
				zz+=18;
			} else {
				zz-=1;
			}
			angle=90;
			break;
			//down
		case 3:
			if(zz == 9){
				zz-=18;
			} else {
				zz+=1;
			}
			angle=270;
			break;
		case 2:
			if(xx == 9){
				xx-=18;
			} else {
				xx+=1;
			}
			angle=360;
			break;
		case 4:
			if(xx == -9){
				xx+=18;
			} else {
				xx-=1;
			}
			angle=180;
			break;
		default:
			break;
		}
		colidi();
		glutPostRedisplay();
		glutTimerFunc(120, moveSnake, 0);
	}
}

void colide(int x) {
	if(treasure_x == xx && treasure_y == zz){
		//somar pontos
		pontos+=10;
		size+=1;
		//dizer para desenhar novo tesouro
		draw_treasure = true;
	}
	glutTimerFunc(120, colide, 0);
}

#endif // controls
