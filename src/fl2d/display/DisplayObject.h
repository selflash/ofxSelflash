/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashDisplayObject.h
 
 ActionScript3.0 Reference
 flash.display.DisplayObject
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/DisplayObject.html
 
 */

#pragma once

#include "../events/EventDispatcher.h"
#include "../geom/Matrix.h"
#include "../geom/Rectangle.h"

#define	BLEND_MODE_NORMAL		0
#define	BLEND_MODE_LAYER		1
#define	BLEND_MODE_MULTIPLY		2
#define	BLEND_MODE_SCREEN		3
#define	BLEND_MODE_LIGHTEN		4
#define	BLEND_MODE_DARKEN		5
#define	BLEND_MODE_DIFFERENCE	6
#define	BLEND_MODE_ADD			7
#define	BLEND_MODE_SUBTRACT		8
#define	BLEND_MODE_INVERT		9
#define	BLEND_MODE_ALPHA		10
#define	BLEND_MODE_ERASE		11
#define	BLEND_MODE_OVERLAY		12
#define	BLEND_MODE_HARDLIGHT	13

namespace fl2d {
    
    class Stage;
    class DisplayObject : public EventDispatcher {
        friend Stage;
        
        public:
            
        protected:
            string _name;
        
            DisplayObject* _stage;
            DisplayObject* _parent;
            DisplayObject* _mask;
        
            float _z;
        
            float _realWidth;
            float _realHeight;
            float _targetWidth;
            float _targetHeight;
        
            float _scaleZ;
        
            float _rotationX;
            float _rotationY;
            float _rotationZ;
        
            float _alpha;
            //Bitmap, Stage,
            float __compoundAlpha;
        
            bool _visible;
        
            int	 _blendMode;
            int	_level;

            Matrix _matrix;
            Matrix _concatenatedMatrix;
            Matrix _concatenatedMatrixInv;
            
            Rectangle* _rect;
            ofPoint _rectTransformed[4];
            Rectangle* _pixelBounds;
                
            bool _smoothing;
        
            int	_mouseX;
            int	_mouseY;
        
        private:
        
        public:
            virtual void setup();
            virtual void update();
            virtual void draw();
            
            virtual string name();
            virtual void name(string value);
            
            virtual DisplayObject* stage();
            virtual void stage(DisplayObject* value);
            
            virtual DisplayObject* parent();
            virtual void parent(DisplayObject* value);
            
            virtual DisplayObject* mask();
            virtual void mask(DisplayObject* value);
        
            virtual float x();
            virtual void x(float value);
            
            virtual float y();
            virtual void y(float value);
            
            virtual float z();
            virtual void z(float value);
        
            virtual float width();
            virtual void width(float value);
            
            virtual float height();
            virtual void height(float value);
        
            //const float& scale();
            //void scale(float value);
            
            virtual float scaleX();
            virtual void scaleX(float value);
            
            virtual float scaleY();
            virtual void scaleY(float value);
            
            virtual float scaleZ();
            virtual void scaleZ(float value);
        
            virtual float rotation();
            virtual void rotation(float value);
            
            virtual float rotationX();
            virtual void rotationX(float value);
            
            virtual float rotationY();
            virtual void rotationY(float value);
            
            virtual float rotationZ();
            virtual void rotationZ(float value);
        
            virtual float alpha();
            virtual void alpha(float value);
            //const float& compoundAlpha();
            
            virtual bool visible();
            virtual void visible(bool value);
            
            virtual int blendMode();
            virtual void blendMode(int value);
            
            virtual int level();
            virtual void level(int value);
            
            virtual const Matrix& matrix();
            virtual void matrix(const Matrix& mat);
            
            virtual const Matrix& concatenatedMatrix();
            
            virtual Rectangle getRect(DisplayObject* targetCoordinateSpace);
            
            virtual bool hitTestObject(DisplayObject* obj);
            
            virtual bool hitTestPoint(float x, float y, bool shapeFlag = false);
            
            virtual ofPoint	globalToLocal(const ofPoint& point);
            
            virtual ofPoint	globalToLocal3D(const ofPoint& point);
            
            virtual ofPoint	local3DToGlobal(const ofPoint& point);
            
            virtual ofPoint	localToGlobal(const ofPoint& point);
            
            //	TODO :: cacheAsBitmap - maybe this can be an FBO?
            //	TODO :: transform :: http://livedocs.adobe.com/flex/3/langref/flash/geom/Transform.html
            //	TODO :: events - added, addedToStage, enterFrame, exitFrame, frameConstructed, removed, removedFromStage, render
            
            virtual void transform(const Matrix& mat);
            
            virtual bool smoothing();
            virtual void smoothing(bool value);
        
            virtual int mouseX();
            virtual int mouseY();
        
        protected:
            DisplayObject();
            ~DisplayObject();
            
            //for override
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
            
            //virtual void updateOnFrame(){};
            //virtual void drawOnFrame(){};
        
        private:
    };
    
}
