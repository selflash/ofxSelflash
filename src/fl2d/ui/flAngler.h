#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flAnglerEvent.h"
#include "flmath.h"

using namespace flinternal;

namespace fl2d {
    
    class flAngler : public flUIBase {
        
    public:
        flSprite* lever;
        
    protected:
        
    private:
        //------------------------------------------
        float _value = 0.0;
        
        ofPoint* _center = NULL;
        
        float _areaRadius;
        float _leverRadius;
        
        ofPoint* _draggablePoint = NULL;
        //------------------------------------------
        
        //------------------------------------------
        bool _flgX;
        bool _flgY;
        float _targetX;
        float _targetY;
        //------------------------------------------
        
        float _zeroAngle = 0.0;
        bool _flg = false;
        ofVec2f _outPosition;
        
    public:
        flAngler(float areaDiameter = 36, float leverDiameter = 10);
        virtual ~flAngler();
        
        virtual flTextField* label();
        virtual void label(flTextField* value);
        
        float value();
        
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
        
        virtual void drawArc(float angle, float innerRad = 18, float outerLRad = 36);
        
    private:
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}
