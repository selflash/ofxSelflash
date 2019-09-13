#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/Joystick1Event.h"

namespace fl2d {
    
    class Joystick1 : public Sprite {
            
        public:
            //水平
            static string HORIZONTALLY;
            //垂直
            static string VERTICALLY;
            
            Sprite* lever;
        protected:
            
        private:
            float _labelNormalColor;
            float _labelOverColor;
            float _labelActiveColor;
            float _labelDeactiveColor;
        
            ofFloatColor _normalLineColor;
            ofFloatColor _overLineColor;
            ofFloatColor _activeLineColor;
            ofFloatColor _deactiveLineColor;
            
            ofFloatColor _normalColor;
            ofFloatColor _overColor;
            ofFloatColor _activeColor;
            ofFloatColor _deactiveColor;
        
            TextField* _label;
            
            string _type;
            
            //------------------------------------------
            float _value;
            
            ofPoint _center;
            
            float _uiLength;
            float _leverRadius;
            
            ofPoint _draggablePoint;
            //------------------------------------------
            
            //------------------------------------------
            bool _flg;
            float _targetValue;
            //------------------------------------------
        
            bool _enabled;

        public:
            Joystick1(float length = 100, float leverDiameter = 14);
            virtual ~Joystick1();
            
            TextField* label();
            void label(TextField* value);
            
            string type();
            void type(string value);
            
            float value();
            
            void moveLever(float value = 1.0);
        
            bool enabled();
            void enabled(bool value);

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
