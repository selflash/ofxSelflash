#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flSlider.h"
#include "flVec2SliderEvent.h"

namespace fl2d {
    
    class flVec2Slider : public flSprite {
        
    public:
        flSlider* xSlider;
        flSlider* ySlider;
        
    protected:
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        
        flTextField* _label;
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
        
        flTextField* label();
        void label(flTextField* value);
        
        virtual void textColor(int color);
        
        virtual ofVec2f vec2Value();
        virtual void vec2Value(ofVec2f value, bool dispatch = true);
        
        //----------------------------------
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
