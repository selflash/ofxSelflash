#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flJoyStick1;
    class flJoyStick1Event : public flEvent {
        friend class flJoyStick1;
        
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
        flJoyStick1Event(string type);
        virtual ~flJoyStick1Event();
        
        virtual inline float value() { return __value; }
        
    protected:
        
    private:
        
    };
    
}
