#include "FlashConfig.h"

namespace fl2d {

    int FlashConfig::UI_LABEL_NORMAL_COLOR = 0xffffff;
    int FlashConfig::UI_LABEL_OVER_COLOR = 0xffffff;
    int FlashConfig::UI_LABEL_ACTIVE_COLOR = 0xffffff;

    int FlashConfig::UI_LINE_COLOR = 0xffffff;
    int FlashConfig::UI_NORMAL_COLOR = 0xaaaaaa;
    int FlashConfig::UI_OVER_COLOR = 0x00cccc;
    int FlashConfig::UI_ACTIVE_COLOR = 0x00ffff;
    
    //OF_EVENT_ORDER_BEFORE_APP, OF_EVENT_ORDER_APP, OF_EVENT_ORDER_AFTER_APP;
    
    ofEventOrder FlashConfig::MOUSE_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    ofEventOrder FlashConfig::KEYBOARD_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    ofEventOrder FlashConfig::UPDATE_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    ofEventOrder FlashConfig::DRAW_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    ofEventOrder FlashConfig::WINDOW_PRIORITY = OF_EVENT_ORDER_AFTER_APP;
    
    string FlashConfig::_FONT_PATH = "fl/fl2d/fonts/verdana.ttf";
    string FlashConfig::_COLORWHEEL_IMAGE_PATH = "fl/fl2d/images/colorwheel.png";

}