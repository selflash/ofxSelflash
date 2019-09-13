#pragma once

#include "ofxSelflash.h"
#include "CustomEvent.h"

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
