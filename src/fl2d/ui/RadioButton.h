#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Shape.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/Event.h"
#include "../events/RadioButtonEvent.h"

namespace fl2d {
    
    class RadioButton : public Sprite {
        
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
            ofFloatColor _deactiveColor;

            TextField* _label;

            bool _bSelected;
            
        public:
            RadioButton(float width = 100);
            ~RadioButton();
            
            TextField* label();
            
            string labelText();
            void labelText(string value);
        
            bool selected();
            void selected(bool value, bool dispatch = true);
            
        protected:
            virtual void _normal();
            virtual void _over();
            virtual void _press();
        
            virtual void _drawGraphics(const ofFloatColor& outerColor);
            virtual void _drawGraphics(const ofFloatColor& outerColor, const ofFloatColor& innerColor);
        
        private:
            
            void _mouseEventHandler(Event& event);
    };
    
}