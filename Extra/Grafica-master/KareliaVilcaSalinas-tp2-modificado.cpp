/////////////////////////////////////////////////////////////////////
///       KARELIA ALEXANDRA VILCA SALINAS                         ///
///       CCOMP 8-1                                               ///
/////////////////////////////////////////////////////////////////////
//Compilar asi : g++ -std=c++11 tp2.cpp -lglut -lGL -lGLU -o b

#define GLUT_DISABLE_ATEXIT_HACK
//#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glut.h>
using namespace std;

GLfloat angulo=0.0f;
GLfloat angulo2=0.0f;

GLfloat frecuencia=0.2f;
GLfloat frecuencia2=0.02f;

int var=0;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
void glPaintInterface();
void Interface();
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


	//initGL();
	init_scene();

	Interface();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}

void displayGizmo()
{
glBegin(GL_LINES);
glColor3d(255,0,0);
glVertex3f(0, 0,0);
glVertex3f(50, 0,0);
glEnd();
glBegin(GL_LINES);
glColor3d(0,255,0);
glVertex3f(0,0,0);
glVertex3f(0,50,0);
glEnd();
glBegin(GL_LINES);
glColor3d(0,0,255);
glVertex3f(0,0,0);
glVertex3f(0,0,50);
glEnd();

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
GLfloat a=-8.0f;
GLfloat signo=1;
GLfloat linea(GLfloat b)
{
	if(b>=8)
	{
		signo=signo*-1;
	}	
	if(b<=-8.2)
	{
		signo=signo*-1;
	}	
		b=b+(signo)*frecuencia/2;
	return b;
}
void material_ini()
{
	GLfloat mat_ambient[] = { 0.329412f, 0.223529f, 0.027451f,1.0f };
    GLfloat mat_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
    GLfloat mat_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
    GLfloat shine[] = {27.8974f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);	
}
void Primero_tetera(GLfloat z)
{
	glPushMatrix();
		glColor3d(0,0,255);
		glTranslatef (0.0, 0.0, z); 
   		glutSolidSphere (0.3, 100, 100);

		glDisable(GL_COLOR_MATERIAL);
			material_ini();
			glRotatef(angulo, 0.0f, 0.0f, 1.0f);
			glTranslatef(4,0,0);
			glutSolidTeapot(1.5);
		glEnable(GL_COLOR_MATERIAL);
  	glPopMatrix();
}
void Segundo_tetera_ocho(GLfloat z)
{
  	glPushMatrix();
  		glColor3d(0,255,255);
  		a=linea(a);
		glTranslatef (a, 0.0, z); 
   	 	glutSolidSphere (0.3, 100, 100);

	   	glDisable(GL_COLOR_MATERIAL);
	   		material_ini();
			glRotatef(angulo, 0.0f, 0.0f, 1.0f);
			glTranslatef(4,0,0);
			glutSolidTeapot(1.5);
		glEnable(GL_COLOR_MATERIAL);
  	glPopMatrix();
}
void Tercero_Elementos(GLfloat z)
{
  	glPushMatrix();
  		glColor3d(0,0,255);
  		a=linea(a);
		glTranslatef (a, 0.0, z); 
   	 	glutSolidSphere (0.3, 100, 100);

  		glDisable(GL_COLOR_MATERIAL);
  			material_ini();
			glRotatef(angulo, 0.0f, 0.0f, 1.0f);
			glTranslatef(4,0,z);
			glutSolidTeapot(1.5);
		glEnable(GL_COLOR_MATERIAL);

		glColor3d(0,255,0);
		glRotatef(angulo*3, 0.0f, 1.0f, 0.0f);
		glTranslatef(3,0,0);
		glutSolidTorus (0.1, 0.3, 100, 100);
	glPopMatrix();	
   	glPushMatrix();
  		glColor3d(0,0,255);
  		a=linea(a);
		glTranslatef (a, 0.0, z); 
   	 	glutSolidSphere (0.3, 100, 100);

		glColor3d(255,0,0);
		glRotatef(angulo, 1.0f, 0.0f, 0.0f);
		glTranslatef(0,0,4);
		glutSolidCube(2); 	 	
  	glPopMatrix();
}
void Cuarto_sistema(GLfloat z)
{
  	glPushMatrix();
  		GLfloat VS=angulo2;
  		///SOL
		glColor3d(70,255,0);
		glTranslatef (0.0, 0.0, z); 
		glRotatef(VS, 0.0f, 1.0f, 0.0f);
   		glutSolidSphere (4, 8, 8);
   	glPopMatrix();
   	glPushMatrix();
   		GLfloat VT=VS*3;
  		GLfloat Vt=angulo2; 
  		GLfloat Vl=2*Vt; 
  		GLfloat VL=1.5*VS;
   		///TIERRA
		glColor3d(0,0,255);
		glRotatef(Vt, 0.0f, 1.0f, 0.0f);
		glRotatef(VT, 0.0f, 1.0f, 0.0f);
		glTranslatef(10,0,0);
		glutSolidSphere (2, 8, 8);
		///LUNA
		glColor3d(255,255,255);
		glRotatef(Vl, 0.0f, 1.0f, 0.0f);		
		glRotatef(VL, 0.0f, 1.0f, 0.0f);
		glTranslatef(3,0,0);
		glutSolidSphere (0.5, 8, 8);	
  	glPopMatrix();

  	glPushMatrix();
  		///MARTE
  	    GLfloat	Vm=Vt;
  	    GLfloat	VM=VS;
  		glColor3d(255,0,0);
		glRotatef(Vm, 0.0f, 1.0f, 0.0f);
		glRotatef(VM, 0.0f, 1.0f, 0.0f);
		glTranslatef(18,0,z);
		glutSolidSphere (1.5, 8, 8);
  	glPopMatrix();
}
void glPaintInterface()
{
	 switch ( var) {
    case 1:
		Primero_tetera(0);
    break;

    case 2:
		Segundo_tetera_ocho(0);
    break;

    case 3:
		Tercero_Elementos(0);
    break;

    case 4:
        Cuarto_sistema(0);
    break;
    
	case 0:
		Primero_tetera(7);
		Segundo_tetera_ocho(14);
		Tercero_Elementos(21);
		Cuarto_sistema(0);
    break;
    }
}
void Interface()
{
    //glPaintDefault();

    cout<<endl<<endl<<endl<<"_______________________________________"<<endl;
    cout<<"   Practica2: Transformaciones 3D"<<endl;
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
    //cin>>var;
    //glPaintInterface();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    gluLookAt(1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	
	glEnable(GL_COLOR_MATERIAL);

	displayGizmo();

    glPaintInterface();
	
	glutSwapBuffers();

	glFlush();
	angulo+=frecuencia;
	angulo2+=frecuencia2;
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
}



void init_scene()
{
// Ubicamos la fuente de luz en el punto
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
//GLfloat luz_ambiental[] = { 0.2, 0.2, 0.2, 1.0 };


// Activamos la fuente de luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

//glLightfv(GL_LIGHT0,GL_POSITION,light_position);
// Queremos que se dibujen las caras frontales
// y con un color solido de relleno.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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