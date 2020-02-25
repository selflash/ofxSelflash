#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flSlider : public flUIBase {
        
        public:
            flSprite* track = NULL;
            flSprite* thumb = NULL;
            flSprite* bar = NULL;
        
        protected:
        
        private:
            bool _roundEnabled = false;

            ofColor _normalBarColor;
            ofColor _overBarColor;
            ofColor _activeBarColor;
            ofColor _disableNormalBarColor;
            ofColor _disableActiveBarColor;
        
            float _trackWidth = 150;
            float _trackHeight = 18;
            float _thumbWidth = 10;
            float _barWidth = 50;
        
            float _min = 0.0;
            float _max = 100.0;
            float _range = 100.0;
            float _value = 50.0;
            float _percent = 0.5;

            flTextField* _valueText = NULL;
            int _digit = 2;

            ofPoint _draggablePoint;
        
        public:
            flSlider(float trackWidth = 200, float min = 0, float max = 100, float defaultValue = 0);
            virtual ~flSlider();
        
            virtual void label(flTextField* value);
        
            virtual void enabled(bool value);
            
            bool roundEnabled();
            void roundEnabled(bool value);

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

            //------------------------------------------
            ofParameter<float>* _floatParam = NULL;
            ofParameter<int>* _intParam = NULL;
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<float>& param) {
                _listeners.unsubscribeAll();
                _floatParam = NULL;
                _intParam = NULL;
                
                _floatParam = &param;
                _listeners.push(_floatParam->newListener([&](float& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        value(val);
                    }
                }));

                _bChangedByOfParm["value"] = true;
                value(_floatParam->get());
            }
            virtual inline void bind(ofParameter<int>& param) {
                _listeners.unsubscribeAll();
                _floatParam = NULL;
                _intParam = NULL;

                _intParam = &param;
                _listeners.push(_intParam->newListener([&](int& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        value(val);
                    }
                }));
                
                _bChangedByOfParm["value"] = true;
                value(_intParam->get());
            }
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
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
