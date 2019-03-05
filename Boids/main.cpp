#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "TextureManager.h"
#include "Flock.h"
#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1
#define ECHAP 27
using namespace std;
//Fack
float ladoCubo=450;
Flock *Manada;
//
GLint pez,obstaculo;
//variables para el gizmo
float delta_x = 100.0;
//float delta_y = 0.0;
float delta_y = 0.0;
float mouse_x, mouse_y;
//float var_x = 0.0;
float var_x = -200.0;
//float var_y = 0.0;
float var_y = 0.0;
//float var_z = 0.0;
float var_z = -200.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)

//LUZ
GLfloat light0Ambient [] = {0.3f,0.3f,0.3f,1.0f};
GLfloat light0Dif [] = {0.8f,0.8f,0.8f,1.0f};
GLfloat light0Spec [] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat light0Pos [] = { -10.0f, 15.0f ,15.0f,1.0f };

GLdouble mvmatrixd[16];

void ConfigLights() {
  GLfloat Light0Pos[] = {0.0f, 20.0f, 20.0f, 1.0f};
  GLfloat direction[] = {0.0, -1.0, -1.0};
  // Light0 parameters.
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR,light0Spec);
  glLightfv(GL_LIGHT0, GL_POSITION,light0Pos);
  // Activate light.
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}
GLvoid initIlumination(){
	glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
	glEnable(GL_CULL_FACE); //no trata las caras escondidas
	glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
	glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva
}
///////////////////////////////(1)///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 50.0f;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 50;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		var_x += 50;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 50;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step+=100;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step-=100;
		glutPostRedisplay();
		break;
	}
}
//////////////////////////////////(2)////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}
///////////////////////////(3)////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{

	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}
GLvoid initGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);////3
	//initIlumination();	
}
GLvoid window_reshape(GLsizei width, GLsizei height)
{   glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}
void init_scene(){}
GLvoid window_key(unsigned char key, int x, int y){
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
GLvoid window_idle(){
	glutPostRedisplay();}
GLvoid window_display()
{  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f,800/600, 0.01f, 1050.0f);
	gluLookAt(200,500,-400,0,0,0,0,1,0);
	//gluLookAt(-150,-120,-200,0,0,0,0,1,0);
	//glFrustum(0.0f,400.0f,0.0f,400.0f,1.0f,400.0f);
	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(step, 0.0, 0.0, 0.0);
	Manada->drawBoids();
	Manada->update();
	glutSwapBuffers();
	glFlush();
}
int main(int argc, char **argv)
{
	Manada=new Flock(2000);
	Manada->setup(ladoCubo,ladoCubo,ladoCubo);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("************ Flock  3D  ********");
	initGL();
	init_scene();
	cout<<" AQUII"<<pez<<endl;
	GLint pez=TextureManager::Inst()->LoadTexture("tes2.png", GL_BGRA_EXT, GL_RGBA);
	cout<<" NO SE MUERE POR AQUII"<<pez<<endl;
	//GLint pez=TextureManager::Inst()->LoadTexture("peces4.jpg", GL_BGR_EXT, GL_RGB);
	//GLint obstac=TextureManager::Inst()->LoadTexture("piedra.jpeg", GL_BGR_EXT, GL_RGB);
	//init_scene();
	Manada->peces=pez;//TextureManager::Inst()->LoadTexture("pescadoAmarillo.jpg", GL_BGR_EXT, GL_RGB);
    Manada->obst=TextureManager::Inst()->LoadTexture("piedra.jpeg", GL_BGR_EXT, GL_RGB);
    Manada->asignarTexturas();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);
	glutKeyboardFunc(&window_key);
	glutSpecialFunc(&callback_special);
	glutIdleFunc(&window_idle);//function called on each frame
	glutMainLoop();
	return 1;
}