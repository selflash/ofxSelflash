﻿#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flJoyStick2Event.h"

using namespace glm;

namespace fl2d {
    
    class flJoyStick2 : public flUIBase {
        public:
            flSprite* lever = NULL;
        
        protected:
        
        private:
            int _digit = 2;

            float _areaRadius = 0.0;
            float _leverRadius = 0.0;
            float _maxDistance = 0.0;
            ofPoint _center;
            ofPoint _draggablePoint;
            bool _flgX = false;
            bool _flgY = false;
            float _targetX = 0.0;
            float _targetY = 0.0;

            float _xValue = 0.0;
            float _yValue = 0.0;
        
            flTextField* _valueText = NULL;

        public:
            flJoyStick2(float areaDiameter = 50);
            virtual ~flJoyStick2();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            float xValue();
            float yValue();
        
            //-1.0 ~ 1.0
            void leverUp(float value = 1.0);
            void leverDown(float value = 1.0);
            void leverLeft(float value = 1.0);
            void leverRight(float value = 1.0);
            void moveLever(float x, float y);
            void moveLever(vec2 value);

            //------------------------------------------
            ofParameter<vec2>* _vec2Param = NULL;
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<vec2>& param) {
                _listeners.unsubscribeAll();
                _vec2Param = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

                _vec2Param = &param;
                _listeners.push(_vec2Param->newListener([&](vec2& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        moveLever(val);
                    }
                }));
                
//                moveLever(_vec2Param->get());
            }
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
                _vec2Param = NULL;
            }
            //------------------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _dispatchEvent();

            virtual void _onLeverOver();
            virtual void _onLeverOut();
            virtual void _onLeverPress();
            virtual void _onLeverRelease();
            virtual void _onLeverMove();
        
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
