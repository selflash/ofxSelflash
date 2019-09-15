#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flButton;
    class flButtonEvent : public flEvent {
    public:
        static string CHANGE;
        static string MOUSE_OVER;
        static string MOUSE_OUT;
        static string ROLL_OVER;
        static string ROLL_OUT;
        static string MOUSE_DOWN;
        static string MOUSE_UP;
        static string CLICK;
        
    protected:
        
    private:
        
    public:
        flButtonEvent(string type);
        virtual ~flButtonEvent();
        
        //            ButtonEvent* clone();
        
    protected:
        
    private:
        
    };
    
}
