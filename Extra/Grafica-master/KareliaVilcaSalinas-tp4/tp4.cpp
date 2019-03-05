/////////////////////////////////////////////////////////////////////
///       KARELIA ALEXANDRA VILCA SALINAS                         ///
///       CCOMP 8-1                                               ///
/////////////////////////////////////////////////////////////////////
//Compilar asi : g++ -std=c++11 tp4.cpp TextureManager.cpp  -lglut -lGL -lGLU -lfreeimage -o b

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
void Interface();
int var=0;
void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLint tejas,pared,arbol,texture,porton;


//variables para el gizmo
float delta_x = 0.0; 
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)


GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};

GLfloat ambient[]={0.3f,0.3f,0.3f,1.0f};
GLfloat diffuse[]={0.8f,0.8f,0.8f,1.0f};
GLfloat specular[]={1.0f,1.0f,1.0f,1.0f};

GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat lightPos[] ={5,10,10,1};
//AMARILLO
//The color of the sphere
GLfloat materialColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
//The specular (shiny) component of the material
GLfloat materialSpecular[] = {0,0,1,1};
//The color emitted by the material
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; 
GLfloat materialEmission_amarillo[] = {1.0f,1.0f,0, 1.0f};
GLfloat materialEmission_verde[] = {0.0f,1.0f,0.5, 1.0f};
GLfloat materialEmission_verde2[] = {0.0f,1.0f,0.2, 1.0f};
GLfloat materialEmission_rojo[] = {1.0f,0.0f,0.2, 1.0f};
GLfloat materialEmission_plomo[] = {0.5f,0.5f,0.5, 1.0f};
GLfloat materialEmission_cafe[] = {0.3f, 0.0f, 0.0f, 1.0f};
GLfloat shininess = 20;

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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 3 : Transformations 3D Part 2");


	initGL();
	Interface();
	init_scene();

	arbol = TextureManager::Inst()->LoadTexture("tree.png", GL_BGRA_EXT, GL_RGBA);
	texture = TextureManager::Inst()->LoadTexture("pas.jpg", GL_BGR_EXT, GL_RGB);
	tejas = TextureManager::Inst()->LoadTexture("tejas.png", GL_BGR_EXT, GL_RGB);
	pared = TextureManager::Inst()->TextureManager::Inst()->LoadTexture("pared.jpg", GL_BGR_EXT, GL_RGB);
	porton = TextureManager::Inst()->TextureManager::Inst()->LoadTexture("a.png", GL_BGRA_EXT, GL_RGBA);
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

void Piso(){
	
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glVertex3f(-20,0,-20);
	glVertex3f(-20, 0,20);
	glVertex3f(20,0,20);
	glVertex3f(20,0,-20);
	glEnd();

	return;

}

void Piso2(){
	
	glBegin(GL_QUADS);

	glVertex3f(-20,0,-20);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura

	glVertex3f(-20, 0,20);	
	glTexCoord2f(0.0, 1.0f);

	glVertex3f(20,0,20);
	glTexCoord2f(1.0, 1.0f);

	glVertex3f(20,0,-20);
	glTexCoord2f(1.0, 0.0);
	
	glEnd();

	return;

}

