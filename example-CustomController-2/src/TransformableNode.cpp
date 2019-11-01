#include "TransformableNode.h"

//--------------------------------------------------------------
TransformableNode::TransformableNode() {
    cout << "[TransformableNode]TransformableNode()" << endl;
    
    ofAddListener(ofEvents().mouseDragged, this, &TransformableNode::_mouseDragEventHandler, OF_EVENT_ORDER_APP);
    ofAddListener(ofEvents().mousePressed, this, &TransformableNode::_mouseDownEventHandler, OF_EVENT_ORDER_APP);
    ofAddListener(ofEvents().mouseReleased, this, &TransformableNode::_mouseUpEventHandler, OF_EVENT_ORDER_APP);
    ofAddListener(ofEvents().mouseScrolled, this, &TransformableNode::_mouseScrolledEventHandler, OF_EVENT_ORDER_APP);
}

//--------------------------------------------------------------
TransformableNode::~TransformableNode() {
    cout << "[TransformableNode]~TransformableNode()" << endl;
    
    ofRemoveListener(ofEvents().mouseDragged, this, &TransformableNode::_mouseDragEventHandler, OF_EVENT_ORDER_APP);
    ofRemoveListener(ofEvents().mousePressed, this, &TransformableNode::_mouseDownEventHandler, OF_EVENT_ORDER_APP);
    ofRemoveListener(ofEvents().mouseReleased, this, &TransformableNode::_mouseUpEventHandler, OF_EVENT_ORDER_APP);
    ofRemoveListener(ofEvents().mouseScrolled, this, &TransformableNode::_mouseScrolledEventHandler, OF_EVENT_ORDER_APP);
}

//--------------------------------------------------------------
// SETUP / UPDATE / DRAW
//--------------------------------------------------------------

//--------------------------------------------------------------
void TransformableNode::begin(bool transration, bool rotation, bool scale) {
    //    glPushMatrix();
    ofPushMatrix();
    
    if(transration && rotation && scale) {
        //        glMultMatrixf(_transformMatrix.getPtr());
        ofMultMatrix(_transformMatrix);
    } else {
        //        if(transration && !rotation && !scale) { glMultMatrixf(_translationMatrix.getPtr()); }
        //        if(!transration && rotation && !scale) { glMultMatrixf(_rotationMatrix.getPtr()); }
        //        if(!transration && !rotation && scale) { glMultMatrixf(_scaleMatrix.getPtr()); }
        //
        //        if(transration && rotation && !scale) {
        //            ofMatrix4x4 m = _translationMatrix * _rotationMatrix;
        //            glMultMatrixf(m.getPtr());
        //        }
        //        if(transration && !rotation && scale) {
        //            ofMatrix4x4 m = _translationMatrix * _scaleMatrix;
        //            glMultMatrixf(m.getPtr());
        //        }
        //        if(!transration && rotation && scale) {
        //            ofMatrix4x4 m = _rotationMatrix * _scaleMatrix;
        //            glMultMatrixf(m.getPtr());
        //        }
        
        if(transration && !rotation && !scale)
        {
            ofTranslate(_transformMatrix.getTranslation());
        }
        else if(!transration && rotation && !scale)
        {
            ofMultMatrix(ofMatrix4x4(_transformMatrix.getRotate()));
        }
        else if(!transration && !rotation && scale)
        {
            ofScale(_transformMatrix.getScale());
        } else {
            if(transration && rotation && !scale) {
                ofMatrix4x4 matrix = ofMatrix4x4::newTranslationMatrix(_transformMatrix.getTranslation()) * ofMatrix4x4::newRotationMatrix(_transformMatrix.getRotate());
                glMultMatrixf(matrix.getPtr());
            }
            if(transration && !rotation && scale) {
                ofMatrix4x4 matrix = ofMatrix4x4::newTranslationMatrix(_transformMatrix.getTranslation()) * ofMatrix4x4::newScaleMatrix(_transformMatrix.getScale());
                glMultMatrixf(matrix.getPtr());
            }
            if(!transration && rotation && scale) {
                ofMatrix4x4 matrix = ofMatrix4x4::newRotationMatrix(_transformMatrix.getRotate()) * ofMatrix4x4::newScaleMatrix(_transformMatrix.getScale());
                glMultMatrixf(matrix.getPtr());
            }
        }
    }
}
//--------------------------------------------------------------
void TransformableNode::end() {
    //    glPopMatrix();
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void TransformableNode::draw(float circleScale) {
    //    _rotationNode.transformGL();
    
    //--------------------------------------
    // save off current state of blend enabled
    GLboolean blendEnabled;
    glGetBooleanv(GL_BLEND, &blendEnabled);
    // save off current state of src / dst blend functions
    GLint blendSrc; GLint blendDst;
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrc);
    glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDst);
    ofEnableAlphaBlending();
    
    GLboolean preLighting = glIsEnabled(GL_LIGHTING);
    GLboolean preDepthTest = glIsEnabled(GL_DEPTH_TEST);
    GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
    GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
    
    ofDisableLighting();
    glDisable(GL_DEPTH_TEST);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    //--------------------------------------
    
