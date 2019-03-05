
#define GLUT_DISABLE_ATEXIT_HACK
//#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "TextureManager.h"

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//texturas
GLint tejas,pared,arboles,texture,porton,piso;
//variables para el gizmo
float delta_x = 0.0;
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_y = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)


//Materiales piso
GLfloat pisoAmbiente [3] = {0.0,0.05,0.0};
GLfloat pisoDifuso [3] = {0.4,0.5,0.4};
GLfloat pisoEspecular [3] = {0.04,0.7,0.04};
//Materiales casa
GLfloat casaAmbiente [3] = {0.05,0.0,0.0};
GLfloat casaDifuso [3] = {0.5,0.4,0.4};
GLfloat casaEspecular [3] = {0.7,0.04,0.04};
//Materiales techo
GLfloat techoAmbiente [3] = {0.25,0.20725,0.20725};
GLfloat techoDifuso [3] = {1,0.829,0.829};
GLfloat techoEspecular [3] = {0.296648,0.296648,0.296648};
//Materiales arbol
GLfloat arbolAmbiente [3] = {0.25,0.25,0.25};
GLfloat arbolDifuso [3] = {0.4,0.4,0.4};
GLfloat arbolEspecular [3] = {0.774597,0.774597,0.774597};

//LUZ
GLfloat light0Ambient [] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat light0Dif [] = {1.0f, 1.0f, 0.2f, 1.0f};
GLfloat light0Spec [] = {0.0f, 2.0f, 2.0f, 1.0f};
GLfloat light0Pos [] = {0.0f, 0.0f, 0.0f, 1.0f};

///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}
///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}
///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{

	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}
//function called on each frame
GLvoid window_idle();

GLvoid initGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);////3
	
	glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
	glEnable(GL_CULL_FACE); //no trata las caras escondidas
	glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
	glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva
}

void Gizmo3D(){
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();
	return;
}

