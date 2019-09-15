/**
 
 ActionScript3.0 Reference
 flash.ui.Mouse
 http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/flash/ui/Mouse.html
 
 */

#pragma once

#include "ofMain.h"

#define FLASH_MOUSE_TYPE_ARROW         0
#define FLASH_MOUSE_TYPE_POINTING_HAND 1
#define FLASH_MOUSE_TYPE_OPEN_HAND     2
#define FLASH_MOUSE_TYPE_CLOSE_HAND    3

namespace fl2d {
    
    class flMouse {
    public:
        
    protected:
        static ofImage* _arrowImage;
        static ofImage* _pointingHandImage;
        static ofImage* _openHandImage;
        static ofImage* _closeHandImage;
        
    private:
        flMouse() {};
        virtual ~flMouse() {};
        
        static int _currentType;
        
    public:
        static void setup();
        static void hide();
        static void show();
        
        static bool currentType();
        
        static void showHandCursor();
        static void hideHandCursor();
        static void changeCursor(int type = 0);
        
        static void draw(float x, float y);
        
    protected:
        
    private:
    };
    
}
