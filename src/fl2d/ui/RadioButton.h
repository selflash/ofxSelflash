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
            TextField* _labelText;
            
            ofFloatColor* _lineColor;
            ofFloatColor* _normalColor;
            ofFloatColor* _overColor;
            ofFloatColor* _activeColor;
            
            bool _bSelected;
            
        public:
            RadioButton(float width = 100);
            ~RadioButton();
            
            string label();
            void label(string value, int color = 0xffffff);
            
            void textColor(int color = 0xffffff);
            
            bool selected();
            void selected(bool value, bool dispatch = true);
            
        protected:
            virtual void _normal();
            virtual void _over();
            virtual void _press();
        
            virtual void _drawGraphics(const ofFloatColor& outerColor, const ofFloatColor* innerColor = NULL);
        
        private:
            
            void _mouseEventHandler(Event& event);
    };
    
}