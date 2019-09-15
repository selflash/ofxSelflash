#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flAnglerEvent.h"
#include "flmath.h"

using namespace flinternal;

namespace fl2d {
    
    class flAngler : public flSprite {
        
    public:
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
        flAngler(float areaDiameter = 50, float leverDiameter = 10);
        virtual ~flAngler();
        
        flTextField* label();
        void label(flTextField* value);
        
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
        void _mouseEventHandler(flEvent& event);
    };
    
}
