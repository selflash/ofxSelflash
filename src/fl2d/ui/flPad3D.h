#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flPadEvent.h"

namespace fl2d {
    
    class flPad3D : public flSprite {
        
    public:
        flSprite* ball;
        
    protected:
        
    private:
        flTextField* _labelText;
        flTextField* _value1Text;
        flTextField* _value2Text;
        
        float _width;
        float _height;
        
        float _lineColor;
        float _normalColor;
        float _overColor;
        float _activeColor;
        
        float _ballRadius;
        
        float _xValue;
        float _yValue;
        
        ofPoint* _draggablePoint;
        
    public:
        flPad3D(float width = 100, float height = 100);
        virtual ~flPad3D();
        
        string label();
        void label(string value, int color = 0xffffff);
        
        void textColor(int color = 0xffffff);
        
        float xValue();
        void xValue(float value);
        
        float yValue();
        void yValue(float value);
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
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
    };
    
}
