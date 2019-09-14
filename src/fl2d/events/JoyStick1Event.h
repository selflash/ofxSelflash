#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Joystick1;
    class Joystick1Event : public Event {
        friend class Joystick1;
        
    public:
        static string CHANGE;
        static string UP;
        static string DOWN;
        static string LEFT;
        static string RIGHT;
        
    protected:
        float __value;
        
    private:
        
    public:
        Joystick1Event(string type);
        virtual ~Joystick1Event();
        
        virtual inline float value() { return __value; }
        
    protected:
        
    private:
        
    };
    
}
