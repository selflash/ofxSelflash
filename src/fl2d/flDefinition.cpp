#include "flDefinition.h"

namespace fl2d {
    //0x555555 = 85, 85, 85
    //0x12b2d2 = 18, 178, 210
    //0x999999 = 153, 153, 153
    //0x777777 = 119, 119, 119
    //0xbbdcde
    ofColor flDefinition::UI_LABEL_NORMAL_COLOR = ofColor(200, 200, 200, 255);
    ofColor flDefinition::UI_LABEL_OVER_COLOR = ofColor(255, 255, 255, 255);
    ofColor flDefinition::UI_LABEL_ACTIVE_COLOR = ofColor(230, 230, 230, 255);
    ofColor flDefinition::UI_LABEL_ACTIVE_COLOR_2 = ofColor(17, 157, 185, 255);
    ofColor flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR = ofColor(150, 150, 150, 255);
    ofColor flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR = ofColor(190, 190, 190, 255);

    ofColor flDefinition::UI_LINE_NORMAL_COLOR = ofColor(200, 200, 200, 255);
//    ofColor flDefinition::UI_LINE_OVER_COLOR = ofColor(18, 178, 210);
    ofColor flDefinition::UI_LINE_OVER_COLOR = ofColor(255, 255, 255, 255);
    ofColor flDefinition::UI_LINE_ACTIVE_COLOR = ofColor(18, 178, 210, 255);
    ofColor flDefinition::UI_LINE_DISABLE_NORMAL_COLOR = ofColor(150, 150, 150, 255);
    ofColor flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR = ofColor(190, 190, 190, 255);

    ofColor flDefinition::UI_NORMAL_COLOR = ofColor(85, 85, 85, 255);
    ofColor flDefinition::UI_OVER_COLOR = ofColor(18, 178, 210, 255);
    ofColor flDefinition::UI_ACTIVE_COLOR = ofColor(17, 157, 185, 255);
    ofColor flDefinition::UI_DISABLE_NORMAL_COLOR = ofColor(85, 85, 85, 255);
    ofColor flDefinition::UI_DISABLE_ACTIVE_COLOR = ofColor(13, 130, 153, 255);

//    int flDefinition::UI_LINE_COLOR = 0xffffff;
//    int flDefinition::UI_OVER_LINE_COLOR = 0x12b2d2;
//    int flDefinition::UI_ACTIVE_LINE_COLOR = 0x12b2d2;
//    //int flDefinition::UI_DEACTIVE_LINE_COLOR = 0xcccccc;
//    int flDefinition::UI_DEACTIVE_LINE_COLOR = 0x777777;

//    int flDefinition::UI_NORMAL_COLOR = 0x555555;
//    int flDefinition::UI_OVER_COLOR = 0x12b2d2;
//    int flDefinition::UI_ACTIVE_COLOR = 0x12b2d2;
//    int flDefinition::UI_DEACTIVE_COLOR = 0x333333;
	//int flDefinition::UI_DEACTIVE_COLOR = 0x5b2d2;

    //OF_EVENT_ORDER_BEFORE_APP, OF_EVENT_ORDER_APP, OF_EVENT_ORDER_AFTER_APP;
    
    //    ofEventOrder flDefinition::MOUSE_PRIORITY = OF_EVENT_ORDER_BEFORE_APP;
    //    ofEventOrder flDefinition::KEYBOARD_PRIORITY = OF_EVENT_ORDER_BEFORE_APP;
    //    
    //    bool flDefinition::AUTO_UPDATE = true;
    //    ofEventOrder flDefinition::UPDATE_PRIORITY = OF_EVENT_ORDER_BEFORE_APP;
    //    bool flDefinition::AUTO_DRAW = true;
    //    ofEventOrder flDefinition::DRAW_PRIORITY = OF_EVENT_ORDER_BEFORE_APP;
    //    
    //    ofEventOrder flDefinition::WINDOW_PRIORITY = OF_EVENT_ORDER_BEFORE_APP;
    
    
    //    ofEventOrder flDefinition::MOUSE_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    //    ofEventOrder flDefinition::KEYBOARD_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    //    
    //    bool flDefinition::AUTO_UPDATE = true;
    //    ofEventOrder flDefinition::UPDATE_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    //    bool flDefinition::AUTO_DRAW = true;
    //    ofEventOrder flDefinition::DRAW_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    //    
    //    ofEventOrder flDefinition::WINDOW_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    
    //    string flDefinition::_FONT_PATH = "fl/fl2d/fonts/verdana.ttf";
    string flDefinition::_FONT_PATH = "fl/fl2d/fonts/03SmartFontUI.ttf";
    //    string flDefinition::_FONT_PATH = "fl/fl2d/fonts/FLOPDesignFont.ttf";
    string flDefinition::_COLORWHEEL_IMAGE_PATH = "fl/fl2d/images/colorwheel.png";
    
}
