/**
 
 ActionScript3.0 Reference
 flash.display.Shape
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Shape.html
 
 */

#pragma once

#include "ofMain.h"

#include "flDisplayObjectContainer.h"
#include "flGraphics.h"

namespace fl2d {
    class flShape : public flDisplayObject {
    public:
        
    protected:
        flGraphics* _graphics;
        
    private:
        
    public:
        flShape();
        virtual ~flShape();
        
        virtual void update();
        virtual void draw(bool applyMatrix = true);
        
        //            virtual float alpha();
        //            virtual void alpha(float value);
        
        virtual inline flGraphics* graphics() { return _graphics; }
        
    protected:
        //            virtual void updateOnFrame(){};
        virtual void _updateRect();
        virtual void __compoundAlpha(float value);
        
    private:
        void _updateEventHandler(ofEventArgs& args);
        
    };
}
