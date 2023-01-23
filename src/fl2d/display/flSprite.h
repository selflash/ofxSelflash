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
#include "flToolTip.h"
#include "flMouseEvent.h"
#include "flmath.h"

using namespace flinternal;

namespace fl2d {
    
    class flStage;
    class flSprite : public flDisplayObjectContainer {
        friend flStage;
        
        public:
        
        protected:
            flGraphics* _graphics = NULL;
        
            flSprite* __hitAreaObject = NULL;
        
            bool _rectVisible = false;
            
            //--------------------------------------
            //Tooltip
            flToolTip* _toolTip = NULL;
            bool _toolTipEnabled = false;
            string _toolTipText = "Some information is displayed here.";
            //--------------------------------------

        private:
			ofPoint _startDragPoint;
			ofPoint _tempPoint;

			ofPoint _draggablePoint;
            flRectangle* _draggableArea = nullptr;
            flRectangle* _tempDraggableArea = nullptr;
			bool _isGrabbed = false;
        
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
        
//            virtual float scaleX();
//            virtual void scaleX(float value);
//        
//            virtual float scaleY();
//            virtual void scaleY(float value);
        
            //            virtual float alpha();
            //            virtual void alpha(float value);
        
            virtual inline flGraphics* graphics() { return _graphics; }
        
            //TODO
            virtual flSprite* hitArea();
            virtual void hitArea(flSprite* value);
            virtual inline bool rectVisible() { return _rectVisible; }
            virtual inline void rectVisible(bool value) { _rectVisible = value; }

            virtual flRectangle getBounds(flDisplayObject* targetCoordinateSpace);
            virtual flRectangle getRect(flDisplayObject* targetCoordinateSpace);
                
            virtual bool hitTestPoint(float x, float y, bool shapeFlag = false);
        
            virtual void useHandCursor(bool value);
            virtual bool useHandCursor();
        
            //void startDrag(bool lockCenter = false, flRectangle bounds = NULL);
            virtual void startDrag(bool lockCenter = false, flRectangle* bounds = NULL);
            virtual void stopDrag();
			virtual inline bool isGrabbed() { return _isGrabbed; }
			virtual void draggableAreaSize(float x, float y = FLT_MIN, float width = FLT_MAX, float height = FLT_MAX) {
                if (!_draggableArea) {
                    _draggableArea = new flRectangle(x, y, width, height);
                }
                else {
                    _draggableArea->x(x);
                    _draggableArea->y(y);
                    _draggableArea->width(width);
                    _draggableArea->height(height);
                }

                _tempDraggableArea = _draggableArea;
            }
            virtual void clearDraggableAreaSize() {
                if (_draggableArea) {
                    delete _draggableArea;
                }
                _draggableArea = nullptr;
                _tempDraggableArea = nullptr;
            }

			virtual ofPoint startDragPoint() { return _startDragPoint; }
        
            //--------------------------------------
            //Tooltip
            inline flToolTip* toolTip() { return _toolTip; }
            bool toolTipEnabled();
            void toolTipEnabled(bool value);
            inline string toolTipText() { return _toolTipText; }
            inline void toolTipText(string value) {
                _toolTipText = value;
                if(_toolTip != NULL) _toolTip->text(_toolTipText);
            }
            //--------------------------------------
        
        protected:
            //virtual void updateOnFrame(){};
            virtual void _updateRect();
        
        private:        
            virtual void __compoundAlpha(float value);
        
            void _mouseDragging(int x, int y, int id);
            void _mouseDragging(ofMouseEventArgs& event) { _mouseDragging(event.x, event.y, -1); };
        
            // TODO :: soundTransform
        
            void _updateEventHandler(ofEventArgs& args);
            void _mouseEventHandler_flSprite(flEvent& event);

    };
    
}
