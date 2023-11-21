#include "ofApp.h"



#define numOfParts 1600
#define numOfColors 5
#define numOfDimension 2
#define RADIUS 3
#define HALFLIFE 0.2f
#define Beta 0.4f
#define Rmax 80.0f

float h[NumColors][NumColors] = {
	{0.8, -0.5, 0.8, -0.5, -0.5, -0.5},
	{-0.5, 0.8, -0.5, -0.5, -0.5, -0.5},
	{-0.5, -0.5, 0.8, -0.5, -0.5, -0.5},
	{-0.5, -0.5, -0.5, 0.8, -0.5, -0.5},
	{-0.5, -0.5, -0.5, -0.5, 0.8, -0.5},
	{-0.5, -0.5,-0.5, -0.5,-0.5, 0.8}
	
};

vector<Particle*> p;
BehaviorMatrix bm(h);



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	ofSetCircleResolution(80);


	

	for (int i = 0; i < numOfParts; i++) {
		float x = ofRandom(ofGetWidth());
		float y = ofRandom(ofGetHeight());
		p.push_back(new Particle( ofVec2f(x, y), static_cast<Colors>(ofRandom(0, NumColors))));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < p.size(); i++) {
		Particle* a = p[i];
		
		ofVec2f acceleration;
		for (int j = 0; j < p.size(); j++) {
			if (j == i) continue;
			ofVec2f vec = (p[j]->Position - a->Position);
			float dist = vec.length();

			acceleration += vec.normalized() * CalculateForce(dist / Rmax, bm.getAttraction(a->myColor, p[j]->myColor));

			
			 
		}
		//ofVec2f fj = (ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2) - a->Position).normalized() * 10;
		//if (ofRandomf() > 0.99) { p.push_back(new Particle(a->Position, static_cast<Colors>(ofRandom(0, NumColors)))); }
		a->Update(ofGetLastFrameTime(), (Rmax * acceleration) /*+ fj*/);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (auto& particle : p) {
		particle->Draw();
	}
}

float CalculateForce(float distance, float attraction) {
	if (distance < Beta) {
		return ((distance / Beta) - 1);
	}
	else if (Beta < distance && distance < 1) {
		return attraction * (1 - abs( (2 * distance) - 1 - Beta) / (1 - Beta));
	}
	else {
		return 0;
	}
}

void ofApp::keyPressed(int key) {
	if (key == OF_KEY_UP) {
		bm = BehaviorMatrix();
	}
}


BehaviorMatrix::BehaviorMatrix(float a[NumColors][NumColors])
{
	matrix = new float* [NumColors];
	for (int i = 0; i < NumColors; i++) {
		matrix[i] = new float[NumColors];
		for (int j = 0; j < NumColors; j++) {
			matrix[i][j] = a[i][j];
		}
	};

}

BehaviorMatrix::BehaviorMatrix()
{
	matrix = new float* [NumColors];
	for (int i = 0; i < NumColors; i++) {
		matrix[i] = new float[NumColors];
		for (int j = 0; j < NumColors; j++) {
			matrix[i][j] = ofRandomf();
		}
	};

}


float BehaviorMatrix::getAttraction(Colors a, Colors b)
{
	return matrix[a][b];
}

void Particle::Update(float deltaTime, ofVec2f Force)
{
	Position = InsideScreen(Position, ofVec2f(ofGetWidth(), ofGetHeight()));
	float mew = pow(0.5, (deltaTime / HALFLIFE));
	Velocity = (mew * Velocity) + (Force * deltaTime);
	Position = Position + (Velocity * deltaTime);

}

void Particle::Draw()
{
	ofSetColor(c);
	ofDrawCircle(Position, RADIUS);
}

Particle::Particle(ofVec2f startPos, Colors color)
{
	myColor = color;
	c = colorLookUp[color];
	Position = startPos;
	Velocity = ofVec2f(0, 0);
}

float Gaussian(float x, float sd, float mean)
{
	float a = 1 / (sd * sqrt(2 * PI));
	float expComp = -pow((x - mean) / sd, 2) / 2;
	float e = expf(expComp);
	return a * e;
}

ofVec2f InsideScreen(ofVec2f p, ofVec2f _sRegion) {
	if (p.x < 0) {
		p.x = 0;
	}
	if (p.x > _sRegion.x) {
		p.x = _sRegion.x;
	}if (p.y < 0) {
		p.y = 0;
	}
	if (p.y > _sRegion.y) {
		p.y = _sRegion.y;
	}
	return p;

		
}
