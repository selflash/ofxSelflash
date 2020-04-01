#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSlider.h"
#include "flVec3SliderEvent.h"

namespace fl2d {
    
    class flVec3Slider : public flUIBase {
        
        public:
            flSlider* xSlider = NULL;
            flSlider* ySlider = NULL;
            flSlider* zSlider = NULL;
        
        protected:
            flTextField* _xLabel = NULL;
            flTextField* _yLabel = NULL;
            flTextField* _zLabel = NULL;
        
            vec3 _value;
        
        private:
        
        public:
            flVec3Slider(
                       float width = 200,
                       float xMin = 0, float xMax = 100, float defaultXValue = 0,
                       float yMin = 0, float yMax = 100, float defaultYValue = 0,
                       float zMin = 0, float zMax = 100, float defaultZValue = 0
                       );
            virtual ~flVec3Slider();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            //----------------------------------
            virtual float min();
            virtual void min(float value, bool dispatch = true);
        
            virtual float max();
            virtual void max(float value, bool dispatch = true);
        
            virtual vec3 value();
            virtual void value(vec3 value, bool dispatch = true);
        
            virtual float xValue();
            virtual void xValue(float value, bool dispatch = true);
        
            virtual float yValue();
            virtual void yValue(float value, bool dispatch = true);
        
            virtual float zValue();
            virtual void zValue(float value, bool dispatch = true);
            //----------------------------------

            //----------------------------------
            ofParameter<vec3>* _vec3Param = NULL;
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<vec3>& param) {
                _listeners.unsubscribeAll();
                _vec3Param = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;
                
                _vec3Param = &param;
                _listeners.push(_vec3Param->newListener([&](vec3& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        value(val);
                    }
                }));
                
                _bChangedByOfParm["value"] = true;
                value(_vec3Param->get());
            }
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
                _vec3Param = NULL;
            }
            //----------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _dispatchEvent();
        
        private:
            virtual void _eventHandler(flEvent& event);
        
    };
    
}
