#include "ofApp.h"

/**
 TweenMaxのoverwriteプロパティ調査
 [参考] http://www.phantom4.org/flash/tweenmax_overwrite/index.html
 */

//--------------------------------------------------------------
//
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("example-Tweener");
    
    //----------------------------------
    //Flashフレームワークの準備
    ofxSelflash::setup(true);
    flStage* stage = ofxSelflash::stage();
//    stage->priority(OF_EVENT_ORDER_AFTER_APP);
    //----------------------------------

    //----------------------------------
    flGraphics* g;
    //2D
    box0 = new flSprite();
    box0->name("BOX 0");
    box0->x(300);
    box0->y(90);
    g = box0->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 25, 20);
    g->endFill();
    box0->mouseEnabled(false);
    stage->addChild(box0);

    box1 = new flSprite();
    box1->name("BOX 1");
    box1->x(300);
    box1->y(190);
    g = box1->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 25, 20);
    g->endFill();
    box1->mouseEnabled(false);
    stage->addChild(box1);
    
    box2 = new flSprite();
    box2->name("BOX 2");
    box2->x(300);
    box2->y(290);
    g = box2->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 25, 20);
    g->endFill();
    box2->mouseEnabled(false);
    stage->addChild(box2);
    
    box3 = new flSprite();
    box3->name("BOX 3");
    box3->x(300);
    box3->y(390);
    g = box3->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 25, 20);
    g->endFill();
    box3->mouseEnabled(false);
    stage->addChild(box3);
    
    box4 = new flSprite();
    box4->name("BOX 4");
    box4->x(300);
    box4->y(490);
    g = box4->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 25, 20);
    g->endFill();
    box4->mouseEnabled(false);
    stage->addChild(box4);
    
    box5 = new flSprite();
    box5->name("BOX 5");
    box5->x(300);
    box5->y(590);
    g = box5->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 25, 20);
    g->endFill();
    box5->mouseEnabled(false);
    stage->addChild(box5);
    //----------------------------------
}

//--------------------------------------------------------------
//
void ofApp::update() {
    
}

//--------------------------------------------------------------
//
void ofApp::draw() {
    ofDrawBitmapString("FPS : " + ofToString((int) ofGetFrameRate()), 10, 20);
    ofDrawBitmapString("NUM TWEENS : " + ofToString(flTweener::numTweens()), 10, 40);
    ofDrawBitmapString("p : flTweener::pause()", 10, 60);
    ofDrawBitmapString("P : flTweener::resume()", 10, 80);
    ofDrawBitmapString("k : flTweener::killAll()", 10, 100);
    ofDrawBitmapString("1 : playAnimation0()", 10, 120);
    ofDrawBitmapString("2 : playAnimation1()", 10, 140);
    ofDrawBitmapString("3 : playAnimation2()", 10, 160);
    ofDrawBitmapString("4 : playAnimation3()", 10, 180);
    ofDrawBitmapString("5 : playAnimation4()", 10, 200);
    ofDrawBitmapString("6 : playAnimation5()", 10, 220);
    
    std::string text;
    int x = 300;
    
    //----------------------------------
    text = "flTweener.to(box, 1, 'x', 350, 'delay', 0, 'overwrite', 0)";
    ofPushStyle();
    if(tween001 && tween001->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 40);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 0, 'overwrite', 0)";
    ofPushStyle();
    if(tween002 && tween002->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 60);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 1, 'overwrite', 0)";
    ofPushStyle();
    if(tween003 && tween003->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 80);
    ofPopStyle();
    //----------------------------------

    //----------------------------------
    text = "flTweener.to(box, 1, 'y', -15, 'delay', 0, 'overwrite', 1)";
    ofPushStyle();
    if(tween101 && tween101->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 140);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 0, 'overwrite', 1)";
    ofPushStyle();
    if(tween102 && tween102->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 160);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 1, 'overwrite', 1)";
    ofPushStyle();
    if(tween103 && tween103->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 180);
    ofPopStyle();
    //----------------------------------
    
    //----------------------------------
    text = "flTweener.to(box, 3, 'y', -15, 'delay', 0, 'overwrite', 2)";
    ofPushStyle();
    if(tween201 && tween201->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 240);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 0, 'overwrite', 2)";
    ofPushStyle();
    if(tween202 && tween202->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 260);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 1, 'overwrite', 2)";
    ofPushStyle();
    if(tween203 && tween203->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 280);
    ofPopStyle();
    //----------------------------------
    
    //----------------------------------
    text = "flTweener.to(box, 3, 'y', -15, 'delay', 0, 'overwrite', 3)";
    ofPushStyle();
    if(tween301 && tween301->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 340);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 0, 'overwrite', 3)";
    ofPushStyle();
    if(tween302 && tween302->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 360);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 1, 'overwrite', 3)";
    ofPushStyle();
    if(tween303 && tween303->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 380);
    ofPopStyle();
    //----------------------------------
    
    //----------------------------------
    text = "flTweener.to(box, 3, 'y', -15, 'delay', 0, 'overwrite', 4)";
    ofPushStyle();
    if(tween401 && tween401->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 440);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 0, 'overwrite', 4)";
    ofPushStyle();
    if(tween402 && tween402->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 460);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 1, 'overwrite', 4)";
    ofPushStyle();
    if(tween403 && tween403->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 480);
    ofPopStyle();
    //----------------------------------
    
    //----------------------------------
    text = "flTweener.to(box, 3, 'y', -15, 'delay', 0, 'overwrite', 5)";
    ofPushStyle();
    if(tween501 && tween501->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 540);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 0, 'overwrite', 5)";
    ofPushStyle();
    if(tween502 && tween502->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 560);
    ofPopStyle();
    
    text = "flTweener.to(box, 2, 'x', 350, 'delay', 1, 'overwrite', 5)";
    ofPushStyle();
    if(tween503 && tween503->isTweening()) ofSetColor(255, 0, 0); else ofSetColor(255, 255, 255);
    ofDrawBitmapString(text, x, 580);
    ofPopStyle();
    //----------------------------------
}

