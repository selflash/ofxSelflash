#pragma once

#include "ofMain.h"

class TransformableNode {
public:
    bool flg = false;
    
protected:
    
private:
    int _mouseID = 0;
    ofRectangle _viewport = ofGetCurrentViewport();
    ofVec2f _mouse;
    ofVec2f _lastMouse;
    bool _isInArea = false;
    string _mode = "";
    float n = 260;
    bool _isDragOn = false;
    
    ofCamera* _camera = NULL;
    
    ofVec3f _anchorPoint;
    
    ofVec3f _position;
    ofVec3f _rotation;
    ofVec3f _scale = ofVec3f::one();
    
    ofQuaternion _tempRot;
    ofMatrix4x4 _transformMatrix;
    //        ofMatrix4x4 _transformMatrix1;
    ofMatrix4x4 _transformMatrix2;
    
    int _dragMode = 0;
    
    bool _enabled = false;
    bool _transrationEnabled = true;
    //        bool _rotationEnabled = true;
    bool _rotationXEnabled = true;
    bool _rotationYEnabled = true;
    bool _rotationZEnabled = true;
    bool _scaleEnabled = true;
    
public:
    TransformableNode();
    virtual ~TransformableNode();
    
    void begin(bool transration = true, bool rotation = true, bool scale = true);
    void end();
    
    void draw(float circleScale = 1.0);
    
    ofRectangle& viewport() { return _viewport; }
    void viewport(ofRectangle value) { _viewport = value; }
    
    ofCamera& camera() { return *_camera; }
    void camera(ofCamera* value) { _camera = value; }
    
    bool enabled() { return _enabled; }
    void enabled(bool value) {
        _enabled = value;
        
        if(_enabled == false) {
            _isDragOn = false;
            _isInArea = false;
            
            _mode = "";
        }
    }
    
    bool transrationEnabled() { return _transrationEnabled; }
    void transrationEnabled(bool value) { _transrationEnabled = value; }
    
    bool rotationEnabled() { return (_rotationXEnabled && _rotationYEnabled && _rotationZEnabled); }
    void rotationEnabled(bool value) { _rotationXEnabled = _rotationYEnabled = _rotationZEnabled = value; }
    
    bool rotationXEnabled() { return _rotationXEnabled; }
    void rotationXEnabled(bool value) { _rotationXEnabled = value; }
    
    bool rotationYEnabled() { return _rotationYEnabled; }
    void rotationYEnabled(bool value) { _rotationYEnabled = value; }
    
    bool rotationZEnabled() { return _rotationZEnabled; }
    void rotationZEnabled(bool value) { _rotationZEnabled = value; }
    
    bool scaleEnabled() { return _scaleEnabled; }
    void scaleEnabled(bool value) { _scaleEnabled = value; }
    
    int dragMode() { return _dragMode; }
    void dragMode(int value) { _dragMode = value; }
    
    float x();
    void x(float value);
    
    float y();
    void y(float value);
    
    float z();
    void z(float value);
    
    ofVec3f position() { return _position; }
    ofVec3f rotation() { return _rotation; }
    
    //        void translate(float x, float y, ofCamera& camera);
    
    float scaleX();
    void scaleX(float value);
    
    float scaleY();
    void scaleY(float value);
    
    float scaleZ();
    void scaleZ(float value);
    
    float rotationX();
    void rotationX(float value);
    
    float rotationY();
    void rotationY(float value);
    
    float rotationZ();
    void rotationZ(float value);
    
    inline ofVec3f anchorPoint() { return _anchorPoint; }
    inline void anchorPoint(ofVec3f value) { _anchorPoint = value; }
    
    void resetTransform();
    void resetRotation();
    
    inline ofMatrix4x4 getTransformMatrix() { return _transformMatrix; }
    inline void setTransformMatrix(ofMatrix4x4 value) { _transformMatrix = value; }
    
    inline ofMatrix4x4 localToGlobalTransformMatrix() {
        return _transformMatrix;
    }
    inline ofMatrix4x4 globalToLocalTransformMatrix() {
        return _transformMatrix.getInverse();
    }
    
    
protected:
    
private:
    void _mouseMoveEventHandler(ofMouseEventArgs& event);
    void _mouseDragEventHandler(ofMouseEventArgs& event);
    void _mouseDownEventHandler(ofMouseEventArgs& event);
    void _mouseUpEventHandler(ofMouseEventArgs& event);
    void _mouseScrolledEventHandler(ofMouseEventArgs& event);
};
