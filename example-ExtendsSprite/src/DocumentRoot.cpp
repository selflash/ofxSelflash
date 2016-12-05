#include "DocumentRoot.h"
//static const double pi = std::acos(-1.0); // お手軽に π を得る。

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
DocumentRoot::DocumentRoot() {
    cout << "[DocumentRoot]DocumentRoot()" << endl;
    _target = this;
    name("DocumentRoot");
    
    useHandCursor(true);
}

//--------------------------------------------------------------
//
DocumentRoot::~DocumentRoot() {
    cout << "[DocumentRoot]~DocumentRoot()" << endl;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void DocumentRoot::_setup() {
    cout << "[DocumentRoot]_setup()" << endl;
        
    //--------------------------------------
    //ステージに追加された時にキーボードイベントを監視する
    addEventListener(flEvent::ADDED_TO_STAGE, this, &DocumentRoot::_eventHandler);
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &DocumentRoot::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_UP, this, &DocumentRoot::_mouseEventHandler);
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0x888888, 0.1);
    g->drawRect(0, 0, ofGetWidth(), ofGetHeight());
    g->endFill();
    //-----------------------------------
    
    //-----------------------------------
    //copy from examples/graphics/graphicsExample
    //graphicsExampleのコードを書き写し
    counter = 0;
    ofSetCircleResolution(50);
    ofBackground(255,255,255);
    bSmooth = false;
//    ofSetWindowTitle("graphics example");
    
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    //-----------------------------------
}

//--------------------------------------------------------------
//
void DocumentRoot::_update() {
    //--------------------------------------
    if(!isMouseDown()){
        _forceX *= 0.95;
        _forceY *= 0.95;
        
        float temp;
        temp = x();
        temp += _forceX;
        x(temp);
        
        temp = y();
        temp += _forceY;
        y(temp);
    } else {
        _preX = x();
        _preY = y();
    }
    
    //動いた分背景の塗りを帳尻合わせる時
//    flGraphics* g;
//    g = graphics();
//    g->clear();
//    g->beginFill(0x0000cc, 0.2);
//    g->drawRect(-x(), -y(), ofGetWidth(), ofGetHeight());
//    g->endFill();
    //--------------------------------------
    
    //-----------------------------------
    //copy from examples/graphics/graphicsExample
    //graphicsExampleのコードを書き写し
    counter = counter + 0.033f;
    //-----------------------------------
}

//--------------------------------------------------------------
//
void DocumentRoot::_draw() {
    //-----------------------------------
    //copy from examples/graphics/graphicsExample
    //graphicsExampleのコードを書き写し
    
    //--------------------------- circles
    //let's draw a circle:
    ofSetColor(255,130,0);
    float radius = 50 + 10 * sin(counter);
    ofFill();		// draw "filled shapes"
    ofDrawCircle(100,400,radius);
    
    // now just an outline
    ofNoFill();
    ofSetHexColor(0xCCCCCC);
    ofDrawCircle(100,400,80);
    
    // use the bitMap type
    // note, this can be slow on some graphics cards
    // because it is using glDrawPixels which varies in
    // speed from system to system.  try using ofTrueTypeFont
    // if this bitMap type slows you down.
    ofSetHexColor(0x000000);
    ofDrawBitmapString("circle", 75,500);
    
    
    //--------------------------- rectangles
    ofFill();
    for (int i = 0; i < 200; i++){
        ofSetColor((int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255));
        ofDrawRectangle(ofRandom(250,350),ofRandom(350,450),ofRandom(10,20),ofRandom(10,20));
    }
    ofSetHexColor(0x000000);
    ofDrawBitmapString("rectangles", 275,500);
    
    //---------------------------  transparency
    ofSetHexColor(0x00FF33);
    ofDrawRectangle(400,350,100,100);
    // alpha is usually turned off - for speed puposes.  let's turn it on!
    ofEnableAlphaBlending();
    ofSetColor(255,0,0,127);   // red, 50% transparent
    ofDrawRectangle(450,430,100,33);
    ofSetColor(255,0,0,(int)(counter * 10.0f) % 255);   // red, variable transparent
    ofDrawRectangle(450,370,100,33);
    ofDisableAlphaBlending();
    
    ofSetHexColor(0x000000);
    ofDrawBitmapString("transparency", 410,500);
    
    //---------------------------  lines
    // a bunch of red lines, make them smooth if the flag is set
    
    ofSetHexColor(0xFF0000);
    for (int i = 0; i < 20; i++){
        ofDrawLine(600,300 + (i*5),800, 250 + (i*10));
    }
    
    ofSetHexColor(0x000000);
    ofDrawBitmapString("lines\npress 's' to toggle smoothness", 600,500);
    //-----------------------------------
}

