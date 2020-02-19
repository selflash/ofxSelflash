#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flRangeSliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flRangeSlider : public flUIBase {
        
    public:
        flSprite* track;
        flSprite* minThumb;
        flSprite* maxThumb;
        flSprite* bar;
        
    protected:
        
    private:
        flTextField* _minValueText;
        flTextField* _maxValueText;
        
        float _trackWidth;
        float _trackHeight;
        float _trackAlpha;
        
        float _thumbWidth;
        float _barWidth;
        
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
        
        virtual void label(flTextField* value);

//        void textColor(int color);
        
        float min();
        void min(float value, bool dispatch = true);
        
        float max();
        void max(float value, bool dispatch = true);
        
        float minValue();
        void minValue(float value, bool dispatch = true);
        
        float maxValue();
        void maxValue(float value, bool dispatch = true);
        
        float range();
        
        bool roundEnabled();
        void roundEnabled(bool value);
        
        virtual bool enabled();
        virtual void enabled(bool value);

    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();

        virtual void _over();
        virtual void _barOut();
        virtual void _thumbOut();
        virtual void _barPress();
        virtual void _minThumbPress();
        virtual void _maxThumbPress();
        virtual void _release();
        
        virtual void _setNormalColor();
        virtual void _setOverColor();
        virtual void _setSelectedBarOverColor();
        virtual void _setSelectedThumbOverColor();
        virtual void _setActiveColor();
        virtual void _setDisableNormalColor();
        virtual void _setDisableActiveColor();
        
        virtual void _drawTrackGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
        virtual void _drawBarGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);

    private:
        virtual void _mouseEventHandler(flEvent& event);
        
    };
}