//==============================================================
// PROTECTED / PRIVATE
//==============================================================

//--------------------------------------------------------------
//
void ofApp::_tweenStart(flSTweenCore* currentTarget) {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_tweenStart()";
    
    if(currentTarget == tween001) { cout << "tween001" << endl; }
    if(currentTarget == tween002) { cout << "tween002" << endl; }
    if(currentTarget == tween003) { cout << "tween003" << endl; }
    
    if(currentTarget == tween101) { cout << "tween101" << endl; }
    if(currentTarget == tween102) { cout << "tween102" << endl; }
    if(currentTarget == tween103) { cout << "tween103" << endl; }
    
    if(currentTarget == tween201) { cout << "tween201" << endl; }
    if(currentTarget == tween202) { cout << "tween202" << endl; }
    if(currentTarget == tween203) { cout << "tween203" << endl; }
    
    if(currentTarget == tween301) { cout << "tween301" << endl; }
    if(currentTarget == tween302) { cout << "tween302" << endl; }
    if(currentTarget == tween303) { cout << "tween303" << endl; }
    
    if(currentTarget == tween401) { cout << "tween401" << endl; }
    if(currentTarget == tween402) { cout << "tween402" << endl; }
    if(currentTarget == tween403) { cout << "tween403" << endl; }
    
    if(currentTarget == tween501) { cout << "tween501" << endl; }
    if(currentTarget == tween502) { cout << "tween502" << endl; }
    if(currentTarget == tween503) { cout << "tween503" << endl; }
}
//--------------------------------------------------------------
//
void ofApp::_tweenUpdate(flSTweenCore* currentTarget) {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_tweenUpdate()";

}
//--------------------------------------------------------------
//
void ofApp::_tweenComplete(flSTweenCore* currentTarget) {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_tweenComplete()";
    
    if(currentTarget == tween001) tween001 = NULL;
    if(currentTarget == tween002) tween002 = NULL;
    if(currentTarget == tween003) tween003 = NULL;
    
    if(currentTarget == tween101) tween101 = NULL;
    if(currentTarget == tween102) tween102 = NULL;
    if(currentTarget == tween103) tween103 = NULL;
    
    if(currentTarget == tween201) tween201 = NULL;
    if(currentTarget == tween202) tween202 = NULL;
    if(currentTarget == tween203) tween203 = NULL;
    
    if(currentTarget == tween301) tween301 = NULL;
    if(currentTarget == tween302) tween302 = NULL;
    if(currentTarget == tween303) tween303 = NULL;
    
    if(currentTarget == tween401) tween401 = NULL;
    if(currentTarget == tween402) tween402 = NULL;
    if(currentTarget == tween403) tween403 = NULL;
    
    if(currentTarget == tween501) tween501 = NULL;
    if(currentTarget == tween502) tween502 = NULL;
    if(currentTarget == tween503) tween503 = NULL;
}

