#pragma once


#include "ofMain.h"


class ofApp : public ofBaseApp
{
public:
	void setup() override;
	void update() override;
	void draw() override;

	void mouseDragged(int x, int y, int button) override;

	ofImage tail;
	ofImage head;
	ofImage body;
	ofImage feet;

	std::vector<ofImage> tails;
	std::vector<float> angles;
	std::vector<float> anglesMinimum;
	std::vector<float> anglesMaximum;
	std::vector<float> anglesNoiseIncrement;
	std::vector<float> anglesNoiseOffsets;
	std::vector<float> anglesNoiseScales;
	std::vector<bool> isNewSegment;

	int draggedX = 400;
	int draggedY = 600;

};
