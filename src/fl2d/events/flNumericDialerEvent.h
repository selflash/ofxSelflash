#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flNumericDialer;
    class flNumericDialerEvent : public flEvent {
        friend class flNumericDialer;
        
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        flNumericDialerEvent(string type);
        virtual ~flNumericDialerEvent();
        
        template <class T>
        T data() { return getProperty<T>("data"); }
        
    protected:
        
    private:
        template <class T>
        void data(T value) { setProperty<T>("data", value); }
        
    };
    
}
