//
//  TransformableNode.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#include "TransformableNode.h"

//--------------------------------------------------------------
TransformableNode::TransformableNode() {
    ofLog() << "[TransformableNode]TransformableNode()";
    
    _enabled = false;
    _mouseID = 0;
    
    _mouse.x = 0.0;
    _mouse.y = 0.0;
    _lastMouse.x = 0.0;
    _lastMouse.y = 0.0;
    _isInArea = false;
    
    _rotationX = 0.0;
    _rotationY = 0.0;
    _rotationZ = 0.0;
    
    ofAddListener(ofEvents().mouseDragged, this, &TransformableNode::_mouseDragEventHandler, OF_EVENT_ORDER_APP);
    ofAddListener(ofEvents().mousePressed, this, &TransformableNode::_mouseDownEventHandler, OF_EVENT_ORDER_APP);
    ofAddListener(ofEvents().mouseReleased, this, &TransformableNode::_mouseUpEventHandler, OF_EVENT_ORDER_APP);
    ofAddListener(ofEvents().mouseScrolled, this, &TransformableNode::_mouseScrolledEventHandler, OF_EVENT_ORDER_APP);
}

//--------------------------------------------------------------
TransformableNode::~TransformableNode() {
    ofLog() << "[TransformableNode]~TransformableNode()";
    
    _enabled = false;
    _mouseID = 0;
    
    _mouse.x = 0.0;
    _mouse.y = 0.0;
    _lastMouse.x = 0.0;
    _lastMouse.y = 0.0;
    _isInArea = false;
    
    _rotationX = 0.0;
    _rotationY = 0.0;
    _rotationZ = 0.0;
    
    ofRemoveListener(ofEvents().mouseDragged, this, &TransformableNode::_mouseDragEventHandler, OF_EVENT_ORDER_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &TransformableNode::_mouseDownEventHandler, OF_EVENT_ORDER_APP);
    ofRemoveListener(ofEvents().mouseReleased, this, &TransformableNode::_mouseUpEventHandler, OF_EVENT_ORDER_APP);
    ofRemoveListener(ofEvents().mouseScrolled, this, &TransformableNode::_mouseScrolledEventHandler, OF_EVENT_ORDER_APP);
}

//--------------------------------------------------------------
// SETUP / UPDATE / DRAW
//--------------------------------------------------------------

//--------------------------------------------------------------
void TransformableNode::begin() {
    //    ofPushMatrix();
    
    _scaleNode.transformGL();
    _rotationNode.transformGL();
    _positionNode.transformGL();
}

//--------------------------------------------------------------
void TransformableNode::end() {
    _positionNode.restoreTransformGL();
    _rotationNode.restoreTransformGL();
    _scaleNode.restoreTransformGL();
    
    //    ofPopMatrix();
}

//--------------------------------------------------------------
void TransformableNode::draw() {
    _rotationNode.transformGL();
    
    //--------------------------------------
    //X軸
    ofPushMatrix();
    ofRotateX(90);
    ofPushStyle();
    ofSetCircleResolution(64);
    ofSetColor(255, 155, 155, 150);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(0, 0, 0, 35);
    ofSetLineWidth(1);
    ofPopStyle();
    ofPopMatrix();
    
    //Y軸
    ofPushMatrix();
    ofRotateY(90);
    ofPushStyle();
    ofSetCircleResolution(64);
    ofSetColor(155, 255, 155, 150);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(0, 0, 0, 35);
    ofSetLineWidth(1);
    ofPopStyle();
    ofPopMatrix();
    
    //Z軸
    ofPushMatrix();
    ofPushStyle();
    ofSetCircleResolution(64);
    ofSetColor(155, 155, 255, 150);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(0, 0, 0, 35);
    ofSetLineWidth(1);
    ofPopStyle();
    ofPopMatrix();
    //--------------------------------------
    
    _rotationNode.restoreTransformGL();
}

//--------------------------------------------------------------
// SETTER / GETTER
//--------------------------------------------------------------

//--------------------------------------------------------------
float TransformableNode::rotationX() { return _rotationX; }
void TransformableNode::rotationX(float value) {
    float diff = value - _rotationX;
    _rotationX = value;
    
    _xRot.makeRotate(diff, 1.0, 0.0, 0.0);
    _qRot *= _xRot;
    //    setOrientation(_qRot);
    
    _rotationNode.setOrientation(_qRot);
}

//--------------------------------------------------------------
float TransformableNode::rotationY() { return _rotationY; }
void TransformableNode::rotationY(float value) {
    float diff = value - _rotationY;
    _rotationY = value;
    
    _yRot.makeRotate(diff, 0.0, 1.0, 0.0);
    _qRot *= _yRot;
    
    //    setOrientation(_qRot);
    _rotationNode.setOrientation(_qRot);
}

//--------------------------------------------------------------
float TransformableNode::rotationZ() { return _rotationZ; }
void TransformableNode::rotationZ(float value) {
    float diff = value - _rotationZ;
    _rotationZ = value;
    
    _zRot.makeRotate(diff, 0.0, 0.0, 1.0);
    _qRot *= _zRot;
    
    //    setOrientation(_qRot);
    _rotationNode.setOrientation(_qRot);
}

//--------------------------------------------------------------
void TransformableNode::resetRotation() {
    _rotationX = 0.0;
    _rotationY = 0.0;
    _rotationZ = 0.0;
    _qRot = ofQuaternion();
    
    //    setOrientation(_qRot);
    _rotationNode.setOrientation(_qRot);
}

