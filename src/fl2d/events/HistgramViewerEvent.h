#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class HistgramViewer;
    class HistgramViewerEvent : public Event {
        public:
            static string CHANGE;
        
        protected:
        
        private:
        
        public:
            HistgramViewerEvent(string type);
            virtual ~HistgramViewerEvent();
        
//            HistgramViewerEvent* clone();

        protected:
            
        private:
        
    };
    
}
