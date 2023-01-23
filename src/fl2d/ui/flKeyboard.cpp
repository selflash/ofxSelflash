#include "flKeyboard.h"

namespace fl2d {
    
    bool flKeyboard::_isShiftKeyDown = false;
    bool flKeyboard::_isShiftKeyChanged = false;
    
    bool flKeyboard::_isSpaceKeyDown = false;
    bool flKeyboard::_isSpaceKeyChanged = false;
    
    vector<int> flKeyboard::_downKeyList;
    
    //--------------------------------------------------------------
    bool flKeyboard::isShiftKeyDown() { return _isShiftKeyDown; }
    void flKeyboard::isShiftKeyDown(bool value) {
        _isShiftKeyChanged = bool(_isShiftKeyDown != value);
        _isShiftKeyDown = value;
    }
    //--------------------------------------------------------------
    bool flKeyboard::isShiftKeyChanged() { return _isShiftKeyChanged; }
    
    //--------------------------------------------------------------
    bool flKeyboard::isSpaceKeyDown() { return _isSpaceKeyDown; }
    void flKeyboard::isSpaceKeyDown(bool value) {
        _isSpaceKeyChanged = bool(_isSpaceKeyDown != value);
        _isSpaceKeyDown = value;
    }
    //--------------------------------------------------------------
    bool flKeyboard::isSpaceKeyChanged() { return _isSpaceKeyChanged; }
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flKeyboard::flKeyboard() {
        
    }
    
    //--------------------------------------------------------------
    flKeyboard::~flKeyboard() {
        
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //--------------------------------------------------------------
    void flKeyboard::setup() {
        
    }
    
    //--------------------------------------------------------------
    void flKeyboard::update() {
        
    }
    
    //--------------------------------------------------------------
    void flKeyboard::draw() {
        
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flKeyboard::__addDownKey(int value) {
        //        ofLog() << "[Keyboard]__addDownKey(" << value << ")";
        
        for(int i = 0; i < _downKeyList.size(); i++) {
            if(_downKeyList[i] == value) return;
        }
        _downKeyList.push_back(value);
    }
    void flKeyboard::__removeDownKey(int value) {
        //        ofLog() << "[Keyboard]__removeDownKey(" << value << ")";
        
        for(int i = 0; i < _downKeyList.size(); i++) {
            if(_downKeyList[i] == value) {
                _downKeyList.erase(_downKeyList.begin() + i);
            }
        }
    }
    bool flKeyboard::__checkKeyIsDown(int value) {
        //        ofLog() << "[Keyboard]__checkKeyIsDown(" << value << ")";
        
        for(int i = 0; i < _downKeyList.size(); i++) {
            if(_downKeyList[i] == value) return true;
        }
        return false;
    }
    
}
