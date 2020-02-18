#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flSlider : public flUIBase {
        
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
        int _digit;

        ofPoint _draggablePoint;
        
    public:
        flSlider(float trackWidth = 200, float min = 0, float max = 100, float defaultValue = 0);
        virtual ~flSlider();
        
        virtual flTextField* label();
        virtual void label(flTextField* value);

        virtual bool enabled();
        virtual void enabled(bool value);

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
        
        //------------------------------------------
        ofParameter<float>* _floatParam;
        ofParameter<int>* _intParam;
        virtual inline void bind(ofParameter<float>& param) {
            if(_floatParam != NULL) {
                _valueListener.unsubscribe();
                _floatParam = NULL;
            }
            if(_intParam != NULL) {
                _valueListener.unsubscribe();
                _intParam = NULL;
            }
            
            _floatParam = &param;
            _valueListener = _floatParam->newListener([&](float& val) {
                if(_changedValueByMyself) {
                    _changedValueByMyself = false;
                } else {
                    value(val);
                }
            });

            value(_floatParam->get());
        }
        virtual inline void bind(ofParameter<int>& param) {
            if(_floatParam != NULL) {
                _valueListener.unsubscribe();
                _floatParam = NULL;
            }
            if(_intParam != NULL) {
                _valueListener.unsubscribe();
                _intParam = NULL;
            }
            
            _intParam = &param;
            _valueListener = _intParam->newListener([&](int& val) {
                if(_changedValueByMyself) {
                    _changedValueByMyself = false;
                } else {
                    value(val);
                }
            });
            
            value(_intParam->get());
        }
        virtual inline void unbind() {
            _valueListener.unsubscribe();
            _floatParam = NULL;
            _intParam = NULL;
        }
        //------------------------------------------
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();

        virtual void _changeValue(bool dispatch = true);

        virtual void _trackOver();
        virtual void _thumbOver();
        virtual void _trackOut();
        virtual void _thumbOut();
        virtual void _press();
        virtual void _release();
        
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
        virtual void _mouseEventHandler(flEvent& event);
    };
}
