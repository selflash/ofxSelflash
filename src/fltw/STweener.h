#pragma once

#include <limits.h>
#include <vector.h>
#include <math.h>

#include "STweenSelector.h"
#include "STweenCore.h"
#include "STween.h"

//#define USE_FLASH_OBJECT

#ifdef USE_FLASH_OBJECT
#include "STween2D.h"
#else
#endif

namespace fltw {

    class STweener {
        public:
            
        protected:
            
        private:
            static STweener* _instance;
            
            bool _bRender;
            vector<STweenCore*> _tweens;
        
        public:
            static STweener* instance();
        
            static const int numTweens();
            static vector<STweenCore*>& getAllTweens();
            
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            static STweenCore* delayedCall(float delay, ListenerClass *listener, void (ListenerClass::*listenerMethod)()) {
                cout << "[STweener]delayedCall()" << endl;
                instance();
                
                STweenCore* tween = new STweenCore(delay, listener, listenerMethod);
                tween->start();
                _instance->_tweens.push_back(tween);
                _instance->_renderStart();
                
                return tween;
            }
            
            //--------------------------------
            static STweenCore* to(
                                  float duration,
                                  float* targetValue1, float toValue1,
                                  string property1 = "", float value1 = numeric_limits<float>::quiet_NaN(),
                                  string property2 = "", float value2 = numeric_limits<float>::quiet_NaN(),
                                  string property3 = "", float value3 = numeric_limits<float>::quiet_NaN());
            static STweenCore* to(
                                  float duration,
                                  float* targetValue1, float toValue1,
                                  float* targetValue2, float toValue2,
                                  string property1 = "", float value1 = numeric_limits<float>::quiet_NaN(),
                                  string property2 = "", float value2 = numeric_limits<float>::quiet_NaN(),
                                  string property3 = "", float value3 = numeric_limits<float>::quiet_NaN());
            static STweenCore* to(
                                  float duration,
                                  float* targetValue1, float toValue1,
                                  float* targetValue2, float toValue2,
                                  float* targetValue3, float toValue3,
                                  string property1 = "", float value1 = numeric_limits<float>::quiet_NaN(),
                                  string property2 = "", float value2 = numeric_limits<float>::quiet_NaN(),
                                  string property3 = "", float value3 = numeric_limits<float>::quiet_NaN());
            static STweenCore* to(
                                  float duration,
                                  float* targetValue1, float toValue1,
                                  float* targetValue2, float toValue2,
                                  float* targetValue3, float toValue3,
                                  float* targetValue4, float toValue4,
                                  string property1 = "", float value1 = numeric_limits<float>::quiet_NaN(),
                                  string property2 = "", float value2 = numeric_limits<float>::quiet_NaN(),
                                  string property3 = "", float value3 = numeric_limits<float>::quiet_NaN());
            static STweenCore* to(
                                  float duration,
                                  float* targetValue1, float toValue1,
                                  float* targetValue2, float toValue2,
                                  float* targetValue3, float toValue3,
                                  float* targetValue4, float toValue4,
                                  float* targetValue5, float toValue5,
                                  string property1 = "", float value1 = numeric_limits<float>::quiet_NaN(),
                                  string property2 = "", float value2 = numeric_limits<float>::quiet_NaN(),
                                  string property3 = "", float value3 = numeric_limits<float>::quiet_NaN());
            //--------------------------------
        
        
        
        
        
