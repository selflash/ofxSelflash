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
        flSprite* minThumb;
        flSprite* maxThumb;
        flSprite* bar;
        
    protected:
        
    private:
        flTextField* _label;
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
        bool _enabled;

        ofPoint* _draggablePoint;
        
    public:
        flRangeSlider(float trackWidth = 200, float min = 0, float max = 100, float minValue = 40, float maxValue = 60);
        virtual ~flRangeSlider();
        
        flTextField* label();
        void label(flTextField* value);

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
        
        bool enabled();
        void enabled(bool value);

    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();

        virtual void _over();
        virtual void _barOut();
        virtual void _thumbOut();
        virtual void _barDown();
        virtual void _minThumbDown();
        virtual void _maxThumbDown();
        virtual void _up();
        
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
        void _mouseEventHandler(flEvent& event);
        
    };
}
