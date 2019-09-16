#include "AppEngine.h"

bool AppEngine::_isSetuped = false;

float AppEngine::_elapsedTimef = 0.0;
int AppEngine::_frameNum = 0;

flEventDispatcher* AppEngine::_dispatcher = new flEventDispatcher();

flStage* AppEngine::_stage = NULL;
ofVec2f AppEngine::_stageCenter;

flSprite* AppEngine::_frontLayer = NULL;
flSprite* AppEngine::_middleLayer = NULL;
flSprite* AppEngine::_backLayer = NULL;

NetworkManager* AppEngine::_networkManager = NULL;

flBasicController* AppEngine::_controller = NULL;

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
// 初期化
void AppEngine::setup() {
    ofLog(OF_LOG_VERBOSE) << "[AppEngine]setup()" << endl;
	if(_isSetuped) return;
    
    //--------------------------------------
    //ステージの用意
    _stage = flStage::instance();
	//-------------------------------------
    
	//-------------------------------------
    //ネットワークマネージャー
    _networkManager = new NetworkManager();
    _networkManager->setup(2);
	//-------------------------------------
    
	_isSetuped = true;
}

//--------------------------------------------------------------
//
void AppEngine::update() {
//    ofLog(OF_LOG_VERBOSE) << "[AppEngine]update()" << endl;
    
    _elapsedTimef = ofGetElapsedTimef();
    _frameNum = ofGetFrameNum();
    
    //ネットワーク
    _networkManager->update();
}

//--------------------------------------------------------------
//
void AppEngine::exit() {
    ofLog(OF_LOG_VERBOSE) << "[AppEngine]exit()" << endl;
    
	_isSetuped = false;
    
    //--------------------------------------
    //ステージの破棄
    flStage::clear();
	//-------------------------------------
    
	//-------------------------------------
    //ネットワークマネージャー
    _networkManager->close();
    delete _networkManager;
    _networkManager = NULL;
	//-------------------------------------
}

//==============================================================
// STATIC PUBLIC METHOD
//==============================================================

//--------------------------------------------------------------
//
const float AppEngine::elapsedTimef() { return _elapsedTimef; }
//--------------------------------------------------------------
//
const int AppEngine::frameNum() { return _frameNum; }

//--------------------------------------------------------------
//
flStage* AppEngine::stage() { return _stage; }
int AppEngine::stageWidth() { return _stage->stageWidth(); }
int AppEngine::stageHeight() { return _stage->stageHeight(); }
//ステージの中央の座標
ofVec2f& AppEngine::stageCenter() {
    _stageCenter.x = _stage->stageWidth() * 0.5;
    _stageCenter.y = _stage->stageHeight() * 0.5;
    return _stageCenter;
}

//--------------------------------------------------------------
//
flSprite* AppEngine::frontLayer() { return _frontLayer; }
void AppEngine::frontLayer(flSprite* value) {
    _frontLayer = value;
    _frontLayer->name("FrontLayer");
    _frontLayer->mouseEnabled(false);
}
//--------------------------------------------------------------
//
flSprite* AppEngine::middleLayer() { return _middleLayer; }
void AppEngine::middleLayer(flSprite* value) {
    _middleLayer = value;
    _middleLayer->name("MiddleLayer");
    _middleLayer->mouseEnabled(false);
}
//--------------------------------------------------------------
//
flSprite* AppEngine::backLayer() { return _backLayer; }
void AppEngine::backLayer(flSprite* value) {
    _backLayer = value;
    _backLayer->name("BackLayer");
    _backLayer->mouseEnabled(false);
}

//--------------------------------------------------------------
//
flBasicController* AppEngine::controller() { return _controller; }
void AppEngine::controller(flBasicController* value) { _controller = value; }

//==============================================================
// NETWORK MANAGER API
//==============================================================

//--------------------------------------------------------------
//ネットワークマネージャー
NetworkManager* AppEngine::networkManager() { return _networkManager; }
