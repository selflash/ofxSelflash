#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flJoyStick1Event.h"

namespace fl2d {
    
    class flJoyStick1 : public flSprite {
        
    public:
        //水平
        static string HORIZONTALLY;
        //垂直
        static string VERTICALLY;
        
        flSprite* lever;
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
        
        flTextField* _label;
        
        string _type;
        
        //------------------------------------------
        float _value;
        
        ofPoint _center;
        
        float _uiLength;
        float _leverRadius;
        
        ofPoint _draggablePoint;
        //------------------------------------------
        
        //------------------------------------------
        bool _flg;
        float _targetValue;
        //------------------------------------------
        
        bool _enabled;
        
    public:
        flJoyStick1(float length = 100, float leverDiameter = 14);
        virtual ~flJoyStick1();
        
        flTextField* label();
        void label(flTextField* value);
        
        string type();
        void type(string value);
        
        float value();
        
        void moveLever(float value = 1.0);
        
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
