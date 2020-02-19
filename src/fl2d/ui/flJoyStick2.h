#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flJoyStick2Event.h"

namespace fl2d {
    
    class flJoyStick2 : public flUIBase {
        public:
            flSprite* lever;
        
        protected:
        
        private:
            flTextField* _valueText;
        
            float _maxDistance;

            //------------------------------------------
            float _xValue;
            float _yValue;
            ofPoint _center;
            float _areaRadius;
            float _leverRadius;
            ofPoint _draggablePoint;
            //------------------------------------------
        
            //------------------------------------------
            bool _flgX;
            bool _flgY;
            float _targetX;
            float _targetY;
            //------------------------------------------
        
        public:
            flJoyStick2(float areaDiameter = 50);
            virtual ~flJoyStick2();
        
            virtual void label(flTextField* value);
        
            float xValue();
            float yValue();
        
            void leverUp(float value = 1.0);
            void leverDown(float value = 1.0);
            void leverLeft(float value = 1.0);
            void leverRight(float value = 1.0);
        
            virtual bool enabled();
            virtual void enabled(bool value);
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
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
