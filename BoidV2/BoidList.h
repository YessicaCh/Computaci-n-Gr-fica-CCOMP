class BoidList {

public:
	void setup(float _width, float _height, float _near, float _far, int n, int _posSize);
	void add();
	void addBoid(Boid* b);
	void update(bool aW);
	void draw();
	vector<ofxVec3f> getTrailPoints(int boidIdx);
	
	static const int YES = 0;
	static const int NO = 1;	
	
	float width;
	float height;
	float near;
	float far;
	vector<Boid*> boids;
	float h;

};
void BoidList::setup(float _width, float _height, float _near, float _far, int n, int _posSize) {
	
	width = _width;
	height = _height;
	near = _near;
	far = _far;
	
	for (int i = 0; i < n; i++) {
		float maxSpeed = ofRandom(4, 6);
		float maxSteerForce = ofRandom(0.01, 0.07);		
		Boid* b = new Boid();
		b->setup(width, height, near, far, ofxVec3f(width/2, height/2, (near+far)/2),
				 maxSpeed, maxSteerForce, _posSize);
		boids.push_back(b);
	}

}

void BoidList::add() {

	Boid* b = new Boid();
	b->setup(width, height, near, far, ofxVec3f(width/2, height/2, 0));
	boids.push_back(b);

}

void BoidList::addBoid(Boid* b) {

	boids.push_back(b);

}

void BoidList::update(bool aW) {

	for (int i = 0; i < boids.size(); i++) {
		Boid* tmpBoid = boids[i];
		//tmpBoid->h = h;
		tmpBoid->avoidWalls = aW;
		tmpBoid->update(boids);
	}

}

void BoidList::draw() {

	for (int i = 0; i < boids.size(); i++) {
		Boid* tmpBoid = boids[i];
		tmpBoid->draw();
	}

}

vector<ofxVec3f> BoidList::getTrailPoints(int boidIdx) {

	Boid* b = boids[boidIdx];
	return b->poss;

}