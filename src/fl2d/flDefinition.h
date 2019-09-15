#pragma once

#include "ofMain.h"

namespace fl2d {
    
    class flFont;
    class flStage;
    class flCircleColorPicker;
    class flDefinition {
        friend flFont;
        friend flStage;
        friend flCircleColorPicker;
        
    public:
        static int UI_LABEL_NORMAL_COLOR;
        static int UI_LABEL_OVER_COLOR;
        static int UI_LABEL_ACTIVE_COLOR;
        static int UI_LABEL_DEACTIVE_COLOR;
        
        static int UI_LINE_COLOR;
        static int UI_OVER_LINE_COLOR;
        static int UI_ACTIVE_LINE_COLOR;
        static int UI_DEACTIVE_LINE_COLOR;
        
        static int UI_NORMAL_COLOR;
        static int UI_OVER_COLOR;
        static int UI_ACTIVE_COLOR;
        static int UI_DEACTIVE_COLOR;
        
    private:
        static string _FONT_PATH;
        static string _COLORWHEEL_IMAGE_PATH;
    };
    
}
