#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flHistgramViewer;
    class flHistgramViewerEvent : public flEvent {
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        flHistgramViewerEvent(string type);
        virtual ~flHistgramViewerEvent();
        
        //            HistgramViewerEvent* clone();
        
    protected:
        
    private:
        
    };
    
}