//--------------------------------------------------------------
// PUBLIC METHOD
//--------------------------------------------------------------

//--------------------------------------------------------------
float TransformableNode::x() { return _positionNode.getPosition().x; }
void TransformableNode::x(float value) {
    ofVec3f position = _positionNode.getPosition();
    
    //    setPosition(value, position.y, position.z);
    _positionNode.setPosition(value, position.y, position.z);
}

//--------------------------------------------------------------
float TransformableNode::y() { return _positionNode.getPosition().y; }
void TransformableNode::y(float value) {
    ofVec3f position = _positionNode.getPosition();
    
    //    setPosition(position.x, value, position.z);
    _positionNode.setPosition(position.x, value, position.z);
}

//--------------------------------------------------------------
float TransformableNode::z() { return _positionNode.getPosition().z; }
void TransformableNode::z(float value) {
    ofVec3f position = _positionNode.getPosition();
    
    //    setPosition(position.x, position.y, value);
    _positionNode.setPosition(position.x, position.y, value);
}

//--------------------------------------------------------------
float TransformableNode::scaleX() { return _scaleNode.getScale().x; }
void TransformableNode::scaleX(float value) {
    ofVec3f scale = _scaleNode.getScale();
    
    //    setScale(value, scale.y, scale.z);
    _scaleNode.setScale(value, scale.y, scale.z);
}

//--------------------------------------------------------------
float TransformableNode::scaleY() { return _scaleNode.getScale().y; }
void TransformableNode::scaleY(float value) {
    ofVec3f scale = _scaleNode.getScale();
    
    //    setScale(scale.x, value, scale.z);
    _scaleNode.setScale(scale.x, value, scale.z);
}

//--------------------------------------------------------------
float TransformableNode::scaleZ() { return _scaleNode.getScale().z; }
void TransformableNode::scaleZ(float value) {
    ofVec3f scale = _scaleNode.getScale();
    
    //    setScale(scale.x, scale.y, value);
    _scaleNode.setScale(scale.x, scale.y, value);
}

//--------------------------------------------------------------
// PROTECTED / PRIVATE METHOD
//--------------------------------------------------------------

//--------------------------------------------------------------
// EVENT HANDLER
//--------------------------------------------------------------

//--------------------------------------------------------------
void TransformableNode::_mouseMoveEventHandler(ofMouseEventArgs& event) {
    //    ofLog() << "[TransformableNode]_mouseMoveEventHandler()";
    if(_mouseID != 0) return;
    if(!_enabled) return;
    
}

//--------------------------------------------------------------
void TransformableNode::_mouseDragEventHandler(ofMouseEventArgs& event) {
    //    ofLog() << "[TransformableNode]_mouseDragEventHandler()";
    if(_mouseID != 0) return;
    if(!_enabled) return;
    
    _mouse.x = event.x;
    _mouse.y = event.y;
    
    float dx = _mouse.x - _lastMouse.x;
    float dy = _mouse.y - _lastMouse.y;
    
    //Rotation
    if(_dragMode == 0) {
        float spinX = dx * 0.1;
        float spinY = dy * 0.1;
        
        ofVec2f center = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
        
        float distanceX = center.x - _mouse.x;
        float distanceY = center.y - _mouse.y;
        
        float distance = center.distance(_mouse);
        float n = 225;
        
        if(distance < n || _isInArea) {
            //            ofLog() << "spinX = " << spinX;
            //            ofLog() << "spinY = " << spinY;
            //X軸
            rotationX(rotationX() + spinY);
            //Y軸
            rotationY(rotationY() + spinX);
        } else {
            //Z軸
            if(distanceY >= n) rotationZ(rotationZ() - spinX);
            if(distanceY <= -n) rotationZ(rotationZ() + spinX);
            if(distanceX >= n) rotationZ(rotationZ() + spinY);
            if(distanceX <= -n) rotationZ(rotationZ() - spinY);
        }
    }
    //Translate
    else if(_dragMode == 1) {
        x(x() + dx * 0.001);
        y(y() - dy * 0.001);
    }
    
    _lastMouse = _mouse;
}

//--------------------------------------------------------------
void TransformableNode::_mouseDownEventHandler(ofMouseEventArgs& event) {
    //    ofLog() << "[TransformableNode]_mouseDownEventHandler()";
    if(!_enabled) return;
    _mouseID = event.button;
    
    _mouse.x = event.x;
    _mouse.y = event.y;
    _lastMouse = _mouse;
    
    ofVec2f center = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
    float distance = center.distance(_mouse);
    float n = 225;
    
    if(distance < n) _isInArea = true;
}

//--------------------------------------------------------------
void TransformableNode::_mouseUpEventHandler(ofMouseEventArgs& event) {
    //    ofLog() << "[TransformableNode]_mouseUpEventHandler()";
    if(!_enabled) return;
    
    _isInArea = false;
}

//--------------------------------------------------------------
void TransformableNode::_mouseScrolledEventHandler(ofMouseEventArgs& event) {
    //    ofLog() << "[TransformableNode]_mouseScrolledEventHandler()";
    if(!_enabled) return;
    
    float scrollY = event.scrollY * 0.1;
    
    ofVec3f scale = _scaleNode.getScale();
    _scaleNode.setScale(
                        scale.x - scrollY,
                        scale.y - scrollY,
                        scale.z - scrollY
                        );
}