//    glPushMatrix();
//    glMultMatrixf(_rotationMatrix.getPtr());
    
    ofQuaternion quaternion = _transformMatrix.getRotate();
    ofMatrix4x4 rotationMatrix = ofMatrix4x4(quaternion);
    
    ofPushMatrix();
    ofMultMatrix(rotationMatrix);
    
    //--------------------------------------
    //X軸
    ofPushMatrix();
    ofRotateXDeg(90);
    ofPushStyle();
    ofSetCircleResolution(64);
    ofSetColor(255, 155, 155, 120);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(0, 0, 0, 0.5 * circleScale);
    ofSetLineWidth(1);
    ofPopStyle();
    ofPopMatrix();
    
    //Y軸
    ofPushMatrix();
    ofRotateYDeg(90);
    ofPushStyle();
    ofSetCircleResolution(64);
    ofSetColor(155, 255, 155, 120);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(0, 0, 0, 0.5 * circleScale);
    ofSetLineWidth(1);
    ofPopStyle();
    ofPopMatrix();
    
    //Z軸
    ofPushMatrix();
    ofPushStyle();
    ofSetCircleResolution(64);
    ofSetColor(155, 155, 255, 120);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(0, 0, 0, 0.5 * circleScale);
    ofSetLineWidth(1);
    ofPopStyle();
    ofPopMatrix();
    //--------------------------------------
    
//    _rotationNode.restoreTransformGL();
//    glPopMatrix();
    ofPopMatrix();
    
    //--------------------------------------
    if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
    if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
    if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
    if(preLighting == GL_TRUE) { ofEnableLighting(); } else { ofDisableLighting(); }
    
    // restore saved state of blend enabled and blend functions
    if (blendEnabled) { glEnable(GL_BLEND); } else { glDisable(GL_BLEND); }
    glBlendFunc(blendSrc, blendDst);
    //--------------------------------------
}

//--------------------------------------------------------------
// PUBLIC METHOD
//--------------------------------------------------------------

//--------------------------------------------------------------
// SETTER / GETTER
//--------------------------------------------------------------

//--------------------------------------------------------------
float TransformableNode::x() { return _position.x; }
void TransformableNode::x(float value) {
    float diff = value - _position.x;
    _position.x = value;
    
    //    ofMatrix4x4 m;
    //    m.setTranslation(diff, 0.0, 0.0);
    //
    //    _translationMatrix = _translationMatrix * m;
    //
    //    _transformMatrix = _transformMatrix * m;
    _transformMatrix.translate(diff, 0, 0);
    
    if(flg) {
        ofMatrix4x4 m;
        m.translate(diff, 0.0, 0.0);
        //        m = m * _transformMatrix1.getInverse();
        
        _transformMatrix2 = _transformMatrix2 * m;
    }
}

