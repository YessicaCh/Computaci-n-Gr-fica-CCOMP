/////////////////////////////////////////////////////////////////////
///       KARELIA ALEXANDRA VILCA SALINAS                         ///
///       CCOMP 8-1                                               ///
/////////////////////////////////////////////////////////////////////
#define GLUT_DISABLE_ATEXIT_HACK	
//#include <windows.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <GL/glut.h>
using namespace std;
#define KEY_ESC 27
float xm,ym,xi,yi,xf,yf;
vector< pair < pair<float, float >, pair<float, float > > > puntos;
int flag=0;
bool drawLine = false;
///g++ -std=c++11 main.cpp -o demo -lglut -lGLs
void setPixel(int x, int y)
{
    glColor3f(0.4, 0.7, 0.5); //Pixel negro 
    glBegin(GL_POINTS);
    glVertex2i(x, y); //Coordenadas 
    glEnd();
}

//Dibuja la linea si la distancia de X es mayor que Y 
void bresenhamX(int x0, int y0, int x1, int y1, int dx, int dy)
{
    int i, j, k;

    i = 2 * dy - dx;
    j = 2 * dy;
    k = 2 * (dy - dx);
    if (!(x0 < x1)) {
        swap(x0, x1);
        swap(y0, y1);
    }
    setPixel(x0, y0);
    while (x0 < x1) {
        if (i < 0)
            i += j;
        else {
            if (y0 < y1)
                ++y0;
            else
                --y0;
            i += k;
        }
        ++x0;
        setPixel(x0, y0);
    }
}

//Dibuja la linea si la distancia de X es menor que Y 
void bresenhamY(int x0, int y0, int x1, int y1, int dx, int dy)
{
    int i, j, k;

    i = 2 * dx - dy;
    j = 2 * dx;
    k = 2 * (dx - dy);
    if (!(y0 < y1)) {
        swap(x0, x1);
        swap(y0, y1);
    }
    setPixel(x0, y0);
    while (y0 < y1) {
        if (i < 0)
            i += j;
        else {
            if (x0 > x1)
                --x0;
            else
                ++x0;
            i += k;
        }
        ++y0;
        setPixel(x0, y0);
    }
}

//Llamara a la funcion apropiada dependiendo de la longitud de los ejes x y y 
void bresenham(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    if (dx >= dy)
        bresenhamX(x0, y0, x1, y1, dx, dy);
    else
        bresenhamY(x0, y0, x1, y1, dx, dy);
}


//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(-400, 0);
	glVertex2d(400, 0);
	glColor3d(0, 255, 0);
	glVertex2d(0, -400);
	glVertex2d(0, 400);
	glEnd();
}
//dibuja lineas almacenadas
void displayLines()
{
	glPointSize(1);  
	glColor3f(0.5f, 1.0f, 1.5f);
	for(int i =0; i<puntos.size();i++)
		bresenham(puntos[i].first.first, puntos[i].first.second, puntos[i].second.first, puntos[i].second.second);

}
//dibuja vertice actual
void displayVertice()
{
	glPointSize(5);  
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	glVertex2d(xi, yi);
	glEnd();
}


void OnMouseClick(int button, int state, int x, int y)
{ 
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  {  //cout<<"ENTRE--------------------"<<endl;
     //hacer algo x,z
	//cout<<"crea punto: "<<x<<" ,  "<<y<<endl;
  	if(flag==0)
  	{
  		xi=x-400;//conversion(x);
  		yi=400-(y-0);//conversion(y);;
  		flag=1;
  		cout<<"coordenadas iniciales:  "<<xi<<" , "<<yi<<endl;
  		drawLine = false;
  	}
  	else if (flag==1)
  	{
  		xf=x-400;//conversion(x);
  		yf=400-(y-0);//conversion(y);
  		flag=0;
  		cout<<"coordenadas finales:  "<<xf<<" , "<<yf<<endl;
  		cout<<endl;
  		puntos.push_back(make_pair( make_pair(xi,yi), make_pair(xf,yf) ) );
        drawLine = true;
  	}	

  }	
  glutPostRedisplay();
}


void OnMouseMotion(int x, int y)
{
     //hacer algo x,z
	 xm=x-400;
	 ym=400-y;
     	
	 //f=1;
	  //cout<<"motion  "<<xm<<" , "<<ym<<"   "<<f<<endl;
}



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay(); 
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(-400.0f,  400.0f,-400.0f, 400.0f, -1.0f, 1.0f); 
	//glTranslated (xm,ym,0);
	
	//dibuja el gizmo
	displayGizmo();
	displayLines();
	displayVertice();
	//TEMPORAL 
	glPointSize(2);  
	glColor3f(0.0f, 0.2f, 1.0f);
	if(flag==1 and drawLine==false)
	{ 
	if(drawLine==false)
    	bresenham(xi, yi, xm, ym);
	else
    	bresenham(xi, yi, xf, yf);
	}

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
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
	
	glOrtho(-400.0f,  400.0f,-400.0f, 400.0f, -1.0f, 1.0f); 
	// todas la informaciones previas se aplican al la matrice del ModelView
	//glMatrixMode(GL_MODELVIEW);
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
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP2 bis OpenGL : Bresenham"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint); 
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMotionFunc(&OnMouseMotion);
	glutMouseFunc(&OnMouseClick);
	glutIdleFunc(&idle);

	glutMainLoop(); //bucle de rendering
	//gl vertex 2d	
	return 0;
}
