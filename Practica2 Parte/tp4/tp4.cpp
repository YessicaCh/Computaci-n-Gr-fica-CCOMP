
#define GLUT_DISABLE_ATEXIT_HACK
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
GLint tejas,pared,paredfront,tronco,rama,piso;
//variables para el gizmo
float delta_x = 0.0;
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_y = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)


//Materiales piso
GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
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
GLfloat light0Ambient [] = {0.3f,0.3f,0.3f,1.0f};
GLfloat light0Dif [] = {0.8f,0.8f,0.8f,1.0f};
GLfloat light0Spec [] = {0.6f, 0.6f, 0.6f, 1.0f};
//GLfloat light0Pos [] = { 5, 15 , 15 , 1 };
GLfloat light0Pos [] = { -10.0f, 15.0f ,15.0f,1.0f };

GLdouble mvmatrixd[16];

void ConfigLights() {
  // Color values: red light.
  // Position values: puntual light.
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

GLvoid initIlumination(){
	glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
	glEnable(GL_CULL_FACE); //no trata las caras escondidas
	glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
	glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva

}
GLvoid initGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);////3
	initIlumination();
	
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
  
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_QUADS);
		glNormal3d(0, 1, 0);
		glVertex3f(-20,0,-20);
		glVertex3f(-20, 0,20);
		glVertex3f(20,0,20);
		glVertex3f(20,0,-20);
	glEnd();

	return;
}
void suelo1()
{
   
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pisoAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pisoDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pisoEspecular);

    glBegin(GL_QUADS);
		glNormal3d(0, 1, 0);
		glVertex3f(-20,0,-20);
		glVertex3f(-20, 0,20);
		glVertex3f(20,0,20);
		glVertex3f(20,0,-20);
	glEnd();

	return;
}
void suelo2()
{
    glBegin(GL_QUADS);
		glVertex3f(-20,0,-20);
		glTexCoord2f(0.0, 0.0);

		glVertex3f(-20, 0,20);	
		glTexCoord2f(0.0, 10.0f);

		glVertex3f(20,0,20);
		glTexCoord2f(10.0f, 10.0f);

		glVertex3f(20,0,-20);
		glTexCoord2f(10.0, 0.0);
	glEnd();

	return;
}
void casa()
{
    //Muros
   int a=3;
	int b=5;
	int c=6;

    glColor3f(1.0f,0.0f,0.0f); 
	glBegin(GL_QUADS);
		   //derecha
			glNormal3d(1, 0, 0);
			glVertex3f(a,0,-c);
			glVertex3f(a,b,-c);
			glVertex3f(a,b,c);
			glVertex3f(a,0,c);
			//izquierda
			glNormal3d(-1, 0, 0);
			glVertex3f(-a,0,-c);
			glVertex3f(-a, 0,c);
			glVertex3f(-a,b,c);
			glVertex3f(-a,b,-c);
			//back
			glNormal3d(0, 0, -1);
			glVertex3f(-a,0,-c);
			glVertex3f(-a,b,-c);
			glVertex3f(a,b,-c);
			glVertex3f(a, 0,-c);
			//front 
			glNormal3d(0, 0, 1);
			glVertex3f(-a,0,c);
			glVertex3f(a, 0,c);
			glVertex3f(a,b,c);
			glVertex3f(-a,b,c);
			//TECHO
			 glColor3f(3.0f,3.0f,3.0f);
			//right
			glNormal3d(-1, 1, 0);
			glVertex3f(-a,b,c);
			glVertex3f(0,b*1.5,c);
			glVertex3f(0,b*1.5,-c);
			glVertex3f(-a,b,-c);
			//left 
			glNormal3d(1, 1, 0);
			glVertex3f(a,b,c);
			glVertex3f(a,b,-c);
			glVertex3f(0,b*1.5,-c);
			glVertex3f(0,b*1.5,c);
    glEnd();
    
    ///TRIANGULOS
    glColor3f(1.0f, 0.0f, 0.2f);
	glBegin(GL_TRIANGLES);

		glNormal3d(0, 0, -1);
		glVertex3f(a,b,-c);
		glVertex3f(-a,b,-c);
		glVertex3f(0,b*1.5,-c);
		//
		glNormal3d(0, 0, 1);
		glVertex3f(a,b,c);
		glVertex3f(0,b*1.5,c);
		glVertex3f(-a,b,c);
	glEnd();
   
    return;
}