//--------------------------------------------------------------
float TransformableNode::y() { return _position.y; }
void TransformableNode::y(float value) {
    float diff = value - _position.y;
    _position.y = value;
    
    //    ofMatrix4x4 m;
    //    m.setTranslation(0.0, diff, 0.0);
    //
    //    _translationMatrix = _translationMatrix * m;
    //
    //    _transformMatrix = _transformMatrix * m;
    _transformMatrix.translate(0, diff, 0);
    
    if(flg) {
        ofMatrix4x4 m;
        m.translate(0.0, diff, 0.0);
        //        m = m * _transformMatrix1.getInverse();
        
        _transformMatrix2 = _transformMatrix2 * m;
    }
}

//--------------------------------------------------------------
float TransformableNode::z() { return _position.z; }
void TransformableNode::z(float value) {
    float diff = value - _position.z;
    _position.z = value;
    
    //    ofMatrix4x4 m;
    //    m.setTranslation(0.0, 0.0, diff);
    //
    //    _translationMatrix = _translationMatrix * m;
    //
    //    _transformMatrix = _transformMatrix * m;
    _transformMatrix.translate(0, 0, diff);
    
    if(flg) {
        ofMatrix4x4 m;
        m.translate(0, 0, diff);
        //        m = m * _transformMatrix1.getInverse();
        
        _transformMatrix2 = _transformMatrix2 * m;
    }
}

//--------------------------------------------------------------
float TransformableNode::scaleX() { return _scale.x; }
void TransformableNode::scaleX(float value) {
    float diff = value - _scale.x;
    _scale.x = value;
    
    //    ofMatrix4x4 m;
    //    m.scale(1.0 + diff, 1.0, 1.0);
    //
    //    _scaleMatrix = _scaleMatrix * m;
    //    _transformMatrix = _transformMatrix * m;
    //    //    _transformNode.setTransformMatrix(_transformMatrix);
    
    _transformMatrix.scale(diff, 0, 0);
    
    if(flg) _transformMatrix2.scale(diff, 0, 0);
}

//--------------------------------------------------------------
float TransformableNode::scaleY() { return _scale.y; }
void TransformableNode::scaleY(float value) {
    float diff = value - _scale.y;
    _scale.y = value;
    
    //    ofMatrix4x4 m;
    //    m.scale(1.0, 1.0 + diff, 1.0);
    //
    //    _scaleMatrix = _scaleMatrix * m;
    //    _transformMatrix = _transformMatrix * m;
    //    //    _transformNode.setTransformMatrix(_transformMatrix);
    
    _transformMatrix.scale(0, diff, 0);
    
    if(flg) _transformMatrix2.scale(0, diff, 0);
}

//--------------------------------------------------------------
float TransformableNode::scaleZ() { return _scale.z; }
void TransformableNode::scaleZ(float value) {
    float diff = value - _scale.z;
    _scale.z = value;
    
    //    ofMatrix4x4 m;
    //    m.scale(1.0, 1.0, 1.0 + diff);
    //
    //    _scaleMatrix = _scaleMatrix * m;
    //    _transformMatrix = _transformMatrix * m;
    //    //    _transformNode.setTransformMatrix(_transformMatrix);
    
    _transformMatrix.scale(0, 0, diff);
    
    if(flg) _transformMatrix2.scale(0, 0, diff);
}

