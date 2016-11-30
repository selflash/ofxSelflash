#pragma once

#include "STweenCore.h"
#include "STweenSelector.h"
#include "CallBackFuncion.h"

#include "ofxSelflash.h"

namespace fltw {

    class STweener;
    class STween2D : public STweenCore {
        friend STweener;
        
        public:
            
        protected:
            //--------------------------------
            float _duration;
            int _easeType;
            float __overwrite;        
            bool _delayComplete;
            //--------------------------------
        
            flDisplayObject* __target;
        
            float _fromX; float __toX; float _diffX;
            float _fromY; float __toY; float _diffY;
            float _fromZ; float __toZ; float _diffZ;
            
            float _fromAlpha; float __toAlpha; float _diffAlpha;
            
            float _fromWidth; float __toWidth; float _diffWidth;
            float _fromHeight; float __toHeight; float _diffHeight;
            
            float _fromScale; float __toScale; float _diffScale;
            float _fromScaleX; float __toScaleX; float _diffScaleX;
            float _fromScaleY; float __toScaleY; float _diffScaleY;
            float _fromScaleZ; float __toScaleZ; float _diffScaleZ;
            
            float _fromRotation; float __toRotation; float _diffRotation;
            
            float _fromRotationX; float __toRotationX; float _diffRotationX;
            float _fromRotationY; float __toRotationY; float _diffRotationY;
            float _fromRotationZ; float __toRotationZ; float _diffRotationZ;
        
        private:
        