void Casa(){
	int a=2;
	int b=4;
	int c=5;
	///PAREDES
	glBegin(GL_QUADS);

	glNormal3d(1, 0, 0);
	glVertex3f(a,0,-c);
	glVertex3f(a,b,-c);
	glVertex3f(a,b,c);
	glVertex3f(a,0,c);
	glEnd();

	glBegin(GL_QUADS);

	glNormal3d(-1, 0, 0);
	glVertex3f(-a,0,-c);
	glVertex3f(-a, 0,c);
	glVertex3f(-a,b,c);
	glVertex3f(-a,b,-c);
	glEnd();

	glBegin(GL_QUADS);

	glNormal3d(0, 0, -1);
	glVertex3f(-a,0,-c);
	glVertex3f(-a,b,-c);
	glVertex3f(a,b,-c);
	glVertex3f(a, 0,-c);
	glEnd();

	glBegin(GL_QUADS);

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
	glEnd();

	glBegin(GL_TRIANGLES);

	glNormal3d(0, 0, 1);
	glVertex3f(a,b,c);
	glVertex3f(0,b*1.5,c);
	glVertex3f(-a,b,c);
	glEnd();
	return;
}
void Casa2(){
	int a=2;
	int b=4;
	int c=5;
	///PAREDES
	
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glVertex3f(a,0,c);			
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(a,0,-c);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(a,b,-c);
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(a,b,c);
	glTexCoord2f(1.0, 0.0);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3d(-1, 0, 0);
	glVertex3f(-a,0,-c);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(-a, 0,c);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-a,b,c);
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(-a,b,-c);
	glTexCoord2f(1.0, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glVertex3f(a, 0,-c);	
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(-a,0,-c);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(-a,b,-c);
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(a,b,-c);
	glTexCoord2f(1.0, 0.0);
	glEnd();

	glBegin(GL_QUADS);
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
	
	///TRIANGULOS
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glVertex3f(a,b,-c);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(-a,b,-c);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0,b*1.5,-c);
	glTexCoord2f(1, 0.5);
	glTexCoord2f(1.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 1);
	glVertex3f(-a,b,c);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(a,b,c);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0,b*1.5,c);
	glTexCoord2f(1, 0.5);
	glTexCoord2f(1.0, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, porton);
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glVertex3f(-a+1,0,c);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(a-1, 0,c);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(a-1,b,c);
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(-a+1,b,c);
	glTexCoord2f(1.0, 0.0);
	glEnd();
	return;
}

