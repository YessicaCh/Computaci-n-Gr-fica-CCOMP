
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

GLdouble innerRaidus=0.5;
GLdouble outterRaidus=1;
GLint sides =50;
GLint rings =50;
GLfloat rotacionX = 0.0f;
GLfloat rotacionY = 0.0f;
float angle=0;
float VT=0;
float VL=0;
float VS=0;
float VM=0;
float RectX=0.0;
float RectY=0.0;
bool dir;

void init_scene();
void render_scene();


GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid callback_special(int key, int x, int y);
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
	}
}

GLvoid callback_motion(int x, int y)
{

	glutPostRedisplay();
}

void exercises1();
void exercises2();
void exercises3();
void exercises4();
//function called on each frame
float ingremento;
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 3 : Transformaciones 3D-2");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutKeyboardFunc(&window_key);
	glutSpecialFunc(&callback_special);
    glutMouseFunc(&callback_mouse);
    glutMotionFunc(&callback_motion);

	//function called on each frame
	glutIdleFunc(&window_idle);
	glutMainLoop();

	return 1;
}
GLvoid initGL()
{
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

	glClearColor(RED, GREEN, BLUE, ALPHA);
}
void exercises1(){

   VS=0.0195;
   VT+=3*VS;
   VL+=1.5*VS;
   
    	//sol
        glRotatef(VS,0,0,1);
		glColor3d(1.0,1.0,0);
		glutSolidSphere(4,8,8);

    glPushMatrix();
		//tierra
		glTranslatef(10*cos(VT),10*sin(VT),0);
		glColor3f(0.0,0.0, 1.0);
		glutSolidSphere(2,8,8); 
       //Luna	
		glTranslatef(3.0*cos(VL),3*sin(VL), 0.0);
	    glColor3f(1.0,1.0, 1.0);
		glutSolidSphere(0.8,8,8);
    glPopMatrix();

        glTranslatef(18.0*cos(VT),18*sin(VT),0.0);	
		glColor3f(1.0,0.0,0.0);
		glutSolidSphere(3.2,8,8);

}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//PARA BORRAR EL MATRIZ DE POSITIONRS
	//glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
	gluPerspective(45.0f,(GLfloat)(800/600),0.01f,100.0f);


	//dibujar aqui******
    
 	exercises1();
	glutSwapBuffers();

	glFlush();
}
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotacionX -= 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_DOWN:
		rotacionX += 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_LEFT:
	    rotacionY -= 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_RIGHT:
		rotacionY += 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;
	}
}
GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
	//gluPerspective(45.0f,(GLfloat)(800/600),0.01f,100.0f);

	glMatrixMode(GL_MODELVIEW);
}
void init_scene(){}
//video juego int a=0,a+=0.1(speeding rapido)*dt(el tiempo transcurrido)
GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}
//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}
