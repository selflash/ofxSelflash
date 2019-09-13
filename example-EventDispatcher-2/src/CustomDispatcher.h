#pragma once

#include "ofxSelflash.h"
#include "CustomEvent.h"

class CustomDispatcher : public flEventDispatcher {
    public:
        
    private:
        
    public:
        CustomDispatcher();
        virtual ~CustomDispatcher();
    
        void addListeners();
        void removeListeners();
    
        void dispatchTest1();
        void dispatchTest2();
        
    private:
        void eventHandler(flEvent& event);
    
};