#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicController.h"

#include "Config.h"
#include "NetworkManager.h"

using namespace fl2d;

class AppEngine {
    public:
    
    protected:
    
    private:
        static bool _isSetuped;
        
        static float _elapsedTimef;
        static int _frameNum;
    
        static flEventDispatcher* _dispatcher;
    
        //--------------------------------------
        //ステージ
        static flStage* _stage;
        static ofVec2f _stageCenter;
        //--------------------------------------
        
        //--------------------------------------
        //レイヤー
        static flSprite* _frontLayer;
        static flSprite* _middleLayer;
        static flSprite* _backLayer;
        //--------------------------------------
        
        //--------------------------------------
        //グローバルコントローラー
        static flBasicController* _controller;
        //--------------------------------------
        
        //--------------------------------------
        //各マネージャー
        //ネットワークマネージャー
        static NetworkManager* _networkManager;
        //--------------------------------------
        
    public:
        static void setup();
        static void update();
        static void exit();
    
        static const float elapsedTimef();
        static const int frameNum();
    
        //--------------------------------------
        static inline void dispatchEvent(flEvent* event) { _dispatcher->dispatchEvent(event); }
    
        template <class ListenerClass>
        static void addEventListener(const string& type, ListenerClass* listener, void (ListenerClass::*listenerMethod)(flEvent& event), bool useCapture = false, int priority = 0) {
            _dispatcher->addEventListener(type, listener, listenerMethod);
        }
    
        template <class ListenerClass>
        static void removeEventListener(const string& type, void (ListenerClass::*listenerMethod)(flEvent& event)) {
            _dispatcher->removeEventListener(type, listenerMethod);
        }
    
        static inline bool hasEventListener(const string& type) {
            return _dispatcher->hasEventListener(type);
        }
        //--------------------------------------
    
        //--------------------------------------
        //ステージ
        static flStage* stage();
        //ステージの幅と高さ
        static int stageWidth();
        static int stageHeight();
        //ステージの中央の座標
        static ofVec2f& stageCenter();
        //--------------------------------------
        
        //--------------------------------------
        //レイヤー
        static flSprite* frontLayer();
        static void frontLayer(flSprite* value);
        static flSprite* middleLayer();
        static void middleLayer(flSprite* value);
        static flSprite* backLayer();
        static void backLayer(flSprite* value);
        //--------------------------------------
        
        //--------------------------------------
        //グローバルコントローラー
        static flBasicController* controller();
        static void controller(flBasicController* value);
        //--------------------------------------
    
        //--------------------------------------
        //ネットワークマネージャー
        static NetworkManager* networkManager();
        //--------------------------------------

    protected:
    
    private:
        AppEngine();
        //~AppEngine();
    
};
