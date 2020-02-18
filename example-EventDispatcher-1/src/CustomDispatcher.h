#pragma once

#include "ofxSelflash.h"
#include "CustomEvent.h"

using namespace fl2d;

class CustomDispatcher : public flEventDispatcher {
    public:
        
    private:
        
    public:
        CustomDispatcher();
        virtual ~CustomDispatcher();
        
        void dispatchTest1();
        void dispatchTest2();
        
    private:
};
