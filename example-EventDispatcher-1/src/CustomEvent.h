#pragma once

#include <string>
#include "ofxSelflash.h"

class CustomEvent : public flEvent {
    public:
        static string TEST1;
        
    private:
        
    public:
        CustomEvent(string type);
        virtual ~CustomEvent();
    
    private:
        
};