void Techo(){
	int a=2;
	int b=4;
	int c=5;
	///TECHO
	glBegin(GL_QUADS);
	glNormal3d(-1, 1, 0);
	glVertex3f(-a,b,c);
	glVertex3f(0,b*1.5,c);
	glVertex3f(0,b*1.5,-c);
	glVertex3f(-a,b,-c);

	glEnd();

	glBegin(GL_QUADS);
	glNormal3d(1, 1, 0);
	glVertex3f(a,b,c);
	glVertex3f(a,b,-c);
	glVertex3f(0,b*1.5,-c);
	glVertex3f(0,b*1.5,c);
	glEnd();
	return;

}
void Techo2(){
	int a=2;
	int b=4;
	int c=5;
	///TECHO

	glBegin(GL_QUADS);
	glNormal3d(1, 1, 0);
	glVertex3f(a,b,c);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(a,b,-c);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(0,b*1.5,-c);
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(0,b*1.5,c);
	glTexCoord2f(1.0, 0.0);
	glEnd();

	glBegin(GL_QUADS);
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
void Arbol_tronco(){
	glPushMatrix();
		GLUquadricObj *qobj;
		qobj = gluNewQuadric();
		//gluQuadricDrawStyle(qobj,GLU_LINE);
		gluQuadricDrawStyle( qobj,GLU_FILL);
	 	gluQuadricNormals( qobj, GLU_SMOOTH); 
		glTranslatef(5,3,0);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		gluCylinder(qobj,1,1,3,8,8);
	glPopMatrix();
	return;
}
void Arbol_copa(){
   	glPushMatrix();
		glTranslatef(5,3,0);
		glutSolidSphere (2, 8, 8);	
	glPopMatrix();
	
	return;
}

void Arbol2a()
{
	int a=5;
	int b=10;
	int c=5;
	///PAREDES
	glBegin(GL_QUADS);
	glVertex3f(-a,0,0);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3f(a, 0,0);
	glTexCoord2f(0.0, 1.0f);
	glVertex3f(a,b,0);
	glTexCoord2f(1.0, 1.0f);
	glVertex3f(-a,b,0);
	glTexCoord2f(1.0, 0.0);
	glEnd();

}
void Arbol2()
{
	for(int i=0;i<180;i+=360/9)
		{
			glRotatef(i, 0.0, 1.0, 0.0);
			Arbol2a();
		}
	
	

}

void Billboard()
{
	glBindTexture(GL_TEXTURE_2D, arbol);
	Arbol2();
}

void Primero()
{
    glPushMatrix();

		glColor3f(0.2f, 1.0f, 0.3f);
		Piso();

		glColor3f(1.0f, 0.0f, 0.2f);
		Casa();

		glColor3f(0.5f, 0.5f, 0.5f);
		Techo();

		glColor3f(0.64f,0.16f,0.10f);
		Arbol_tronco();

		glColor3f(0.87f, 1.66f, 0.57f);
		Arbol_copa();

	glPopMatrix();

}
void Segundo()
{
	glEnable(GL_LIGHTING);
	glEnable( GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);


	//Diffuse (non-shiny) light component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//Specular (shiny) light component
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //The shininess parameter

		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission_verde2);
		Piso();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission_rojo);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		Casa();

			//GLfloat roofAmbient[] = {0.3f, 0.0f, 0.0f, 1.0f};
			//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, roofAmbient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission_plomo);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		Techo();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission_cafe);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		Arbol_tronco();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission_verde);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		Arbol_copa();

	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT0);
}
void Tercero()
{
	Segundo();
}
void Cuarto()
{
glEnable(GL_LIGHTING);
	glEnable( GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);


	//Diffuse (non-shiny) light component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//Specular (shiny) light component
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glClear(GL_COLOR_BUFFER_BIT); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
	glEnable(GL_BLEND);//utilizar transparencia

	glBindTexture(GL_TEXTURE_2D, texture);
	Piso2();

	glBindTexture(GL_TEXTURE_2D, pared);
	Casa2();

	glBindTexture(GL_TEXTURE_2D, tejas);
	Techo2();

	glTranslatef(10, 0.0, 10);
	Billboard();

	glColor3f(0.64f,0.16f,0.10f);
	Arbol_tronco();

	glColor3f(0.87f, 1.66f, 0.57f);
	Arbol_copa();
	glDisable(GL_BLEND);

	glDisable(GL_LIGHTING); 
	glDisable(GL_LIGHT0);
}
void Interface()
{
    //glPaintDefault();

    cout<<endl<<endl<<endl<<"_______________________________________"<<endl;
    cout<<"   Practica4: TExturas"<<endl;
    cout<<"_______________________________________"<<endl;
    cout<<"Presione el numero de ejercicio"<<endl<<"(en la pantalla de dibujo)"<<endl<<" para verlo por separado"<<endl;
    cout<<endl;
    cout<<"0 -> Muestra inicial"<<endl;
    cout<<"1 -> Primer ejercico"<<endl;
    cout<<"2 -> Segundo ejercico"<<endl;
    cout<<"3 -> Tercer ejercico"<<endl;
    cout<<"4 -> Cuarto ejercico"<<endl;
    cout<<"_______________________________________"<<endl;
    /*
    while(var!=0 and var!=1 and var!=2 and var!=3 and var!=4)
    {
    	cout<<"Intente ingresar un numero correcto: ";
    	cin>>var; 
    }*/
    // cin.get();


}
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);
	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);

	switch ( var) {
	    case 1:
	    	Primero();
	    break;

	    case 2:
			Segundo();
	    break;

	    case 3:
			Tercero();
	    break;

	    case 4:
	    	Cuarto();

		break;
	    
		case 0:
			//Tercero();
			//Segundo();
			//Primero();
			Cuarto();	
	    break;
    }
   
	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;
	default:
		if(key-48>=0 and key-48<=4)
			printf("Cambio a la acción %d : \n", key-48);
		var=key-48;
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}





