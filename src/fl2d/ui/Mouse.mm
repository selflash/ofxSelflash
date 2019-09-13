#include "Mouse.h"

#ifdef __APPLE__

//--------------------------------------------------------------
//MAC
//--------------------------------------------------------------

#import <Cocoa/Cocoa.h>

namespace fl2d {

    int Mouse::_currentType = FLASH_MOUSE_TYPE_ARROW;

    ofImage* Mouse::_arrowImage;
    ofImage* Mouse::_pointingHandImage;
    ofImage* Mouse::_openHandImage;
    ofImage* Mouse::_closeHandImage;

    //--------------------------------------------------------------
    //
    void Mouse::setup() {
        //_handCursorImage = new ofImage();
        //ofDisableArbTex();
        //_handCursorImage->loadImage("components/hand_cursor.png");
    }

    //--------------------------------------------------------------
    //
    void Mouse::draw(float x, float y) {
        //ofPushStyle();
        //ofEnableAlphaBlending();
        //_handCursorImage->draw(x - 10, y - 4);
        //ofDisableAlphaBlending();
        //ofPopStyle();
    }

    //--------------------------------------------------------------
    //
    bool Mouse::currentType() { return _currentType; }

    //--------------------------------------------------------------
    //
    void Mouse::hide() {
        ofHideCursor();
    }
    //--------------------------------------------------------------
    //
    void Mouse::show() {
        //ofShowCursor();
    }

    //--------------------------------------------------------------
    //
    void Mouse::changeCursor(int type) {
        if(_currentType == type) return;
        
        if(type == FLASH_MOUSE_TYPE_ARROW) [[NSCursor arrowCursor] set];
        if(type == FLASH_MOUSE_TYPE_POINTING_HAND)[[NSCursor pointingHandCursor] set];
        if(type == FLASH_MOUSE_TYPE_OPEN_HAND) [[NSCursor openHandCursor] set];
        if(type == FLASH_MOUSE_TYPE_CLOSE_HAND) [[NSCursor closedHandCursor] set];
        
        _currentType = type;
    }

    //--------------------------------------------------------------
    //
    void Mouse::showHandCursor() {
//    [[NSCursor pointingHandCursor] set];
//    [[NSCursor openHandCursor] set];
//    [[NSCursor closedHandCursor] set];
//    [[NSCursor IBeamCursor] set];
//    [[NSCursor contextualMenuCursor] set];
//    [[NSCursor resizeLeftCursor] set];
//    [[NSCursor resizeRightCursor] set];
//    [[NSCursor resizeUpCursor] set];
//    [[NSCursor resizeDownCursor] set];
//    [[NSCursor crosshairCursor] set];
    };

    //--------------------------------------------------------------
    //
    void Mouse::hideHandCursor() {
        [[NSCursor arrowCursor] set];
    }
        
}

#elif defined _WIN32

//--------------------------------------------------------------
//WINDOWS
//--------------------------------------------------------------


namespace fl2d {
    
    int Mouse::_currentType = FLASH_MOUSE_TYPE_ARROW;
    
    ofImage* Mouse::_arrowImage;
    ofImage* Mouse::_pointingHandImage;
    ofImage* Mouse::_openHandImage;
    ofImage* Mouse::_closeHandImage;
    
    //--------------------------------------------------------------
    //
    void Mouse::setup() {
        //_handCursorImage = new ofImage();
        //ofDisableArbTex();
        //_handCursorImage->loadImage("components/hand_cursor.png");
    }
    
    //--------------------------------------------------------------
    //
    void Mouse::draw(float x, float y) {
        //ofPushStyle();
        //ofEnableAlphaBlending();
        //_handCursorImage->draw(x - 10, y - 4);
        //ofDisableAlphaBlending();
        //ofPopStyle();
    }
    
    //--------------------------------------------------------------
    //
    bool Mouse::currentType() { return _currentType; }
    
    //--------------------------------------------------------------
    //
    void Mouse::hide() {
        ofHideCursor();
    }
    //--------------------------------------------------------------
    //
    void Mouse::show() {
        //ofShowCursor();
    }
    
    //--------------------------------------------------------------
    //
    void Mouse::changeCursor(int type) {
        if(_currentType == type) return;
        
        if(type == FLASH_MOUSE_TYPE_ARROW) { }
        if(type == FLASH_MOUSE_TYPE_POINTING_HAND) { }
        if(type == FLASH_MOUSE_TYPE_OPEN_HAND) { }
        if(type == FLASH_MOUSE_TYPE_CLOSE_HAND) { }
        
        _currentType = type;
    }
    
    //--------------------------------------------------------------
    //
    void Mouse::showHandCursor() {
        
    };
    
    //--------------------------------------------------------------
    //
    void Mouse::hideHandCursor() {
        
    }
    
}

#endif