        public:
            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1) {
                
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8,
                     const std::string& property9, float value9) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                _setProperty(property9, value9);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8,
                     const std::string& property9, float value9,
                     const std::string& property10, float value10) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                _setProperty(property9, value9);
                _setProperty(property10, value10);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8,
                     const std::string& property9, float value9,
                     const std::string& property10, float value10,
                     const std::string& property11, float value11) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                _setProperty(property9, value9);
                _setProperty(property10, value10);
                _setProperty(property11, value11);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8,
                     const std::string& property9, float value9,
                     const std::string& property10, float value10,
                     const std::string& property11, float value11,
                     const std::string& property12, float value12) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                _setProperty(property9, value9);
                _setProperty(property10, value10);
                _setProperty(property11, value11);
                _setProperty(property12, value12);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8,
                     const std::string& property9, float value9,
                     const std::string& property10, float value10,
                     const std::string& property11, float value11,
                     const std::string& property12, float value12,
                     const std::string& property13, float value13) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                _setProperty(property9, value9);
                _setProperty(property10, value10);
                _setProperty(property11, value11);
                _setProperty(property12, value12);
                _setProperty(property13, value13);
                //-------------------------------
            }

            //--------------------------------------------------------------
            STween2D(
                     flDisplayObject* target,
                     float duration,
                     const std::string& property1, float value1,
                     const std::string& property2, float value2,
                     const std::string& property3, float value3,
                     const std::string& property4, float value4,
                     const std::string& property5, float value5,
                     const std::string& property6, float value6,
                     const std::string& property7, float value7,
                     const std::string& property8, float value8,
                     const std::string& property9, float value9,
                     const std::string& property10, float value10,
                     const std::string& property11, float value11,
                     const std::string& property12, float value12,
                     const std::string& property13, float value13,
                     const std::string& property14, float value14) {
                reset();
                
                //-------------------------------
                __target = target;
                
                _duration = duration * 1000.0;
                
                _setProperty(property1, value1);
                _setProperty(property2, value2);
                _setProperty(property3, value3);
                _setProperty(property4, value4);
                _setProperty(property5, value5);
                _setProperty(property6, value6);
                _setProperty(property7, value7);
                _setProperty(property8, value8);
                _setProperty(property9, value9);
                _setProperty(property10, value10);
                _setProperty(property11, value11);
                _setProperty(property12, value12);
                _setProperty(property13, value13);
                _setProperty(property14, value14);
                //-------------------------------
            }

            //--------------------------------------------------------------
            //
            ~STween2D() {
                reset();
            }
        
            //==============================================================
            // SETUP / UPDATE / DRAW
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline virtual void update() {
                if(_isStart) {
                    _startTime = STweenCore::elapsedTimeMillis;
                    _isStart = false;
                }
                
                if (_isPause) return;
                
                //-------------------------------
                bool temp = _delayComplete;
                _time = (STweenCore::elapsedTimeMillis - _pauseTime) - _startTime;
                //delay
                if (_time < _delay) {
                    _delayComplete = false;
    //                if(__overwrite == TW_NONE) return;
                } else {
                    _delayComplete = true;
                }
                
                bool onStart = bool(temp != _delayComplete);
                if(onStart) __onStart(this);
                //-------------------------------
                
                //-------------------------------
                if(__target) {
                    __isCompleted = _updateProperty(onStart);
                }
                //-------------------------------
                
                _isTweening = true;
                if(__isCompleted) _isTweening = false;
                
                if(_delayComplete) __onUpdate(this);
            }
            
            //==============================================================
            // PUBLIC METHOD
            //==============================================================

            //--------------------------------------------------------------
            //
            inline virtual STweenCore* reset() {
                STweenCore::reset();
                
                //-------------------------------
                _duration = 0.0;
                _easeType = EASE_LINEAR;
                __overwrite = TW_AUTO;
                _delayComplete = false;
                
                __target = NULL;
                
                _fromX = std::numeric_limits<float>::quiet_NaN(); __toX = std::numeric_limits<float>::quiet_NaN(); _diffX = std::numeric_limits<float>::quiet_NaN();
                _fromY = std::numeric_limits<float>::quiet_NaN(); __toY = std::numeric_limits<float>::quiet_NaN(); _diffY = std::numeric_limits<float>::quiet_NaN();
                _fromZ = std::numeric_limits<float>::quiet_NaN(); __toZ = std::numeric_limits<float>::quiet_NaN(); _diffZ = std::numeric_limits<float>::quiet_NaN();
                
                _fromAlpha = std::numeric_limits<float>::quiet_NaN(); __toAlpha = std::numeric_limits<float>::quiet_NaN(); _diffAlpha = std::numeric_limits<float>::quiet_NaN();
                
                _fromWidth = std::numeric_limits<float>::quiet_NaN(); __toWidth = std::numeric_limits<float>::quiet_NaN(); _diffWidth = std::numeric_limits<float>::quiet_NaN();
                _fromHeight = std::numeric_limits<float>::quiet_NaN(); __toHeight = std::numeric_limits<float>::quiet_NaN(); _diffHeight = std::numeric_limits<float>::quiet_NaN();
                
                _fromScale = std::numeric_limits<float>::quiet_NaN(); __toScale = std::numeric_limits<float>::quiet_NaN(); _diffScale = std::numeric_limits<float>::quiet_NaN();
                _fromScaleX = std::numeric_limits<float>::quiet_NaN(); __toScaleX = std::numeric_limits<float>::quiet_NaN(); _diffScaleX = std::numeric_limits<float>::quiet_NaN();
                _fromScaleY = std::numeric_limits<float>::quiet_NaN(); __toScaleY = std::numeric_limits<float>::quiet_NaN(); _diffScaleY = std::numeric_limits<float>::quiet_NaN();
                _fromScaleZ = std::numeric_limits<float>::quiet_NaN(); __toScaleZ = std::numeric_limits<float>::quiet_NaN(); _diffScaleZ = std::numeric_limits<float>::quiet_NaN();
                
                _fromRotation = std::numeric_limits<float>::quiet_NaN(); __toRotation = std::numeric_limits<float>::quiet_NaN(); _diffRotation = std::numeric_limits<float>::quiet_NaN();
                
                _fromRotationX = std::numeric_limits<float>::quiet_NaN(); __toRotationX = std::numeric_limits<float>::quiet_NaN(); _diffRotationX = std::numeric_limits<float>::quiet_NaN();
                _fromRotationY = std::numeric_limits<float>::quiet_NaN(); __toRotationY = std::numeric_limits<float>::quiet_NaN(); _diffRotationY = std::numeric_limits<float>::quiet_NaN();
                _fromRotationZ = std::numeric_limits<float>::quiet_NaN(); __toRotationZ = std::numeric_limits<float>::quiet_NaN(); _diffRotationZ = std::numeric_limits<float>::quiet_NaN();
                //-------------------------------
                
                return this;
            }
        
            //==============================================================
            // SETTER / GETTER
            //==============================================================
        
        protected:
            virtual bool _updateProperty(bool onStart = false);
            virtual void _setProperty(const std::string& propertyName, float value);
        
        private:
        
    };

}