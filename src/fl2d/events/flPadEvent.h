#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flPad2D;
    class flPad3D;
    class flPadEvent : public flEvent {
        friend class flPad2D;
        friend class flPad3D;
        
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
        flPadEvent(string type);
        virtual ~flPadEvent();
        
        virtual inline float xRatio() { return __xRatio; }
        virtual inline float yRatio() { return __yRatio; }
        virtual inline float xValue() { return __xValue; }
        virtual inline float yValue() { return __yValue; }
        virtual inline float zValue() { return __zValue; }
        
    protected:
        
    private:
        
    };
    
}
