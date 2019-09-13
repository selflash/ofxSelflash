#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Shape.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/PadEvent.h"

namespace fl2d {
    
    class Pad3D : public Sprite {
        
        public:
            Sprite* ball;
            
        protected:
            
        private:
            TextField* _labelText;
            TextField* _value1Text;
            TextField* _value2Text;
            
            float _width;
            float _height;
            
            float _lineColor;
            float _normalColor;
            float _overColor;
            float _activeColor;
            
            float _ballRadius;
            
            float _xValue;
            float _yValue;
            
            ofPoint* _draggablePoint;
            
        public:
            Pad3D(float width = 100, float height = 100);
            virtual ~Pad3D();
            
            string label();
            void label(string value, int color = 0xffffff);
            
            void textColor(int color = 0xffffff);
            
            float xValue();
            void xValue(float value);
            
            float yValue();
            void yValue(float value);
            
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
            
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
    };
    
}
