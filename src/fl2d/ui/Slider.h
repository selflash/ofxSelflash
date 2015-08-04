#pragma once

#include "ofMain.h"

#include "../../utils/MathUtil.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/SliderEvent.h"

namespace fl2d {
    
    class Slider : public Sprite {
            
        public:
            Sprite* track;
            Sprite* thumb;
            Sprite* bar;        
            
        protected:
            
        private:
            TextField* _labelText;
            TextField* _valueText;
        
            ofFloatColor* _lineColor;
            ofFloatColor* _normalColor;
            ofFloatColor* _overColor;
            ofFloatColor* _activeColor;
        
            float _trackWidth;
            float _trackHeight;
            float _thumbWidth;
            float _barWidth;
            
            float _percent;
            float _min;
            float _max;
            float _range;
            float _value;
            
            bool _roundEnabled;
            
            ofPoint* _draggablePoint;
            
        public:
            Slider(float trackWidth = 200, float min = 0, float max = 100, float defaultValue = 0);
            ~Slider();
            
            string label();
            void label(string value, int color = 0xffffff);
            
            void textColor(int color = 0xffffff);
            
            float min();
            void min(float value, bool dispatch = true);
            
            float max();
            void max(float value, bool dispatch = true);
            
            float value();
            void value(float value, bool dispatch = true);
            
            int barColor();
            void barColor(int value);
            void barColor(int red, int green, int blue, int alpha);
            void barColor(const ofColor& color);
            void barColor(const ofFloatColor& color);
        
            bool roundEnabled();
            void roundEnabled(bool value);
            
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();

            virtual void _drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor);
            virtual void _drawBarGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor);
        
            virtual void _trackOver();
            virtual void _trackOut();
            virtual void _trackPress();
            virtual void _trackRelease();
            
            virtual void _thumbOver();
            virtual void _thumbOut();
            virtual void _thumbPress();
            virtual void _thumbRelease();
            
        private:
            void _mouseEventHandler(Event& event);
    };
}