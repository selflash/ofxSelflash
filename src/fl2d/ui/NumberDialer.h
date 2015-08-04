#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/NumberDialerEvent.h"

//水平
#define FL_HORIZONTALLY "horizontally"
//垂直
#define FL_VERTICALLY   "vertically"

namespace fl2d {
    
    class NumberDialer : public Sprite {
        
        public:
            Sprite* track;
            
        protected:
            
        private:
            TextField* _labelText;

            float _trackWidth;
            float _trackHeight;
            
            float _labelNormalColor;
            float _labelOverColor;
            float _labelActiveColor;
        
            ofFloatColor* _lineColor;
            ofFloatColor* _normalColor;
            ofFloatColor* _overColor;
            ofFloatColor* _activeColor;
        
            string _type;
        
            TextField* _valueText;
            float _value;
            float _tempValue;
            float _stepValue;
        
            float _max;
            float _min;
        
            ofPoint* _startPos;
            
        public:
            NumberDialer(float width = 100, float height = 20);
            ~NumberDialer();
            
            string label();
            void label(string value, int color = FlashConfig::UI_LABEL_NORMAL_COLOR);
            
            void textColor(int color = FlashConfig::UI_LABEL_NORMAL_COLOR);
        
            string type();
            void type(string value);
        
            float value();
            void value(float value, bool dispatch = true);
            
            float stepValue();
            void stepValue(float value, bool dispatch = true);
            
            float min();
            void min(float value, bool dispatch = true);
            
            float max();
            void max(float value, bool dispatch = true);
        
        protected:
            //virtual void _setup();
            virtual void _update();
            //virtual void _draw();
        
            virtual void _drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor);
        
            virtual void _over();
            virtual void _out();
            virtual void _press();
            virtual void _release();
            
        private:
            void _mouseEventHandler(Event& event);
    };
    
}