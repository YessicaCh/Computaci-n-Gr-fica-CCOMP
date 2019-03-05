#ifndef VECTOR3D_H_
#define VECTOR3D_H_
#include <iostream>
#include <math.h>
using namespace std;
class vector3d
{
	public:
		float x;
		float y;
		float z;
    public:
		vector3d(){
			x=0.0;
			y=0.0;
			z=0.0;	
		}
		vector3d(float a,float b,float c){
			x=a;
			y=b;
			z=c;
		}
		void mult(float a){
			x*=a;
			y*=a;
			z*=a;
		}	
		void div(float n){
			x/=n;
			y/=n;
			z/=n;
		}	
		void sub(vector3d a){
			x-=a.x;
			y-=a.y;
			z-=a.z;
		}
		void add(vector3d a){
			x+=a.x;
			y+=a.y;
			z+=a.z;
		}
		void limit(float m){
			double size = magnitude();

		    if (size > m) {
		    	x=x/size;
		    	y=y/size;
		    	z=z/size;
		       
		    }
			
		}
		float magnitude(){
			    return sqrt(x*x + y*y + z*z);
			}

		void normalize(){  //vector normalizado;
			float m=magnitude();
			if (m>0)
			{
				div(m);
			}
		}	
		void print(){
			cout<<" ("<<x<<","<<y<<","<<z<<") "<<endl; }
			
};
#endif