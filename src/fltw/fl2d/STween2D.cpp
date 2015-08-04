#include "STween2D.h"

namespace fltw {

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    bool STween2D::_updateProperty(bool onStart) {
        float diff; float temp;
        bool complete = true;
        
        float t; float b; float c; float d; float p; float a;
        
        //-------------------------------
        //ofxSTween x
        if(!isnan(__toX)) {
            if(!_delayComplete) {
                _fromX = __target->x();
                _diffX = __toX - _fromX;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromX;
                c = _diffX;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->x(temp);
                
                complete = false;
            } else {
                __target->x(__toX);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween y
        if(!isnan(__toY)) {
            if(!_delayComplete) {
                _fromY = __target->y();
                _diffY = __toY - _fromY;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromY;
                c = _diffY;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->y(temp);
                
                complete = false;
            } else {
                __target->y(__toY);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween z
        if(!isnan(__toZ)) {
            if(!_delayComplete) {
                _fromZ = __target->z();
                _diffZ = __toZ - _fromZ;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromZ;
                c = _diffZ;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->z(temp);
                
                complete = false;
            } else {
                __target->z(__toZ);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        
        //-------------------------------
        //ofxSTween alpha
        if(!isnan(__toAlpha)) {
            if(!_delayComplete) {
                _fromAlpha = __target->alpha();
                _diffAlpha = __toAlpha - _fromAlpha;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromAlpha;
                c = _diffAlpha;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->alpha(temp);
                
                complete = false;
            } else {
                __target->alpha(__toAlpha);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        
        //-------------------------------
        //ofxSTween width
        if(!isnan(__toWidth)) {
            if(!_delayComplete) {
                _fromWidth = __target->width();
                _diffWidth = __toWidth - _fromWidth;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromWidth;
                c = _diffWidth;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->width(temp);
                
                complete = false;
            } else {
                __target->width(__toWidth);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        
        //-------------------------------
        //ofxSTween height
        if(!isnan(__toHeight)) {
            if(!_delayComplete) {
                _fromHeight = __target->height();
                _diffHeight = __toHeight - _fromHeight;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromHeight;
                c = _diffHeight;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->height(temp);
                
                complete = false;
            } else {
                __target->height(__toHeight);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        
        //-------------------------------
        //ofxSTween scaleX
        if(!isnan(__toScaleX)) {
            if(!_delayComplete) {
                _fromScaleX = __target->scaleX();
                _diffScaleX = __toScaleX - _fromScaleX;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromScaleX;
                c = _diffScaleX;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->scaleX(temp);
                
                complete = false;
            } else {
                __target->scaleX(__toScaleX);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween scaleY
        if(!isnan(__toScaleY)) {
            if(!_delayComplete) {
                _fromScaleY = __target->scaleY();
                _diffScaleY = __toScaleY - _fromScaleY;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromScaleY;
                c = _diffScaleY;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->scaleY(temp);
                
                complete = false;
            } else {
                __target->scaleY(__toScaleY);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween scaleZ
        if(!isnan(__toScaleZ)) {
            if(!_delayComplete) {
                _fromScaleZ = __target->scaleZ();
                _diffScaleZ = __toScaleZ - _fromScaleZ;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromScaleZ;
                c = _diffScaleZ;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->scaleZ(temp);
                
                complete = false;
            } else {
                __target->scaleZ(__toScaleZ);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        
        //-------------------------------
        //ofxSTween rotation
        if(!isnan(__toRotation)) {
            if(!_delayComplete) {
                _fromRotation = __target->rotation();
                _diffRotation = __toRotation - _fromRotation;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromRotation;
                c = _diffRotation;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->rotation(temp);
                
                complete = false;
            } else {
                __target->rotation(__toRotation);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween rotationX
        if(!isnan(__toRotationX)) {
            if(!_delayComplete) {
                _fromRotationX = __target->rotationX();
                _diffRotationX = __toRotationX - _fromRotationX;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromRotationX;
                c = _diffRotationX;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->rotationX(temp);
                
                complete = false;
            } else {
                __target->rotationX(__toRotationX);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween rotationY
        if(!isnan(__toRotationY)) {
            if(!_delayComplete) {
                _fromRotationY = __target->rotationY();
                _diffRotationY = __toRotationY - _fromRotationY;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromRotationY;
                c = _diffRotationY;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->rotationY(temp);
                
                complete = false;
            } else {
                __target->rotationY(__toRotationY);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        //-------------------------------
        //ofxSTween rotationZ
        if(!isnan(__toRotationZ)) {
            if(!_delayComplete) {
                _fromRotationZ = __target->rotationZ();
                _diffRotationZ = __toRotationZ - _fromRotationZ;
            }
            
            if (_time <= _duration + _delay) {
                t = MAX(_time - (float)_delay, 0.f);
                b = _fromRotationZ;
                c = _diffRotationZ;
                d = _duration;
                p = 0;
                a = 0;
                
                temp = STweenSelector::getValueEase(t, b, c, d, _easeType, p, a);
                __target->rotationZ(temp);
                
                complete = false;
            } else {
                __target->rotationZ(__toRotationZ);
                complete = complete && true;
            }
        } else {
            complete = complete && true;
        }
        //-------------------------------
        
    //    complete = complete && bComplete;
    //    cout << "[STween2D::_updateProperty() complete = " << complete << ", " << bComplete << endl;
        
        return complete;
    }

    //--------------------------------------------------------------
    //
    void STween2D::_setProperty(const std::string& propertyName, float value) {
        if(propertyName == "overwrite") {
            __overwrite = value;
            return;
        }
        if(propertyName == "delay") {
            //-------------------------------
            //convert seconds to millis
            _delay = value * 1000.0f;
            _startTime = STweenCore::elapsedTimeMillis;
            //-------------------------------
            return;
        }
        if(propertyName == "ease") {
            _easeType = value;
            return;
        }
        
        if(propertyName == "x") {
            _fromX = __target->x();
            __toX = value;
            _diffX = __toX - _fromX;
            return;
        }
        if(propertyName == "y") {
            _fromY = __target->y();
            __toY = value;
            _diffY = __toY - _fromY;
            return;
        }
        if(propertyName == "z") {
            _fromZ = __target->z();
            __toZ = value;
            _diffZ = __toZ - _fromZ;
            return;
        }
        if(propertyName == "alpha") {
            _fromAlpha = __target->alpha();
            __toAlpha = value;
            _diffAlpha = __toAlpha - _fromAlpha;
            return;
        }
        if(propertyName == "width") {
            _fromWidth = __target->width();
            __toWidth = value;
            _diffWidth = __toWidth - _fromWidth;
            return;
        }
        if(propertyName == "height") {
            _fromHeight = __target->height();
            __toHeight = value;
            _diffHeight = __toHeight - _fromHeight;
            return;
        }
        if(propertyName == "scaleX") {
            _fromScaleX = __target->scaleX();
            __toScaleX = value;
            _diffScaleX = __toScaleX - _fromScaleX;
            return;
        }
        if(propertyName == "scaleY") {
            _fromScaleY = __target->scaleY();
            __toScaleY = value;
            _diffScaleY = __toScaleY - _fromScaleY;
            return;
        }
        if(propertyName == "scaleZ") {
            _fromScaleZ = __target->scaleZ();
            __toScaleZ = value;
            _diffScaleZ = __toScaleZ - _fromScaleZ;
            return;
        }
        if(propertyName == "rotation") {
            _fromRotation = __target->rotation();
            __toRotation = value;
            _diffRotation = __toRotation - _fromRotation;
            return;
        }
        if(propertyName == "rotationX") {
            _fromRotationX = __target->rotationX();
            __toRotationX = value;
            _diffRotationX = __toRotationX - _fromRotationX;
            return;
        }
        if(propertyName == "rotationY") {
            _fromRotationY = __target->rotationY();
            __toRotationY = value;
            _diffRotationY = __toRotationY - _fromRotationY;
            return;
        }
        if(propertyName == "rotationZ") {
            _fromRotationZ = __target->rotationZ();
            __toRotationZ = value;
            _diffRotationZ = __toRotationZ - _fromRotationZ;
            return;
        }
    }

}