#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSlider.h"
#include "flVec2SliderEvent.h"

using namespace glm;

namespace fl2d {
    
    class flVec2Slider : public flUIBase {
        
        public:
            flSlider* xSlider = NULL;
            flSlider* ySlider = NULL;
        
        protected:
            flTextField* _xLabel = NULL;
            flTextField* _yLabel = NULL;
        
            vec2 _value;
        
        private:
        
        public:
            flVec2Slider(
                       float width = 200,
                       float xMin = 0, float xMax = 100, float defaultXValue = 0,
                       float yMin = 0, float yMax = 100, float defaultYValue = 0
                       );
            virtual ~flVec2Slider();

            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            //----------------------------------
            virtual float min();
            virtual void min(float value, bool dispatch = true);
        
            virtual float max();
            virtual void max(float value, bool dispatch = true);
            
            virtual vec2 value();
            virtual void value(vec2 value, bool dispatch = true);

            virtual float xValue();
            virtual void xValue(float value, bool dispatch = true);
        
            virtual float yValue();
            virtual void yValue(float value, bool dispatch = true);
            //----------------------------------
        
            //----------------------------------
            ofParameter<vec2>* _vec2Param = NULL;
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<vec2>& param) {
                _listeners.unsubscribeAll();
                _vec2Param = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

                _vec2Param = &param;
                _listeners.push(_vec2Param->newListener([&](vec2& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        value(val);
                    }
                }));
                
                _bChangedByOfParm["value"] = true;
                value(_vec2Param->get());
				_bChangedByOfParm["value"] = false;
			}
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
                _vec2Param = NULL;
            }
            //----------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _dispatchEvent();

        private:
            void _eventHandler(flEvent& event);
        
    };
    
}
