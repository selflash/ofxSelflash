#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flSlider.h"
#include "flVec3SliderEvent.h"

namespace fl2d {
    
    class flVec3Slider : public flSprite {
        
    public:
        flSlider* xSlider;
        flSlider* ySlider;
        flSlider* zSlider;
        
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
        
        flTextField* label();
        void label(flTextField* value);
        
        virtual void textColor(int color);
        
        virtual ofVec3f vec3Value();
        virtual void vec3Value(ofVec3f value, bool dispatch = true);
        
        //----------------------------------
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
        void _eventHandler(flEvent& event);
        
    };
    
}
