#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Shape.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/PadEvent.h"
#include "NumberDialer.h"
#include "../events/NumberDialerEvent.h"

namespace fl2d {
    
    class Pad2D : public Sprite {
            
        public:
            Sprite* ball;
            
        protected:
            
        private:
            TextField* _labelText;
            TextField* _xRatioText;
            TextField* _yRatioText;
            TextField* _xValueText;
            TextField* _yValueText;
            
            float _width;
            float _height;
            
            float _lineColor;
            float _normalColor;
            float _overColor;
            float _activeColor;
            
            float _ballRadius;
            
            float _xRatio;
            float _yRatio;
            float _xValue;
            float _yValue;
        
            float _leftValue;
            float _rightValue;
            float _topValue;
            float _bottomValue;
            float _rangeWidth;
            float _rangeHeight;
        
            ofPoint* _draggablePoint;
        
            NumberDialer* _dialer01;
            NumberDialer* _dialer02;
            NumberDialer* _dialer03;
            NumberDialer* _dialer04;
        
        public:
            Pad2D(float width = 100, float height = 100, float left = 0, float right = 100, float top = 0, float bottom = 100);
            ~Pad2D();
            
            string label();
            void label(string value, int color = 0x0);
            
            void textColor(int color = 0x0);
        
            float xRatio();
            void xRatio(float value, bool dispatch = true);
            
            float yRatio();
            void yRatio(float value, bool dispatch = true);
        
            float xValue();
            void xValue(float value, bool dispatch = true);
            
            float yValue();
            void yValue(float value, bool dispatch = true);
        
            float rangeWidth();
            void rangeWidth(float value, bool dispatch = true);
        
            float rangeHeight();
            void rangeHeight(float value, bool dispatch = true);
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _updateValue();
        
            virtual void _areaOver();
            virtual void _areaOut();
            virtual void _areaPress();
            virtual void _areaRelease();
            
            virtual void _ballOver();
            virtual void _ballOut();
            virtual void _ballPress();
            virtual void _ballRelease();
            virtual void _ballMove();
            
        private:
            void _mouseEventHandler(Event& event);
            void _uiEventHandler(Event& event);
    };
}