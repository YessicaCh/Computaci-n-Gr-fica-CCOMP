#include <iostream>
#include <vector>
#include <FreeImage.h>
//#include "Boid.h"
//#include "red.h"
//#include "vector3d.h"
#include "BoidLIst.h"
#include "TextureManager.h"
using namespace std;

class Flock                                                         //Clase que contiene a todos los peces
{
	public:         //Atributos
    	int boidsQuantity;
        int nBoidList;
        vector<vector<vector<BoidList*>>> Flocks;
        vector<vector3d> Obstaculos;
        GLint  Obst;  
        float width;
        float height;
        float znear;
        float L;
        int nGrill;

	public:         //Metodos 
		Flock();
		Flock(int mBoidsQuantity);
        void setup(float _width, float _height, float _zn);
		void initialize();
        void locateBoid();
        void drawObstaculo();
        void drawPecera();
		void drawBoids();
		void update();
        void list(int i,int j,int k,std::vector<Boid*> lista);
        std::vector<Boid*> listaBoids(int i,int j,int k);
        void applyForce(vector3d  a,int j);
        void limit_velocity(int j);
        vector3d Bound_position(int i);
        vector3d movement();
	
};
Flock::Flock(){  boidsQuantity = 10;}
Flock::Flock(int mBoidsQuantity){
	 this->boidsQuantity = mBoidsQuantity;    
}
void Flock::setup(float _width, float _height, float _zn){
    width = _width;
    height = _height;
    znear = _zn;
    nGrill=9;
    L=width/nGrill;
    initialize();
    //Obst = TextureManager::Inst()->LoadTexture("piedra2.jpg", GL_BGR_EXT, GL_RGB);
}
void Flock::initialize(){
    Flocks.resize(nGrill);
    for (int i = 0; i < nGrill; ++i)
    {   Flocks[i].resize(nGrill);
        for(int j=0;j<nGrill;j++){
            Flocks[i][j].resize(nGrill);
            for(int k=0;k<nGrill;k++){
                BoidList* flock = new BoidList();
                flock->setup(width,height,znear);
                Flocks[i][j][k]=flock;
            }
        }
    }
    // cout<<" vamos a poner obstaculo"<<endl;
     vector3d t1(75,25,75);
     vector3d t2(125,25,325);
     vector3d t3(325,25,275);
     Obstaculos.push_back(t1);
     Obstaculos.push_back(t2);
     Obstaculos.push_back(t3);
    //CREANDO LOS BOIDS 
	for(int i=0; i < boidsQuantity; ++i){
        //vector3d t(randome(5,width-10),randome(5,width-10),randome(5,width-10));
        vector3d t(width/2,height/2,znear/2);
        if((t.x!=75 and t.x!=125 and t.x!=325) and (t.y!=25) and (t.z!=75 and t.z!=325 and t.z!=275)){
        Boid* tmp=new Boid(t);
        Flocks[(int)(t.x/L)][(int)(t.y/L)][(int)(t.z/L)]->addBoid(tmp);
        }
       // cout<<" flocks("<<(int)(t.x/L)<<","<<(int)(t.y/L)<<","<<(int)(t.z/L)<<")"<<endl;
        //}
    }
    
}
void Flock::drawObstaculo(){
   glColor3f(1.0f,1.0f,1.0f);
    for(int i=0;i<Obstaculos.size();++i){
        glPushMatrix();
            glTranslatef(Obstaculos[i].x,Obstaculos[i].y,Obstaculos[i].z);
             glutSolidCube(25);
        glPopMatrix();
    } 
}
void Flock::drawPecera(){
           glColor3f(1.0f, 0.0f, 0.0f);
            //cara de atras 
            glBegin(GL_LINES);//l1
                glVertex3f(0.0f,0.0f,0.0f);
                glVertex3f(width, 0.0f, 0.0f);
            glEnd();
            
            glBegin(GL_LINES);//l2
                glVertex3f(width, 0.0f, 0.0f);
                glVertex3f(width, height, 0.0f);
            glEnd();
            glBegin(GL_LINES);//l3
                glVertex3f(width, height, 0.0f);
                glVertex3f(0.0f,height,0.0f);
            glEnd();
            glBegin(GL_LINES);//l4
                glVertex3f(0.0f,height,0.0f);
                glVertex3f(0.0f, 0.0f, 0.0f);
            glEnd();
            //laterales
             glBegin(GL_LINES);//l5
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, znear);
            glEnd();
             glBegin(GL_LINES);//l6
                glVertex3f(width, 0.0f, 0.0f);
                glVertex3f(width, 0.0f, znear);
            glEnd();
            glBegin(GL_LINES);//l7
                glVertex3f(width, height, 0.0f);
                glVertex3f(width, height, znear);
            glEnd();
    
            glBegin(GL_LINES);//l8
                glVertex3f(0.0f, height, 0.0f);
                glVertex3f(0.0f, height, znear);
            glEnd();

            //cara de adelante
            glBegin(GL_LINES);//l9
                glVertex3f(0.0f, 0.0f, znear);
                glVertex3f(width, 0.0f, znear);
            glEnd();
            
            glBegin(GL_LINES);//l10
                glVertex3f(width, 0.0f, znear);
                glVertex3f(width, height, znear);
            glEnd();
            glBegin(GL_LINES);//l11
                glVertex3f(width, height, znear);
                glVertex3f(0.0f,height,znear);
            glEnd();
            glBegin(GL_LINES);//l12
                glVertex3f(0.0f,height,znear);
                glVertex3f(0.0f, 0.0f, znear);
            glEnd();}