    #ifdef USE_FLASH_OBJECT
        //--------------------------------
        //2D
        //--------------------------------
        
        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8,
                                 string property9, float value9
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            _instance->_overwriteCheck2d(target, property9);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8,
                                                   property9, value9
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8,
                                 string property9, float value9,
                                 string property10, float value10
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            _instance->_overwriteCheck2d(target, property9);
            _instance->_overwriteCheck2d(target, property10);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8,
                                                   property9, value9,
                                                   property10, value10
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8,
                                 string property9, float value9,
                                 string property10, float value10,
                                 string property11, float value11
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            _instance->_overwriteCheck2d(target, property9);
            _instance->_overwriteCheck2d(target, property10);
            _instance->_overwriteCheck2d(target, property11);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8,
                                                   property9, value9,
                                                   property10, value10,
                                                   property11, value11
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8,
                                 string property9, float value9,
                                 string property10, float value10,
                                 string property11, float value11,
                                 string property12, float value12
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            _instance->_overwriteCheck2d(target, property9);
            _instance->_overwriteCheck2d(target, property10);
            _instance->_overwriteCheck2d(target, property11);
            _instance->_overwriteCheck2d(target, property12);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8,
                                                   property9, value9,
                                                   property10, value10,
                                                   property11, value11,
                                                   property12, value12
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8,
                                 string property9, float value9,
                                 string property10, float value10,
                                 string property11, float value11,
                                 string property12, float value12,
                                 string property13, float value13
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            _instance->_overwriteCheck2d(target, property9);
            _instance->_overwriteCheck2d(target, property10);
            _instance->_overwriteCheck2d(target, property11);
            _instance->_overwriteCheck2d(target, property12);
            _instance->_overwriteCheck2d(target, property13);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8,
                                                   property9, value9,
                                                   property10, value10,
                                                   property11, value11,
                                                   property12, value12,
                                                   property13, value13
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

        //--------------------------------
        static STweenCore* to(
                                 flDisplayObject* target,
                                 float duration,
                                 string property1, float value1,
                                 string property2, float value2,
                                 string property3, float value3,
                                 string property4, float value4,
                                 string property5, float value5,
                                 string property6, float value6,
                                 string property7, float value7,
                                 string property8, float value8,
                                 string property9, float value9,
                                 string property10, float value10,
                                 string property11, float value11,
                                 string property12, float value12,
                                 string property13, float value13,
                                 string property14, float value14
                                 ) {
            instance();
            
            for(int i = 0; i < _instance->_tweens.size(); i++) {
                STweenCore* tween = _instance->_tweens[i];
                if(((STween2D*)tween)->__target == target) {
                    //if(tween->__overwrite == TW_NONE) return;
                }
            }
            //overwrite
            _instance->_overwriteCheck2d(target, property1);
            _instance->_overwriteCheck2d(target, property2);
            _instance->_overwriteCheck2d(target, property3);
            _instance->_overwriteCheck2d(target, property4);
            _instance->_overwriteCheck2d(target, property5);
            _instance->_overwriteCheck2d(target, property6);
            _instance->_overwriteCheck2d(target, property7);
            _instance->_overwriteCheck2d(target, property8);
            _instance->_overwriteCheck2d(target, property9);
            _instance->_overwriteCheck2d(target, property10);
            _instance->_overwriteCheck2d(target, property11);
            _instance->_overwriteCheck2d(target, property12);
            _instance->_overwriteCheck2d(target, property13);
            _instance->_overwriteCheck2d(target, property14);
            
            STweenCore* tween = new STween2D(
                                                   target, duration,
                                                   property1, value1,
                                                   property2, value2,
                                                   property3, value3,
                                                   property4, value4,
                                                   property5, value5,
                                                   property6, value6,
                                                   property7, value7,
                                                   property8, value8,
                                                   property9, value9,
                                                   property10, value10,
                                                   property11, value11,
                                                   property12, value12,
                                                   property13, value13,
                                                   property14, value14
                                                   );
            tween->start();
            _instance->_tweens.push_back(tween);
            _instance->_renderStart();
            
            return tween;
        }

    #endif
        
        
        
        
        
        
            //--------------------------------
            //
            inline static void killAll() {
                if(!_instance) return;
                
                int i; int l;
                l = _instance->_tweens.size();
                for(i = 0; i < l; i++) {
                    _instance->_tweens[i]->kill();
                }
            }
            //--------------------------------
            //
            inline static void pause() {
                if(!_instance) return;
                
                int i; int l;
                l = _instance->_tweens.size();
                for(i = 0; i < l; i++) {
                    _instance->_tweens[i]->pause();
                }
            }
            //--------------------------------
            //
            inline static void resume() {
                if(!_instance) return;
                
                int i; int l;
                l = _instance->_tweens.size();
                for(i = 0; i < l; i++) {
                    _instance->_tweens[i]->resume();
                }
            }
        
