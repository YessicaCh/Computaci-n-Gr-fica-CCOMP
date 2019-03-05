#ifndef RED_H_
#define RED_H_
#include "GL/glut.h"
#include "vector3d.h"
#include <cmath>
#include <stdio.h>

 bool LEFT = false;
 bool RIGHT = true;
float MAXJUMPHEIGHT = 20;
//const float MINJUMPHEIGHT = 2;
//const float MAXJUMPTIME = 0.44;
float GRAVITY = -2;
//const float JUMPVELOCITY = sqrtf(2 * GRAVITY * MAXJUMPHEIGHT);

float TIME;
float NEWTIME;
float DTTIME;
float modV(vector3d v){
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}
double degToRad(double deg){
	return deg * M_PI / 180.0;
}
float randome(float a,float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

//**********************extras
float dist(vector3d a, vector3d b){
      float tmpX=b.x-a.x;
      float tmpY=b.y-a.y;
      float tmpZ=b.z-a.z;

      return sqrt(tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ);
}
//*********************!= diferentes posiciones
bool dif(vector3d a, vector3d b){
      if(a.x!=b.x and a.y!=b.y and  a.z!=b.z)
      	return 1;
      else
          return 0;
}
#endif
