#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flCircleColorPicker;
    class flColorPickerEvent : public flEvent {
        friend class flCircleColorPicker;
        
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        flColorPickerEvent(string type);
        virtual ~flColorPickerEvent();
        
    protected:
        
    private:
        
    };
    
}
