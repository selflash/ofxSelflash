#pragma once

#include "ofMain.h"

#include "../../utils/MathUtil.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/RangeSliderEvent.h"

namespace fl2d {
    
    class RangeSlider : public Sprite {
        
        public:
            Sprite* track;
            Sprite* nearThumb;
            Sprite* farThumb;
            Sprite* bar;
            
            
        protected:
            
        private:
            TextField* _labelText;
            TextField* _minValueText;
            TextField* _maxValueText;
                
            ofFloatColor* _lineColor;
            ofFloatColor* _normalColor;
            ofFloatColor* _overColor;
            ofFloatColor* _activeColor;
        
            float _trackWidth;
            float _trackHeight;
            float _trackAlpha;
        
            float _thumbWidth;
            float _barWidth;
            float _barAlpha;
        
            float _percent;
            float _min;
            float _max;
            float _range;
            float _minValue;
            float _maxValue;
            
            bool _roundEnabled;
            
            ofPoint* _draggablePoint;
            
        public:
            RangeSlider(float trackWidth = 200, float min = 0, float max = 100, float minValue = 40, float maxValue = 60);
            ~RangeSlider();
            
            string label();
            void label(string value, int color = FlashConfig::UI_LABEL_NORMAL_COLOR);
            
            void textColor(int color = FlashConfig::UI_LABEL_NORMAL_COLOR);
            
            float min();
            void min(float value, bool dispatch = true);
            
            float max();
            void max(float value, bool dispatch = true);
            
            float minValue();
            void minValue(float value, bool dispatch = true);
            
            float maxValue();
            void maxValue(float value, bool dispatch = true);
            
            float range();
                
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
        
            void _over();
            void _out();
            void _press();
            void _release();
            
        private:
            void _mouseEventHandler(Event& event);
        
    };
}