#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flRotarySliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flRotarySlider : public flUIBase {
        
    public:
        flSprite* lever;
    protected:
        
    private:
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
        
    public:
        flRotarySlider(float areaDiameter = 50, float leverDiameter = 10);
        virtual ~flRotarySlider();
        
        virtual void label(flTextField* value);
        
        float xValue();
        float yValue();
        
        void leverUp(float value = 1.0);
        void leverDown(float value = 1.0);
        void leverLeft(float value = 1.0);
        void leverRight(float value = 1.0);
        
        virtual bool enabled();
        virtual void enabled(bool value);
        
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
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}
