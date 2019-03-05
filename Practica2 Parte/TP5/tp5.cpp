//Compilar g++ -std=c++11 main.cpp TextureManager.cpp  -lglut -lGL -lGLU -lfreeimage -o b
#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

#include <FreeImage.h>
#include "TextureManager.h"
#include  "Terreno.h"
#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
int var=0;

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


GLint texture;
float delta_x = 0.0;
float delta_y = 90.0;
float mouse_x, mouse_y;
float var_x = -2000;
float var_z = -4000.0;
float step = 0;
Terreno terreno;
GLfloat light0Position[4];
GLfloat light_axis_x=-2525,light_axis_y=-1500,light_axis_z=0;


//function called on each frame
GLvoid window_idle()
{
    glutPostRedisplay();
}

GLvoid callback_special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        var_z += 50.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        var_z -= 50.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        var_x += 50.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        var_x -= 50.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_UP:
        light_axis_y+=100;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN:
        light_axis_y-=100;
        glutPostRedisplay();
        break;
    }
}


GLvoid window_key(unsigned char key, int x, int y)
{
    switch (key) {
    case ECHAP:
        exit(1);
        break;
    case 99:
        light_axis_x+=15;
        glutPostRedisplay();
        break;
    case 122:
        light_axis_x-=15;
        glutPostRedisplay();
        break;
    case 115:
        light_axis_y+=15;
        glutPostRedisplay();
        break;
    case 120:
        light_axis_y-=15;
        glutPostRedisplay();
        break;
    case 108:
    	//cout<<"l"<<endl;
    	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    	break;
    case 102:
    	//cout<<"f"<<endl;
    	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    	break;
    default:
        //printf("La touche %d non active.\n", key);
        if(key-48>=0 and key-48<=4)
			printf("Cambio a la acción %d : \n", key-48);
		var=key-48;
        break;
    }
}

GLvoid callback_mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        mouse_x = x;
        mouse_y = y;
    }
}

GLvoid callback_motion(int x, int y)
{

    delta_x += x - mouse_x;
    delta_y += y - mouse_y;
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("TP 5 - Modelo digital del terreno");



    texture = TextureManager::Inst()->LoadTexture("fontvieille.tga", GL_BGR_EXT, GL_RGB);
    terreno.load("fontvieille.txt");
   	terreno.computeNormals();

    initGL();

    init_scene();
    glutDisplayFunc(&window_display);
    glutReshapeFunc(&window_reshape);


    glutMouseFunc(&callback_mouse);
    glutMotionFunc(&callback_motion);
    glutKeyboardFunc(&window_key);

    glutSpecialFunc(&callback_special);
    glutIdleFunc(&window_idle);
    glutMainLoop();
    return 1;
}


void init_scene() {}


GLvoid initGL()
{
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE); //no trata las caras escondidas
	glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
	glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);


    light0Position[0]=light_axis_x;
    light0Position[1]=light_axis_y;
    light0Position[2]=light_axis_z;
    light0Position[3]=0.4f;

    GLfloat light0Ambient [] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat light0Difusa [] = {1.0f, 1.0f, 0.2f, 1.0f};
    GLfloat light0Especular [] = {2.0f, 2.0f, 0.2f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Especular);

    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

}

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 1.0f, 0.01f, 15200.0f);
    glTranslatef(var_x+2525, -1500, var_z);
    glRotatef(delta_x, 0.0, 1.0, 0.0);
    glRotatef(delta_y, 1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    terreno.display_no_texture();
    glutSwapBuffers();
    glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 1.0f, 0.01f, 15200.0f);
    glMatrixMode(GL_MODELVIEW);
}