//--------------------------------------------------------------
float TransformableNode::rotationX() { return _rotation.x; }
void TransformableNode::rotationX(float value) {
    float diff = value - _rotation.x;
    _rotation.x = value;
    
    _tempRot.makeRotate(diff, 1.0, 0.0, 0.0);
    //    _qRot *= _tempRot;
    //    //    _rotationNode.setOrientation(_qRot);
    //
    //    ofMatrix4x4 m;
    //    m.translate(-_anchorPoint);
    //    m.rotate(_tempRot);
    //    m.translate(_anchorPoint);
    //
    //    _rotationMatrix = _rotationMatrix * m;
    //    _transformMatrix = _transformMatrix * m;
    //    _transformNode.setTransformMatrix(_transformMatrix);
    
    _transformMatrix.translate(-_anchorPoint);
    _transformMatrix.rotate(_tempRot);
    _transformMatrix.translate(_anchorPoint);
    
    //    if(flg)  {
    ////        _transformMatrix2.translate(-_anchorPoint);
    //        _transformMatrix2.rotate(_tempRot);
    ////        _transformMatrix2.translate(_anchorPoint);
    //    }
    if(flg) {
        ofMatrix4x4 m;
        m.translate(-_anchorPoint);
        m.rotate(_tempRot);
        m.translate(_anchorPoint);
        //        m = m * _transformMatrix1.getInverse();
        
        _transformMatrix2 = _transformMatrix2 * m;
    }
}

//--------------------------------------------------------------
float TransformableNode::rotationY() { return _rotation.y; }
void TransformableNode::rotationY(float value) {
    float diff = value - _rotation.y;
    _rotation.y = value;
    
    _tempRot.makeRotate(diff, 0.0, 1.0, 0.0);
    //    _qRot *= _tempRot;
    //    //    _rotationNode.setOrientation(_qRot);
    //
    //    ofMatrix4x4 m;
    //    m.translate(-_anchorPoint);
    //    m.rotate(_tempRot);
    //    m.translate(_anchorPoint);
    //
    //    _rotationMatrix = _rotationMatrix * m;
    //    _transformMatrix = _transformMatrix * m;
    //    //    _transformNode.setTransformMatrix(_transformMatrix);
    
    _transformMatrix.translate(-_anchorPoint);
    _transformMatrix.rotate(_tempRot);
    _transformMatrix.translate(_anchorPoint);
    
    //    if(flg)  {
    ////        _transformMatrix2.translate(-_anchorPoint);
    //        _transformMatrix2.rotate(_tempRot);
    ////        _transformMatrix2.translate(_anchorPoint);
    //    }
    if(flg) {
        ofMatrix4x4 m;
        m.translate(-_anchorPoint);
        m.rotate(_tempRot);
        m.translate(_anchorPoint);
        //        m = m * _transformMatrix1.getInverse();
        
        _transformMatrix2 = _transformMatrix2 * m;
    }
}

//--------------------------------------------------------------
float TransformableNode::rotationZ() { return _rotation.z; }
void TransformableNode::rotationZ(float value) {
    float diff = value - _rotation.z;
    _rotation.z = value;
    
    _tempRot.makeRotate(diff, 0.0, 0.0, 1.0);
    //    _qRot *= _tempRot;
    //    //    _rotationNode.setOrientation(_qRot);
    //
    //    ofMatrix4x4 m;
    //    m.translate(-_anchorPoint);
    //    m.rotate(_tempRot);
    //    m.translate(_anchorPoint);
    //
    //    _rotationMatrix = _rotationMatrix * m;
    //    _transformMatrix = _transformMatrix * m;
    //    //    _transformNode.setTransformMatrix(_transformMatrix);
    
    _transformMatrix.translate(-_anchorPoint);
    _transformMatrix.rotate(_tempRot);
    _transformMatrix.translate(_anchorPoint);
    
    //    if(flg)  {
    ////        _transformMatrix2.translate(-_anchorPoint);
    //        _transformMatrix2.rotate(_tempRot);
    ////        _transformMatrix2.translate(_anchorPoint);
    //    }
    if(flg) {
        ofMatrix4x4 m;
        m.translate(-_anchorPoint);
        m.rotate(_tempRot);
        m.translate(_anchorPoint);
        //        m = m * _transformMatrix1.getInverse();
        
        _transformMatrix2 = _transformMatrix2 * m;
    }
    
}

