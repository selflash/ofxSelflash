#include "MainView.h"
//static const double pi = std::acos(-1.0); // お手軽に π を得る。

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
MainView::MainView() {
    cout << "[MainView]MainView()" << endl;
    _target = this;
    name("DocumentRoot");
    
    useHandCursor(true);
}

//--------------------------------------------------------------
//
MainView::~MainView() {
    cout << "[MainView]~MainView()" << endl;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void MainView::_setup() {
    cout << "[MainView]_setup()" << endl;
    
    //--------------------------------------
    //ステージに追加された時にキーボードイベントを監視する
    addEventListener(flEvent::ADDED_TO_STAGE, this, &MainView::_eventHandler);
//    addEventListener(flMouseEvent::MOUSE_DOWN, this, &MainView::_mouseEventHandler);
//    addEventListener(flMouseEvent::MOUSE_UP, this, &MainView::_mouseEventHandler);
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0xffffff, 0.5);
    g->drawRect(0, 0, ofGetWidth(), ofGetHeight());
    g->endFill();
    //-----------------------------------
    
    flFont::loadFont(_fontSize);
}

//--------------------------------------------------------------
//
void MainView::_update() {

}

//--------------------------------------------------------------
//
void MainView::_draw() {
    auto drawText = [](string text, int fontSize, float ix, float iy, bool centering = false)->void {
        ofPushMatrix();
        ofTranslate(ix, iy);
        
        float x = 0;
        float y = 0;
        if(centering) {
            x = -flFont::getStringWidth(text, fontSize) * 0.5;
            y = -flFont::getStringHeight(text, fontSize) * 0.5;
        }
        
        ofPushStyle();
        ofSetColor(0, 0, 0, 255);
        flFont::drawString(text, fontSize, x, y);
        ofPopStyle();
        
        ofPopMatrix();
    };
    
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    string message = "";
    if(type == 1) {
        message = "キャリブレーションを開始します。\r\n    Start Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 2) {
        message = "デバイス1とデバイス2の両方からマーカーが見えるようにして\r\nゆっくり動かしてください。\r\n    Start Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 3) {
        message = "これでいいですか？\r\nOK : Enterキー\r\nやり直す : Spaceキー\r\nキャリブレーションをやめる : Deleteキー\r\nStart Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 4) {
        message = "デバイス1とデバイス3の両方からマーカーが見えるようにして\r\nゆっくり動かしてください。\r\n    Start Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 5) {
        message = "これでいいですか？\r\nOK : Enterキー\r\nやり直す : Spaceキー\r\nキャリブレーションをやめる : Deleteキー\r\nStart Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 6) {
        message = "デバイス1とデバイス4の両方からマーカーが見えるようにして\r\nゆっくり動かしてください。\r\n    Start Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 7) {
        message = "これでいいですか？\r\nOK : Enterキー\r\nやり直す : Spaceキー\r\nキャリブレーションをやめる : Deleteキー\r\nStart Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
    if(type == 8) {
        message = "床にマーカーを置いて、Enterキーを押してください。\r\n    Start Calibration.";
        drawText(message, _fontSize, w * 0.5, h * 0.5, true);
    }
}

//==============================================================
// PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void MainView::_eventHandler(flEvent& event) {
    cout << "[DocumentRoot]_eventHandler(" + event.type() + ")";
    
    if(event.type() == flEvent::ADDED_TO_STAGE) {
        removeEventListener(flEvent::ADDED_TO_STAGE, this, &MainView::_eventHandler);
        
//        stage()->addEventListener(flKeyboardEvent::KEY_PRESS, this, &MainView::_keyboardEventHandler);
//        stage()->addEventListener(flKeyboardEvent::KEY_RELEASE, this, &MainView::_keyboardEventHandler);
    }
}

//--------------------------------------------------------------
//
void MainView::_moveEventHandler(flEvent& event) {
    //cout << "[DocumentRoot]_moveEventHandler(" << event.type() << ")" << endl;
    
    //    cout << "mouse is moving" << endl;
}

//--------------------------------------------------------------
//
void MainView::_mouseEventHandler(flEvent& event) {
    //    cout << "[DocumentRoot]_mouseEventHandler(" << event.type() << ")" << endl;
    //    cout << "[PrentBox]this          = " << this << endl;
    //    cout << "[ParetBox]currentTarget = " << event.currentTarget() << endl;
    //    cout << "[ParetBox]target        = " << event.target() << endl;
    
    if(event.type() == flMouseEvent::MOUSE_OVER) {
        if(event.target() == this) {
            
        }
    }
    if(event.type() == flMouseEvent::MOUSE_OUT) {
        if(event.target() == this) {
            
        }
    }
//    if(event.type() == flMouseEvent::MOUSE_DOWN) {
//        if(event.target() == this) {
//            startDrag();
//            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &MainView::_mouseEventHandler);
//            stage()->addEventListener(flMouseEvent::MOUSE_MOVE, this, &MainView::_moveEventHandler);
//        }
//    }
//    if(event.type() == flMouseEvent::MOUSE_UP) {
//        if(event.currentTarget() == stage()) {
//            stopDrag();
//            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &MainView::_mouseEventHandler);
//            stage()->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &MainView::_moveEventHandler);
//
//            _forceX = (x() - _preX) * 0.5;
//            _forceY = (y() - _preY) * 0.5;
//        }
//    }
}
