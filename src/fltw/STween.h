#pragma once

#include "STweenCore.h"
#include "STweenSelector.h"

namespace fltw {
    
    class STweener;
    class STween : public STweenCore {
        friend STweener;
        
        public:

        protected:
            //--------------------------------
            float _duration;
            int _easeType;
            float __overwrite;
            bool _delayComplete;
            //--------------------------------

            std::vector<float*> __targetValueList;
            std::map<float*, float> _fromValueList;
            std::map<float*, float> __toValueList;
            std::map<float*, float> _diffValueList;
        
        private:
        
        public:
            //--------------------------------------------------------------
            //
            STween(
                   float duration,
                   float* targetValue1, float toValue1,
                   const std::string& property1 = "", float value1 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property2 = "", float value2 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property3 = "", float value3 = std::numeric_limits<float>::quiet_NaN()) {
                reset();
                
                //-------------------------------
                _startTime = STweenCore::elapsedTimeMillis;
                _duration = duration * 1000.0;
                //-------------------------------
                
                //-------------------------------
                _addTargetValue(targetValue1, toValue1);
                
                if(property1 != "") _setProperty(property1, value1);
                if(property2 != "") _setProperty(property2, value2);
                if(property3 != "") _setProperty(property3, value3);
                //-------------------------------
            }
            //--------------------------------------------------------------
            //
            STween(
                   float duration,
                   float* targetValue1, float toValue1,
                   float* targetValue2, float toValue2,
                   const std::string& property1 = "", float value1 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property2 = "", float value2 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property3 = "", float value3 = std::numeric_limits<float>::quiet_NaN()) {
                reset();
                
                //-------------------------------
                _startTime = STweenCore::elapsedTimeMillis;
                _duration = duration * 1000.0;
                //-------------------------------
                
                //-------------------------------
                _addTargetValue(targetValue1, toValue1);
                _addTargetValue(targetValue2, toValue2);
                
                if(property1 != "") _setProperty(property1, value1);
                if(property2 != "") _setProperty(property2, value2);
                if(property3 != "") _setProperty(property3, value3);
                //-------------------------------
            }
            //--------------------------------------------------------------
            //
            STween(
                   float duration,
                   float* targetValue1, float toValue1,
                   float* targetValue2, float toValue2,
                   float* targetValue3, float toValue3,
                   const std::string& property1 = "", float value1 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property2 = "", float value2 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property3 = "", float value3 = std::numeric_limits<float>::quiet_NaN()) {
                reset();
                
                //-------------------------------
                _startTime = STweenCore::elapsedTimeMillis;
                _duration = duration * 1000.0;
                //-------------------------------
                
                //-------------------------------
                _addTargetValue(targetValue1, toValue1);
                _addTargetValue(targetValue2, toValue2);
                _addTargetValue(targetValue3, toValue3);
                
                if(property1 != "") _setProperty(property1, value1);
                if(property2 != "") _setProperty(property2, value2);
                if(property3 != "") _setProperty(property3, value3);
                //-------------------------------
            }
            //--------------------------------------------------------------
            //
            STween(
                   float duration,
                   float* targetValue1, float toValue1,
                   float* targetValue2, float toValue2,
                   float* targetValue3, float toValue3,
                   float* targetValue4, float toValue4,
                   const std::string& property1 = "", float value1 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property2 = "", float value2 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property3 = "", float value3 = std::numeric_limits<float>::quiet_NaN()) {
                reset();
                
                //-------------------------------
                _startTime = STweenCore::elapsedTimeMillis;
                _duration = duration * 1000.0;
                //-------------------------------
                
                //-------------------------------
                _addTargetValue(targetValue1, toValue1);
                _addTargetValue(targetValue2, toValue2);
                _addTargetValue(targetValue3, toValue3);
                _addTargetValue(targetValue4, toValue4);
                
                if(property1 != "") _setProperty(property1, value1);
                if(property2 != "") _setProperty(property2, value2);
                if(property3 != "") _setProperty(property3, value3);
                //-------------------------------
            }
            //--------------------------------------------------------------
            //
            STween(
                   float duration,
                   float* targetValue1, float toValue1,
                   float* targetValue2, float toValue2,
                   float* targetValue3, float toValue3,
                   float* targetValue4, float toValue4,
                   float* targetValue5, float toValue5,
                   const std::string& property1 = "", float value1 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property2 = "", float value2 = std::numeric_limits<float>::quiet_NaN(),
                   const std::string& property3 = "", float value3 = std::numeric_limits<float>::quiet_NaN()) {
                reset();
                
                //-------------------------------
                _startTime = STweenCore::elapsedTimeMillis;
                _duration = duration * 1000.0;
                //-------------------------------
                
                //-------------------------------
                _addTargetValue(targetValue1, toValue1);
                _addTargetValue(targetValue2, toValue2);
                _addTargetValue(targetValue3, toValue3);
                _addTargetValue(targetValue4, toValue4);
                _addTargetValue(targetValue5, toValue5);
                
                if(property1 != "") _setProperty(property1, value1);
                if(property2 != "") _setProperty(property2, value2);
                if(property3 != "") _setProperty(property3, value3);
                //-------------------------------
            }
        
