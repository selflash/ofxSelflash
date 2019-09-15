#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flRadioButton;
    class flRadioButtonEvent : public flEvent {
        friend class flRadioButton;
        
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        flRadioButtonEvent(string type);
        virtual ~flRadioButtonEvent();
        
    protected:
        
    private:
        
    };
    
}
