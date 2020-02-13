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
        static ofColor UI_LABEL_NORMAL_COLOR;
        static ofColor UI_LABEL_OVER_COLOR;
        static ofColor UI_LABEL_ACTIVE_COLOR;
        static ofColor UI_LABEL_ACTIVE_COLOR_2;
        static ofColor UI_LABEL_DISABLE_NORMAL_COLOR;
        static ofColor UI_LABEL_DISABLE_ACTIVE_COLOR;

        static ofColor UI_LINE_NORMAL_COLOR;
        static ofColor UI_LINE_OVER_COLOR;
        static ofColor UI_LINE_ACTIVE_COLOR;
        static ofColor UI_LINE_DISABLE_NORMAL_COLOR;
        static ofColor UI_LINE_DISABLE_ACTIVE_COLOR;
        
        static ofColor UI_NORMAL_COLOR;
        static ofColor UI_OVER_COLOR;
        static ofColor UI_ACTIVE_COLOR;
        static ofColor UI_DISABLE_NORMAL_COLOR;
        static ofColor UI_DISABLE_ACTIVE_COLOR;

//        static int UI_LINE_COLOR;
//        static int UI_OVER_LINE_COLOR;
//        static int UI_ACTIVE_LINE_COLOR;
//        static int UI_DEACTIVE_LINE_COLOR;
        
//        static int UI_NORMAL_COLOR;
//        static int UI_OVER_COLOR;
//        static int UI_ACTIVE_COLOR;
//        static int UI_DEACTIVE_COLOR;
        
    private:
        static string _FONT_PATH;
        static string _COLORWHEEL_IMAGE_PATH;
    };
    
}
