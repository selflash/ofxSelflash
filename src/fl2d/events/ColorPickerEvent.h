#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class CircleColorPicker;
    class ColorPickerEvent : public Event {
        friend class CircleColorPicker;
        
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        ColorPickerEvent(string type);
        ~ColorPickerEvent();
        
    protected:
        
    private:
        
    };
    
}