            //--------------------------------------------------------------
            //
            ~STween() {
                reset();
            }
        
            //==============================================================
            // SETUP / UPDATE / DRAW
            //==============================================================

            //--------------------------------------------------------------
            //
            inline virtual void update() {
                if (_isPause) return;
                
                //-------------------------------
                bool temp = _delayComplete;
                _time = (STweenCore::elapsedTimeMillis - _pauseTime) - _startTime;
                //delay
                if (_time < _delay) {
                    _delayComplete = false;
                } else {
                    _delayComplete = true;
                }
                
                if(temp != _delayComplete) __onStart(this);
                //-------------------------------
                
                //-------------------------------
                bool completed = true;
                
                int i = 0; int l = 0;
                l = __targetValueList.size();
                for(i = 0; i < l; i++) {
                    bool flg = _updateProperty(__targetValueList[i]);
                    completed = completed && flg;
                }
                
                __isCompleted = completed;
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
                ofLog(OF_LOG_VERBOSE) << "[STween]reset()";
                
                STweenCore::reset();
                
                //-------------------------------
                _duration = 0.0;
                _easeType = EASE_LINEAR;
                __overwrite = TW_AUTO;
                _delayComplete = false;
                //-------------------------------

                __targetValueList.clear();
                _fromValueList.clear();
                __toValueList.clear();
                _diffValueList.clear();
                
                return this;
            }

        protected:
        
            //--------------------------------------------------------------
            //
            inline virtual bool _updateProperty(float* target) {
                bool complete = false;
                
                float t; float b; float c; float d; float p; float a;
                
                float from = _fromValueList[target];
                float to = __toValueList[target];
                float diff = _diffValueList[target];
                
                //-------------------------------
                //STween value1
                if(!isnan(__toValueList[target])) {
                    if(!_delayComplete) {
                        _fromValueList[target] = *target;
                        from = _fromValueList[target];
                        _diffValueList[target] = to - from;
                    }
                    
                    from = _fromValueList[target];
                    diff = _diffValueList[target];
                    
                    if (_time <= _duration + _delay) {
                        t = MAX(_time - (float)_delay, 0.0);
                        b = from;
                        c = diff;
                        d = _duration;
                        p = 0.0;
                        a = 0.0;
                        
                        *target = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                    } else {
                        *target = to;
                        complete = true;
                    }
                } else {
                    complete = true;
                }
                //-------------------------------
                
                return complete;
            }
        
            //--------------------------------------------------------------
            //
            inline virtual void _addTargetValue(float* targetValue, float value) {
                __targetValueList.push_back(targetValue);
                _fromValueList[targetValue] = *targetValue;
                __toValueList[targetValue] = value;
                _diffValueList[targetValue] = __toValueList[targetValue] - _fromValueList[targetValue];
            }
        
            //--------------------------------------------------------------
            //
            inline virtual void _setProperty(const std::string& propertyName, float value) {
                if(propertyName == "overwrite") {
                    __overwrite = value;
                    return;
                }
                
                if(propertyName == "delay") {
                    //-------------------------------
                    //convert seconds to millis
                    _delay = value * 1000.0;
                    _startTime = STweenCore::elapsedTimeMillis;
                    //-------------------------------
                    return;
                }
                
                if(propertyName == "ease") {
                    _easeType = value;
                    return;
                }
            }
        
        private:
    };
    
}
