#pragma once

#include "ofMain.h"

class TransformableNode {
public:
    
protected:
    
private:
    bool _enabled = false;
    int _mouseID = false;
    ofVec2f _mouse;
    ofVec2f _lastMouse;
    bool _isInArea = false;
    
    float _rotationX = 0.0;
    float _rotationY = 0.0;
    float _rotationZ = 0.0;
    ofQuaternion _xRot, _yRot, _zRot;
    ofQuaternion _qRot;
    
    ofNode _positionNode;
    ofNode _rotationNode;
    ofNode _scaleNode;
    
    int _dragMode = 0;
    
public:
    TransformableNode();
    virtual ~TransformableNode();
    
    void begin();
    void end();
    void draw();
    
    bool enabled() { return _enabled; }
    void enabled(bool value) { _enabled = value; }
    
    int dragMode() { return _dragMode; }
    void dragMode(int value) { _dragMode = value; }
    
    float x();
    void x(float value);
    
    float y();
    void y(float value);
    
    float z();
    void z(float value);
    
    ofVec3f position() { return _positionNode.getPosition(); }
    
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
    
    void resetRotation();
    
    inline ofMatrix4x4 localToGlobalTransformMatrix() {
        ofMatrix4x4 m1 = _positionNode.getLocalTransformMatrix();
        ofMatrix4x4 m2 = _rotationNode.getLocalTransformMatrix();
        ofMatrix4x4 m3 = _scaleNode.getLocalTransformMatrix();
        
        return m1 * m2 * m3;
    }
    inline ofMatrix4x4 globalToLocalTransformMatrix() {
        ofMatrix4x4 m1 = ofMatrix4x4::getInverseOf(_positionNode.getLocalTransformMatrix());
        ofMatrix4x4 m2 = ofMatrix4x4::getInverseOf(_rotationNode.getLocalTransformMatrix());
        ofMatrix4x4 m3 = ofMatrix4x4::getInverseOf(_scaleNode.getLocalTransformMatrix());
        
        return m3 * m2 * m1;
    }
    
    
protected:
    
private:
    void _mouseMoveEventHandler(ofMouseEventArgs& event);
    void _mouseDragEventHandler(ofMouseEventArgs& event);
    void _mouseDownEventHandler(ofMouseEventArgs& event);
    void _mouseUpEventHandler(ofMouseEventArgs& event);
    void _mouseScrolledEventHandler(ofMouseEventArgs& event);
};
