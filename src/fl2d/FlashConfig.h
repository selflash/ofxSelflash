#pragma once

#include "ofMain.h"

namespace fl2d {
    
    class Font;
    class CircleColorPicker;
    class FlashConfig {
        friend Font;
        friend CircleColorPicker;
        
        public:
            static int UI_LABEL_NORMAL_COLOR;
            static int UI_LABEL_OVER_COLOR;
            static int UI_LABEL_ACTIVE_COLOR;
            
            static int UI_LINE_COLOR;
            static int UI_NORMAL_COLOR;
            static int UI_OVER_COLOR;
            static int UI_ACTIVE_COLOR;
        
            static ofEventOrder MOUSE_PRIORITY;
            static ofEventOrder KEYBOARD_PRIORITY;
            static ofEventOrder UPDATE_PRIORITY;
            static ofEventOrder DRAW_PRIORITY;
            static ofEventOrder WINDOW_PRIORITY;
        
        private:
            static string _FONT_PATH;
            static string _COLORWHEEL_IMAGE_PATH;
    };
    
}