#include "ofApp.h"


//Heavily used code from https://github.com/SAIC-ATS/ARTTECH-3135/tree/master/Session_03/Flailer for the tail movement.

void ofApp::setup()
{
	tail.load("img/tail.png");
	head.load("img/head.png");
	body.load("img/body.png");
	feet.load("img/feet.png");

	tails = { tail, tail, tail, tail, tail };
	angles = { -120, -80, -50, -50, -60 };
	anglesMinimum = { -120, -80, -50, -50, -60 };
	anglesMaximum = { -90, -40, -50, 60, 60 };
	anglesNoiseIncrement = { 0.003, 0.003, 0.003, 0.001, 0.001 };
	anglesNoiseOffsets = { 1, 1, 1, 1, 1 };
	anglesNoiseScales = { 1, 1, 2, 3, 5 };
	isNewSegment = { false, false, false, false, false };

}


void ofApp::update()
{
	// Loop through all of the images!
	for (std::size_t i = 0; i < tails.size(); i++)
	{
		// This is how we move through the Perlin noise. We adjust the offset
		// just a tiny bit to get the next value in the neighborhood of noise.
		anglesNoiseOffsets[i] += anglesNoiseIncrement[i];

		// ... next we ask for the noise at the current offset. It will be a
		// value between -1 and 1 for ofSignedNoise.
		float noiseAtOffset = ofSignedNoise(anglesNoiseOffsets[i]);

		// ... next we scale the noise by multiplying it by a scaler.
		noiseAtOffset *= anglesNoiseScales[i];

		// Now add some noise to the angle.
		angles[i] = angles[i] + noiseAtOffset ;

		// Now clamp the angle values to keep them in a reasonable range.
		angles[i] = ofClamp(angles[i], anglesMinimum[i], anglesMaximum[i]);
	}
}


void ofApp::draw()
{
	ofBackground(38);
	ofDrawBitmapString("Drag the cat around with mouse.", 100, 100);
	//draw main body parts
	ofPushMatrix();

		ofTranslate(draggedX - body.getWidth()/3.0, draggedY - body.getHeight()/3.0);
		ofScale(0.5, 0.5, 1);

			//body breathing
			ofPushMatrix();
			float bodyBreathe = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, -20);
			ofTranslate(0, bodyBreathe);
			body.draw(0, 0);
			ofPopMatrix();

			ofPushMatrix();
				
			//hard calculating the positions of different parts instead of using image.getWidth() because the assets I drew weren't made with size and position relationship in mind.
				feet.draw(-70, 180);

					ofPushMatrix();

						head.draw(-50, 30);
		
					ofPopMatrix();
			ofPopMatrix();
					
		//ofPushMatrix();
		//	
		//ofTranslate(700, 350);
		//ofRotateZDeg(-120);
		//tail.draw(0, 0);

		//ofPopMatrix();


		ofPushMatrix();

		ofTranslate(700, 350);

		// Loop through all o fthe images.
		for (std::size_t i = 0; i < tails.size(); i++)
		{
			// If we want to have different attachment points, we must push (or not
			// push) a new transoformation matrix.
			if (isNewSegment[i])
			{
				ofPushMatrix();
			}

				ofRotateZDeg(angles[i]);

				tails[i].draw(-tails[i].getWidth() / 3,
					-tails[i].getWidth() / 3);


				ofTranslate(0, tails[i].getHeight());

			// If we pushed a new matrix, go ahead and pop it off again.
			if (isNewSegment[i])
			{
				ofPopMatrix();
			}
		}

		ofPopMatrix();

	ofPopMatrix();




}

void ofApp::mouseDragged(int x, int y, int button) {

	//cout << "test   " << x << " , " << y << endl;
	draggedX = x;
	draggedY = y;
}