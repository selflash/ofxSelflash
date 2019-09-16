#include "ViewController.h"

//==============================================================
// Constructor / Deconstructor
//==============================================================

//--------------------------------------------------------------
//
ViewController::ViewController() {
    ofLog() << "[ViewManager]ViewManager()";
}

//--------------------------------------------------------------
//
ViewController::~ViewController() {
    ofLog() << "[ViewManager]~ViewManager()";
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//--------------------------------------------------------------
//
void ViewController::setup() {
    ofLog() << "[ViewManager]setup()";

    
    _mainView = new MainView();
    _mainView->setup();
    _mainView->visible(false);

    flStage* stage = ofxSelflash::stage();
    stage->addChildAt(_mainView, 0);
}

//--------------------------------------------------------------
//
void ViewController::update() {
    
}

//==============================================================
// Public Method
//==============================================================

void ViewController::showPage(int type) {
    _mainView->type = type;
    _mainView->visible(true);

}

void ViewController::prev() {
    if(_mainView->type > 1) {
        _mainView->type --;
    }
}
void ViewController::next() {
    if(_mainView->type < 8) {
        _mainView->type ++;
    }
}

//==============================================================
// Protected / Private Method
//==============================================================

//==============================================================
// Event Handler
//==============================================================
