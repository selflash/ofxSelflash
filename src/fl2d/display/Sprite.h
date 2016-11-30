/**
 
 Original code ported from julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashSprite.h
 
 ActionScript3.0 Reference
 flash.display.Sprite
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Sprite.html
 
 */

#pragma once

#include "DisplayObjectContainer.h"
#include "Graphics.h"

namespace fl2d {
    
    class Sprite : public DisplayObjectContainer {
        public:
        
        protected:
            Graphics* _graphics;
        
        private:
            ofPoint _draggablePoint;
            Rectangle* _draggableArea;
            
            bool _buttonMode;
            DisplayObject* _dropTarget;
            bool _useHandCursor;        
            
        public:
            Sprite();
            ~Sprite();

            virtual void update();
            virtual void draw();
            
            virtual float width();
            virtual void width(float value);
            
            virtual float height();
            virtual void height(float value);
        
            virtual float scaleX();
            virtual void scaleX(float value);
            
            virtual float scaleY();
            virtual void scaleY(float value);
        
            virtual float alpha();
            virtual void alpha(float value);
        
            virtual Graphics* graphics();
        
            //TODO
            Sprite* client;
            Sprite* _hitArea;
            Sprite* hitArea();
            void hitArea(Sprite* value);
        
            virtual bool hitTestPoint(float x, float y, bool shapeFlag = false);
        
            virtual void useHandCursor(bool value);
            virtual bool useHandCursor();
            
            //void startDrag(bool lockCenter = false, Rectangle bounds = NULL);
            virtual void startDrag(bool lockCenter = false, Rectangle* bounds = NULL);
            virtual void stopDrag();
        
        protected:
            //virtual void updateOnFrame(){};
            virtual void _updateRect();
        
        private:
            void _mouseDragging(int x, int y, int id);
            void _mouseDragging(ofMouseEventArgs& event) { _mouseDragging(event.x, event.y, -1); };

            // TODO :: soundTransform
    };
    
}