//==============================================================
// PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void DocumentRoot::_eventHandler(flEvent& event) {
    cout << "[DocumentRoot]_eventHandler(" + event.type() + ")";
    
    if(event.type() == flEvent::ADDED_TO_STAGE) {
        removeEventListener(flEvent::ADDED_TO_STAGE, this, &DocumentRoot::_eventHandler);
        
        stage()->addEventListener(flKeyboardEvent::KEY_PRESS, this, &DocumentRoot::_keyboardEventHandler);
        stage()->addEventListener(flKeyboardEvent::KEY_RELEASE, this, &DocumentRoot::_keyboardEventHandler);
    }
}

//--------------------------------------------------------------
//
void DocumentRoot::_keyboardEventHandler(flEvent& event) {
//    cout << "[DocumentRoot]_keyboardEventHandler(" + event.type() + ")";
    
    flKeyboardEvent* keyboardEvent = dynamic_cast<flKeyboardEvent*>(&event);
    int key = keyboardEvent->keyCode();
    
    if(event.type() == flKeyboardEvent::KEY_PRESS) {
        //-----------------------------------
        //copy from examples/graphics/graphicsExample
        //graphicsExampleのコードを書き写し
        if (key == 's') {
            bSmooth = !bSmooth;
            if (bSmooth){
                ofEnableAntiAliasing();
            }else{
                ofDisableAntiAliasing();
            }
        }
        //-----------------------------------
    }
    
    if(event.type() == flKeyboardEvent::KEY_RELEASE) {
        
    }
}

//--------------------------------------------------------------
//
void DocumentRoot::_moveEventHandler(flEvent& event) {
    //cout << "[DocumentRoot]_moveEventHandler(" << event.type() << ")" << endl;
    
    cout << "mouse is moving" << endl;
}

//--------------------------------------------------------------
//
void DocumentRoot::_mouseEventHandler(flEvent& event) {
//    cout << "[DocumentRoot]_mouseEventHandler(" << event.type() << ")" << endl;
//    cout << "[PrentBox]this          = " << this << endl;
//    cout << "[ParetBox]currentTarget = " << event.currentTarget() << endl;
//    cout << "[ParetBox]target        = " << event.target() << endl;
    
    if(event.type() == flMouseEvent::MOUSE_OVER) {
        if(event.target() == this) {
            
        }
    }
    if(event.type() == flMouseEvent::MOUSE_OUT) {
        if(event.target() == this) {
            
        }
    }
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        if(event.target() == this) {
            startDrag();
            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &DocumentRoot::_mouseEventHandler);
            stage()->addEventListener(flMouseEvent::MOUSE_MOVE, this, &DocumentRoot::_moveEventHandler);
        }
    }
    if(event.type() == flMouseEvent::MOUSE_UP) {
        if(event.currentTarget() == stage()) {
            stopDrag();
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &DocumentRoot::_mouseEventHandler);
            stage()->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &DocumentRoot::_moveEventHandler);
            
            _forceX = (x() - _preX) * 0.5;
            _forceY = (y() - _preY) * 0.5;
        }
    }
}