//--------------------------------------------------------------
void TransformableNode::resetTransform() {
    _position.x = 0.0;
    _position.y = 0.0;
    _position.z = 0.0;
    //    _translationMatrix.makeIdentityMatrix();
    
    _rotation.x = 0.0;
    _rotation.y = 0.0;
    _rotation.z = 0.0;
    //    _qRot = ofQuaternion();
    //    _rotationMatrix.makeIdentityMatrix();
    
    //    _scaleMatrix.makeIdentityMatrix();
    
    _transformMatrix.makeIdentityMatrix();
}

//--------------------------------------------------------------
void TransformableNode::resetRotation() {
    //    ofVec3f translation = _transformMatrix.getTranslation();
    
    //    rotationX(0.0);
    //    rotationY(0.0);
    //    rotationZ(0.0);
    
    _rotation.x = 0.0;
    _rotation.y = 0.0;
    _rotation.z = 0.0;
    _transformMatrix.makeIdentityMatrix();
    
    _transformMatrix.translate(_position.x, 0, 0);
    _transformMatrix.translate(0, _position.y, 0);
    _transformMatrix.translate(0, 0, _position.z);
    
    //    _qRot = ofQuaternion();
    
    //        _rotationMatrix.makeIdentityMatrix();
    //    _rotationNode.setOrientation(_qRot);
}

//void TransformableNode::translate(float x, float y, ofCamera& camera) {
//    cout << "[TransformableNode]translate(" << x << ", " << y << ")" << endl;
//
//    float _nearDepth;
//    float _farDepth;
//    ofRectangle _nearScreen;
//    ofRectangle _farScreen;
//
//    //--------------------------------------
//    ofVec3f nearLeftTop = camera.screenToWorld(ofVec3f(0, 0, 0.0));
//    ofVec3f nearRightBottom = camera.screenToWorld(ofVec3f(_viewport.width, _viewport.height, 0.0));
//    _nearScreen.set(nearLeftTop.x, nearLeftTop.y, nearRightBottom.x, nearRightBottom.y);
//
//    ofVec3f farLeftTop = camera.screenToWorld(ofVec3f(0, 0, 1.0));
//    ofVec3f farRightBottom = camera.screenToWorld(ofVec3f(_viewport.width, _viewport.height, 1.0));
//    _farScreen.set(farLeftTop.x, farLeftTop.y, farRightBottom.x, farRightBottom.y);
//
//    ofVec3f rayStart = camera.screenToWorld(ofVec3f(_viewport.width / 2, _viewport.height / 2, 0.0));
//    _nearDepth = rayStart.z;
//    ofVec3f rayEnd = camera.screenToWorld(ofVec3f(_viewport.width / 2, _viewport.height / 2, 1.0));
//    _farDepth = rayEnd.z;
//    //--------------------------------------
//
//
//    //スクリーンの幅
//    ofRectangle screen = ofRectangle(0.0, 0.0, _viewport.width, _viewport.height);
//    //--------------------------------------
//
////    ofMatrix4x4 localToGlobal = _positionNode.getLocalTransformMatrix();
////    ofMatrix4x4 globalToLocal = ofMatrix4x4::getInverseOf(_positionNode.getLocalTransformMatrix());
//
//    //--------------------------------------
//    ofVec3f temp = _positionNode.getPosition();
//    //グローバル空間上の座標に変換する
////    temp = temp * localToGlobal;
//
//    float targetDepth = temp.z;
//    //左上の値で計算する
//    float n1 = ofMap(targetDepth, _nearDepth, _farDepth,  _nearScreen.x, _farScreen.x);
//    float n2 = ofMap(targetDepth, _nearDepth, _farDepth,  _nearScreen.y, _farScreen.y);
//    temp.x = ofMap(x, screen.x, screen.width, n1, -n1);
//    temp.y = ofMap(y, screen.y, screen.height, n2, -n2);
//    temp.z = targetDepth;
//
//    //ローカル空間上の座標に変換する
////    temp = temp * globalToLocal;
//
//    ofVec3f position = _positionNode.getPosition();
////    ofVec3f diff = temp - position;
//    _positionNode.setPosition(
//                              temp.x,
//                              temp.y,
//                              temp.z
//                              );
//
////    this->x(temp.x);
////    this->y(temp.y);
////    this->z(temp.z);
//    //--------------------------------------
//}

