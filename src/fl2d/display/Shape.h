/**
 
 ActionScript3.0 Reference
 flash.display.Shape
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Shape.html
 
 */

#pragma once

#include "ofMain.h"

#include "DisplayObjectContainer.h"
#include "Graphics.h"

namespace fl2d {
    class Shape : public DisplayObject {
        public:
            Graphics* graphics;
            
        protected:
            
        private:
            
        public:
            Shape();
            ~Shape();
        
            virtual void update();
            virtual void draw();
            
            virtual float alpha();
            virtual void alpha(float value);
            
        protected:
//            virtual void updateOnFrame(){};
        
        private:
            void _updateEventHandler(ofEventArgs& args);
        
        };
}
