#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "Slider.h"
#include "../events/Vec3SliderEvent.h"

namespace fl2d {
    
    class Vec3Slider : public Sprite {
        
        public:
            Slider* xSlider;
            Slider* ySlider;
            Slider* zSlider;
            
        protected:
            float _labelNormalColor;
            float _labelOverColor;
            float _labelActiveColor;
            float _labelDeactiveColor;
            
            ofFloatColor _lineColor;
            ofFloatColor _normalColor;
            ofFloatColor _overColor;
            ofFloatColor _activeColor;
            
            TextField* _label;
            TextField* _label1Text;
            TextField* _label2Text;
            TextField* _label3Text;
            
            ofVec3f _vec3Value;
            
        private:

        public:
            Vec3Slider(
                       float width = 200,
                       float xMin = 0, float xMax = 100, float defaultXValue = 0,
                       float yMin = 0, float yMax = 100, float defaultYValue = 0,
                       float zMin = 0, float zMax = 100, float defaultZValue = 0
                       );
            ~Vec3Slider();
            
            TextField* label();
            void label(TextField* value);
        
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
            void _eventHandler(Event& event);

    };
    
}
