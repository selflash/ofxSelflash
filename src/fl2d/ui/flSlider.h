﻿#pragma once

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
            int _digit = 2;

            ofColor _normalBarColor;
            ofColor _overBarColor;
            ofColor _activeBarColor;
            ofColor _disableNormalBarColor;
            ofColor _disableActiveBarColor;
        
            float _trackWidth = 150;
            float _trackHeight = 18;
            float _thumbWidth = 10;
            float _barWidth = 50;
        
			ofParameter<float> _min = 0.0;
			ofParameter<float> _max = 100.0;
            float _range = 100.0;
			ofParameter<float> _value = 0.0;
            float _percent = 0.5;

            flTextField* _valueText = NULL;

            ofPoint _draggablePoint;
        
        public:
            flSlider(float trackWidth = 200, float min = 0, float max = 100, float defaultValue = 0);
            virtual ~flSlider();
        
            virtual void label(flTextField* value);
        
            virtual void enabled(bool value);
            
            bool roundEnabled();
            void roundEnabled(bool value);

			ofParameter<float>& min();
            void min(float value, bool dispatch = true);
        
			ofParameter<float>& max();
            void max(float value, bool dispatch = true);
        
			ofParameter<float>& value();
            void value(float value, bool dispatch = true);
        
            int barColor();
            void barColor(int value);
            void barColor(int red, int green, int blue, int alpha);
            void barColor(const ofColor& color);
            void barColor(const ofFloatColor& color);

            //------------------------------------------
            ofParameter<float>* _floatParam = NULL;
            ofParameter<int>* _intParam = NULL;
            ofEventListeners _paramListeners;
            virtual inline void bind(ofParameter<float>& param) {
				roundEnabled(false);

                _paramListeners.unsubscribeAll();
                _floatParam = NULL;
                _intParam = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

				min(param.getMin(), false);
				max(param.getMax(), false);
				_floatParam = &param;
				_paramListeners.push(_floatParam->newListener([&](float& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        value(val);
                    }

                    //2023.04.07 動作確認不十分
                    _bChangedByOfParm["value"] = false;
                    _bChangedByMyself["value"] = false;
                }));

                _bChangedByOfParm["value"] = true;
                value(_floatParam->get());
				_bChangedByOfParm["value"] = false;
			}
            virtual inline void bind(ofParameter<int>& param) {
				roundEnabled(true);

                _paramListeners.unsubscribeAll();
                _floatParam = NULL;
                _intParam = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

				if (INT_MIN < param.getMin()) min(param.getMin(), false);
				if (param.getMax() < INT_MAX) max(param.getMax(), false);
				_intParam = &param;
                _paramListeners.push(_intParam->newListener([&](int& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        value(val);
                    }
                    
                    //2023.04.07 動作確認不十分
                    _bChangedByOfParm["value"] = false;
                    _bChangedByMyself["value"] = false;
                }));
                
                _bChangedByOfParm["value"] = true;
                value(_intParam->get());
				_bChangedByOfParm["value"] = false;
			}
            virtual inline void unbind() {
                _paramListeners.unsubscribeAll();
                _floatParam = NULL;
                _intParam = NULL;
            }
            //------------------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();

            virtual void _dispatchEvent();

            virtual void _onTrackOver();
            virtual void _onThumbOver();
            virtual void _onTrackOut();
            virtual void _onThumbOut();
            virtual void _onPress();
            virtual void _onRelease();
        
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
