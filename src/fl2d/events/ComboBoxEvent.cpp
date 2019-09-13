#include "ComboBoxEvent.h"

namespace fl2d {

    string ComboBoxEvent::CHANGE = "comboBoxChange";
    string ComboBoxEvent::ENTER = "enger";
    string ComboBoxEvent::ITEM_ROLL_OUT = "itemRollOut";
    string ComboBoxEvent::ITEM_ROLL_OVER = "itemRollOver";
    string ComboBoxEvent::OPEN = "open";
    string ComboBoxEvent::SCROLL = "scroll";

    //--------------------------------------------------------------
    //
    ComboBoxEvent::ComboBoxEvent(string type):Event(type) {
        __label = "";
    }

    //--------------------------------------------------------------
    //
    ComboBoxEvent::~ComboBoxEvent() {
        __label = "";
    }
    
}
