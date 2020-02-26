#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flPadEvent.h"
#include "flNumericDialer.h"
#include "flNumericDialerEvent.h"

namespace fl2d {
    
    class flPad2D : public flUIBase {
        
    public:
        flSprite* lever;
        
    protected:
        
    private:
        flTextField* _ratioText = NULL;
        flTextField* _valueText = NULL;

        float _width;
        float _height;
        float _areaWidth;
        float _areaHeight;
        float _n;
        
        float _leverRadius;
        
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
        
        ofPoint _draggablePoint;
        
        flNumericDialer* _dialer01 = NULL;
        flNumericDialer* _dialer02 = NULL;
        flNumericDialer* _dialer03 = NULL;
        flNumericDialer* _dialer04 = NULL;
        
    public:
        flPad2D(float width = 100, float height = 100);
        flPad2D(float width, float height, float left, float right, float top, float bottom);
        virtual ~flPad2D();
        
        virtual void label(flTextField* value);
        virtual void enabled(bool value);
        
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
        
        virtual void _leverOver();
        virtual void _leverOut();
        virtual void _leverPress();
        virtual void _leverRelease();
        virtual void _leverMove();
        
        virtual void _setNormalColor();
        virtual void _setOverColor();
        virtual void _setSelectedOverColor();
        virtual void _setActiveColor();
        virtual void _setDisableNormalColor();
        virtual void _setDisableActiveColor();
        
        virtual void _drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
        virtual void _drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
        
    private:
        virtual void _mouseEventHandler(flEvent& event);
        void _uiEventHandler(flEvent& event);
    };
}
