#ifndef luz

//Add ambient light
GLfloat ambientColor[] = {0.2, 0.2, 0.2};

//Add positioned light
GLfloat lightColor0[] = {0.0, 0.0, 0.0, 0.0f};
GLfloat lightColor1[] = {0.7, 0.6, 0.9, 0.0f};
GLfloat lightPos0[] = {20.0f, 5.0f, 0.0f, 0.0f};

void luzes() {
	//global
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//ligth0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

//activar luzes
void init_lights() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_COLOR_MATERIAL);
	//glShadeModel( GL_SMOOTH );
	luzes();
}

#endif // !luz
