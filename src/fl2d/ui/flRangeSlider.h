#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flRangeSliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flRangeSlider : public flUIBase {
        
        public:
            flSprite* track = NULL;
            flSprite* minThumb = NULL;
            flSprite* maxThumb = NULL;
            flSprite* bar = NULL;
        
        protected:
        
        private:
            bool _roundEnabled = false;
            int _digit = 2;

            //DEBUGG—p
            float _trackAlpha = 1.0;

            float _trackWidth = 150;
            float _trackHeight = 18;
            float _thumbWidth = 10;
            float _barWidth = 50;
        
			ofParameter<float> _min = 0.0;
			ofParameter<float> _max = 100.0;
			float _preRange = 0.0;
            float _range = 100.0;
			ofParameter<float> _minValue = 50.0;
			ofParameter<float> _maxValue = 70.0;
            float _percent = 0.5;

            flTextField* _minValueText = NULL;
            flTextField* _maxValueText = NULL;

            ofPoint _draggablePoint;
        
        public:
            flRangeSlider(float trackWidth = 200, float min = 0, float max = 100, float minValue = 40, float maxValue = 60);
            virtual ~flRangeSlider();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);
        
            bool roundEnabled();
            void roundEnabled(bool value);

			ofParameter<float>& min();
            void min(float value, bool dispatch = true);
        
			ofParameter<float>& max();
            void max(float value, bool dispatch = true);
        
			ofParameter<float>& minValue();
            void minValue(float value, bool dispatch = true);
        
			ofParameter<float>& maxValue();
            void maxValue(float value, bool dispatch = true);
        
            float range();

            //------------------------------------------
            ofParameter<float>* _floatMinParam = NULL;
            ofParameter<int>* _intMinParam = NULL;
            ofEventListeners _minListeners;
            virtual inline void bindMin(ofParameter<float>& param) {
                _minListeners.unsubscribeAll();
                _floatMinParam = NULL;
                _intMinParam = NULL;
                _bChangedByMyself["minValue"] = false;
                _bChangedByOfParm["minValue"] = false;

                _floatMinParam = &param;
                _minListeners.push(_floatMinParam->newListener([&](float& val) {
                    if(_bChangedByMyself["minValue"]) {
                        _bChangedByMyself["minValue"] = false;
                    } else {
                        _bChangedByOfParm["minValue"] = true;
                        minValue(val);
                    }
                }));
                
                _bChangedByOfParm["minValue"] = true;
                minValue(_floatMinParam->get());
				_bChangedByOfParm["minValue"] = false;
			}
            virtual inline void bindMin(ofParameter<int>& param) {
                _minListeners.unsubscribeAll();
                _floatMinParam = NULL;
                _intMinParam = NULL;
                _bChangedByMyself["minValue"] = false;
                _bChangedByOfParm["minValue"] = false;

                _intMinParam = &param;
                _minListeners.push(_intMinParam->newListener([&](int& val) {
                    if(_bChangedByMyself["minValue"]) {
                        _bChangedByMyself["minValue"] = false;
                    } else {
                        _bChangedByOfParm["minValue"] = true;
                        minValue(val);
                    }
                }));
                
                _bChangedByOfParm["minValue"] = true;
                minValue(_intMinParam->get());
				_bChangedByOfParm["minValue"] = false;
			}
        
            ofParameter<float>* _floatMaxParam = NULL;
            ofParameter<int>* _intMaxParam = NULL;
            ofEventListeners _maxListeners;
            virtual inline void bindMax(ofParameter<float>& param) {
                _maxListeners.unsubscribeAll();
                _floatMaxParam = NULL;
                _intMaxParam = NULL;
                _bChangedByMyself["maxValue"] = false;
                _bChangedByOfParm["maxValue"] = false;

                _floatMaxParam = &param;
                _maxListeners.push(_floatMaxParam->newListener([&](float& val) {
                    if(_bChangedByMyself["maxValue"]) {
                        _bChangedByMyself["maxValue"] = false;
                    } else {
                        _bChangedByOfParm["maxValue"] = true;
                        maxValue(val);
                    }
                }));
                
                _bChangedByOfParm["maxValue"] = true;
                maxValue(_floatMaxParam->get());
				_bChangedByOfParm["maxValue"] = false;
			}
            virtual inline void bindMax(ofParameter<int>& param) {
                _maxListeners.unsubscribeAll();
                _floatMaxParam = NULL;
                _intMaxParam = NULL;
                _bChangedByMyself["maxValue"] = false;
                _bChangedByOfParm["maxValue"] = false;

                _intMaxParam = &param;
                _maxListeners.push(_intMaxParam->newListener([&](int& val) {
                    if(_bChangedByMyself["maxValue"]) {
                        _bChangedByMyself["maxValue"] = false;
                    } else {
                        _bChangedByOfParm["maxValue"] = true;
                        maxValue(val);
                    }
                }));
                
                _bChangedByOfParm["maxValue"] = true;
                maxValue(_intMaxParam->get());
				_bChangedByOfParm["maxValue"] = false;
			}
            virtual inline void unbind() {
                _minListeners.unsubscribeAll();
                _maxListeners.unsubscribeAll();
                _floatMinParam = NULL;
                _intMinParam = NULL;
                _floatMaxParam = NULL;
                _intMaxParam = NULL;
            }
            //------------------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _dispatchEvent();

            virtual void _onOver();
            virtual void _onBarOut();
            virtual void _onThumbOut();
            virtual void _onBarPress();
            virtual void _onMinThumbPress();
            virtual void _onMaxThumbPress();
            virtual void _onRelease();
        
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
