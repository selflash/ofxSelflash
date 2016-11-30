#pragma once

#include <limits>
#include <stdarg.h>
#include <string>

#include "STweenSelector.h"
#include "DelayedCallFunction.h"
#include "CallBackFuncion.h"

/*
 TW_NONE
 上書きしない。
 パフォーマンスは一番いいらしい。
 [未実装]onCompleteはトゥイーンごとに実行される。
 
 TW_ALL_IMMEDIAT
 すべて上書き。
 [未実装?]delayが設定してあってもトゥイーンするプロパティが違っていても、記述があった時点で上書きされる。
 とにかく書いた順に上書きされる。
 
 TW_AUTO
 同じプロパティを上書きする。
 デフォルトの設定。
 [未実装]onCompleteはプロパティごとに実行される。
 
 TW_CONCURRENT
 動いていたらトゥイーンを上書き。
 [未実装]delayを見て動いているトゥイーンを上書きする。
 プロパティごとの上書きではないので、違うプロパティでも上書きされる。
 
 TW_ALL_ONSTART
 優先的にトゥイーン。
 [未実装]同時にトゥイーンさせると、delayの値が一番小さく、かつ、その中で最後に記述されたトゥイーンが実行される。
 滅多に使わないとのこと。
 
 TW_PREEXISTING
 [未実装]優先的にトゥイーン。ただし、overwrite=4とは違い、delayも反映される。
 overwrite=3との違いがイマイチ不明。
 */


#define TW_NONE                     0
#define TW_ALL_IMMEDIATE            1
#define TW_AUTO                     2
#define TW_CONCURRENT               3
#define TW_ALL_ONSTART              4
#define TW_PREEXISTING              5

namespace fltw {

    class STweener;
    class STweenCore {
        friend STweener;
        
        public:
            static float elapsedTimeMillis;
        
        protected:
            //--------------------------------
            bool _isTweening;
            bool _isStart;
            bool _isPause;
            bool __isCompleted;
        
            float _startTime;
            float _time;
        
            float _pauseStartTime;
            float _pauseTime;
        
            float _delay;
            //--------------------------------
        
            typedef DelayedCallFunction<float> DelayedCall;
            DelayedCall __delayedCall;
        
            typedef CallBackFuncion<float> CallBack;
            CallBack __onStart;
            CallBack __onUpdate;
            CallBack __onComplete;
        
        private:

        public:
            //--------------------------------------------------------------
            //
            STweenCore() { };
        
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            inline STweenCore(float delay, ListenerClass *listener, void (ListenerClass::*listenerMethod)()) {
                ofLog(OF_LOG_VERBOSE) << "[STweenCore]STweenCore()";
                reset();
                
                _startTime = STweenCore::elapsedTimeMillis;
            
                _delay = delay * 1000.0;
                
                __delayedCall = new DelayedCall::T<ListenerClass>(listener, listenerMethod);
            }
        
            //--------------------------------------------------------------
            //
            ~STweenCore() {
                reset();
            };
        
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
                //TODO PAUSEしてた時間を考慮しないといけない
                _time = (STweenCore::elapsedTimeMillis - _pauseTime) - _startTime;
                if (_time <= _delay) return;
                
                __isCompleted = true;
                
                __delayedCall();
            }
        
            //==============================================================
            // PUBLIC METHOD
            //==============================================================
        
            //--------------------------------------------------------------
            //
            virtual STweenCore* start() {
                _isStart = true;
                _isPause = false;
    //            _startTime = (float)ofGetElapsedTimeMillis();
    //            cout << "StartTime" << _startTime << endl;
                return this;
            }
        
            //--------------------------------------------------------------
            //
            inline virtual STweenCore* pause() {
                _isPause = true;
                _pauseStartTime = STweenCore::elapsedTimeMillis;
                return this;
            }
            //--------------------------------------------------------------
            //
            inline virtual STweenCore* resume() {
                if(_isPause) _pauseTime += (STweenCore::elapsedTimeMillis - _pauseStartTime);
                _isPause = false;
                return this;
            }
        
            //--------------------------------------------------------------
            //
            inline virtual STweenCore* kill() {
                _isPause = true;
                //reset();
                __isCompleted = true;
                return this;
            }
        
            //--------------------------------------------------------------
            //
            inline virtual STweenCore* reset() {
                ofLog(OF_LOG_VERBOSE) << "[STweenCore]reset()";
                
                _isTweening = false;
                _isStart = false;
                _isPause = true;
                __isCompleted = false;

                _startTime = 0.0;
                _time = 0.0;
                
                _pauseStartTime = 0.0;
                _pauseTime = 0.0;
                
                _delay = 0.0;
                
                __delayedCall = 0;
                __onStart = 0;
                __onUpdate = 0;
                __onComplete = 0;
                
                return this;
            }
        
            //==============================================================
            // SETTER / GETTER
            //==============================================================
        
            //--------------------------------------------------------------
            //
            inline bool isTweening() { return _isTweening; };
            //--------------------------------------------------------------
            //
            inline float time() { return _time; };

            //--------------------------------------------------------------
            //
    //        template <class ListenerClass>
    //        inline STweenCore* onStart(ListenerClass *listener, void (ListenerClass::*listenerMethod)()) {
    //            __onStart = new CallBack::T<ListenerClass>(listener, listenerMethod);
    //            return this;
    //        }
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            inline STweenCore* onStart(ListenerClass *listener, void (ListenerClass::*listenerMethod)(STweenCore* currentTarget)) {
                __onStart = new CallBack::T<ListenerClass>(listener, listenerMethod);
                return this;
            }
        
            //--------------------------------------------------------------
            //
    //        template <class ListenerClass>
    //        inline STweenCore* onUpdate(ListenerClass *listener, void (ListenerClass::*listenerMethod)()) {
    //            __onUpdate = new CallBack::T<ListenerClass>(listener, listenerMethod);
    //            return this;
    //        }
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            inline STweenCore* onUpdate(ListenerClass *listener, void (ListenerClass::*listenerMethod)(STweenCore* currentTarget)) {
                __onUpdate = new CallBack::T<ListenerClass>(listener, listenerMethod);
                return this;
            }
        
            //--------------------------------------------------------------
            //
    //        template <class ListenerClass>
    //        inline STweenCore* onComplete(ListenerClass *listener, void (ListenerClass::*listenerMethod)()) {
    //            __onComplete = new CallBack::T<ListenerClass>(listener, listenerMethod);
    //            return this;
    //        }
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            inline STweenCore* onComplete(ListenerClass *listener, void (ListenerClass::*listenerMethod)(STweenCore* currentTarget)) {
                __onComplete = new CallBack::T<ListenerClass>(listener, listenerMethod);
                return this;
            }

        protected:
            virtual bool _updateProperty(float* target) { }
            virtual bool _updateProperty(bool onStart = false) { };
            virtual void _setProperty(const std::string& propertyName, float value) { };
        
        private:
        
    };

}