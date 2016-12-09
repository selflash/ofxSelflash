#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class AnimationEvent : public Event {
        
    public:
        static string POSITION_COMPLETE;
        static string SIZE_COMPLETE;
        static string SCALE_COMPLETE;
        static string ROTATION_COMPLETE;
        static string COLOR_COMPLETE;
        
    private:
        
    public:
        AnimationEvent(string type);
        virtual ~AnimationEvent();
        
    private:
        
    };
    
}
