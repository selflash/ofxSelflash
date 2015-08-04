#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Shape.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"

namespace fl2d {
    
    class Button : public Sprite {
            
        public:

        protected:

        private:
            TextField* _labelText;
            
            float _buttonWidth;
            float _buttonHeight;
            
            float _labelNormalColor;
            float _labelOverColor;
            float _labelActiveColor;
            
            float _lineColor;
            float _normalColor;
            float _overColor;
            float _activeColor;
            
            bool _toggleEnabled;
            bool _selected;
            
            void* _pointerValue;
            string _stringValue;
            float _floatValue;
            int _intValue;
            
        public:
            Button(float buttonWidth = 100, float buttonHeight = 20);
            ~Button();
            
            string label();
            void label(string value, int color = FlashConfig::UI_LABEL_NORMAL_COLOR);
            
            void textColor(int color = FlashConfig::UI_LABEL_NORMAL_COLOR);
            
            bool toggleEnabled();
            void toggleEnabled(bool value);
            
            bool selected();
            void selected(bool value);
            
            void* pointerValue();
            void pointerValue(void* value);
            
            string stringValue();
            void stringValue(string value);
            
            float floatValue();
            void floatValue(float value);
            
            int intValue();
            void intValue(int value);

        protected:
            //virtual void _setup();
            //virtual void _update();
            //virtual void _draw();
            
            virtual void _over();
            virtual void _out();
            virtual void _press();
            virtual void _release();

        private:
            void _mouseEventHandler(Event& event);
    };
    
}