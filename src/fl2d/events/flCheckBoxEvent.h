#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flCheckBox;
    class flCheckBoxEvent : public flEvent {
        friend class flCheckBox;
        
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        flCheckBoxEvent(string type);
        virtual ~flCheckBoxEvent();
        
    protected:
        
    private:
        
    };
    
}
