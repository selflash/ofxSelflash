#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "MainView.h"

using namespace fl2d;

class ViewController {
public:
    
private:
    MainView* _mainView;

public:
    ViewController();
    ~ViewController();
    
    void setup();
    void update();
    
    void showPage(int type);
    void prev();
    void next();

private:
    
};
