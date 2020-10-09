#include "ofApp.h"


int main()
{
	ofSetupOpenGL(1000, 1000, OF_WINDOW);
	return ofRunApp(std::make_shared<ofApp>());
}
