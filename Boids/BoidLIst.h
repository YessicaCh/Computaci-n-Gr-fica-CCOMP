#include "Boid.h"

class BoidList {

	public:

		float width;
		float height;
		float znear;
		float far;
		vector<Boid*> boids;
		float h;

	public:
		BoidList();
		void setup(float _width, float _height, float _zn);
		void add();
		void addBoid(Boid* b);
		std::vector<Boid*> update(std::vector<Boid*> grupo,vector<vector3d> Obstaculos);
		void draw();
		~BoidList();

};
BoidList::BoidList(){}
BoidList::~BoidList(){
	for(int i=0;i<boids.size();i++){
		delete boids[i];
	}

}
void BoidList::setup(float _width, float _height, float _zn){
    width = _width;
	height = _height;
	znear = _zn;
}
void BoidList::addBoid(Boid* b){
	    float maxSpeed = randome(0.5,1.5);
		float maxSteerForce = randome(0.01, 0.07);	
		vector3d acelera(randome(0.5,1.0),randome(0.5,1.0),randome(0.5,1.0));
		b->setUp(width,height,znear,maxSpeed,maxSteerForce,(width/27),acelera);
	    boids.push_back(b);
}
std::vector<Boid*> BoidList::update(std::vector<Boid*> grupo,vector<vector3d> Obstaculos){
	
	cout<<endl;
	//cout<<"update list ************************** "<<boids.size()<<endl;
	//cout<<"grupo"<<grupo.size()<<endl;
	//cout<<"Obstaculos"<<Obstaculos.size()<<endl;
	cout<<endl;
	std::vector<Boid*> boidReOrg;
	for (int i = 0; i < boids.size(); i++) {
		Boid* tmpBoid = boids[i];
		if(tmpBoid->update(grupo,Obstaculos)==0)
		{  //cout<<" 0 ";
           boidReOrg.push_back(tmpBoid);
		}
	}
   //eliminar de este grupo para poner en otro
	for(int i=0;i<boidReOrg.size();i++){

        for(int j=0;j<boids.size();j++){
        	if(boidReOrg[i]->pos.x==boids[j]->pos.x and boidReOrg[i]->pos.y==boids[j]->pos.y and boidReOrg[i]->pos.z==boids[j]->pos.z )
		        {  boids.erase(boids.begin()+j);
		           break;
		        }
	        }
	}
	return boidReOrg;
}
void BoidList::draw(){
	for (int i = 0; i < boids.size(); i++) {
		Boid* tmpBoid = boids[i];
		tmpBoid->draw();
	}
}