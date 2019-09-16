#pragma once

#include <string>
#include "ofxSelflash.h"

using namespace fl2d;

class CustomEvent : public flEvent {
public:
    static string TEST1;
    
private:
    
public:
    CustomEvent(string type);
    virtual ~CustomEvent();
    
private:
    
};
