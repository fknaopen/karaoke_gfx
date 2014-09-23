#include "testApp.h"

GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};

GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(50, 50, 50);
    ofSetVerticalSync(true);
    
    //some model / light stuff
   
    glShadeModel(GL_SMOOTH);
    
    /* initialize lighting */
    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);
    
    // assimpModel
    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    
    model.loadModel("astroBoy_walk.dae", true);
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    mesh = model.getMesh(0);
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    light.enable();
    ofEnableSeparateSpecularLight();
    ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);

    fft.setup(12000);
    
    ofEnableAlphaBlending();
    
    sample_level=0;
    sample_tone=540;
    
    cam.setNearClip(-100);
    cam.setFarClip(100);
    cam.enableOrtho();
    cam.setPosition(0,0,0);

    str = "サンプルテロップ";
	font.loadFont("mplus-1c-regular.ttf", 42, true);
    //font.loadFont("JiyunoTsubasa.ttf", 42, true);
    
    //allocate our fbos.
	rgbaFbo.allocate(1024, 200, GL_RGBA);
    
    rgbaFbo.begin();
	ofClear(255,255,255, 0);
    ofSetColor(255, 255, 255, 0xff);
    font.drawString(str, 0, 100);
    rgbaFbo.end();
}

//--------------------------------------------------------------
void testApp::update(){
    fft.update();
    //lets draw some graphics into our fbo(s)
    rgbaFbo.begin();
    drawFboTest();
    rgbaFbo.end();
    
    
    model.update();
    
    if(bAnimateMouse) {
        model.setPositionForAllAnimations(animationPosition);
    }
    
    mesh = model.getCurrentAnimatedMesh(0);
}

//--------------------------------------------------------------
void testApp::draw(){
    stringstream ss;
    ss << "Framerate : " << ofToString(ofGetFrameRate(),0) << "\n";
    ofDrawBitmapString(ss.str().c_str(), 10,30);
 
    
    ofSetColor(10, 100, 120, 0x60);
    ofRect(200, 80-sample_level, -25, 400, 200);
    ofSetColor(10, sample_level, 10, 0x60);
    ofRect(200, 200, -50, 360, 300);
    ofSetColor(100, 10, 100, 0xa0);
    ofCircle(sample_tone, 260, 60, 4);
    
    ofSetColor(10, 90, 120, 0xb0);
 	plot(fft.getBins(), 240);
    
    // assimpModel

    ofPushMatrix();
    ofScale(0.5, 0.5);
    ofEnableDepthTest();
    ofSetColor(255,255,255);
    model.drawFaces();
    ofDisableDepthTest();
    ofPopMatrix();
    
    ofPushMatrix();
    ofScale(0.8, 0.8);
    ofTranslate(model.getPosition().x-300, model.getPosition().y, 0);
    ofRotate(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    ofSetColor(180,255,180, 0xa0);
    model.drawWireframe();
    ofPopMatrix();

    int posy=300;
    int posx=20;
    int posVoice=(ofGetFrameNum()%1024);
    // 色変わり後の歌詞を書く
    ofSetColor(255,0,255, 0xff);
    rgbaFbo.draw(posx,posy);
    
    // 色変わり前の歌詞を書く
    ofSetColor(255,255,255);
    rgbaFbo.getTextureReference().drawSubsection(posx+posVoice, posy, 1024-posVoice, 200, posVoice, 0);
    
}

//--------------------------------------------------------------
void testApp::drawFboTest(){
}

void testApp::plot(vector<float>& buffer, float scale) {
	ofNoFill();
	int n = MIN(1024, buffer.size());

	ofPushMatrix();
	ofTranslate(0, scale);
	ofScale(1, -scale);
	ofBeginShape();
    sample_level=0;
    
	for (int i = 0; i < n; i++) {
		ofVertex(i, buffer[i]);
        //printf("%f  ", buffer[i]*100);
        if (i==sample_tone){
            sample_level=buffer[i]*100;
        }
	}
	ofEndShape();
	ofPopMatrix();
    ofFill();
    
    {
        //printf("%d\n", sample_tone);
        string msg = "sample, level: " + ofToString(sample_tone) + " " + ofToString(sample_level);
        ofDrawBitmapString(msg, 10, 10);
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    sample_tone=x;
    viewport2D.x = x;
    viewport2D.y = y;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
