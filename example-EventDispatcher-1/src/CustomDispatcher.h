#pragma once

#include "ofxSelflash.h"
#include "CustomEvent.h"

class CustomDispatcher : public flEventDispatcher {
    public:
        
    private:
        
    public:
        CustomDispatcher();
        ~CustomDispatcher();
        
        void dispatchTest1();
        void dispatchTest2();

    private:
};