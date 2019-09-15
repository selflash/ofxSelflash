#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flPadEvent.h"
#include "flNumberDialer.h"
#include "flNumberDialerEvent.h"

namespace fl2d {
    
    class flPad2D : public flSprite {
        
    public:
        flSprite* ball;
        
    protected:
        
    private:
        float _width;
        float _height;
        float _areaWidth;
        float _areaHeight;
        float _n;
        
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        float _lineColor;
        float _normalColor;
        float _overColor;
        float _activeColor;
        
        flTextField* _label;
        flTextField* _xRatioText;
        flTextField* _yRatioText;
        flTextField* _xValueText;
        flTextField* _yValueText;
        
        float _ballRadius;
        
        float _xRatio;
        float _yRatio;
        float _xValue;
        float _yValue;
        
        float _leftValue;
        float _rightValue;
        float _topValue;
        float _bottomValue;
        float _rangeWidth;
        float _rangeHeight;
        
        ofPoint* _draggablePoint;
        
        flNumberDialer* _dialer01;
        flNumberDialer* _dialer02;
        flNumberDialer* _dialer03;
        flNumberDialer* _dialer04;
        
    public:
        flPad2D(float width = 100, float height = 100);
        flPad2D(float width, float height, float left, float right, float top, float bottom);
        virtual ~flPad2D();
        
        flTextField* label();
        void label(flTextField* value);
        
        float xRatio();
        void xRatio(float value, bool dispatch = true);
        
        float yRatio();
        void yRatio(float value, bool dispatch = true);
        
        float xValue();
        void xValue(float value, bool dispatch = true);
        
        float yValue();
        void yValue(float value, bool dispatch = true);
        
        float rangeWidth();
        void rangeWidth(float value, bool dispatch = true);
        
        float rangeHeight();
        void rangeHeight(float value, bool dispatch = true);
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _updateValue();
        
        virtual void _areaOver();
        virtual void _areaOut();
        virtual void _areaPress();
        virtual void _areaRelease();
        
        virtual void _ballOver();
        virtual void _ballOut();
        virtual void _ballPress();
        virtual void _ballRelease();
        virtual void _ballMove();
        
    private:
        void _mouseEventHandler(flEvent& event);
        void _uiEventHandler(flEvent& event);
    };
}
