﻿/**
 
 Original code is Gnash :: SWFRect
 http://www.gnu.org/software/gnash/
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/geom/ofxFlashRectangle.h
 
 ActionScript3.0 Reference
 fl.geom.Rectangle
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/geom/Rectangle.html
 
 */

#pragma once

#include "ofMain.h"

namespace fl2d {
    
    // forward decleration.
    class Matrix;
    class DisplayObject;
    class DisplayObjectContainer;
    class Shape;
    class Sprite;
    class Bitmap;
    class Graphics;
    class TextField;

    class Rectangle {
        //TODO
        friend Matrix;
        friend DisplayObject;
        friend DisplayObjectContainer;
        friend Shape;
        friend Sprite;
        friend Bitmap;
        friend Graphics;
        friend TextField;

        public:
            
        protected:
            
        private:
            float _xMin = 0.0;
            float _yMin = 0.0;
            float _xMax = 0.0;
            float _yMax = 0.0;
        
            bool _isChanged = false;
        
        public:
            Rectangle();
            Rectangle(float x, float y, float width, float height);
            virtual ~Rectangle();
            
            float x() const;
            void x(float value);
            
            float y() const;
            void y(float value);
            
            float left() const;
            void left(float value);
            
            float right() const;
            void right(float value);
            
            float top() const;
            void top(float value);
            
            float bottom() const;
            void bottom(float value);
            
            ofPoint& topLeft() const;
            void topLeft(ofPoint& value);
        
            ofPoint& bottomRight() const;
            void bottomRight(ofPoint& value);

            float size();
            
            float width();
            void width(float value);
            
            float height();
            void height(float value);
            
            bool isNull() const;
            bool isZero() const;
            bool pointTest(float x, float y);
        
            bool isChanged();
        
        protected:
            
        private:
            //DisplayObject
            void __setNull();
            void __setZero();
            void __expandTo(float x, float y);
            void __expandToX(float x);
            void __expandToY(float y);
            void __expandToPoint(float x, float y);
            void __expandToRect(const Rectangle& rect);
            void __expandToCircle(float x, float y, float radius);
        
            void __setToPoint(float x, float y);
            void __setToRect(const Rectangle& rect);
            void __setToRect(float x1, float y1, float x2, float y2);
        
            void __encloseRect(const vector<ofPoint>& points);
    };
}