void casa1()
{
    //Muros
    int a=3;
	int b=5;
	int c=6;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, casaAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, casaDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, casaEspecular);
    //******************************
    //Muros
	glBegin(GL_QUADS);
		   //derecha
			glNormal3d(1, 0, 0);
			glVertex3f(a,0,-c);
			glVertex3f(a,b,-c);
			glVertex3f(a,b,c);
			glVertex3f(a,0,c);
			//izquierda
			glNormal3d(-1, 0, 0);
			glVertex3f(-a,0,-c);
			glVertex3f(-a, 0,c);
			glVertex3f(-a,b,c);
			glVertex3f(-a,b,-c);
			//back
			glNormal3d(0, 0, -1);
			glVertex3f(-a,0,-c);
			glVertex3f(-a,b,-c);
			glVertex3f(a,b,-c);
			glVertex3f(a, 0,-c);
			//front 
			glNormal3d(0, 0, 1);
			glVertex3f(-a,0,c);
			glVertex3f(a, 0,c);
			glVertex3f(a,b,c);
			glVertex3f(-a,b,c);
	glEnd();    
    ///TRIANGULOS
	glBegin(GL_TRIANGLES);

		glNormal3d(0, 0, -1);
		glVertex3f(a,b,-c);
		glVertex3f(-a,b,-c);
		glVertex3f(0,b*1.5,-c);
		//
		glNormal3d(0, 0, 1);
		glVertex3f(a,b,c);
		glVertex3f(0,b*1.5,c);
		glVertex3f(-a,b,c);
	glEnd();
			//TECHO
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,techoAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,techoDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,techoEspecular);
	glBegin(GL_QUADS);
			//right
			glNormal3d(-1, 1, 0);
			glVertex3f(-a,b,c);
			glVertex3f(0,b*1.5,c);
			glVertex3f(0,b*1.5,-c);
			glVertex3f(-a,b,-c);
			//left 
			glNormal3d(1, 1, 0);
			glVertex3f(a,b,c);
			glVertex3f(a,b,-c);
			glVertex3f(0,b*1.5,-c);
			glVertex3f(0,b*1.5,c);
    glEnd();
   
    return;
}
void casa2()
{
   //Muros
   int a=3;
	int b=5;
	int c=6;
 
	glBegin(GL_QUADS);
		   //derecha
			glNormal3d(1, 0, 0);
			glVertex3f(a,0,c);			
			glTexCoord2f(0.0, 0.0);
			glVertex3f(a,0,-c);
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(a,b,-c);
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(a,b,c);
			glTexCoord2f(1.0, 0.0);
			//izquierda
			glNormal3d(-1, 0, 0);
			glVertex3f(-a,0,-c);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-a, 0,c);
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-a,b,c);
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(-a,b,-c);
			glTexCoord2f(1.0, 0.0);
			//back
			glNormal3d(0, 0, -1);
			glVertex3f(a, 0,-c);	
			glTexCoord2f(0.0, 0.0);//coordenadas de textura
			glVertex3f(-a,0,-c);
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(-a,b,-c);
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(a,b,-c);
			glTexCoord2f(1.0, 0.0);
			//front 
			glNormal3d(0, 0, 1);
			glVertex3f(-a,0,c);
			glTexCoord2f(0.0, 0.0);//coordenadas de textura
			glVertex3f(a, 0,c);
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(a,b,c);
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(-a,b,c);
			glTexCoord2f(1.0, 0.0);
    glEnd();
	glBegin(GL_TRIANGLES);  // triangulo left
	    glNormal3d(0, 0, -1);

		glVertex3f(a,b,-c);
		glTexCoord2f(0.0, 0.0);

		glVertex3f(-a,b,-c);
		glTexCoord2f(0.0, 1.0);

		glVertex3f(0,b*1.5,-c);
		glTexCoord2f(1, 0.5);

		glTexCoord2f(1.0, 0.0);
	 glEnd();
	 glBegin(GL_TRIANGLES);  // triangulo right
	    glNormal3d(0, 0, 1);

		glVertex3f(-a,b,c);
		glTexCoord2f(0.0, 0.0);

		glVertex3f(a,b,c);
		glTexCoord2f(0.0, 1.0);

		glVertex3f(0,b*1.5,c);
		glTexCoord2f(1, 0.5);

		glTexCoord2f(1.0, 0.0);

	 glEnd();

    //techo
    
    glBindTexture(GL_TEXTURE_2D,tejas);
    glBegin(GL_QUADS);  // back
			//right
			glNormal3d(1, 1, 0);
			glVertex3f(a,b,c);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(a,b,-c);
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(0,b*1.5,-c);
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(0,b*1.5,c);
			glTexCoord2f(1.0, 0.0);
			//left 
			glNormal3d(-1, 1, 0);
			glVertex3f(-a,b,-c);	
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-a,b,c);
			glTexCoord2f(0.0, 1.0f);
			glVertex3f(0,b*1.5,c);							
			glTexCoord2f(1.0, 1.0f);
			glVertex3f(0,b*1.5,-c);						
			glTexCoord2f(1.0, 0.0);  
    glEnd();
    return;
}
void arbol(){
    glColor3f(1.0f,1.0f,0.0f);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(-8,4,7);
    glPushMatrix();
        glRotatef(90,1,0,0);
        gluCylinder(quadratic,1,1,4,10,10);
    glPopMatrix();
    //Copo
    glColor3f(0.0f,0.8f,0.0f);
    glTranslatef(0,1,0);
    gluSphere(quadratic,2,16,16);
}
void arbol1(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, arbolAmbiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, arbolDifuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arbolEspecular);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glTranslatef(-8,4,5);
    glPushMatrix();
        glRotatef(90,1,0,0);
        gluCylinder(quadratic,1,1,4,10,10);
    glPopMatrix();
    //Copo
    glTranslatef(0,1,0);
    gluSphere(quadratic,2,16,16);
}
void arbol2(){
	GLUquadricObj *quadratic,*q2;
		quadratic = gluNewQuadric();
		q2=gluNewQuadric();
		gluQuadricTexture(quadratic,GLU_TRUE);
	    glBindTexture(GL_TEXTURE_2D, tronco);
		//gluQuadricDrawStyle( quadratic,GLU_FILL);
	 	//gluQuadricNormals( quadratic, GLU_SMOOTH); 
		glTranslatef(-8,4,7);
		glPushMatrix();
	        glRotatef(90,1,0,0);
	        gluCylinder(quadratic,1,1,3,8,8);
        glPopMatrix();
     	gluQuadricTexture(q2,GLU_TRUE);
	 	glBindTexture(GL_TEXTURE_2D,rama);
        glTranslatef(0,1,0);
        gluSphere(q2,2,16,16);

}
void EjercicioUno(){
	suelo();
	casa();
	arbol();
}
void EjercicioDos(){
	suelo1();
	casa1();
	arbol1();
}
void EjercicioTres(){
	ConfigLights();
	suelo1();
	casa1();
	arbol1();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
void EjercicioCuatro(){
	ConfigLights();
		//glClear(GL_COLOR_BUFFER_BIT); 
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
		glEnable(GL_BLEND);//utilizar transparencia

			glBindTexture(GL_TEXTURE_2D,piso);
			suelo2();
            glBindTexture(GL_TEXTURE_2D,pared);
            casa2();
            glBindTexture(GL_TEXTURE_2D,tronco);
            arbol2();
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
	gluPerspective(45.0f,1.0f, 0.01f, 100.0f);
	//gluLookAt(0,20,20,0,10,0,0,1,0);
	gluLookAt(0,30,40,0,20,0,0,1,0);
	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);

    
	//Gizmo3D();
	//glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrixd);
	//EjercicioUno();
	//EjercicioDos();
	//EjercicioTres();
	EjercicioCuatro();
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
    pared= TextureManager::Inst()->LoadTexture("pared.jpg", GL_BGR_EXT, GL_RGB);
    tejas = TextureManager::Inst()->LoadTexture("techo.jpg", GL_BGR_EXT, GL_RGB);
    tronco = TextureManager::Inst()->LoadTexture("tronco.jpg", GL_BGR_EXT, GL_RGB);
    rama = TextureManager::Inst()->LoadTexture("rama.jpg", GL_BGR_EXT, GL_RGB);
    cout<<" -> piso "<< piso <<endl;
    cout<<" -> pared "<< pared <<endl;
    cout<<" -> tejas "<< tejas <<endl;
    cout<<" -> tronco "<< tronco <<endl;
    cout<<" -> rama "<< rama <<endl;

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





