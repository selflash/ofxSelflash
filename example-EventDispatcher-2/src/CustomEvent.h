#pragma once

#include "ofxSelflash.h"

class CustomEvent : public flEvent {
    public:
        static string TEST1;
        
    private:
        
    public:
        CustomEvent(string type);
        ~CustomEvent();
    
    private:
        
};