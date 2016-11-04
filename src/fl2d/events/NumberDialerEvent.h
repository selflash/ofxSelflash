#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class NumberDialer;
    class NumberDialerEvent : public Event {
        friend class NumberDialer;
            
        public:
            static string CHANGE;
            
        protected:
            
        private:
        
        public:
            NumberDialerEvent(string type);
            ~NumberDialerEvent();
        
            template <class T>
            T data() { return getProperty<T>("data"); }
            
        protected:
            
        private:
            template <class T>
            void data(T value) { setProperty<T>("data", value); }
        
    };
    
}