void suelo()
{
    float Largo=40,Ancho=40;
    glColor3f(0.0f,1.0f,0.0f);
	 glBegin(GL_QUADS);
	 	glNormal3d(0, 1, 0);
        glVertex3f(var_x - Largo,0,var_z+Ancho);
        glVertex3f(var_x + Largo,0,var_z+ Ancho);
        glVertex3f(var_x+ Largo,0,var_z-Ancho);
        glVertex3f(var_x-Largo,0,var_z-Ancho);
    glEnd();

	return;
}
void suelo1()
{
    float Largo=40,Ancho=40;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pisoAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pisoDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,pisoEspecular);
	 glBegin(GL_QUADS);
        glVertex3f(var_x - Largo,0,var_z+Ancho);
        glVertex3f(var_x + Largo,0,var_z+ Ancho);
        glVertex3f(var_x+ Largo,0,var_z-Ancho);
        glVertex3f(var_x-Largo,0,var_z-Ancho);
    glEnd();

	return;
}
void suelo2()
{
    float Largo=40,Ancho=40;
	 glBegin(GL_QUADS);
        glVertex3f(var_x - Largo,0,var_z+Ancho);
         glTexCoord2f(0.0,0.0);

        glVertex3f(var_x + Largo,0,var_z+ Ancho);
         glTexCoord2f(40.0,0.0);

        glVertex3f(var_x+ Largo,0,var_z-Ancho);
         glTexCoord2f(40.0,40.0);

        glVertex3f(var_x-Largo,0,var_z-Ancho);
        glTexCoord2f(0.0,40.0);
    glEnd();

	return;
}
void casa()
{
    //Muros

    glColor3f(1.0f,0.0f,0.0f);
     glBegin(GL_QUADS);  // root front
        glVertex3f(var_x-10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+0,var_z+10);
        glVertex3f(var_x-10,var_y+0,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  //root back
        glVertex3f(var_x-10,var_y+10,var_z-10);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        glVertex3f(var_x+10,var_y+0,var_z-10);
        glVertex3f(var_x-10,var_y+0,var_z-10);
    glEnd();
    glBegin(GL_QUADS);  // root right
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        glVertex3f(var_x+10,var_y+0,var_z-10);
        glVertex3f(var_x+10,var_y+0,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  //root left
        glVertex3f(var_x-10,var_y+10,var_z+10);
        glVertex3f(var_x-10,var_y+10,var_z-10);
        glVertex3f(var_x-10,var_y+0,var_z-10);
        glVertex3f(var_x-10,var_y+0,var_z+10);
    glEnd();
    //techo

    glColor3f(3.0f,3.0f,3.0f);
     glBegin(GL_QUADS);  // front
        glVertex3f(var_x-10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x-10,var_y+10,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  // back
        glVertex3f(var_x-10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        glVertex3f(var_x-10,var_y+10,var_z-10);
    glEnd();

    //triangulo
    glColor3f(1.0f,0.0f,0.0f);
     glBegin(GL_TRIANGLES);  // right
        glVertex3f(var_x+10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+10,var_z-10);
    glEnd();
    glBegin(GL_TRIANGLES);  // left
        glVertex3f(var_x-10,var_y+15,var_z+0);
        glVertex3f(var_x-10,var_y+10,var_z+10);
        glVertex3f(var_x-10,var_y+10,var_z-10);
    glEnd();
    return;
}
void casa1()
{
    //Muros
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, casaAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, casaDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, casaEspecular);
     glBegin(GL_QUADS);  // root front
        glVertex3f(var_x-10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+0,var_z+10);
        glVertex3f(var_x-10,var_y+0,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  //root back
        glVertex3f(var_x-10,var_y+10,var_z-10);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        glVertex3f(var_x+10,var_y+0,var_z-10);
        glVertex3f(var_x-10,var_y+0,var_z-10);
    glEnd();
    glBegin(GL_QUADS);  // root right
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        glVertex3f(var_x+10,var_y+0,var_z-10);
        glVertex3f(var_x+10,var_y+0,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  //root left
        glVertex3f(var_x-10,var_y+10,var_z+10);
        glVertex3f(var_x-10,var_y+10,var_z-10);
        glVertex3f(var_x-10,var_y+0,var_z-10);
        glVertex3f(var_x-10,var_y+0,var_z+10);
    glEnd();
    //techo

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, techoAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, techoDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, techoEspecular);
     glBegin(GL_QUADS);  // front
        glVertex3f(var_x-10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x-10,var_y+10,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  // back
        glVertex3f(var_x-10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        glVertex3f(var_x-10,var_y+10,var_z-10);
    glEnd();

    //triangulo
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, casaAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, casaDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, casaEspecular);
     glBegin(GL_TRIANGLES);  // right
        glVertex3f(var_x+10,var_y+15,var_z+0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        glVertex3f(var_x+10,var_y+10,var_z-10);
    glEnd();
    glBegin(GL_TRIANGLES);  // left
        glVertex3f(var_x-10,var_y+15,var_z+0);
        glVertex3f(var_x-10,var_y+10,var_z+10);
        glVertex3f(var_x-10,var_y+10,var_z-10);
    glEnd();
    return;
}
void arbol(){
    glColor3f(1.0f,1.0f,0.0f);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(-10,8,5);
    glPushMatrix();
        glRotatef(90,1,0,0);
        gluCylinder(quadratic,1,1,8,10,10);
    glPopMatrix();
    //Copo
    glColor3f(0.0f,0.8f,0.0f);
    glTranslatef(0,3,0);
    gluSphere(quadratic,4,16,16);
}
void arbol1(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, arbolAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arbolDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arbolEspecular);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(-10,8,5);
    glPushMatrix();
        glRotatef(90,1,0,0);
        gluCylinder(quadratic,1,1,8,10,10);
    glPopMatrix();
    //Copo
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, arbolAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arbolDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arbolEspecular);
    glTranslatef(0,3,0);
    gluSphere(quadratic,4,16,16);
}
void EjercicioUno(){
	suelo();
	casa();
	arbol();
}
void EejercicioDos(){
	suelo1();
	casa1();
	arbol1();
}
void EejercicioTres(){
	glEnable(GL_LIGHTING);
	glEnable( GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

	suelo();
	casa();
	arbol();
	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT0);
}
void EejercicioCuadro(){
	glEnable(GL_LIGHTING);
	glEnable( GL_LIGHT0);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light0Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
		//glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

		glClear(GL_COLOR_BUFFER_BIT); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
		glEnable(GL_BLEND);//utilizar transparencia

			glBindTexture(GL_TEXTURE_2D,piso);
			suelo2();

			/*glBindTexture(GL_TEXTURE_2D, pared);
			//Casa2();

			glBindTexture(GL_TEXTURE_2D, tejas);
			//Techo2();

			glTranslatef(10, 0.0, 10);
			//Billboard();

			glColor3f(0.64f,0.16f,0.10f);
			//Arbol_tronco();

			glColor3f(0.87f, 1.66f, 0.57f);
			Arbol_copa();*/
		glDisable(GL_BLEND);

	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT0);
}
GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}
void init_scene(){}
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
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);
	//gluLookAt(0,20,20,0,10,0,0,1,0);
	gluLookAt(0,20,20,0,18,0,0,1,0);
	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);

	//Gizmo3D();
	//EjercicioUno();
	EejercicioCuadro();
	glutSwapBuffers();
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 4 : Transformations 3D Part 2");


	initGL();
	init_scene();
	piso = TextureManager::Inst()->LoadTexture("pasto.jpg", GL_BGR_EXT, GL_RGB);


	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);


	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}





