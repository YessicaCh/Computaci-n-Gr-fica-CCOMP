#define GLUT_DISABLE_ATEXIT_HACK	
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define KEY_ESC 27
using namespace std;
#define GL_PI 3.14159f

float ANCHO_BASE=4,LARGO_BASE=2;
float ANCHO_BRAZO_UNO=10,LARGO_BRAZO_UNO=1;
void dibujaRectangulo(float ancho,float largo){
	glBegin(GL_QUADS);
		glVertex2f(0.0,-(largo/2));
		glVertex2f(ancho,-largo/2);
		glVertex2f(ancho,largo/2);
		glVertex2f(0.0,largo/2);
	glEnd();
}
void DibujaGrua(int angulo1,int angulo2,int largo){
	//La base
	glColor3f(255,0,0);
	dibujaRectangulo(ANCHO_BASE,LARGO_BASE);


	//brazo1 
	glTranslatef(ANCHO_BASE/2, LARGO_BASE/2,0.0f);
	glRotatef(angulo1,0.0,0.0,1.0);
	glColor3f(230,230,230);
	dibujaRectangulo(ANCHO_BRAZO_UNO,LARGO_BRAZO_UNO);

}
//funcion llamada a cada imagen
void glPaint(void) {
	int x,y,l;

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();
	
	glOrtho(0,300,0,300,-1.0,1.0);
	//glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	//dibujar aqui****** 
	DibujaGrua(45,10,LARGO_BASE); 

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//ini|cializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0,300,0,300,-1.0,1.0);
	//glOrtho(-100.0f, 100.0f,-100.0f, 100.0f, -1.0f, 1.0f); 
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(0,0); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint); 
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}
