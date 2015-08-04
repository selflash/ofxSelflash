#include "BasicController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
BasicController::BasicController() {
    //cout << "[BasicController]BasicController()" << endl;
    _target = this;
    name("BasicController");
    
    useHandCursor(true);
    
    addEventListener(flMouseEvent::ROLL_OVER, this, &BasicController::_mouseEventHandler);
    addEventListener(flMouseEvent::ROLL_OUT, this, &BasicController::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &BasicController::_mouseEventHandler);
    //addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    //--------------------------------------
    marginLeft = 10;
    marginTop = 15;
    spacing = 100;
    lineSpacing = 20;
    
    titleTf = new flTextField();
    titleTf->x(marginLeft + spacing * 0);
    titleTf->y(marginTop + lineSpacing * 0);
    titleTf->width(120);
    titleTf->textColor(0xffffff);
    titleTf->text("[CONTROLLER]");
    addChild(titleTf);
    //--------------------------------------
    
    _isMinimize = false;
    
    //最小化ボタン
    minimizeButton = new flButton(20);
    minimizeButton->label("-");
    minimizeButton->toggleEnabled(true);
    minimizeButton->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_buttonEventHandler);
    addChild(minimizeButton);
    
    //閉じるボタン
    xButton = new flButton(20);
    xButton->label("x");
    xButton->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_buttonEventHandler);
    addChild(xButton);
    
    _backWidth = 0;
    _backHeight = 0;
    
    _minBackWidth = 0;
    _minBackHeight = 40;
    
    _normalBackWidth = 0;
    _normalBackHeight = 0;
    
    _onTop = true;
}

//--------------------------------------------------------------
//
BasicController::~BasicController() {
    cout << "[BasicController]~BasicController()" << endl;
    _target = NULL;
    
    removeEventListener(flMouseEvent::ROLL_OVER, &BasicController::_mouseEventHandler);
    removeEventListener(flMouseEvent::ROLL_OUT, &BasicController::_mouseEventHandler);
    removeEventListener(flMouseEvent::MOUSE_DOWN, &BasicController::_mouseEventHandler);
    //removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
    
    //最小化ボタン
    minimizeButton->removeEventListener(flMouseEvent::MOUSE_UP, &BasicController::_buttonEventHandler);
    delete minimizeButton;
    minimizeButton = NULL;
    
    //閉じるボタン
    xButton->removeEventListener(flMouseEvent::MOUSE_UP, &BasicController::_buttonEventHandler);
    delete xButton;
    xButton = NULL;
    
    _backWidth = 0;
    _backHeight = 0;
    
    _minBackWidth = 0;
    _minBackHeight = 0;
    
    _normalBackWidth = 0;
    _normalBackHeight = 0;
    
    _onTop = false;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void BasicController::setup() {
    //Sprite::setup();
    
    _setup();
    
    _updateRect();
    
    minimizeButton->x(width() - 60);
    minimizeButton->y(10);
    
    xButton->x(width() - 30);
    xButton->y(10);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
void BasicController::minimize() {
    if(_isMinimize) return;
    _isMinimize = true;
    minimizeButton->selected(true);
    
    //----------------------------------
    _backWidth = _minBackWidth;
    _backHeight = _minBackHeight;
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    //----------------------------------
    
    //----------------------------------
    int i; int l;
    l = numChildren();
    for(i = 0; i < l; i++) {
        getChildAt(i)->visible(false);
    }
    titleTf->visible(true);
    minimizeButton->visible(true);
    xButton->visible(true);
    //----------------------------------
}
//--------------------------------------------------------------
//
void BasicController::normalize() {
    if(!_isMinimize) return;
    _isMinimize = false;
    
    minimizeButton->selected(false);
    
    //----------------------------------
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    //----------------------------------
    
    //----------------------------------
    int i; int l;
    l = numChildren();
    for(i = 0; i < l; i++) {
        getChildAt(i)->visible(true);
    }
    
    if(parent()) ((DisplayObjectContainer*)parent())->addChild(this);
    //----------------------------------
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void BasicController::_mouseEventHandler(flEvent& event) {
/*
    cout << "\n----------------------------------------------------------" << endl;
    printf("[BasicController]_mouseEventHandler(%s) %s\n", ofToString(event.type()).c_str(), name().c_str());
    cout << "target = " << ((DisplayObject*)event.target())->name().c_str() << endl;
    cout << "currnetTarget = " << ((DisplayObject*)event.currentTarget())->name().c_str() << endl;
    cout << "----------------------------------------------------------\n" << endl;
*/    
    
    //ボタン(ロールオーバー)
    if(event.type() == flMouseEvent::ROLL_OVER) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            
        }
    }
    //ボタン(ロールアウト)
    if(event.type() == flMouseEvent::ROLL_OUT) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());

        if(event.target() == this) {
            
        }
    }
    //ボタン(マウスオーバー)
    if(event.type() == flMouseEvent::MOUSE_OVER) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            
        }
    }
    //ボタン(マウスアウト)
    if(event.type() == flMouseEvent::MOUSE_OUT) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            
        }
    }
    //ボタン(マウスダウン)
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            if(_onTop) ((DisplayObjectContainer*)parent())->addChild(this);
            startDrag();
            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
        }
    }
    //ボタン(マウスアップ)
    if(event.type() == flMouseEvent::MOUSE_UP) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        //if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
        if(event.target() == stage()) {
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, &BasicController::_mouseEventHandler);
            stopDrag();
        }
    }
}

//--------------------------------------------------------------
//
void BasicController::_buttonEventHandler(flEvent& event) {
    if(event.type() == flMouseEvent::MOUSE_UP) {
        if(event.target() == xButton) dispatchEvent(new flEvent(flEvent::CLOSE));
        if(event.target() == minimizeButton) {
            if(minimizeButton->selected()) {
                minimize();
            } else {
                normalize();
            }
        }
    }
}