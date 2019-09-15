#include "flMouse.h"

#ifdef __APPLE__

//--------------------------------------------------------------
//MAC
//--------------------------------------------------------------

#import <Cocoa/Cocoa.h>

namespace fl2d {
    
    int flMouse::_currentType = FLASH_MOUSE_TYPE_ARROW;
    
    ofImage* flMouse::_arrowImage;
    ofImage* flMouse::_pointingHandImage;
    ofImage* flMouse::_openHandImage;
    ofImage* flMouse::_closeHandImage;
    
    //--------------------------------------------------------------
    //
    void flMouse::setup() {
        //_handCursorImage = new ofImage();
        //ofDisableArbTex();
        //_handCursorImage->loadImage("components/hand_cursor.png");
    }
    
    //--------------------------------------------------------------
    //
    void flMouse::draw(float x, float y) {
        //ofPushStyle();
        //ofEnableAlphaBlending();
        //_handCursorImage->draw(x - 10, y - 4);
        //ofDisableAlphaBlending();
        //ofPopStyle();
    }
    
    //--------------------------------------------------------------
    //
    bool flMouse::currentType() { return _currentType; }
    
    //--------------------------------------------------------------
    //
    void flMouse::hide() {
        ofHideCursor();
    }
    //--------------------------------------------------------------
    //
    void flMouse::show() {
        //ofShowCursor();
    }
    
    //--------------------------------------------------------------
    //
    void flMouse::changeCursor(int type) {
        if(_currentType == type) return;
        
        if(type == FLASH_MOUSE_TYPE_ARROW) [[NSCursor arrowCursor] set];
        if(type == FLASH_MOUSE_TYPE_POINTING_HAND)[[NSCursor pointingHandCursor] set];
        if(type == FLASH_MOUSE_TYPE_OPEN_HAND) [[NSCursor openHandCursor] set];
        if(type == FLASH_MOUSE_TYPE_CLOSE_HAND) [[NSCursor closedHandCursor] set];
        
        _currentType = type;
    }
    
    //--------------------------------------------------------------
    //
    void flMouse::showHandCursor() {
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
    void flMouse::hideHandCursor() {
        [[NSCursor arrowCursor] set];
    }
    
}

#elif defined _WIN32

//--------------------------------------------------------------
//WINDOWS
//--------------------------------------------------------------


namespace fl2d {
    
    int flMouse::_currentType = FLASH_MOUSE_TYPE_ARROW;
    
    ofImage* flMouse::_arrowImage;
    ofImage* flMouse::_pointingHandImage;
    ofImage* flMouse::_openHandImage;
    ofImage* flMouse::_closeHandImage;
    
    //--------------------------------------------------------------
    //
    void flMouse::setup() {
        //_handCursorImage = new ofImage();
        //ofDisableArbTex();
        //_handCursorImage->loadImage("components/hand_cursor.png");
    }
    
    //--------------------------------------------------------------
    //
    void flMouse::draw(float x, float y) {
        //ofPushStyle();
        //ofEnableAlphaBlending();
        //_handCursorImage->draw(x - 10, y - 4);
        //ofDisableAlphaBlending();
        //ofPopStyle();
    }
    
    //--------------------------------------------------------------
    //
    bool flMouse::currentType() { return _currentType; }
    
    //--------------------------------------------------------------
    //
    void flMouse::hide() {
        ofHideCursor();
    }
    //--------------------------------------------------------------
    //
    void flMouse::show() {
        //ofShowCursor();
    }
    
    //--------------------------------------------------------------
    //
    void flMouse::changeCursor(int type) {
        if(_currentType == type) return;
        
        if(type == FLASH_MOUSE_TYPE_ARROW) { }
        if(type == FLASH_MOUSE_TYPE_POINTING_HAND) { }
        if(type == FLASH_MOUSE_TYPE_OPEN_HAND) { }
        if(type == FLASH_MOUSE_TYPE_CLOSE_HAND) { }
        
        _currentType = type;
    }
    
    //--------------------------------------------------------------
    //
    void flMouse::showHandCursor() {
        
    };
    
    //--------------------------------------------------------------
    //
    void flMouse::hideHandCursor() {
        
    }
    
}

#endif

