#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("example-TextField");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Ready ofxSelflash
    ofxSelflash::autoUpdate(false);
    ofxSelflash::autoDraw(false);
    ofxSelflash::setup(false);
    //--------------------------------------
    
    flStage* stage = ofxSelflash::stage();
    
    //---------------------------------
    //デフォルト
    textField001 = new flTextField();
    textField001->x(300);
    textField001->y(51);
    textField001->text("openFrameworks");
    textField001->textColor(0xffffff);
    stage->addChild(textField001);
    //---------------------------------
    
    
    //---------------------------------
    //
    textField101 = new flTextField();
    textField101->x(300);
    textField101->y(101);
    textField101->text("LEFT");
    textField101->width(200);
    textField101->autoSize(flTextFieldAutoSize::LEFT);
    textField101->textColor(0xffffff);
    stage->addChild(textField101);
    
    textField102 = new flTextField();
    textField102->x(300);
    textField102->y(176);
    textField102->text("CENTER");
    textField102->width(200);
    textField102->autoSize(flTextFieldAutoSize::CENTER);
    textField102->textColor(0xffffff);
    stage->addChild(textField102);
    
    textField103 = new flTextField();
    textField103->x(300);
    textField103->y(251);
    textField103->text("RIGHT");
    textField103->width(200);
    textField103->autoSize(flTextFieldAutoSize::RIGHT);
    textField103->textColor(0xffffff);
    stage->addChild(textField103);
    //---------------------------------
    
    
    //---------------------------------
    //インプットテキストフィールド
    textField201 = new flTextField();
    textField201->x(300);
    textField201->y(366);
    textField201->text("openFrameworks");
    textField201->autoSize(flTextFieldAutoSize::LEFT);
    textField201->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    textField201->textColor(0x0);
    textField201->mouseEnabled(true);
    textField201->buttonMode(true);
    stage->addChild(textField201);
    
    textField202 = new flTextField();
    textField202->x(300);
    textField202->y(501);
    textField202->text("openFrameworks");
    textField202->width(200);
//    textField202->height(50);
    textField202->autoSize(flTextFieldAutoSize::CENTER);
    textField202->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    textField202->textColor(0x990000);
    textField202->mouseEnabled(true);
    textField202->buttonMode(true);
    stage->addChild(textField202);
    
    textField203 = new flTextField();
    textField203->x(300);
    textField203->y(636);
    textField203->text("openFrameworks\nopenFrameworks");
    textField203->width(200);
//    textField203->height(50);
    textField203->autoSize(flTextFieldAutoSize::RIGHT);
    textField203->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    textField203->textColor(0x009900);
    textField203->mouseEnabled(true);
    textField203->buttonMode(true);
    stage->addChild(textField203);
    
    stage->addChild(textField203);
    stage->addChild(textField202);
    stage->addChild(textField201);
    //---------------------------------
    
    isShowRect = true;
    isTween = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    //----------------------------------
    ofxSelflash::update();
    //----------------------------------
    
    if(!isTween) return;
    int frameNum = ofGetFrameNum();
    
    //---------------------------------
    int w = sin(frameNum * 0.05) * 50 + 100;
    int h = sin(frameNum * 0.07) * 50 + 100;
    
//    textField001->width(w);
//    textField001->height(h);
    
    textField101->width(w);
//    textField101->height(h);
    
    textField102->width(w);
//    textField102->height(h);
    
    textField103->width(w);
//    textField103->height(h);
    
