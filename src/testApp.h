#pragma once

#include "ofMain.h"
#include "ofx3DModelLoader.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxEasyFft.h"
#include "ofxFTGLFont.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofx3DModelLoader squirrelModel;
        ofxAssimpModelLoader model;
    
        bool bAnimate;
        bool bAnimateMouse;
        float animationPosition;
    
        ofMesh mesh;
        ofLight	light;
    
        void plot(vector<float>& buffer, float scale);
        ofxEasyFft fft;
    
        ofxFTGLFont font;
        string str;
        vector<ofVec2f> points;
    
        void drawFboTest(); // draws some test graphics into the two fbos
        ofFbo rgbaFbo; // with alpha
    
        ofShader shader;
    
        void drawViewportOutline(const ofRectangle & viewport);
        ofRectangle viewport2D;
    
    private:
        int sample_tone;
        int sample_level;
        ofCamera    cam;

};
