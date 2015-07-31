#ifndef controls
using namespace std;

extern int xx, zz, angle;
int index_missil=0;

void keyInput(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	}
	else if(key == 32){
		if(index_missil==50){
			index_missil=0;
		}
		missil[0][index_missil] = xx;	//posicao x da nave
		missil[1][index_missil] = zz-20;  //cabeca da nave
		

		//cout << index_missil <<" "<< missil[0][index_missil] << " "<< missil[1][index_missil] <<endl;

		launch_missil[index_missil++]=true;
	} 
}

void SpecialInput(int key, int x, int y) {
	switch(key){
	case GLUT_KEY_UP:
		//if(zz>9){
			zz-=1;
		//}
		break;	
	case GLUT_KEY_DOWN:
		//if(zz<9){
			zz+=1;
		//}
		break;
	case GLUT_KEY_LEFT:
		if(xx>-80){
			xx-=4;
			angle = -10;
			if(angle>-40){
				angle--;
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if(xx<80){
			xx+=4;
			angle = 10;
			if(angle<40){
				angle++;
			}
		}
		break;
	default:
		break;
	}
	//cout << xx << " "<< zz << endl;
	glutPostRedisplay();
}

#endif // !controls
