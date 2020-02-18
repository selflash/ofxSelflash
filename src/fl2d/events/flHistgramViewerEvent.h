#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flHistgramViewer;
    class flHistgramViewerEvent : public flEvent {
        friend class flHistgramViewer;
        
        public:
            static string CHANGE;
            
        protected:
            float __value;

        private:
            
        public:
            flHistgramViewerEvent(string type);
            virtual ~flHistgramViewerEvent();
            
            virtual inline float value() { return __value; }

        protected:
            
        private:
            
    };
    
}