//    textField201->width(w);
//    textField201->height(h);
    
    float a = (sin(frameNum * 0.03) + 1.0) * 0.5;
    cout << a << endl;
    textField203->alpha(a);
    //---------------------------------
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //----------------------------------
    ofxSelflash::draw();
    //----------------------------------
    
    //---------------------------------
    if(isShowRect) {
        ofPushStyle();
        
        ofSetColor(255, 0, 0, 100);
        ofNoFill();
        ofRect(textField001->x(), textField001->y(), textField001->width(), textField001->height());
        ofRect(textField101->x(), textField101->y(), textField101->width(), textField101->height());
        ofRect(textField102->x(), textField102->y(), textField102->width(), textField102->height());
        ofRect(textField103->x(), textField103->y(), textField103->width(), textField103->height());
        
        ofPopStyle();
    }
    //---------------------------------
    
    //---------------------------------
    string help = "";
    help += "[ ALT ] Play / Stop Tween.\n";
    help += "[SPACE] Show / Hide Rect.\n";
    
    ofPushMatrix();
    ofTranslate(600, 20);
    flFont::drawString(help, 0, 0);
    ofPopMatrix();
    //---------------------------------
    
    //---------------------------------
    string info;
    info = "";
    info += "[Default]\n";
//    info += "__________________________________________________\n";
    ofPushMatrix();
    ofTranslate(20, 50);
    flFont::drawString(info, 0, 0);
    ofPopMatrix();
    //---------------------------------
    
    //---------------------------------
    info = "";
    info += "[Auto Size]\n";
    info += "Width = " + ofToString(textField101->width()) + "\n";
    info += "Height = " + ofToString(textField101->height()) + "\n";
    info += "ScaleX = " + ofToString(textField101->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(textField101->scaleY()) + "\n";
    
    info += "\n";
    info += "Width = " + ofToString(textField102->width()) + "\n";
    info += "Height = " + ofToString(textField102->height()) + "\n";
    info += "ScaleX = " + ofToString(textField102->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(textField102->scaleY()) + "\n";
    
    info += "\n";
    info += "Width = " + ofToString(textField103->width()) + "\n";
    info += "Height = " + ofToString(textField103->height()) + "\n";
    info += "ScaleX = " + ofToString(textField103->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(textField103->scaleY()) + "\n";

    ofPushMatrix();
    ofTranslate(20, 100);
    flFont::drawString(info, 0, 0);
    ofPopMatrix();
    //---------------------------------
    
    //---------------------------------
    info = "";
    info += "[Input Text]\n";
    
    info += "TextField\n";
    info += "Width = " + ofToString(textField201->width()) + "\n";
    info += "Height = " + ofToString(textField201->height()) + "\n";
    info += "ScaleX = " + ofToString(textField201->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(textField201->scaleY()) + "\n";
    info += "TextWidth = " + ofToString(textField201->textWidth()) + "\n";
    info += "TextHeight = " + ofToString(textField201->textHeight()) + "\n";
    info += "AutoSize = " + ofToString(textField201->autoSize()) + "\n";
    
    info += "\n";
    info += "TextField (width fixed)\n";
    info += "Width = " + ofToString(textField202->width()) + "\n";
    info += "Height = " + ofToString(textField202->height()) + "\n";
    info += "ScaleX = " + ofToString(textField202->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(textField202->scaleY()) + "\n";
    info += "TextWidth = " + ofToString(textField202->textWidth()) + "\n";
    info += "TextHeight = " + ofToString(textField202->textHeight()) + "\n";
    info += "AutoSize = " + ofToString(textField202->autoSize()) + "\n";
    
    info += "\n";
    info += "TextField (width fixed)\n";
    info += "Width = " + ofToString(textField203->width()) + "\n";
    info += "Height = " + ofToString(textField203->height()) + "\n";
    info += "ScaleX = " + ofToString(textField203->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(textField203->scaleY()) + "\n";
    info += "TextWidth = " + ofToString(textField203->textWidth()) + "\n";
    info += "TextHeight = " + ofToString(textField203->textHeight()) + "\n";
    info += "AutoSize = " + ofToString(textField203->autoSize()) + "\n";
    
    ofPushMatrix();
    ofTranslate(20, 350);
    flFont::drawString(info, 0, 0);
    ofPopMatrix();
    //---------------------------------
    
    //--------------------------------------
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    ofCircle(ofGetMouseX(), ofGetMouseY(), 5);
    ofPopStyle();
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') isShowRect = !isShowRect;
    if(key == OF_KEY_ALT) isTween = !isTween;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
