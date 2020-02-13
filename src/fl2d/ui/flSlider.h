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
		ofColor _normalBarColor;
        ofColor _overBarColor;
        ofColor _activeBarColor;
		ofColor _disableNormalBarColor;
        ofColor _disableActiveBarColor;

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
		bool _enabled;
        
        ofPoint* _draggablePoint;
        
    public:
        flSlider(float trackWidth = 200, float min = 0, float max = 100, float defaultValue = 0);
        virtual ~flSlider();
        
        flTextField* label();
        void label(flTextField* value);
        
//        void textColor(int color);
        
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

		bool enabled();
		void enabled(bool value);
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _trackOver();
        virtual void _thumbOver();
        virtual void _trackOut();
        virtual void _thumbOut();
        virtual void _trackDown();
        virtual void _thumbDown();
        virtual void _up();
        
        virtual void _setNormalColor();
        virtual void _setTrackOverColor();
        virtual void _setThumbOverColor();
        virtual void _setSelectedTrackOverColor();
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
