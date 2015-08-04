#include "DepthOfFieldController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
DepthOfFieldController::DepthOfFieldController() {
    cout << "[DepthOfFieldController]BloomController()" << endl;
    _target = this;
    
    useHandCursor(true);
    
    _status = "[STATUS]";
    _bokehDOF = NULL;
    
    _nearClip = 1.0;
    _farClip = 20000.0;
    _focalLength = 2.0;
    _focalDepth = 0.5;
    _fstop = 1.0;
    
    _ringCount = 3;
    _ringSamples = 3;
    _texel = 0.0;
    _depthBlurSize = 1.25;
    _maxBlur = 1000;
    
    _highlightThreshold = 0.3;
    _higilightGain = 0.1;
    _edgeBias = 0.5;
    _feather = 0.4;
    _ditherAmount = 0.0001;
    
    _fringe = 0.7;    
}

//--------------------------------------------------------------
//
DepthOfFieldController::~DepthOfFieldController() {
    cout << "[DepthOfFieldController]~DepthOfFieldController()" << endl;
    _target = NULL;
    
    _status = "";
    _bokehDOF = NULL;
    
    _nearClip = 0.0;
    _farClip = 0.0;
    _focalLength = 0.0;
    _focalDepth = 0.0;
    _fstop = 0.0;
    
    _ringCount = 0;
    _ringSamples = 0;
    _texel = 0.0;
    _depthBlurSize = 0.0;
    _maxBlur = 0.0;
    
    _highlightThreshold = 0.0;
    _higilightGain = 0.0;
    _edgeBias = 0.0;
    _feather = 0.0;
    _ditherAmount = 0.0;
    
    _fringe = 0.0;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void DepthOfFieldController::_setup() {
    cout << "[DepthOfFieldController]_setup()" << endl;
    
    BasicController::_setup();
    
    _normalBackWidth = 510;
    _normalBackHeight = 450;
    _minBackWidth = _normalBackWidth;
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    Graphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    
    titleTf->text("[DOF CONTROLLER]");
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    //--------------------------------------
    marginLeft = 200;
    marginTop = 40;
    spacing = 90;
    lineSpacing = 90;
    
    pad001 = new Pad2D(90, 90);
    pad001->label("XZ", 0xffffff);
    pad001->x(marginLeft + spacing * 0);
    pad001->y(marginTop + lineSpacing * 0);
    pad001->addEventListener(PadEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(pad001);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 300;
    marginTop = 25;
    spacing = 320;
    lineSpacing = 40;
    
    
    rangeSlider001 = new RangeSlider(200);
    rangeSlider001->label("CLIPING", 0xffffff);
    rangeSlider001->min(0.1, false);
    rangeSlider001->max(50000.0, false);
    rangeSlider001->minValue(0.1, false);
    rangeSlider001->maxValue(50000.0, false);
    rangeSlider001->x(marginLeft + spacing * 0);
    rangeSlider001->y(marginTop + lineSpacing * 0);
    rangeSlider001->addEventListener(RangeSliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(rangeSlider001);
    
    slider001 = new Slider(200);
    slider001->label("SAMPLES", 0xffffff);
    slider001->min(1.0, false);
    slider001->max(10.0, false);
    slider001->value(5.0, false);
    slider001->x(marginLeft + spacing * 0);
    slider001->y(marginTop + lineSpacing * 1);
    slider001->roundEnabled(true);
    slider001->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider001);
    
    slider002 = new Slider(200);
    slider002->label("RING COUNT", 0xffffff);
    slider002->min(1.0, false);
    slider002->max(10.0, false);
    slider002->value(4.0, false);
    slider002->x(marginLeft + spacing * 0);
    slider002->y(marginTop + lineSpacing * 2);
    slider002->roundEnabled(true);
    slider002->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider002);
    
    slider003 = new Slider(200);
    slider003->label("TEXEL SIZE", 0xffffff);
    slider003->min(0.0, false);
    slider003->max(1.0, false);
    slider003->value(0.25, false);
    slider003->x(marginLeft + spacing * 0);
    slider003->y(marginTop + lineSpacing * 3);
//    slider003->roundEnabled(true);
    slider003->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider003);

    slider004 = new Slider(200);
    slider004->label("BLUR SIZE", 0xffffff);
    slider004->min(0.0, false);
    slider004->max(100.0, false);
    slider004->value(1.25, false);
    slider004->x(marginLeft + spacing * 0);
    slider004->y(marginTop + lineSpacing * 4);
//    slider004->roundEnabled(true);
    slider004->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider004);
    
    slider005 = new Slider(200);
    slider005->label("MAX BLUR SIZE", 0xffffff);
    slider005->min(0.0, false);
    slider005->max(1000.0, false);
    slider005->value(500.0, false);
    slider005->x(marginLeft + spacing * 0);
    slider005->y(marginTop + lineSpacing * 5);
