#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flJoyStick1Event.h"

namespace fl2d {
    
    class flJoyStick1 : public flUIBase {
        public:
            //水平
            static string HORIZONTALLY;
            //垂直
            static string VERTICALLY;
        
            flSprite* lever;
        
        protected:
        
        private:
            flTextField* _valueText;
            string _type;

            float _maxDistance;

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
            flJoyStick1(float length = 100);
            virtual ~flJoyStick1();
        
            virtual void label(flTextField* value);
        
            string type();
            void type(string value);
        
            float value();
        
            void moveLever(float value = 1.0);
        
            virtual bool enabled();
            virtual void enabled(bool value);
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
    //        virtual void _areaOver();
    //        virtual void _areaOut();
    //        virtual void _areaPress();
    //        virtual void _areaRelease();
    //
    //        virtual void _ballOver();
    //        virtual void _ballOut();
    //        virtual void _ballPress();
    //        virtual void _ballRelease();
    //        virtual void _ballMove();
        
            virtual void _leverOver();
            virtual void _leverOut();
            virtual void _leverPress();
            virtual void _leverRelease();
            virtual void _leverMove();
        
            virtual void _setNormalColor();
            virtual void _setOverColor();
            virtual void _setSelectedOverColor();
            virtual void _setActiveColor();
            virtual void _setDisableNormalColor();
            virtual void _setDisableActiveColor();
        
            virtual void _drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
            virtual void _drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
        
        private:
            virtual void _mouseEventHandler(flEvent& event);
    };
    
}
