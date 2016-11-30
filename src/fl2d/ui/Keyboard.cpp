#include "Keyboard.h"

namespace fl2d {
    
    bool Keyboard::_isShiftKeyDown = false;
    bool Keyboard::_isShiftKeyChanged = false;
    
    bool Keyboard::_isSpaceKeyDown = false;
    bool Keyboard::_isSpaceKeyChanged = false;
    
    vector<int> Keyboard::_downKeyList;
    
    //--------------------------------------------------------------
    //
    bool Keyboard::isShiftKeyDown() { return _isShiftKeyDown; }
    void Keyboard::isShiftKeyDown(bool value) {
        _isShiftKeyChanged = bool(_isShiftKeyDown != value);
        _isShiftKeyDown = value;
    }
    //--------------------------------------------------------------
    //
    bool Keyboard::isShiftKeyChanged() { return _isShiftKeyChanged; }
    
    //--------------------------------------------------------------
    //
    bool Keyboard::isSpaceKeyDown() { return _isSpaceKeyDown; }
    void Keyboard::isSpaceKeyDown(bool value) {
        _isSpaceKeyChanged = bool(_isSpaceKeyDown != value);
        _isSpaceKeyDown = value;
    }
    //--------------------------------------------------------------
    //
    bool Keyboard::isSpaceKeyChanged() { return _isSpaceKeyChanged; }
    
    //--------------------------------------------------------------
    //
    Keyboard::Keyboard() {
        
    }
    
    //--------------------------------------------------------------
    //
    Keyboard::~Keyboard() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Keyboard::setup() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Keyboard::update() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Keyboard::draw() {
        
    }
    
    //--------------------------------------------------------------
    // PROTECTED / PRIVATE METHOD
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    //
    void Keyboard::__addDownKey(int value) {
        cout << "[Keyboard]__addDownKey(" << value << ")" << endl;
        
        for(int i = 0; i < _downKeyList.size(); i++) {
            if(_downKeyList[i] == value) return;
        }
        _downKeyList.push_back(value);
    }
    void Keyboard::__removeDownKey(int value) {
        cout << "[Keyboard]__removeDownKey(" << value << ")" << endl;
        
        for(int i = 0; i < _downKeyList.size(); i++) {
            if(_downKeyList[i] == value) {
                _downKeyList.erase(_downKeyList.begin() + i);
            }
        }
    }
    bool Keyboard::__checkKeyIsDown(int value) {
        cout << "[Keyboard]__checkKeyIsDown(" << value << ")" << endl;
        
        for(int i = 0; i < _downKeyList.size(); i++) {
            if(_downKeyList[i] == value) return true;
        }
        return false;
    }
    
}