//--------------------------------------------------------------
// PROTECTED / PRIVATE METHOD
//--------------------------------------------------------------

//--------------------------------------------------------------
// EVENT HANDLER
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void TransformableNode::_mouseMoveEventHandler(ofMouseEventArgs& event) {
    //    cout << "[TransformableNode]_mouseMoveEventHandler() << endl";
    if(_mouseID != 0) return;
    if(!_enabled) return;
    
}

//--------------------------------------------------------------
//
void TransformableNode::_mouseDragEventHandler(ofMouseEventArgs& event) {
    //    cout << "[TransformableNode]_mouseDragEventHandler() << endl";
    if(_mouseID != 0) return;
    if(!_enabled) return;
    if(!_rotationXEnabled && !_rotationYEnabled && !_rotationZEnabled) return;
    
    if(!_isDragOn) return;
    //    if(event.x < _viewport.x) return;
    //    if(_viewport.x + _viewport.width < event.x) return;
    //    if(event.y < _viewport.y) return;
    //    if(_viewport.y + _viewport.height < event.y) return;
    
    //    cout << "HOGE" << endl;
    
    _mouse.x = event.x;
    _mouse.y = event.y;
    
    float dx = _mouse.x - _lastMouse.x;
    float dy = _mouse.y - _lastMouse.y;
    
    //Rotation
    if(_dragMode == 0) {
        float spinX = dx * 0.3;
        float spinY = dy * 0.3;
        
        ofVec2f center = ofVec2f(
                                 _viewport.x + _viewport.width / 2.0,
                                 _viewport.y + _viewport.height / 2.0
                                 );
        
        float distanceX = center.x - _mouse.x;
        float distanceY = center.y - _mouse.y;
        
        float distance = center.distance(_mouse);
        //        float n = 220;
        //        float n = 330;
        
        //        if(distance < n && _isInArea) {
        if(_isInArea) {
            //            cout << "spinX = " << spinX << endl;
            //            cout << "spinY = " << spinY << endl;
            
            if(_camera) {
//                if(_mode == "1") {
//                    ofVec3f rotation = ofVec3f(spinY, spinX, 0) * _camera->getLocalTransformMatrix().getRotate();
//
//                    //X軸
//                    if(_rotationXEnabled) rotationX(rotationX() + rotation.x);
//                } else if(_mode == "2") {
//                    ofVec3f rotation = ofVec3f(spinY, spinX, 0) * _camera->getLocalTransformMatrix().getRotate();
//
//                    //Y軸
//                    if(_rotationYEnabled) rotationY(rotationY() + rotation.y);
//                } else {
//                    ofVec3f rotation = ofVec3f(spinY, spinX, 0) * _camera->getLocalTransformMatrix().getRotate();
//
//                    //X軸
//                    if(_rotationXEnabled) rotationX(rotationX() + rotation.x);
//                    //Y軸
//                    if(_rotationYEnabled) rotationY(rotationY() + rotation.y);
//                    //Z軸
//                    if(_rotationZEnabled) rotationZ(rotationZ() + rotation.z);
//                }
            } else {
                if(_mode == "1") {
                    //X軸
                    if(_rotationXEnabled) rotationX(rotationX() + spinY);
                } else if(_mode == "2") {
                    //Y軸
                    if(_rotationYEnabled) rotationY(rotationY() + spinX);
                } else {
                    //X軸
                    if(_rotationXEnabled) rotationX(rotationX() + spinY);
                    //Y軸
                    if(_rotationYEnabled) rotationY(rotationY() + spinX);
                }
            }
        } else {
            if(_camera) {
                ofVec3f rotation;
//                if(distanceY >= n) {
//                    rotation = ofVec3f(0, 0, -spinX) * _camera->getLocalTransformMatrix().getRotate();
//                }
//                if(distanceY <= -n) {
//                    rotation = ofVec3f(0, 0, spinX) * _camera->getLocalTransformMatrix().getRotate();
//                }
//                if(distanceX >= n) {
//                    rotation = ofVec3f(0, 0, spinY) * _camera->getLocalTransformMatrix().getRotate();
//                }
//                if(distanceX <= -n) {
//                    rotation = ofVec3f(0, 0, -spinY) * _camera->getLocalTransformMatrix().getRotate();
//                }
//                //X軸
//                if(_rotationXEnabled) rotationX(rotationX() + rotation.x);
//                //Y軸
//                if(_rotationYEnabled) rotationY(rotationY() + rotation.y);
//                //Z軸
//                if(_rotationZEnabled) rotationZ(rotationZ() + rotation.z);
            } else {
                //Z軸
                //                if(distanceY >= n) rotationZ(rotationZ() - spinX);
                //                if(distanceY <= -n) rotationZ(rotationZ() + spinX);
                //                if(distanceX >= n) rotationZ(rotationZ() + spinY);
                //                if(distanceX <= -n) rotationZ(rotationZ() - spinY);
                if(_rotationZEnabled) if(distanceY >= 0) rotationZ(rotationZ() - spinX);
                if(_rotationZEnabled) if(distanceY <= 0) rotationZ(rotationZ() + spinX);
                if(_rotationZEnabled) if(distanceX >= 0) rotationZ(rotationZ() + spinY);
                if(_rotationZEnabled) if(distanceX <= 0) rotationZ(rotationZ() - spinY);
            }
        }
    }
    //Translate
    else if(_dragMode == 1) {
        x(x() + dx * 0.01);
        y(y() - dy * 0.01);
    }
    
    _lastMouse = _mouse;
}

