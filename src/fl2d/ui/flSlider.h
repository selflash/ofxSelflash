#pragma once

#include "ofMain.h"

#include "flmath.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flSliderEvent.h"

namespace fl2d {
    
    class flSlider : public flSprite {
        
    public:
        flSprite* track;
        flSprite* thumb;
        flSprite* bar;        
        
    protected:
        
    private:
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        
        flTextField* _label;
        flTextField* _valueText;
        
        float _trackWidth;
        float _trackHeight;
        float _thumbWidth;
        float _barWidth;
        
        float _percent;
        float _min;
        float _max;
        float _range;
        float _value;
        
        bool _roundEnabled;
        
        ofPoint* _draggablePoint;
        
    public:
        flSlider(float trackWidth = 200, float min = 0, float max = 100, float defaultValue = 0);
        virtual ~flSlider();
        
        flTextField* label();
        void label(flTextField* value);
        
        void textColor(int color);
        
        float min();
        void min(float value, bool dispatch = true);
        
        float max();
        void max(float value, bool dispatch = true);
        
        float value();
        void value(float value, bool dispatch = true);
        
        int barColor();
        void barColor(int value);
        void barColor(int red, int green, int blue, int alpha);
        void barColor(const ofColor& color);
        void barColor(const ofFloatColor& color);
        
        bool roundEnabled();
        void roundEnabled(bool value);
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
        virtual void _drawBarGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
        
        virtual void _trackOver();
        virtual void _trackOut();
        virtual void _trackPress();
        virtual void _trackRelease();
        
        virtual void _thumbOver();
        virtual void _thumbOut();
        virtual void _thumbPress();
        virtual void _thumbRelease();
        
    private:
        void _mouseEventHandler(flEvent& event);
    };
}
