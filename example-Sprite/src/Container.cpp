#include "Container.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
Container::Container() {
    cout << "[Container]Container()" << endl;
    _target = this;
    name("Container");
    
    spriteA = NULL;
    spriteB = NULL;
}

//--------------------------------------------------------------
//
Container::~Container() {
    cout << "[Container]~Container()" << endl;
    
    delete spriteA;
    spriteA = NULL;
    
    delete spriteB;
    spriteB = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void Container::_setup() {
    cout << "[Container]_setup()" << endl;
    
    spriteA = new CustomSpriteA();
    spriteA->x(300);
    spriteA->y(20);
    addChild(spriteA);
    
    spriteB = new CustomSpriteA();
    spriteB->x(300);
    spriteB->y(400);
    addChild(spriteB);
}

//--------------------------------------------------------------
//
void Container::_update() {
    int frameNum = ofGetFrameNum();
    float w = sin(frameNum * 0.05) * 50 + 200;
    float h = sin(frameNum * 0.075) * 50 + 200;
    
    float s = sin(frameNum * 0.03) * 0.2 + 0.5;
    
    spriteA->width(w);
    spriteA->height(h);
    
    spriteB->scaleX(s);
    spriteB->scaleY(s);
}

//--------------------------------------------------------------
//
void Container::_draw() {
    
    //---------------------------------
    string info;
    info = "";
    info += "[Width and Height Tween]\n";
    info += "Width = " + ofToString(spriteA->width()) + "\n";
    info += "Height = " + ofToString(spriteA->height()) + "\n";
    info += "ScaleX = " + ofToString(spriteA->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(spriteA->scaleY()) + "\n";
    
    info += "\n";
    info += "[ScaleX and ScaleY Tween]\n";
    info += "Width = " + ofToString(spriteB->width()) + "\n";
    info += "Height = " + ofToString(spriteB->height()) + "\n";
    info += "ScaleX = " + ofToString(spriteB->scaleX()) + "\n";
    info += "ScaleY = " + ofToString(spriteB->scaleY()) + "\n";
    
    ofPushMatrix();
    ofTranslate(20, 20);
    flFont::drawString(info, 0, 0);
    ofPopMatrix();
    //---------------------------------

}

//==============================================================
// PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================