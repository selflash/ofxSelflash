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
            ~PadEvent();
            
            virtual float xRatio();
            virtual float yRatio();
            virtual float xValue();
            virtual float yValue();
            virtual float zValue();
        
        protected:
            
        private:
            
    };
    
}