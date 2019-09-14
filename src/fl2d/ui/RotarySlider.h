#pragma once

#include "ofMain.h"

#include "FlashConfig.h"
#include "Sprite.h"
#include "TextField.h"
#include "RotarySliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class RotarySlider : public Sprite {
        
    public:
        Sprite* lever;
    protected:
        
    private:
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _normalLineColor;
        ofFloatColor _overLineColor;
        ofFloatColor _activeLineColor;
        ofFloatColor _deactiveLineColor;
        
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        ofFloatColor _deactiveColor;
        
        TextField* _label;
        
        //------------------------------------------
        float _xValue;
        float _yValue;
        
        ofPoint* _center;
        
        float _areaRadius;
        float _leverRadius;
        
        ofPoint* _draggablePoint;
        //------------------------------------------
        
        //------------------------------------------
        bool _flgX;
        bool _flgY;
        float _targetX;
        float _targetY;
        //------------------------------------------
        
        bool _enabled;
        
    public:
        RotarySlider(float areaDiameter = 50, float leverDiameter = 10);
        virtual ~RotarySlider();
        
        TextField* label();
        void label(TextField* value);
        
        float xValue();
        float yValue();
        
        void leverUp(float value = 1.0);
        void leverDown(float value = 1.0);
        void leverLeft(float value = 1.0);
        void leverRight(float value = 1.0);
        
        bool enabled();
        void enabled(bool value);
        
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
        void _mouseEventHandler(Event& event);
    };
    
}