//    slider005->roundEnabled(true);
    slider005->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider005);
    
    slider006 = new Slider(200);
    slider006->label("HIGHLIGHT THRESHOLD", 0xffffff);
    slider006->min(0.1, false);
    slider006->max(15.0, false);
    slider006->value(2.6, false);
    slider006->x(marginLeft + spacing * 0);
    slider006->y(marginTop + lineSpacing * 6);
//    slider006->roundEnabled(true);
    slider006->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider006);
    
    slider007 = new Slider(200);
    slider007->label("HIGHLIGHT GAIN", 0xffffff);
    slider007->min(0.1, false);
    slider007->max(15.0, false);
    slider007->value(8.0, false);
    slider007->x(marginLeft + spacing * 0);
    slider007->y(marginTop + lineSpacing * 7);
//    slider007->roundEnabled(true);
    slider007->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider007);
    
    slider008 = new Slider(200);
    slider008->label("EDGE BIAS", 0xffffff);
    slider008->min(0.1, false);
    slider008->max(15.0, false);
    slider008->value(0.5, false);
    slider008->x(marginLeft + spacing * 0);
    slider008->y(marginTop + lineSpacing * 8);
//    slider008->roundEnabled(true);
    slider008->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider008);
    
    slider009 = new Slider(200);
    slider009->label("FEATHER", 0xffffff);
    slider009->min(0.1, false);
    slider009->max(10.0, false);
    slider009->value(3.0, false);
    slider009->x(marginLeft + spacing * 0);
    slider009->y(marginTop + lineSpacing * 9);
//    slider009->roundEnabled(true);
    slider009->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider009);
    
    slider010 = new Slider(200);
    slider010->label("DITHER AMOUNT", 0xffffff);
    slider010->min(0.0001, false);
    slider010->max(0.001, false);
    slider010->value(0.001, false);
    slider010->x(marginLeft + spacing * 0);
    slider010->y(marginTop + lineSpacing * 10);
//    slider010->roundEnabled(true);
    slider010->addEventListener(SliderEvent::CHANGE, this, &DepthOfFieldController::_uiEventHandler);
    addChild(slider010);
}

//--------------------------------------------------------------
//
void DepthOfFieldController::_update() {
    //    cout << "[BloomController]_update()" << endl;
    
    if(_bokehDOF) {
//        _status = "RENDERER----------\n";
//        _status += "[NAME]\n";
//        _status += ofToString(_renderer->name()) + "\n";
//        _status += "[FADE]\n";
//        _status += "ENABLED           : " + ofToString(_renderer->afterglowEnabled()) + "\n";
//        _status += "ALPHA             : " + ofToString(_renderer->afterglowAlpha()) + "\n";
//        _status += "[DOF]\n";
//        _status += "ENABLED           : " + ofToString(_renderer->dofEnabled()) + "\n";
//        _status += "FOCAL DISTANCE    : " + ofToString(_renderer->focalDistance()) + "\n";
//        _status += "FOCAL RANGE       : " + ofToString(_renderer->focalLength()) + "\n";
//        _status += "BLUR RADIUS       : " + ofToString(_renderer->blurRadius()) + "\n";
//        _status += "[SHADOWMAPPING]\n";
//        _status += "ENABLED           : " + ofToString(_renderer->shadowMappingEnabled()) + "\n";
//        _status += "MAP SIZE          : " + ofToString(_renderer->shadowMappingFx().mapSize()) + "\n";
//        _status += "FOV               : " + ofToString(_renderer->shadowMappingFx().fov()) + "\n";
//        _status += "NEAR              : " + ofToString(_renderer->shadowMappingFx().near()) + "\n";
//        _status += "FAR               : " + ofToString(_renderer->shadowMappingFx().far()) + "\n";
//        _status += "[FOG]\n";
//        _status += "ENABLED           : " + ofToString(_renderer->fogEnabled()) + "\n";
//        _status += "NEAR              : " + ofToString(_renderer->fogNear()) + "\n";
//        _status += "FAR               : " + ofToString(_renderer->fogFar()) + "\n";
    }
}

