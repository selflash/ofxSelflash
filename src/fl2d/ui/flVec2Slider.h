#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSlider.h"
#include "flVec2SliderEvent.h"

namespace fl2d {
    
    class flVec2Slider : public flUIBase {
        
    public:
        flSlider* xSlider;
        flSlider* ySlider;
        
    protected:
        flTextField* _label1Text;
        flTextField* _label2Text;
        
        ofVec2f _vec2Value;
        
    private:
        
    public:
        flVec2Slider(
                   float width = 200,
                   float xMin = 0, float xMax = 100, float defaultXValue = 0,
                   float yMin = 0, float yMax = 100, float defaultYValue = 0
                   );
        virtual ~flVec2Slider();
        
        virtual void label(flTextField* value);
        
        virtual ofVec2f vec2Value();
        virtual void vec2Value(ofVec2f value, bool dispatch = true);
        
        //----------------------------------
        inline virtual float min() { xSlider->min(); }
        inline virtual void min(float value, bool dispatch = true) {
            xSlider->min(value, dispatch);
            ySlider->min(value, dispatch);
        }
        
        inline virtual float max() { xSlider->max(); }
        inline virtual void max(float value, bool dispatch = true) {
            xSlider->max(value, dispatch);
            ySlider->max(value, dispatch);
        }

        inline virtual float xValue() { return xSlider->value(); }
        inline virtual void xValue(float value, bool dispatch = true) { xSlider->value(value, dispatch); }
        
        inline virtual float yValue() { return ySlider->value(); }
        inline virtual void yValue(float value, bool dispatch = true) { ySlider->value(value, dispatch); }
        //----------------------------------
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _eventHandler(flEvent& event);
        
    };
    
}
