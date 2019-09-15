#pragma once

#include "ofMain.h"

#include "flmath.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flRangeSliderEvent.h"

namespace fl2d {
    
    class flRangeSlider : public flSprite {
        
    public:
        flSprite* track;
        flSprite* nearThumb;
        flSprite* farThumb;
        flSprite* bar;
        
        
    protected:
        
    private:
        flTextField* _minValueText;
        flTextField* _maxValueText;
        
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        
        float _trackWidth;
        float _trackHeight;
        float _trackAlpha;
        
        float _thumbWidth;
        float _barWidth;
        float _barAlpha;
        
        float _percent;
        float _min;
        float _max;
        float _range;
        float _minValue;
        float _maxValue;
        
        bool _roundEnabled;
        
        ofPoint* _draggablePoint;
        
    public:
        flRangeSlider(float trackWidth = 200, float min = 0, float max = 100, float minValue = 40, float maxValue = 60);
        virtual ~flRangeSlider();
        
        void textColor(int color);
        
        float min();
        void min(float value, bool dispatch = true);
        
        float max();
        void max(float value, bool dispatch = true);
        
        float minValue();
        void minValue(float value, bool dispatch = true);
        
        float maxValue();
        void maxValue(float value, bool dispatch = true);
        
        float range();
        
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
        
        void _over();
        void _out();
        void _press();
        void _release();
        
    private:
        void _mouseEventHandler(flEvent& event);
        
    };
}