//--------------------------------------------------------------
//
void DepthOfFieldController::_draw() {
//    cout << "[DepthOfFieldController]_draw()" << endl;
    
    if(_isMinimize) return;

    ofDrawBitmapString(_status, 10, 40);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

/**
        if(slider == slider001) _renderer->samples(slider->value());
        if(slider == slider002) _renderer->ringCount(slider->value());
        if(slider == slider003) _renderer->ringCount(slider->value());
        if(slider == slider004) _renderer->dofBlurSize(slider->value());
        if(slider == slider005) _renderer->dofMaxBlur(slider->value());
        if(slider == slider006) _renderer->highlightThreshold(slider->value());
        if(slider == slider007) _renderer->highlightGain(slider->value());
        if(slider == slider008) _renderer->edgeBias(slider->value());
        if(slider == slider009) _renderer->feather(slider->value());
        if(slider == slider010) _renderer->ditherAmount(slider->value());
 */

//--------------------------------------------------------------
//
BokehDOF* DepthOfFieldController::bokehDOF() { return _bokehDOF; }
void DepthOfFieldController::bokehDOF(BokehDOF* value) {
    _bokehDOF = value;
    
    nearClip(_bokehDOF->nearClip());
    farClip(_bokehDOF->farClip());
    ringSamples(_bokehDOF->ringSamples());
    ringCount(_bokehDOF->ringCount());
    depthBlurSize(_bokehDOF->depthBlurSize());
    maxBlur(_bokehDOF->maxBlur());
    highlightThreshold(_bokehDOF->highlightThreshold());
    higilightGain(_bokehDOF->higilightGain());
    edgeBias(_bokehDOF->edgeBias());
    feather(_bokehDOF->feather());
    ditherAmount(_bokehDOF->ditherAmount());
}

//--------------------------------------------------------------
//
float DepthOfFieldController::nearClip() { return _nearClip; }
void DepthOfFieldController::nearClip(float value) {
    _nearClip = value;
    _bokehDOF->nearClip(_nearClip);
    rangeSlider001->minValue(_nearClip, false);
}

//--------------------------------------------------------------
//
float DepthOfFieldController::farClip() { return _farClip; }
void DepthOfFieldController::farClip(float value) {
    _farClip = value;
    _bokehDOF->farClip(_farClip);
    rangeSlider001->maxValue(_farClip, false);
}

//--------------------------------------------------------------
// where is the focal plane from the camera
float DepthOfFieldController::focalLength() { return _focalLength; }
void DepthOfFieldController::focalLength(float value) { _focalLength = value; }

//--------------------------------------------------------------
// how much of the scene is in focus, smaller number is a narrower focal distance
float DepthOfFieldController::focalDepth() { return _focalDepth; }
void DepthOfFieldController::focalDepth(float value) { _focalDepth = value; }

float DepthOfFieldController::fstop() { return _fstop; }
void DepthOfFieldController::fstop(float value) { _fstop = value; }


int DepthOfFieldController::ringCount() { return _ringCount; }
void DepthOfFieldController::ringCount(int value) {
    _ringCount = value;
    _bokehDOF->ringCount(_ringCount);
    slider002->value(_ringCount, false);
}

int DepthOfFieldController::ringSamples() { return _ringSamples; }
void DepthOfFieldController::ringSamples(int value) {
    _ringSamples = value;
    _bokehDOF->ringSamples(_ringSamples);
    slider001->value(_ringSamples, false);
}

float DepthOfFieldController::texel() { return _texel; }
void DepthOfFieldController::texel(float value) { _texel = value; }

float DepthOfFieldController::depthBlurSize() { return _depthBlurSize; }
void DepthOfFieldController::depthBlurSize(float value) {
    _depthBlurSize = value;
    _bokehDOF->depthBlurSize(_depthBlurSize);
    slider004->value(_depthBlurSize, false);
}

float DepthOfFieldController::maxBlur() { return _maxBlur; }
void DepthOfFieldController::maxBlur(float value) {
    _maxBlur = value;
    _bokehDOF->maxBlur(_maxBlur);
    slider005->value(_maxBlur, false);
}


float DepthOfFieldController::highlightThreshold() { return _highlightThreshold; }
void DepthOfFieldController::highlightThreshold(float value) {
    _highlightThreshold = value;
    _bokehDOF->highlightThreshold(_highlightThreshold);
    slider006->value(_highlightThreshold, false);
}

float DepthOfFieldController::higilightGain() { return _higilightGain; }
void DepthOfFieldController::higilightGain(float value) {
    _higilightGain = value;
    _bokehDOF->higilightGain(_higilightGain);
    slider007->value(_higilightGain, false);
}

float DepthOfFieldController::edgeBias() { return _edgeBias; }
void DepthOfFieldController::edgeBias(float value) {
    _edgeBias = value;
    _bokehDOF->edgeBias(_edgeBias);
    slider008->value(_edgeBias, false);
}

float DepthOfFieldController::feather() { return _feather; }
void DepthOfFieldController::feather(float value) {
    _feather = value;
    _bokehDOF->feather(_feather);
    slider009->value(_feather, false);
}

float DepthOfFieldController::ditherAmount() { return _ditherAmount; }
void DepthOfFieldController::ditherAmount(float value) {
    _ditherAmount = value;
    _bokehDOF->ditherAmount(_ditherAmount);
    slider010->value(_ditherAmount, false);
}

float DepthOfFieldController::fringe() { return _fringe; }
void DepthOfFieldController::fringe(float value) { _fringe = value; }

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void DepthOfFieldController::_uiEventHandler(Event& event) {
    cout << "[DepthOfFieldController]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスアップ)
    if(event.type() == MouseEvent::MOUSE_UP) {
        Button* button = (Button*)(event.currentTarget());
    };
    
    //ラジオボタン
    if(event.type() == RadioButtonEvent::CHANGE) {
        RadioButton* radio = (RadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
    
    //スライダー
    if(event.type() == SliderEvent::CHANGE) {
        Slider* slider = (Slider*)(event.currentTarget());
        if(slider == slider001) ringSamples(slider->value());
        if(slider == slider002) ringCount(slider->value());
//        if(slider == slider003) _renderer->ringCount(slider->value());
        if(slider == slider004) depthBlurSize(slider->value());
        if(slider == slider005) maxBlur(slider->value());
        if(slider == slider006) highlightThreshold(slider->value());
        if(slider == slider007) higilightGain(slider->value());
        if(slider == slider008) edgeBias(slider->value());
        if(slider == slider009) feather(slider->value());
        if(slider == slider010) ditherAmount(slider->value());
    }
    
    //レンジスライダー
    if(event.type() == RangeSliderEvent::CHANGE) {
        RangeSlider* slider = (RangeSlider*)(event.currentTarget());
        if(slider == rangeSlider001) {
            nearClip(slider->minValue());
            farClip(slider->maxValue());
        }
    }
    
    //カラースライダー
    if(event.type() == ColorSliderEvent::CHANGE){
        ColorSlider* slider = (ColorSlider*)(event.currentTarget());
    }
    
    //カラーピッカー
    
    //2Dパッド
    if(event.type() == PadEvent::CHANGE) {
        Pad2D* pad = (Pad2D*)(event.currentTarget());
    }
    
    //ジョイスティック
    if(event.type() == JoystickEvent::UP) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::DOWN) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::LEFT) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::RIGHT) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    
    //コンボボックス
    if(event.type() == ComboBoxEvent::CHANGE) {
        ComboBox* comboBox = (ComboBox*)(event.currentTarget());
    };
}
