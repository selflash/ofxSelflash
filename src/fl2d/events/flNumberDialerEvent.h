#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flNumberDialer;
    class flNumberDialerEvent : public flEvent {
        friend class flNumberDialer;
        
    public:
        static string CHANGE;
        
    protected:
        
    private:
        
    public:
        flNumberDialerEvent(string type);
        virtual ~flNumberDialerEvent();
        
        template <class T>
        T data() { return getProperty<T>("data"); }
        
    protected:
        
    private:
        template <class T>
        void data(T value) { setProperty<T>("data", value); }
        
    };
    
}
