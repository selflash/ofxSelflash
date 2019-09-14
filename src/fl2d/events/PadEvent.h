#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Pad2D;
    class Pad3D;
    class PadEvent : public Event {
        friend class Pad2D;
        friend class Pad3D;
        
    public:
        static string CHANGE;
        
    protected:
        float __xRatio;
        float __yRatio;
        float __xValue;
        float __yValue;
        float __zValue;
        
    private:
        
    public:
        PadEvent(string type);
        virtual ~PadEvent();
        
        virtual inline float xRatio() { return __xRatio; }
        virtual inline float yRatio() { return __yRatio; }
        virtual inline float xValue() { return __xValue; }
        virtual inline float yValue() { return __yValue; }
        virtual inline float zValue() { return __zValue; }
        
    protected:
        
    private:
        
    };
    
}
