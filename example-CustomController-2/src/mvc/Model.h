#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "Oveservable.h"
#include "Observer.h"

using namespace fl2d;

class Model : Oveservable {
    public:
    
    private:
        list<Observer*> _observers;
    
    public:
        Model();
        ~Model();
    
        void setup();
        void addObserver(Observer& value);

    private:
    
};
