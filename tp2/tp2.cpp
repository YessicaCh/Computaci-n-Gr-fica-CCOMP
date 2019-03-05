
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
	glutCreateWindow("TP 2 : Transformaciones");


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
void exercises4(){

   VS=0.5;
   VT+=3*VS;
   VL+=1.5*VS;
    
    glPushMatrix();
    	//sol
        glRotatef(VS,0,0,1);
		glColor3d(1.0,1.0,0);
		glutSolidSphere(4,8,8);

    glPopMatrix();

    glPushMatrix();
		//tierra
		glRotatef(VT,0,0,1);
		glTranslatef(10,0,0);
		glColor3f(0.0,0.0, 1.0);
		glutSolidSphere(2,8,8); 
       //Luna
		glRotatef(VL,0.0,1.0,0.0);	
		glTranslatef(3.0, 0.0, 0.0);
	    glColor3f(1.0,1.0, 1.0);
		glutSolidSphere(0.8,8,8);
    glPopMatrix();

    glPushMatrix();//marte
        glRotatef(VT,0.0,0.0,1.0);	
        glTranslatef(18.0,0.0,0.0);
        glRotatef(VS,0.0,1.0,0.0);	
		glColor3f(1.0,0.0,0.0);
		glutSolidSphere(3.2,8,8);
	glPopMatrix();
}
void exercises3(){
	
	glPushMatrix();	
		glTranslatef(RectX,0,0);
		glColor3d(0,0,255);
		glutSolidSphere(1,16,3);

	    glPushMatrix();//solidCube()
	        glRotatef(angle,1,0,0);
	        glTranslatef(0,6,0);
		    glColor3f(1.0,0.0, 0.0);
		    glutSolidCube(2);
	    glPopMatrix();
	    
		glRotatef(angle,0,0,1);
		glTranslatef(10,0,0);
		glColor3d(255,0,255);
		glutSolidTeapot(2);//para dibujar la tetera aquii** de tamaño de dos********
       
		glRotatef(-RectY,0.0,1.0,0.0);	
		glTranslatef(3.0, 0.0, 0.0);
	    glColor3f(1.0,0.0, 0.0);
		glutSolidTorus(0.9,0.6,3*angle,20);
    

	glPopMatrix();

    angle+=1.5;
    RectY+=3;

    if(RectX>=8)
    	dir=false;
    else if(RectX<=-8)
   	dir=true;
    if(dir==true)
    	RectX+=0.1;
    else
    	RectX-=0.1;
}
void exercises2(){


	    glPushMatrix();
		    glTranslatef(RectX,0,0);
			glColor3d(0,0,255);
			glutSolidSphere(1,16,3);
	

		    glRotatef(angle,0,0,1);
		    glTranslatef(10,0,0);
		    glColor3d(255,0,255);
		    glutSolidTeapot(2);//para dibujar la tetera aquii** de tamaño de dos********
       glPopMatrix();

    angle+=1.5;

    if(RectX>=8)
    	dir=false;
    else if(RectX<=-8)
    	dir=true;
    if(dir==true)
    	RectX+=0.1;
    else
    	RectX-=0.1;
	
}
void exercises1(){
	
	glColor3d(0,0,255);
	glutSolidSphere(1,16,3);

    glRotatef(angle,0,0,1);
    glTranslatef(10,0,0);
    glColor3d(255,0,255);
    glutSolidTeapot(2);//para dibujar la tetera aquii** de tamaño de dos********
    angle+=1.2;	
}
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//PARA BORRAR EL MATRIZ DE POSITIONRS
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);


	//dibujar aqui******
    
 	exercises3();
	glutSwapBuffers();

	glFlush();
}
GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

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
