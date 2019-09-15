#include "flComboBoxEvent.h"

namespace fl2d {
    
    string flComboBoxEvent::CHANGE = "comboBoxChange";
    string flComboBoxEvent::ENTER = "enger";
    string flComboBoxEvent::ITEM_ROLL_OUT = "itemRollOut";
    string flComboBoxEvent::ITEM_ROLL_OVER = "itemRollOver";
    string flComboBoxEvent::OPEN = "open";
    string flComboBoxEvent::SCROLL = "scroll";
    
    //--------------------------------------------------------------
    //
    flComboBoxEvent::flComboBoxEvent(string type):flEvent(type) {
        __label = "";
    }
    
    //--------------------------------------------------------------
    //
    flComboBoxEvent::~flComboBoxEvent() {
        __label = "";
    }
    
}