void Flock::update(){
    
    std::vector<Boid*> boidReOrg;
    std::vector<vector<Boid*>> v;
    for (int i = 0; i < Flocks.size(); i++) 
         for(int j=0;j<Flocks[i].size();j++)
             for(int k=0;k<Flocks[i][j].size();k++){
                     std::vector<Boid*> G=listaBoids(i,j,k);
                     boidReOrg=Flocks[i][j][k]->update(G,Obstaculos);
                     v.push_back(boidReOrg);
                 }
    
   //Reorganizando algunos boids
    for(int i=0;i<v.size();i++){
        std::vector<Boid*> temporal=v[i];
        for(int x=0;x<temporal.size();++x){

                            Boid* tmp=new Boid(temporal[x]->pos);
                            Flocks[(int)(tmp->pos.x/L)][(int)(tmp->pos.y/L)][(int)(tmp->pos.z/L)]->addBoid(tmp);
                           // cout<<" flocks("<<(int)(tmp->pos.x/L)<<","<<(int)(tmp->pos.y/L)<<","<<(int)(tmp->pos.z/L)<<")"<<endl;

        }
    }
}
void Flock::list(int i,int j,int k,std::vector<Boid*> lista){
    for(int x=0;x<Flocks[i][j][k]->boids.size();++x){
        lista.push_back(Flocks[i][j][k]->boids[x]);
    }
  
}
std::vector<Boid*> Flock::listaBoids(int i,int j,int k){
    std::vector<Boid*> lista;
    list(i,j,k,lista);
    if(i+1<=(nGrill-1)){
        list(i+1,j,k,lista);
        if(j+1<=(nGrill-1))
            list(i+1,j+1,k,lista);
        if(j-1>=0)
            list(i+1,j-1,k,lista);
       }
    if(i-1>=0){
        list(i-1,j,k,lista);
        if(j+1<=(nGrill-1))
            list(i-1,j+1,k,lista);
        if(j-1>=0)
            list(i-1,j-1,k,lista);
     }
     if(k+1<=(nGrill-1)){
        list(i,j,k+1,lista);
        if(j+1<=(nGrill-1))
            list(i,j+1,k+1,lista);
        if(j-1>=0)
            list(i,j-1,k+1,lista);
       }
     if(k-1>=0){
        list(i,j,k-1,lista);
        if(j+1<=(nGrill-1))
            list(i,j+1,k-1,lista);
        if(j-1>=0)
            list(i,j-1,k-1,lista);
     }
     if(j+1<=(nGrill-1))
            list(i,j+1,k,lista);
     if(j-1>=0)
            list(i,j-1,k,lista);
     return lista;
}
void Flock::drawBoids(){

	for (int i = 0; i < Flocks.size(); i++) 
         for(int j=0;j<Flocks[i].size();j++)
             for(int k=0;k<Flocks[i][j].size();k++)
                     Flocks[i][j][k]->draw();
     drawObstaculo();
     drawPecera();	
}

