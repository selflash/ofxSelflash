#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/AnglerEvent.h"
#include "../../utils/MathUtil.h"

namespace fl2d {
    
    class Angler : public Sprite {
        
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
        float _value;
        
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
        
        float _zeroAngle = 0.0;
        bool _flg = false;
        ofVec2f _outPosition;
        
    public:
        Angler(float areaDiameter = 50, float leverDiameter = 10);
        virtual ~Angler();
        
        TextField* label();
        void label(TextField* value);
        
        float value();
        
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
