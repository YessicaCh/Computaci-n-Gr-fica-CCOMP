#include <iostream>
#include <FreeImage.h>
#include "GL/glut.h"
#include "vector3d.h"
#include "red.h"
#include "TextureManager.h"

using namespace std;

class Boid
{	
	public://Atributos 
    	vector3d pos;					//posicion de ubicacion
    	vector3d acel;					//aceleracion
    	vector3d veloc;	
    	vector3d dir;
    	vector<Boid*> Boids;
    	vector<vector3d> Obst;
    	GLint  TexturaPez, OBS;				
	    float radius;
        float bodySize;
        float visionAngle;
        float w,h,zm,MaxSpeed,maxForce;  
	public:  //metodos
		Boid();
		Boid(vector3d mPosition);
		///Boid(float mRadius, float mVisionAngle, float mDirection, vector3d mPosition);
		vector3d Regla1();
		vector3d Regla2();
		vector3d Regla3();
		void setUp(float weight,float height,float prof,float maxSpeed,
				   float _maxForce,float mRadius,vector3d aceleracion);
		bool update(vector<Boid*> boides,vector<vector3d> Obstaculos);
		bool checkPos(vector3d posAnt);
		void draw();
		void flock();
		void move();
		void checkBounds();
		void print();
		//bool dif(Boid b);//aquii deberia sobracargar Operador

};
Boid::Boid(){
	pos.x=0;pos.y=0;pos.z=0;
	//TexturaPez = TextureManager::Inst()->LoadTexture("pescado.png", GL_BGR_EXT, GL_RGB);
}
Boid::Boid(vector3d mPosition){
	pos.x=mPosition.x;pos.y=mPosition.y;pos.z=mPosition.z;
	veloc.x=0;veloc.y=0;veloc.z=0;
	acel.x=0;acel.y=0;acel.z=0;
	TexturaPez = TextureManager::Inst()->LoadTexture("pescadito.jpeg", GL_BGR_EXT, GL_RGB);
}
void Boid::setUp(float weight,float height,float prof,float maxSpeed,
				 float _maxForce,float mRadius,vector3d aceleracion){
  w=weight;
  h=height;
  zm=prof;
  MaxSpeed=maxSpeed;
  maxForce=_maxForce;
  radius=mRadius;
  visionAngle=120;
  acel.x=aceleracion.x;acel.y=aceleracion.y;acel.z=aceleracion.z;
}
//Regla de 
//cohesion 
vector3d Boid::Regla1(){
    vector3d posSum(0,0,0);
    int cont=0;
    for(int i=0;i<Boids.size();i++)
    {   
    	float d=dist(pos,Boids[i]->pos);
        if(d>0 and d<=radius){
        		posSum.add(Boids[i]->pos);
        		cont++;
        	 }    	
    }
    if(cont>0){
    	 posSum.div(cont);
    	 posSum.sub(pos);
    	 posSum.limit(maxForce);
    	 //
    	 return posSum;
    }
    else{
    	vector3d tmpPosSum(0,0,0);
    	return tmpPosSum;
    }
    
    //cout<<"Boid j-->";Boids[j]->pos.print();cout<<endl;
   // posSum.sub(Boids[j]->pos);
    //return posSum;
}
//SEPARACION
vector3d Boid::Regla2(){ //Separation
   // vector3d R(0,0,0);
    vector3d  C(0,0,0);
    vector3d steer(0,0,0);
    float cercania=70.0f;
    int cont=0;

    for (int i = 0; i < Boids.size(); ++i)
    {   
            float d=dist(pos,Boids[i]->pos);
            if(d>0 and d<cercania)
            {   vector3d dif=pos;
            	dif.sub(Boids[i]->pos);
            	dif.normalize();
                dif.div(d);
                steer.add(dif);
                cont++;
            }
    }
    for (int i = 0 ; i <Obst.size(); i++)
        {
            vector3d other = Obst[i];
            float d = dist(pos,other);
            if ((d > 0) && (d < cercania))
            {
                // Calculate vector pointing away from neighbor
                vector3d diferencia = pos;
                diferencia.sub(other);
                diferencia.normalize();
                diferencia.div(d);
                steer.add(diferencia);
                
                //sum+=diferencia;
                //diferencia.div(d);        // Weight by distance
                //sum.add(diferencia);
                cont++;            // Keep track of how many
            }
        }
    if(cont>0)
    	steer.div(cont);
    if(steer.magnitude()>0){
    	steer.normalize();
    	steer.mult(MaxSpeed);
    	steer.sub(veloc);
    	steer.limit(maxForce);
    }
    return steer;
}
//aliniamiento 
vector3d Boid::Regla3(){ //Separation
    vector3d  velSum(0,0,0);
    int cont=0;

    for (int i = 0; i < Boids.size(); ++i)
    {   
        float d=dist(pos,Boids[i]->pos);
        if(d>0 and d<=radius){

            // Boids[i]->veloc.mult(2);
             velSum.add(Boids[i]->veloc);
             cont++;
        }  
        
    }
    if(cont>0){
    	velSum.div(cont);
    	velSum.normalize();
    	velSum.mult(MaxSpeed);

    	vector3d steer=velSum;
    	steer.sub(veloc);
    	steer.limit(maxForce);
    	return steer;
    }
    else{
    	vector3d tmp(0,0,0);
    	return tmp;
    }
    //pvj.div(Boids.size());
    //pvj.sub(Boids[j]->veloc);
    //return velSum;
}
bool Boid::checkPos(vector3d posAnt){
	int L=w/3;
   if((int)(posAnt.x/L)==(int)(pos.x/L) and (int)(posAnt.y/L)==(int)(pos.y/L) and (int)(posAnt.z/L)==(int)(pos.z/L))
   	  return 1;
   else
   	  return 0;
}
bool Boid::update(vector<Boid*> boides,vector<vector3d> Obstaculos){
  
	Boids=boides;
	Obst=Obstaculos;
    //cout<<"Primera posicion ";
    //pos.print();
    vector3d posAnt=pos;
	flock();
	move();
	checkBounds();
	//cout<<"Posicion  cambiante ";
	//pos.print();
    //cout<<"           "<<endl;
    //pos.print();
    return checkPos(posAnt);

}
void Boid::flock(){
		vector3d v1,v2,v3,v4;
		
	    	//Boids[i]->pos.print();
	    	v1=Regla2();//separacion
	    	//cout<<"Regla1 "<<endl;
	    	//v1.print();
	    	//cout<<"................... "<<endl;
	    	v2=Regla3();//alineamiento
	    	//cout<<"Regla2 "<<endl;
	    	//v2.print();
	    	//cout<<"................... "<<endl;
	    	v3=Regla1();//cohesion
	    	//cout<<"Regla3 "<<endl;
	    	//v3.print();
	    	//cout<<"................... "<<endl;
	    	veloc.add(v1);
			veloc.add(v2);
			veloc.add(v3);
			pos.add(veloc);
}
void Boid::print(){
	cout<<" P: ("<<pos.x<<","<<pos.y<<","<<pos.z<<")"<<endl;
}
void Boid::move(){
	veloc.add(acel);
	veloc.limit(MaxSpeed);
	pos.add(veloc);
	acel.mult(0.0);
}
void Boid::checkBounds(){
	 if (pos.x > w) pos.x -= w;
    if (pos.x < 0) pos.x += w;
    if (pos.y > h) pos.y -= h;
    if (pos.y < 0) pos.y += h;
    if (pos.z > zm)pos.z -= zm;
    if (pos.z < 0) pos.z += zm;


	/*if (pos.x > w) pos.x = 10;
	if (pos.x < 0) pos.x = (w-10);
	if (pos.y > h) pos.y = 10;
	if (pos.y < 0) pos.y = (h-10);
	if (pos.z > zm)pos.z = 10;
	if (pos.z < 0) pos.z = (zm-10);


    if (pos.x > w) pos.x -= w;
    if (pos.x < 0) pos.x += w;
    if (pos.y > h) pos.y -= h;
    if (pos.y < 0) pos.y += h;
    if (pos.z > zm)pos.z -= zm;
    if (pos.z < 0) pos.z += zm;*/

}
void Boid::draw(){
	//cout<<"Boid position ("<<pos.x<<","<<pos.y<<","<<pos.z<<")"<<endl;
	//cout<<" -->aceleracion :"<<acel.x<<","<<acel.y<<","<<acel.z<<")"<<endl;
	glColor3f(0.0f,0.0f,1.0f);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    int a=4;
	int b=6;
	int c=7;

	glBindTexture(GL_TEXTURE_2D,TexturaPez);
    glPushMatrix();
    	glTranslatef(pos.x,pos.y,pos.z);
	    	glBegin(GL_TRIANGLES);
				//glNormal3d(0, 0, -1);
	    	    glVertex3f(0,0,0);
	    	    glTexCoord2f(0.0, 0.0);

	    	    glVertex3f(5,-5,5);
	    	    glTexCoord2f(0.0, 1.0);

	    	    glVertex3f(9,0,0);
	    	    glTexCoord2f(1.0, 0.0);


	    	    glVertex3f(0,0,0);
	    	    glVertex3f(5,-5,-5);
	    	    glVertex3f(9,0,0);
	    	    

				/*glVertex3f(a,b,-c);
				glVertex3f(-a,b,-c);
				glVertex3f(0,b*1.5,-c);*/
				//
				//glNormal3d(0, 0, 1);
				/*glVertex3f(a,b,c);
				glVertex3f(0,b*1.5,c);
				glVertex3f(-a,b,c);*/
		    glEnd();
       // gluCylinder(quadratic,1,1,2,6,6);
    glPopMatrix();
    
	
}