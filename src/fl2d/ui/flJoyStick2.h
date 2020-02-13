#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flJoyStick2Event.h"

namespace fl2d {
    
    class flJoyStick2 : public flSprite {
        
    public:
        flSprite* lever;
    protected:
        
    private:
        flTextField* _label;
        
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
        flJoyStick2(float areaDiameter = 50, float leverDiameter = 25);
        virtual ~flJoyStick2();
        
        flTextField* label();
        void label(flTextField* value);
        
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
        void _mouseEventHandler(flEvent& event);
    };
    
}