//--------------------------------------------------------------
//
void ofApp::_playAnimation0() {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_playAnimation0()";
    
    int x = 300;
    int y = 90;
    
    box0->x(x);
    box0->y(y);
    
    tween001 = flTweener::to(
                            box0,
                            1.0,
                            "x", x + 350,
                            "delay", 0.0,
                            "overwrite", TW_NONE,
                            "ease", EASE_LINEAR);
    tween001->onStart(this, &ofApp::_tweenStart);
    tween001->onUpdate(this, &ofApp::_tweenUpdate);
    tween001->onComplete(this, &ofApp::_tweenComplete);
    
    tween002 = flTweener::to(
                            box0,
                            2.0,
                            "x", x + 350,
                            "delay", 0.0,
                            "overwrite", TW_NONE,
                            "ease", EASE_LINEAR);
    tween002->onStart(this, &ofApp::_tweenStart);
    tween002->onUpdate(this, &ofApp::_tweenUpdate);
    tween002->onComplete(this, &ofApp::_tweenComplete);
    
    tween003 = flTweener::to(
                            box0,
                            2.0,
                            "x", x + 350,
                            "delay", 1.5,
                            "overwrite", TW_NONE,
                            "ease", EASE_LINEAR);
    tween003->onStart(this, &ofApp::_tweenStart);
    tween003->onUpdate(this, &ofApp::_tweenUpdate);
    tween003->onComplete(this, &ofApp::_tweenComplete);
}
//--------------------------------------------------------------
//
void ofApp::_playAnimation1() {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_playAnimation1()";
    
    int x = 300;
    int y = 190;
    
    box1->x(x);
    box1->y(y);
    
    tween101 = flTweener::to(
                            box1,
                            1.0,
                            "y", y - 15,
                            "delay", 0.0,
                            "overwrite", TW_ALL_IMMEDIATE,
                            "ease", EASE_LINEAR);
    tween101->onStart(this, &ofApp::_tweenStart);
    tween101->onUpdate(this, &ofApp::_tweenUpdate);
    tween101->onComplete(this, &ofApp::_tweenComplete);

    tween102 = flTweener::to(
                            box1,
                            2.0,
                            "x", x + 350,
                            "delay", 0.0,
                            "overwrite", TW_ALL_IMMEDIATE,
                            "ease", EASE_LINEAR);
    tween102->onStart(this, &ofApp::_tweenStart);
    tween102->onUpdate(this, &ofApp::_tweenUpdate);
    tween102->onComplete(this, &ofApp::_tweenComplete);
    
    tween103 = flTweener::to(
                            box1,
                            2.0,
                            "x", x + 350,
                            "delay", 1.0,
                            "overwrite", TW_ALL_IMMEDIATE,
                            "ease", EASE_LINEAR);
    tween103->onStart(this, &ofApp::_tweenStart);
    tween103->onUpdate(this, &ofApp::_tweenUpdate);
    tween103->onComplete(this, &ofApp::_tweenComplete);
}
//--------------------------------------------------------------
//
void ofApp::_playAnimation2() {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_playAnimation2()";
    
    int x = 300;
    int y = 290;
    
    box2->x(x);
    box2->y(y);
    
    tween201 = flTweener::to(
                             box2,
                             1.0,
                             "y", y - 15,
                             "delay", 0.0,
                             "overwrite", TW_AUTO,
                             "ease", EASE_LINEAR);
    tween201->onStart(this, &ofApp::_tweenStart);
    tween201->onUpdate(this, &ofApp::_tweenUpdate);
    tween201->onComplete(this, &ofApp::_tweenComplete);
    
    tween202 = flTweener::to(
                             box2,
                             2.0,
                             "x", x + 350,
                             "delay", 0.0,
                             "overwrite", TW_AUTO,
                             "ease", EASE_LINEAR);
    tween202->onStart(this, &ofApp::_tweenStart);
    tween202->onUpdate(this, &ofApp::_tweenUpdate);
    tween202->onComplete(this, &ofApp::_tweenComplete);
    
    tween203 = flTweener::to(
                             box2,
                             2.0,
                             "x", x + 350,
                             "delay", 1.0,
                             "overwrite", TW_AUTO,
                             "ease", EASE_LINEAR);
    tween203->onStart(this, &ofApp::_tweenStart);
    tween203->onUpdate(this, &ofApp::_tweenUpdate);
    tween203->onComplete(this, &ofApp::_tweenComplete);
}
//--------------------------------------------------------------
//
void ofApp::_playAnimation3() {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_playAnimation3()";
    
    int x = 300;
    int y = 390;
    
    box3->x(x);
    box3->y(y);
    
    tween301 = flTweener::to(
                             box3,
                             1.0,
                             "y", y - 15,
                             "delay", 0.0,
                             "overwrite", TW_CONCURRENT,
                             "ease", EASE_LINEAR);
    tween301->onStart(this, &ofApp::_tweenStart);
    tween301->onUpdate(this, &ofApp::_tweenUpdate);
    tween301->onComplete(this, &ofApp::_tweenComplete);
    
    tween302 = flTweener::to(
                             box3,
                             2.0,
                             "x", x + 350,
                             "delay", 0.0,
                             "overwrite", TW_CONCURRENT,
                             "ease", EASE_LINEAR);
    tween302->onStart(this, &ofApp::_tweenStart);
    tween302->onUpdate(this, &ofApp::_tweenUpdate);
    tween302->onComplete(this, &ofApp::_tweenComplete);
    
    tween303 = flTweener::to(
                             box3,
                             2.0,
                             "x", x + 350,
                             "delay", 1.0,
                             "overwrite", TW_CONCURRENT,
                             "ease", EASE_LINEAR);
    tween303->onStart(this, &ofApp::_tweenStart);
    tween303->onUpdate(this, &ofApp::_tweenUpdate);
    tween303->onComplete(this, &ofApp::_tweenComplete);
}
//--------------------------------------------------------------
//
void ofApp::_playAnimation4() {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_playAnimation4()";
    
    int x = 300;
    int y = 490;
    
    box4->x(x);
    box4->y(y);
    
    tween401 = flTweener::to(
                             box4,
                             1.0,
                             "y", y - 15,
                             "delay", 0.0,
                             "overwrite", TW_ALL_ONSTART,
                             "ease", EASE_LINEAR);
    tween401->onStart(this, &ofApp::_tweenStart);
    tween401->onUpdate(this, &ofApp::_tweenUpdate);
    tween401->onComplete(this, &ofApp::_tweenComplete);
    
    tween402 = flTweener::to(
                             box4,
                             2.0,
                             "x", x + 350,
                             "delay", 0.0,
                             "overwrite", TW_ALL_ONSTART,
                             "ease", EASE_LINEAR);
    tween402->onStart(this, &ofApp::_tweenStart);
    tween402->onUpdate(this, &ofApp::_tweenUpdate);
    tween402->onComplete(this, &ofApp::_tweenComplete);
    
    tween403 = flTweener::to(
                             box4,
                             2.0,
                             "x", x + 350,
                             "delay", 1.0,
                             "overwrite", TW_ALL_ONSTART,
                             "ease", EASE_LINEAR);
    tween403->onStart(this, &ofApp::_tweenStart);
    tween403->onUpdate(this, &ofApp::_tweenUpdate);
    tween403->onComplete(this, &ofApp::_tweenComplete);
}
//--------------------------------------------------------------
//
void ofApp::_playAnimation5() {
    ofLog(OF_LOG_VERBOSE) << "[ofApp]_playAnimation5()";
    
    int x = 300;
    int y = 590;
    
    box5->x(x);
    box5->y(y);
    
    tween501 = flTweener::to(
                             box5,
                             1.0,
                             "y", y - 15,
                             "delay", 0.0,
                             "overwrite", TW_PREEXISTING,
                             "ease", EASE_LINEAR);
    tween501->onStart(this, &ofApp::_tweenStart);
    tween501->onUpdate(this, &ofApp::_tweenUpdate);
    tween501->onComplete(this, &ofApp::_tweenComplete);
    
    tween502 = flTweener::to(
                             box5,
                             2.0,
                             "x", x + 350,
                             "delay", 0.0,
                             "overwrite", TW_PREEXISTING,
                             "ease", EASE_LINEAR);
    tween502->onStart(this, &ofApp::_tweenStart);
    tween502->onUpdate(this, &ofApp::_tweenUpdate);
    tween502->onComplete(this, &ofApp::_tweenComplete);
    
    tween503 = flTweener::to(
                             box5,
                             2.0,
                             "x", x + 350,
                             "delay", 1.0,
                             "overwrite", TW_PREEXISTING,
                             "ease", EASE_LINEAR);
    tween503->onStart(this, &ofApp::_tweenStart);
    tween503->onUpdate(this, &ofApp::_tweenUpdate);
    tween503->onComplete(this, &ofApp::_tweenComplete);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void ofApp::keyPressed(int key) {
    if(key == 'p') {
        flTweener::pause();
    }
    if(key == 'P') {
        flTweener::resume();
    }
    
    if(key == 'k') {
        flTweener::killAll();
    }
    
    if(key == '1') _playAnimation0();
    if(key == '2') _playAnimation1();
    if(key == '3') _playAnimation2();
    if(key == '4') _playAnimation3();
    if(key == '5') _playAnimation4();
    if(key == '6') _playAnimation5();
    
    if(key == '7') flTweener::delayedCall(2.0, this, &ofApp::_playAnimation0);
}

//--------------------------------------------------------------
//
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
//
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
//
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
//
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
//
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
//
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
//
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
//
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
