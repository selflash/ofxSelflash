#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/JoystickEvent.h"

namespace fl2d {
    
    class Joystick : public Sprite {
        
        public:
            Sprite* lever;
        protected:
            
        private:
            TextField* _labelText;
            
            float _lineColor;
            float _normalColor;
            float _overColor;
            float _activeColor;
            
            //------------------------------------------
            float _xValue;
            float _yValue;
            
            ofPoint* _center;
            float _diameter;
            
            float _areaRadius;
            float _leverRadius;
            
            ofPoint* _draggablePoint;
            //------------------------------------------
            
            //------------------------------------------
            bool _flgX;
            bool _flgY;
            float _targetX;
            float _targetY;
            //------------------------------------------
            
        public:
            Joystick(float diameter = 50);
            ~Joystick();
            
            string label();
            void label(string value, int color = 0xffffff);
            
            void textColor(int color = 0xffffff);
            
            float xValue();
            float yValue();
            
            void leverUp(float value = 1.0);
            void leverDown(float value = 1.0);
            void leverLeft(float value = 1.0);
            void leverRight(float value = 1.0);

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