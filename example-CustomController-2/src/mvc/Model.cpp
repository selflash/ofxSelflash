#include "Model.h"

//==============================================================
// Constructor / Deconstructor
//==============================================================

//--------------------------------------------------------------
//
Model::Model() {
    ofLog() << "[Model]Model()";
}

//--------------------------------------------------------------
//
Model::~Model() {
    ofLog() << "[Model]~Model()";
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//--------------------------------------------------------------
//
void Model::setup() {
    ofLog() << "[Model]setup()";

}

//==============================================================
// Public Method
//==============================================================

void Model::addObserver(Observer& value) {
    _observers.push_back(&value);
}

//void Model::showPage() {
//
//}

//==============================================================
// Protected / Private Method
//==============================================================

//==============================================================
// Event Handler
//==============================================================
