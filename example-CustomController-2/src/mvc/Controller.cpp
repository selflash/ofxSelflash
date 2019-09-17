#include "Controller.h"

//==============================================================
// Constructor / Deconstructor
//==============================================================

//--------------------------------------------------------------
//
Controller::Controller() {
    ofLog() << "[Controller]Controller()";
}

//--------------------------------------------------------------
//
Controller::~Controller() {
    ofLog() << "[Controller]~Controller()";
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//--------------------------------------------------------------
//
void Controller::setup(Model& value) {
    ofLog() << "[Controller]setup()";
    
    _model = &value;
    _model->addObserver(*this);
}

//==============================================================
// Public Method
//==============================================================

//void Controller::showPage() {
//
//}

//==============================================================
// Protected / Private Method
//==============================================================

//==============================================================
// Event Handler
//==============================================================