/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashDisplayObject.h
 
 ActionScript3.0 Reference
 flash.display.DisplayObject
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/DisplayObject.html
 
 */

#pragma once

#include "flEventDispatcher.h"
#include "flMatrix.h"
#include "flRectangle.h"

#define	FL_BLEND_MODE_NORMAL		0
#define	FL_BLEND_MODE_LAYER		    1
#define	FL_BLEND_MODE_MULTIPLY		2
#define	FL_BLEND_MODE_SCREEN		3
#define	FL_BLEND_MODE_LIGHTEN		4
#define	FL_BLEND_MODE_DARKEN		5
#define	FL_BLEND_MODE_DIFFERENCE	6
#define	FL_BLEND_MODE_ADD			7
#define	FL_BLEND_MODE_SUBTRACT		8
#define	FL_BLEND_MODE_INVERT		9
#define	FL_BLEND_MODE_ALPHA		   10
#define	FL_BLEND_MODE_ERASE		   11
#define	FL_BLEND_MODE_OVERLAY	   12
#define	FL_BLEND_MODE_HARDLIGHT    13

namespace fl2d {
    
    class flStage;
    class flDisplayObject : public flEventDispatcher {
        friend flStage;
        
    public:
        
    protected:
        string _name;
        
        flDisplayObject* _stage;
        flDisplayObject* _parent;
        flDisplayObject* _mask;
        
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
        float _compoundAlpha;
        
        bool _visible;
        
        int	 _blendMode;
        int	_level;
        
        flMatrix _matrix;
        flMatrix _concatenatedMatrix;
        flMatrix _concatenatedMatrixInv;
        
        flRectangle* _rect;
        ofPoint _rectTransformed[4];
        flRectangle* _pixelBounds;
        
        bool _enabledSmoothing;
        bool _enabledAntiAliasing;
        
        int	_mouseX;
        int	_mouseY;
        
    private:
        
    public:
        virtual void setup();
        virtual void update();
        virtual void draw(bool applyMatrix = true);
        
        virtual string name();
        virtual void name(string value);
        
        virtual flDisplayObject* stage();
        virtual void stage(flDisplayObject* value);
        
        virtual flDisplayObject* parent();
        virtual void parent(flDisplayObject* value);
        
        virtual flDisplayObject* mask();
        virtual void mask(flDisplayObject* value);
        
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
        
        virtual const flMatrix& matrix();
        virtual void matrix(const flMatrix& mat);
        
        virtual const flMatrix& concatenatedMatrix();
        
        virtual flRectangle getRect(flDisplayObject* targetCoordinateSpace);
        
        virtual bool hitTestObject(flDisplayObject* obj);
        
        virtual bool hitTestPoint(float x, float y, bool shapeFlag = false);
        
        virtual ofPoint	globalToLocal(const ofPoint& point);
        
        virtual ofPoint	globalToLocal3D(const ofPoint& point);
        
        virtual ofPoint	local3DToGlobal(const ofPoint& point);
        
        virtual ofPoint	localToGlobal(const ofPoint& point);
        
        //	TODO :: cacheAsBitmap - maybe this can be an FBO?
        //	TODO :: transform :: http://livedocs.adobe.com/flex/3/langref/flash/geom/Transform.html
        //	TODO :: events - added, addedToStage, enterFrame, exitFrame, frameConstructed, removed, removedFromStage, render
        
        virtual void transform(const flMatrix& mat);
        
        virtual bool enabledSmoothing();
        virtual void enabledSmoothing(bool value);
        
        virtual bool enabledAntiAliasing();
        virtual void enabledAntiAliasing(bool value);
        
        virtual int mouseX();
        virtual int mouseY();
        
    protected:
        flDisplayObject();
        virtual ~flDisplayObject();
        
        //for override
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _updateRect();
        
        virtual float __compoundAlpha();
        virtual void __compoundAlpha(float value);
        
        //virtual void updateOnFrame(){};
        //virtual void drawOnFrame(){};
        
    private:
    };
    
}
