/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashSprite.h
 
 ActionScript3.0 Reference
 flash.display.Sprite
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Sprite.html
 
 */

#pragma once

#include "flDisplayObjectContainer.h"
#include "flGraphics.h"
#include "flmath.h"

using namespace flinternal;

namespace fl2d {
    
    class flStage;
    class flSprite : public flDisplayObjectContainer {
        friend flStage;
        
        public:
        
        protected:
            flGraphics* _graphics;
        
            flSprite* __client = NULL;
        
            bool _showHitArea = false;
        
        private:
            ofPoint _draggablePoint;
            flRectangle* _draggableArea = NULL;
        
            bool _buttonMode;
            flDisplayObject* _dropTarget = NULL;
            bool _useHandCursor;
        
            flSprite* _hitArea = NULL;

        public:
            flSprite();
            virtual ~flSprite();
        
            virtual void update();
            virtual void draw(bool applyMatrix = true);
        
            virtual float width();
            virtual void width(float value);
        
            virtual float height();
            virtual void height(float value);
        
            virtual float scaleX();
            virtual void scaleX(float value);
        
            virtual float scaleY();
            virtual void scaleY(float value);
        
            //            virtual float alpha();
            //            virtual void alpha(float value);
        
            virtual inline flGraphics* graphics() { return _graphics; }
        
            //TODO
            virtual flSprite* hitArea();
            virtual void hitArea(flSprite* value);
        
            virtual bool hitTestPoint(float x, float y, bool shapeFlag = false);
        
            virtual void useHandCursor(bool value);
            virtual bool useHandCursor();
        
            //void startDrag(bool lockCenter = false, flRectangle bounds = NULL);
            virtual void startDrag(bool lockCenter = false, flRectangle* bounds = NULL);
            virtual void stopDrag();
        
        protected:
            //virtual void updateOnFrame(){};
            virtual void _updateRect();
        
        private:
            void _updateEventHandler(ofEventArgs& args);
        
            virtual void __compoundAlpha(float value);
        
            void _mouseDragging(int x, int y, int id);
            void _mouseDragging(ofMouseEventArgs& event) { _mouseDragging(event.x, event.y, -1); };
        
            // TODO :: soundTransform
    };
    
}
