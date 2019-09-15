/**
 
 ActionScript3.0 Reference
 flash.ui.Keyboard
 http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/flash/ui/Keyboard.html
 
 */

#pragma once

#include "ofMain.h"

namespace fl2d {
    
    class flStage;
    class flKeyboard {
        friend flStage;
        
    public:
        static bool isShiftKeyDown();
        static void isShiftKeyDown(bool value);
        static bool isShiftKeyChanged();
        
        static bool isSpaceKeyDown();
        static void isSpaceKeyDown(bool value);
        static bool isSpaceKeyChanged();
        
    protected:
        
    private:
        static vector<int> _downKeyList;
        
        static bool _isShiftKeyDown;
        static bool _isShiftKeyChanged;
        
        static bool _isSpaceKeyDown;
        static bool _isSpaceKeyChanged;
        
    public:
        static void setup();
        static void update();
        static void draw();
        
    protected:
        
    private:
        flKeyboard();
        virtual ~flKeyboard();
        
        static void __addDownKey(int value);
        static void __removeDownKey(int value);
        static bool __checkKeyIsDown(int value);
    };
    
}
