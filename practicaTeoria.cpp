#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
#define GL_PI 3.14159f

float ANCHO_BASE=60,LARGO_BASE=60;
float ANCHO_BRAZO_UNO=120,LARGO_BRAZO_UNO=30;
float ANCHO_BRAZO_DOS=60,LARGO_BRAZO_DOS=30;

void init_scene();
void render_scene();


//function called on each frame
GLvoid window_idle();
GLvoid initGL(){
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);}


void dibujaRectangulo(float ancho,float largo){
	glBegin(GL_QUADS);
		glVertex2f(0.0,-(largo/2));
		glVertex2f(ancho,-largo/2);
		glVertex2f(ancho,largo/2);
		glVertex2f(0.0,largo/2);
	glEnd();
}
void DibujaGrua(int angulo1,int angulo2,int largo){


	glPushMatrix();
	//La base
	glColor3f(1.0,0.7,0.5);
	dibujaRectangulo(ANCHO_BASE,LARGO_BASE);


	//brazo1 
	glTranslatef(ANCHO_BASE/2, LARGO_BASE/2,0.0f);
	glRotatef(angulo1,0.0,0.0,1.0);
	glColor3f(1.0,1.0,0.0);
	dibujaRectangulo(ANCHO_BRAZO_UNO,LARGO_BRAZO_UNO);

   //brazo2
	glTranslatef(ANCHO_BRAZO_UNO-LARGO_BRAZO_DOS/2,0.0f,0.0f);
	glRotatef(-angulo2,0.0,0.0,1.0);
	glColor3f(0.1,0.9,0.06);
	dibujaRectangulo(ANCHO_BRAZO_DOS,LARGO_BRAZO_DOS);


	/*glColor3f(0.1,0.9,0.06);
	glBegin(GL_LINES);
		glVertex2f(ANCHO_BRAZO_DOS,largo);
		glVertex2f(ANCHO_BRAZO_DOS,-largo);
		
	glEnd();*/
   glPopMatrix();
	//cuerda

	glColor3f(0.1,0.9,0.06);
	glBegin(GL_LINES);
		glVertex2f(ANCHO_BRAZO_DOS,largo);
		glVertex2f(ANCHO_BRAZO_DOS+ANCHO_BRAZO_UNO,-largo);
		
	glEnd();

}



GLvoid window_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//PARA BORRAR EL MATRIZ DE POSITIONRS
	glOrtho(0,300,0,300,-1.0,1.0);
	//glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	//dibujar aqui****** 
	DibujaGrua(45,100,LARGO_BASE);   
	glutSwapBuffers();

	glFlush();}
GLvoid window_reshape(GLsizei width, GLsizei height){
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,300,0,300,-1.0,1.0);
	//glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);}
void init_scene(){}
//video juego int a=0,a+=0.1(speeding rapido)*dt(el tiempo transcurrido)
GLvoid window_key(unsigned char key, int x, int y){
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}}
//function called on each frame
GLvoid window_idle(){ glutPostRedisplay();}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" Dibujar Grua : Transformaciones");


	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();
	return 1;
}

