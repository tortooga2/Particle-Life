#pragma once

#include "ofMain.h"

enum Colors {Red, Green, Purple, yellow, blue, pink, NumColors};


const ofColor colorLookUp[NumColors] = {
	ofColor(250, 0, 0),
	ofColor(0, 250, 0),
	ofColor(125, 0, 125),
	ofColor(252, 186, 3),
	ofColor(00, 00, 255),
	ofColor(255, 0, 208)

};

ofVec2f InsideScreen(ofVec2f, ofVec2f);

class BehaviorMatrix {
public:
	BehaviorMatrix();
	BehaviorMatrix(float[NumColors][NumColors]);
	float** matrix;
	float getAttraction(Colors, Colors);
	float getDefaultAttraction();
	//void RandomizeMatrix();

};


class Particle {
public:
	Colors myColor;
	ofColor c;
	ofVec2f Position;
	ofVec2f Velocity;


	void Update(float, ofVec2f);
	void Draw();

	Particle(ofVec2f, Colors);

};

float CalculateForce(float, float);
float Gaussian(float, float, float);


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);/*
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);*/
		
		
};




