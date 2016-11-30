#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class ComboBox;
    class ComboBoxEvent : public Event {
        friend class ComboBox;
            
        public:
            static string CHANGE;
            static string CLOSE;
            static string ENTER;
            static string ITEM_ROLL_OUT;
            static string ITEM_ROLL_OVER;
            static string OPEN;
            static string SCROLL;
        
        protected:
            
        private:
            string __label;
        
        public:
            ComboBoxEvent(string type);
        
            template <class T>
            ComboBoxEvent(string type, T data) {
                cout << "[ComboBoxEvent]ComboBoxEvent2()" << endl;
                
                _type = type;
                
                setProperty<T>("data", data);
                
                _currentTarget = NULL;
                _target = NULL;
            }
            
            ~ComboBoxEvent();

            virtual inline string label() { return __label; }

            template <class T>
            T data() { return getProperty<T>("data"); }
        
        protected:
            
        private:
        
    };
    
}
