#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

#define KEY_ESC 27
int var;

//dibuja un simple gizmo
void displayGizmo()
{
    glBegin(GL_LINES);
    glColor3d(255,0,0);
    glVertex2d(0, 0);
    glVertex2d(1, 0);
    glColor3d(0, 255, 0);
    glVertex2d(0, 0);
    glVertex2d(0, 1);
    glEnd();
}

//ROJO
//1. Elaborar una función que permite crear un cuadrado gracias a una línea cerrada. Esta función tomara como parámetro, su centro y el tamaño de su arista.

void displayCuadrado(float x, float y, float tamArista)
{
    /*    1              2
     *     ------------
     *     |          |
     *     |    xy    |      
     *     |          |
     *     ------------
     *   4              3
     */
    glBegin(GL_LINE_LOOP);
    //Lateral 1
    glColor3d(255,0,0);
    glVertex2d(x-tamArista/2,y+tamArista/2);
    //Lateral 2
    glColor3d(255,0,0);
    glVertex2d(x+tamArista/2,y+tamArista/2);
    //Lateral 3
    glColor3d(255,0,0);
    glVertex2d(x+tamArista/2,y-tamArista/2);
    //Lateral 4
    glColor3d(255,0,0);
    glVertex2d(x-tamArista/2,y-tamArista/2);
    glEnd();

}
/// VERDE
///2. Elaborar una función que permite crear un círculo gracias a una línea cerrada. Esta función tomara como parámetro, su centro y su radio.
void displayCirculo(float x, float y, float tamRadio)
{
    glColor3d(0,255,0);
    glBegin(GL_LINE_LOOP);
    for (double ii = 0.0; ii < 10; ii+=0.01)   
        {
            float theta = 2.0f * 3.1415926f * float(ii) / float(10);//angulo actual
            float xn = tamRadio * cosf(theta) + x;//calcular la componente x
            float yn = tamRadio * sinf(theta) + y;//calcular la componente y 
            glVertex2f(xn , yn);//vertice saliente
        } 
    glEnd();

}

///AZUL
///3. Elaborar una función en OpenGL que permite obtener el resultado siguiente :Circulo de cìrculo
///La cantidad de círculos y el porcentaje de reducción del radio serán definidos por el usuario.
void displayCirculos(float x, float y, float tamRadio/*Ini*/, int num, float reduc)
{
    glColor3d(0,0,255);
    glBegin(GL_LINE_LOOP);
    for(int i =0; i<num; i++)
    {   float reduccion=tamRadio*reduc/100;
        glBegin(GL_LINE_LOOP);
            for (double ii = 0.0; ii < 10; ii+=0.01)   
                {
                    float theta = 2.0f * 3.1415926f * float(ii) / float(10);//angulo actual
                    float xn = tamRadio * cosf(theta) + /*abs(*/x/*)*/;//calcular la componente x
                    float yn = tamRadio * sinf(theta) + y;//calcular la componente y 
                    glVertex2f(xn , yn);//vertice saliente
                } 
            //cout<<x<<"-="<<tamRadio<<"/(100/"<<reduc<<")"<<endl;
            /*abs(*/x -= tamRadio/(100/reduc)/*)*/;
            /*abs(*/tamRadio-=reduccion/*)*/;
        glEnd();
    }
}

/// AMARILLO
///4. Elaborar una función en OpenGL que permite obtener el resultado siguiente : circulos decrecientes
///El primer círculo es el de la izquierda. La cantidad de círculos y el porcentaje de reducción del radioserán definidos por el usuario.
void displayCirculosDec(float x, float y, float tamRadio/*Ini*/, int num, float reduc)
{
    glColor3d(100,100,0);
    glBegin(GL_LINE_LOOP);
    for(int i =0; i<num; i++)
    {   float reduccion=tamRadio*reduc/100;
        glBegin(GL_LINE_LOOP);
            for (double ii = 0.0; ii < 10; ii+=0.01)   
                {
                    float theta = 2.0f * 3.1415926f * float(ii) / float(10);//angulo actual
                    float xn = tamRadio * cosf(theta) + x;//calcular la componente x
                    float yn = tamRadio * sinf(theta) + y;//calcular la componente y 
                    glVertex2f(xn , yn);//vertice saliente
                } 
            
            x += tamRadio*2-reduccion;
            tamRadio-=reduccion;
        glEnd();
    }
}

/// CELESTE
///4. Elaborar una función en OpenGL que permite obtener el resultado siguiente : circulos decrecientes diagonal
///La cantidad de círculos, el porcentaje de reducción del radio y el Angulo serán definidos por el usuario.
vector<pair<float,float>> arr;
void displayCirculosDiag(float x, float y, float tamRadio/*Ini*/, int num, float reduc, float angulo)
{
    glColor3d(0,100,100);
    glBegin(GL_LINE_LOOP);
    float m= tanf(angulo);
    arr.push_back(make_pair(x,y));
    for(int i =0; i<num; i++)
    {   float xn,yn; 
        float reduccion=tamRadio*reduc/100;
        glBegin(GL_LINE_LOOP);
            for (double ii = 0.0; ii < 10; ii+=0.01)   
                {
                    float theta = 2.0f * 3.1415926f * float(ii) / float(10);//angulo actual
                    //cout<<"Angulo"<<theta;
                    xn = tamRadio * cosf(theta) + x;//calcular la componente x
                    yn = tamRadio * sinf(theta) + y;//calcular la componente y 
                    glVertex2f(xn , yn);//vertice saliente
                } 
        glEnd();    
            float xa=x;
            x =(tamRadio+(tamRadio-reduccion) )* cosf(angulo) + x;
            y +=m*(x-xa);
            tamRadio-=reduccion;
            arr.push_back(make_pair(x,y));
            
        
    }
}
void Line()
{
    glColor3d(0,0,255);
    glBegin(GL_LINE_STRIP);
    for(int i =0; i<arr.size()-1; i++)
    {
        glVertex2f(arr[i].first, arr[i].second);   
    }
    glEnd();
    glPointSize(2.5);
    glBegin(GL_POINTS);
    glColor3f(0.1f,0.5f,0.9f);
     
    for(int i =0; i<arr.size()-1; i++)
    {
        glVertex3f(arr[i].first,arr[i].second,0.0f);
    }
     glEnd();

}

