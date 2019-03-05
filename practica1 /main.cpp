#define GLUT_DISABLE_ATEXIT_HACK	
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define KEY_ESC 27
using namespace std;
#define GL_PI 3.14159f

//dibuja un simple gizmo
void primerEjercicio(int x,int y ,int L)
{
	glBegin(GL_LINE_LOOP);
	glColor3d(255,0,0);

	glVertex2f(x+(L/2),y+(L/2));
	glVertex2f(x+(L/2),y-(L/2));

	glVertex2f(x+(L/2),y-(L/2));
	glVertex2f(x-(L/2),y-(L/2));

	glVertex2f(x-(L/2),y-(L/2));
	glVertex2f(x-(L/2),y+(L/2));
	glEnd();
}
void segundoEjercicio(float x,float y ,int r)
{
	 float i;
	 int precision = 20;
	 
	 glBegin(GL_LINE_LOOP);
		 glColor3d(255,0,0);
	       for (i=0; i< GL_PI*2; i = i + (GL_PI/precision)) {
		      glVertex2f(r*cosf(i)+x,r*sinf(i)+y);
	  		}
    glEnd();
}
void TercerEjercicio(float x,float y ,int r)
{
	 int nCircuferencias=5;
	 float xnew=x;
	 float rnew=r;

	 for(int i=1;i<nCircuferencias;i++)
	 {
	 	segundoEjercicio(xnew,y,rnew);
	 	xnew=xnew+rnew;
	 	rnew=2*rnew;	
	 }
}
void CuartoEjercicio(float x,float y ,int r)
{
	 int nCircuferencias=5;
	 float xnew=x;
	 float rnew=r;

	 for(int i=1;i<nCircuferencias;i++)
	 {
	 	segundoEjercicio(xnew,y,rnew);
	 	xnew=xnew+rnew+(rnew/2);
	 	rnew=rnew/2;	
	 }
}
void QuintoEjercicio(float x,float y ,int r)
{
	 int nCircuferencias=3;
	 float xnew=x;
	 float ynew=y;
	 float rnew=r;
	 float grado=90;

	 for(int i=0;i<nCircuferencias;i++)
	 {
	 	segundoEjercicio(xnew,ynew,rnew);
	 	xnew=xnew+rnew+(rnew/2);
        ynew=(rnew/2)+ynew*sinf(90);
	 	rnew=rnew/2;	
	 }
}
//
//funcion llamada a cada imagen
void glPaint(void) {
	int x,y,l;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();
	
	QuintoEjercicio(0,0,20);

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
	
	glOrtho(-100.0f, 100.0f,-100.0f, 100.0f, -1.0f, 1.0f); 
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
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint); 
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}

