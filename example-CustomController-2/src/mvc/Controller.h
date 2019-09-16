#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "Model.h"
#include "Observer.h"

using namespace fl2d;

class Controller : Observer {
public:
    
private:
    Model* _model;
    
public:
    Controller();
    ~Controller();
    
    void setup(Model& value);

private:
    
};
