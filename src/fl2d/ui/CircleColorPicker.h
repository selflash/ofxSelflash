#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"

#include "../events/ColorPickerEvent.h"

namespace fl2d {
    
    class CircleColorPicker : public Sprite {
        
        public:
            
        protected:
            
        private:
            float _uiWidth;
            float _uiHeight;
                
            float _labelNormalColor;
            float _labelOverColor;
            float _labelActiveColor;
            float _labelDeactiveColor;
            
            ofFloatColor _lineColor;
            ofFloatColor _normalColor;
            ofFloatColor _overColor;
            ofFloatColor _activeColor;
            
            TextField* _label;

            ofImage* _pixelCaptureImage;
            ofImage* _colorWheelImage;
            ofColor* _selectedPixel;
            
            float _radius;
            
        public:
            CircleColorPicker(float width = 100, float height = 100);
            ~CircleColorPicker();
            
            TextField* label();
            void label(TextField* value);
        
            const ofColor& getPixel(int x, int y);
            
            int red();
            int green();
            int blue();
            
            string hexCode();
            int hue();
            int saturation();
            int brightness();

        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
            
            virtual void _over();
            virtual void _out();
            virtual void _press();
            virtual void _release();
            virtual void _move();

        private:
            void _mouseEventHandler(Event& event);
    };
    
}