//--------------------------------------------------------------
//
void TransformableNode::_mouseDownEventHandler(ofMouseEventArgs& event) {
    //    cout << "[TransformableNode]_mouseDownEventHandler()" << endl;
    if(!_enabled) return;
    
    if(event.x < _viewport.x) return;
    if(_viewport.x + _viewport.width < event.x) return;
    if(event.y < _viewport.y) return;
    if(_viewport.y + _viewport.height < event.y) return;
    
    _isDragOn = true;
    
    _mouseID = event.button;
    
    _mouse.x = event.x;
    _mouse.y = event.y;
    
    _lastMouse = _mouse;
    
    ofVec2f center = ofVec2f(
                             _viewport.x + _viewport.width / 2.0,
                             _viewport.y + _viewport.height / 2.0
                             );
    float distance = center.distance(_mouse);
    //    float n = 220;
    
    if(distance < n) _isInArea = true;
    
    if(abs(_mouse.x - center.x) < 6.0) {
        _mode = "1";
    }
    if(abs(_mouse.y - center.y) < 6.0) {
        _mode = "2";
    }
}

//--------------------------------------------------------------
//
void TransformableNode::_mouseUpEventHandler(ofMouseEventArgs& event) {
    //    cout << "[TransformableNode]_mouseUpEventHandler()";
    if(!_enabled) return;
    
    _isDragOn = false;
    _isInArea = false;
    
    _mode = "";
}

//--------------------------------------------------------------
//
void TransformableNode::_mouseScrolledEventHandler(ofMouseEventArgs& event) {
    //    cout << "[TransformableNode]_mouseScrolledEventHandler() << endl";
    //    return;
    if(!_enabled) return;
    if(!_scaleEnabled) return;
    
    float scrollY = event.scrollY * 0.01;
    
    scaleX(scaleX() - scrollY);
    scaleY(scaleY() - scrollY);
    scaleZ(scaleZ() - scrollY);
    
    cout << scaleX() << endl;
    cout << scaleY() << endl;
    cout << scaleZ() << endl;
}
