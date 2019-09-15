#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flComboBox;
    class flComboBoxEvent : public flEvent {
        friend class flComboBox;
        
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
        flComboBoxEvent(string type);
        
        template <class T>
        flComboBoxEvent(string type, T data) {
//            cout << "[flComboBoxEvent]ComboBoxEvent2()" << endl;
            
            _type = type;
            
            setProperty<T>("data", data);
            
            _currentTarget = NULL;
            _target = NULL;
        }
        
        virtual ~flComboBoxEvent();
        
        virtual inline string label() { return __label; }
        
        template <class T>
        T data() { return getProperty<T>("data"); }
        
    protected:
        
    private:
        
    };
    
}
