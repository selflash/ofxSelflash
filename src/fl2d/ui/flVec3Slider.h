#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSlider.h"
#include "flVec3SliderEvent.h"

namespace fl2d {
    
    class flVec3Slider : public flUIBase {
        
    public:
        flSlider* xSlider;
        flSlider* ySlider;
        flSlider* zSlider;
        
    protected:
        flTextField* _label1Text;
        flTextField* _label2Text;
        flTextField* _label3Text;
        
        ofVec3f _vec3Value;
        
    private:
        
    public:
        flVec3Slider(
                   float width = 200,
                   float xMin = 0, float xMax = 100, float defaultXValue = 0,
                   float yMin = 0, float yMax = 100, float defaultYValue = 0,
                   float zMin = 0, float zMax = 100, float defaultZValue = 0
                   );
        virtual ~flVec3Slider();
        
        virtual flTextField* label();
        virtual void label(flTextField* value);
        
        virtual ofVec3f vec3Value();
        virtual void vec3Value(ofVec3f value, bool dispatch = true);
        
        //----------------------------------
        inline virtual float min() { xSlider->min(); }
        inline virtual void min(float value, bool dispatch = true) {
            xSlider->min(value, dispatch);
            ySlider->min(value, dispatch);
            zSlider->min(value, dispatch);
        }
        
        inline virtual float max() { xSlider->max(); }
        inline virtual void max(float value, bool dispatch = true) {
            xSlider->max(value, dispatch);
            ySlider->max(value, dispatch);
            zSlider->max(value, dispatch);
        }
        
        inline virtual float xValue() { return xSlider->value(); }
        inline virtual void xValue(float value, bool dispatch = true) { xSlider->value(value, dispatch); }
        
        inline virtual float yValue() { return ySlider->value(); }
        inline virtual void yValue(float value, bool dispatch = true) { ySlider->value(value, dispatch); }
        
        inline virtual float zValue() { return zSlider->value(); }
        inline virtual void zValue(float value, bool dispatch = true) { zSlider->value(value, dispatch); }
        //----------------------------------
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        virtual void _eventHandler(flEvent& event);
        
    };
    
}