void glPaintDefault(void){

    //dibuja el gizmo
    displayGizmo();

    //dibuja el cuadrado
    displayCuadrado(-20,10,5);

    //dibuja el circulo
    displayCirculo(0,10,5);

    //dibuja el circulos
    displayCirculos(20,10,5,5,20);

    //dibuja el circulos decrecientes
    displayCirculosDec(-20,-10,5,5,20);

    //dibuja el circulos decrecientes con angulo
    //displayCirculosDiag(0,0,5,5,1,0);
    //displayCirculosDiag(0,0,5,5,1,45);
    arr.clear();
    displayCirculosDiag(-20,-40,5,5,20,45*3.1415926f/180);
    Line();
    arr.clear();
    displayCirculosDiag(20,-40,5,5,50,70*3.1415926f/180);

} 
void glPaintInterface(void) {
    float x,y,tam,red,ang;
    int num;
    //El fondo de la escena al color initial
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
    switch ( var) {
    case 1:
        cout<<"Centro x: ";
        cin>>x;
        cout<<"Centro y: ";
        cin>>y;
        cout<<"Tamanho de arista: ";
        cin>>tam;
        //dibuja el cuadrado
        displayCuadrado(x,y,tam);
    break;
    case 2:
        cout<<"Centro x: ";
        cin>>x;
        cout<<"Centro y: ";
        cin>>y;
        cout<<"Tamanho de radio: ";
        cin>>tam;
        //dibuja el circulo
        displayCirculo(x,y,tam);
    break;
    case 3:
        cout<<"Centro x: ";
        cin>>x;
        cout<<"Centro y: ";
        cin>>y;
        cout<<"Tamanho de radio inicial: ";
        cin>>tam;
        cout<<"Numero de circulos: ";
        cin>>num;
        cout<<"Porcentaje de reduccion sobre 100% : ";
        cin>>red;
        //dibuja el circulos
        displayCirculos(x,y,tam,num,red);
    break;
    case 4:
        //dibuja el circulos decrecientes
        cout<<"Centro x: ";
        cin>>x;
        cout<<"Centro y: ";
        cin>>y;
        cout<<"Tamanho de radio inicial: ";
        cin>>tam;
        cout<<"Numero de circulos: ";
        cin>>num;
        cout<<"Porcentaje de reduccion sobre 100%: ";
        cin>>red;
        //dibuja el circulos
        displayCirculosDec(x,y,tam,num,red);
    break;
    case 5:
        cout<<"Centro x: ";
        cin>>x;
        cout<<"Centro y: ";
        cin>>y;
        cout<<"Tamanho de radio inicial: ";
        cin>>tam;
        cout<<"Numero de circulos: ";
        cin>>num;
        cout<<"Porcentaje de reduccion sobre 100%: ";
        cin>>red;
        cout<<"Angulo de inclinacion: ";
        cin>>ang;
        //dibuja el circulos decrecientes con angulo
        arr.clear();
        displayCirculosDiag(x,y,tam,num,red,ang*3.1415926f/180);
        Line();
        arr.clear();
    break;
    case 0:
        glPaintDefault();
    break;
    }
    glutSwapBuffers();
}
void Interface(){
    //glPaintDefault();

    cout<<endl<<endl<<endl<<"_______________________________________"<<endl;
    cout<<"   Practica: Introducción a OpenGL"<<endl;
    cout<<"_______________________________________"<<endl;
    cout<<"Presione el numero de ejercico"<<endl;
    cout<<"0 -> Muestra inicial"<<endl;
    cout<<"1 -> Primer ejercico"<<endl;
    cout<<"2 -> Segundo ejercico"<<endl;
    cout<<"3 -> Tercer ejercico"<<endl;
    cout<<"4 -> Cuarto ejercico"<<endl;
    cout<<"5 -> Quinto ejercico"<<endl;
    cout<<"_______________________________________"<<endl;
    cin>>var;
    glPaintInterface();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Interface();


}
//funcion llamada a cada imagen
void glPaint(void) {

    //El fondo de la escena al color initial
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
    glLoadIdentity();
    var=0;
    glPaintInterface();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Interface();
    //glutDisplayFunc(glPaintInterface);
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

    glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
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
    glutCreateWindow("TP1 OpenGL : Practica 1"); //titulo de la ventana

    init_GL(); //funcion de inicializacion de OpenGL

    glutDisplayFunc(glPaint);
    glutReshapeFunc(&window_redraw);
    // Callback del teclado
    glutKeyboardFunc(&window_key);

    glutMainLoop(); //bucle de rendering

    return 0;
}