        protected:
            
        private:
            STweener();
            ~STweener();
            
            void _renderStart();
            void _renderStop();
            void _update();
            
            void _overwriteCheck(float* targetValue);
    #ifdef USE_FLASH_OBJECT
            void _overwriteCheck2d(flDisplayObject* target, string propertyName) {
                STween2D* tween;
                float overwrite;
                //--------------------------------
                //overwrite
                for(int i = 0; i < _instance->_tweens.size(); i++) {
                    tween = (STween2D*)_instance->_tweens[i];
                    if(tween->__target == target) {
                        overwrite = tween->__overwrite;
                        
                        //すべて上書き。
                        //[未実装?]delayが設定してあってもトゥイーンするプロパティが違っていても、記述があった時点で上書きされる。
                        //とにかく書いた順に上書きされる。
                        if(overwrite == TW_ALL_IMMEDIATE) {
                            tween->__toX = numeric_limits<float>::quiet_NaN();
                            tween->__toY = numeric_limits<float>::quiet_NaN();
                            tween->__toZ = numeric_limits<float>::quiet_NaN();
                            tween->__toAlpha = numeric_limits<float>::quiet_NaN();
                            tween->__toWidth = numeric_limits<float>::quiet_NaN();
                            tween->__toHeight = numeric_limits<float>::quiet_NaN();
                            tween->__toScaleX = numeric_limits<float>::quiet_NaN();
                            tween->__toScaleY = numeric_limits<float>::quiet_NaN();
                            tween->__toScaleZ = numeric_limits<float>::quiet_NaN();
                            tween->__toRotation = numeric_limits<float>::quiet_NaN();
                            tween->__toRotationX = numeric_limits<float>::quiet_NaN();
                            tween->__toRotationY = numeric_limits<float>::quiet_NaN();
                            tween->__toRotationZ = numeric_limits<float>::quiet_NaN();
                        }
                        
                        //同じプロパティを上書きする。
                        //デフォルトの設定。
                        //[未実装]onCompleteはプロパティごとに実行される。
                        if(overwrite == TW_AUTO) {
                            if(propertyName == "x") tween->__toX = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "y") tween->__toY = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "z") tween->__toZ = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "alpha") tween->__toAlpha = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "width") tween->__toWidth = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "height") tween->__toHeight = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "scaleX") tween->__toScaleX = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "scaleY") tween->__toScaleY = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "scaleZ") tween->__toScaleZ = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "rotation") tween->__toRotation = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "rotationX") tween->__toRotationX = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "rotationY") tween->__toRotationY = numeric_limits<float>::quiet_NaN();
                            if(propertyName == "rotationZ") tween->__toRotationZ = numeric_limits<float>::quiet_NaN();
                        }
                        
                        //動いていたらトゥイーンを上書き。
                        //[未実装]delayを見て動いているトゥイーンを上書きする。
                        //プロパティごとの上書きではないので、違うプロパティでも上書きされる。
                        if(overwrite == TW_CONCURRENT) {
                            
                        }
                        
                        //優先的にトゥイーン。
                        //[未実装]同時にトゥイーンさせると、delayの値が一番小さく、かつ、その中で最後に記述されたトゥイーンが実行される。
                        //滅多に使わないとのこと。
                        if(overwrite == TW_ALL_ONSTART) {
                            
                        }
                        
                        //[未実装]優先的にトゥイーン。ただし、overwrite=4とは違い、delayも反映される。
                        //overwrite=3との違いがイマイチ不明。
                        if(overwrite == TW_PREEXISTING) {
                            
                        }
                    }
                }
                //--------------------------------
            }

    #endif
        
            void update(ofEventArgs& event) { _update(); };
    };

}