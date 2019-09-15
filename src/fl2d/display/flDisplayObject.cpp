#include "flDisplayObject.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flDisplayObject::flDisplayObject() {
        _typeID = FL_TYPE_DISPLAY_OBJECT;
        _target = this;
        _name = "DisplayObject";
        
        _stage = NULL;
        _parent = NULL;
        _mask = NULL;
        
        _z = 0.0;
        
        _realWidth = 0.0;
        _realHeight = 0.0;
        //        _targetWidth = 0 / 0.f;
        //        _targetHeight = 0 / 0.f;
        _targetWidth = numeric_limits<float>::quiet_NaN();
        _targetHeight = numeric_limits<float>::quiet_NaN();
        //        _targetWidth = -9999.0;
        //        _targetHeight = -9999.0;
        
        _scaleZ = 1.0;
        
        _rotationX = 0.0;
        _rotationY = 0.0;
        _rotationZ = 0.0;
        
        _alpha = 1.0;
        _compoundAlpha	= 1.0;
        
        _visible = true;
        
        _blendMode = FL_BLEND_MODE_NORMAL;
        _level = -1;
        
        //        _matrix = NULL;
        //        _concatenatedMatrix = NULL;
        //        _concatenatedMatrixInv = NULL;
        
        _rect = new flRectangle();
        //        _rectTransformed = NULL;
        _pixelBounds = new flRectangle();
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _mouseX = 0;
        _mouseY = 0;
    }
    
    //--------------------------------------------------------------
    //
    flDisplayObject::~flDisplayObject() {
        _target = NULL;
        _name = "";
        
        _stage = NULL;
        _parent = NULL;
        _mask = NULL;
        
        _z = 0.0;
        
        _realWidth = 0.0;
        _realHeight = 0.0;
        _targetWidth = 0.0;
        _targetHeight = 0.0;
        
        _scaleZ = 0.0;
        
        _rotationX = 0.0;
        _rotationY = 0.0;
        _rotationZ = 0.0;
        
        _alpha = 0.0;
        _compoundAlpha	= 0.0;
        
        _visible = false;
        
        _blendMode = FL_BLEND_MODE_NORMAL;
        _level = 0;
        
        //        _matrix = NULL;
        //        _concatenatedMatrix = NULL;
        //        _concatenatedMatrixInv = NULL;
        
        delete _rect;
        _rect = NULL;
        
        delete _pixelBounds;
        _pixelBounds = NULL;
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _mouseX = 0;
        _mouseY = 0;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::setup() {
        _setup();
    }
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::update() {
        _update();
        
        _updateRect();
    }
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::draw(bool applyMatrix) {
        if(!visible() && applyMatrix) return;
        
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
        if(_enabledSmoothing) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        if(_enabledAntiAliasing) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        
        //------------------------------------------
        //-- matrix transform.
        //        bool bIdentity = true;
        //        bIdentity = matrix().isIdentity();
        //        bIdentity = false;
        
        if(applyMatrix){
            //            glPushMatrix();
            ofPushMatrix();
            //            glMultMatrixf(matrix().getPtr());
            ofMultMatrix(matrix().getPtr());
        }
        
        ofPushStyle();
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _draw();
        ofPopStyle();
        
        if(applyMatrix){
            //            glPopMatrix();
            ofPopMatrix();
        }
        //------------------------------------------
        
        if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
        if(preLighting == GL_TRUE) { ofEnableLighting(); } else { ofDisableLighting(); }
        
        // restore saved state of blend enabled and blend functions
        if (blendEnabled) { glEnable(GL_BLEND); } else { glDisable(GL_BLEND); }
        glBlendFunc(blendSrc, blendDst);
    };
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::_setup() {
        
    }
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::_update() {
        
    }
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    string flDisplayObject::name() { return _name; }
    void flDisplayObject::name(string value) { _name = value; }
    
    //--------------------------------------------------------------
    //
    flDisplayObject* flDisplayObject::stage() { return _stage; }
    void flDisplayObject::stage(flDisplayObject* value) {
        //cout << "[flDisplayObject]stage(" << value << ")" << name() << endl;
        
        //今までステージへの参照がもっていなくてvalueにステージへの参照が入ってる時
        if(!_stage && value) {
            _stage = value;
            
            flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
            event->target(_target);
            dispatchEvent(event);
        }
        //既にステージへの参照がもっていてvalueにステージへの参照が入っていない時
        if(_stage && !value) {
            _stage = value;
            
            flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
            event->target(_target);
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    //
    flDisplayObject* flDisplayObject::parent() { return _parent; }
    void flDisplayObject::parent(flDisplayObject* value) {
        //cout << "[flDisplayObject]parent(" << value << ")" << name() << endl;
        
        //今まで親への参照がもっていなくてvalueに親への参照が入ってる時
        if(!_parent && value) {
            _parent = value;
            _compoundAlpha = _parent->__compoundAlpha() * _alpha;
            
            flEvent* event = new flEvent(flEvent::ADDED);
            event->target(_target);
            dispatchEvent(event);
        }
        //既に親への参照がもっていてvalueに親への参照が入っていない時
        if(_parent && !value) {
            _parent = value;
            
            flEvent* event = new flEvent(flEvent::REMOVED);
            event->target(_target);
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    // TODO
    void flDisplayObject::mask(flDisplayObject* value){ }
    flDisplayObject* flDisplayObject::mask() { return _mask; }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::x() { return _matrix.tx(); }
    void flDisplayObject::x(float value) { _matrix.tx(value); }
    //--------------------------------------------------------------
    //
    float flDisplayObject::y() { return _matrix.ty(); }
    void flDisplayObject::y(float value) { _matrix.ty(value); }
    //--------------------------------------------------------------
    //
    float flDisplayObject::z() { return _z; }
    void flDisplayObject::z(float value) { _z = value; }
    
    //    //--------------------------------------------------------------
    //    //
    //    float flDisplayObject::width() {
    //        _updateRect();
    //        
    //        return _rect->width() * scaleX();
    //    }
    //    void flDisplayObject::width(float value) {
    //        _rect->width(value);
    //    }
    //    //--------------------------------------------------------------
    //    //
    //    float flDisplayObject::height() {
    //        _updateRect();
    //        
    //        return _rect->height() * scaleY();
    //    }
    //    void flDisplayObject::height(float value) {
    //        _rect->height(value);
    //    }
    //    
    ////    //--------------------------------------------------------------
    ////    //
    ////    float flDisplayObject::width() {
    ////        _updateRect();
    ////        return _realWidth * scaleX();
    ////    }
    ////    void flDisplayObject::width(float value) { _targetWidth = value; }
    ////
    ////    //--------------------------------------------------------------
    ////    //
    ////    float flDisplayObject::height() {
    ////        _updateRect();
    ////        return _realHeight * scaleY();
    ////    }
    ////    void flDisplayObject::height(float value) { _targetHeight = value; }
    //    
    //    //--------------------------------------------------------------
    //    //
    //    float flDisplayObject::scaleX() { return _matrix.scaleX(); }
    //    void flDisplayObject::scaleX(float value) { _matrix.scaleX(value); }
    //    //--------------------------------------------------------------
    //    //
    //    float flDisplayObject::scaleY() { return _matrix.scaleY(); }
    //    void flDisplayObject::scaleY(float value) { _matrix.scaleY(value); }
    
    
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::width() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _realWidth * scaleX();
    }
    void flDisplayObject::width(float value) {
        _targetWidth = value;
        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
    }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::height() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _realHeight * scaleY();
    }
    void flDisplayObject::height(float value) {
        _targetHeight = value;
        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
    }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::scaleX() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _matrix.scaleX();
    }
    void flDisplayObject::scaleX(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleX(value);
    }
    //--------------------------------------------------------------
    //
    float flDisplayObject::scaleY() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _matrix.scaleY();
    }
    void flDisplayObject::scaleY(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleY(value);
    }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::scaleZ() { return _scaleZ; }
    void flDisplayObject::scaleZ(float value) { _scaleZ = value; }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::rotation() { return _matrix.rotation() * RAD_TO_DEG; }
    void flDisplayObject::rotation(float value) { _matrix.rotate(value * DEG_TO_RAD); }
    //--------------------------------------------------------------
    //
    float flDisplayObject::rotationX() { return _rotationX; }
    void flDisplayObject::rotationX(float value) { _rotationX = value; }
    //--------------------------------------------------------------
    //
    float flDisplayObject::rotationY() { return _rotationY; }
    void flDisplayObject::rotationY(float value) { _rotationY = value; }
    //--------------------------------------------------------------
    //
    float flDisplayObject::rotationZ() { return _rotationZ; }
    void flDisplayObject::rotationZ(float value) { _rotationZ = value; }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::alpha() { return _alpha; }
    void flDisplayObject::alpha(float value) { _alpha = value; }
    
    //--------------------------------------------------------------
    //
    bool flDisplayObject::visible() { return _visible; }
    void flDisplayObject::visible(bool value) { _visible = value; }
    
    //--------------------------------------------------------------
    //
    int flDisplayObject::blendMode() { return _blendMode; }
    void flDisplayObject::blendMode(int value) {
        if(value < 0 || 13 < value) return;
        _blendMode = value;
    }
    
    //--------------------------------------------------------------
    //
    int flDisplayObject::level() { return _level; }
    void flDisplayObject::level(int value) { _level = value; }
    
    //--------------------------------------------------------------
    //
    const flMatrix& flDisplayObject::matrix() { return _matrix; }
    void flDisplayObject::matrix(const flMatrix& mat) { _matrix = mat; }
    
    //--------------------------------------------------------------
    //
    const flMatrix& flDisplayObject::concatenatedMatrix() { return _concatenatedMatrix; }
    
    //--------------------------------------------------------------
    // TODO
    flRectangle flDisplayObject::getRect(flDisplayObject* targetCoordinateSpace) {
        flRectangle rect;
        rect.left(_rect->left() * scaleX());
        rect.right(_rect->right() * scaleX());
        rect.top(_rect->top() * scaleY());
        rect.bottom(_rect->bottom() * scaleY());
        return rect;
    }
    
    //--------------------------------------------------------------
    //
    bool flDisplayObject::hitTestObject(flDisplayObject* obj) {
        // TODO - working if two rectangles of different world matrices make any contact.
        return false;
    }
    
    //--------------------------------------------------------------
    //
    bool flDisplayObject::hitTestPoint(float x, float y, bool shapeFlag) {
        ofPoint p(x, y);
        //グローバル座標からローカル座標に変換
        _concatenatedMatrixInv.transformPoint(p);
        return _rect->pointTest(p.x, p.y);
    }
    
    //--------------------------------------------------------------
    //
    ofPoint flDisplayObject::globalToLocal(const ofPoint& point) {
        ofPoint p = point;
        //グローバル座標からローカル座標に変換
        _concatenatedMatrixInv.transformPoint(p);
        return p;
    }
    
    //--------------------------------------------------------------
    //
    ofPoint flDisplayObject::globalToLocal3D(const ofPoint& point) {
        ofPoint p = point;
        _concatenatedMatrixInv.transformPoint(p);
        return p;
    }
    
    //--------------------------------------------------------------
    //
    ofPoint flDisplayObject::local3DToGlobal(const ofPoint& point) {
        ofPoint p = point;
        _concatenatedMatrix.transformPoint(p);
        return p;
    }
    
    //--------------------------------------------------------------
    //
    ofPoint flDisplayObject::localToGlobal(const ofPoint& point) {
        ofPoint p = point;
        _concatenatedMatrix.transformPoint(p);
        return p;
    }
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::transform(const flMatrix& mat) {
        _concatenatedMatrix = mat;
        _concatenatedMatrixInv = mat;
        _concatenatedMatrixInv.invert();
        
        float x1 = _rect->left();
        float y1 = _rect->top();
        float x2 = _rect->right();
        float y2 = _rect->bottom();
        
        ofPoint p0(x1, y1);
        ofPoint p1(x2, y1);
        ofPoint p2(x2, y2);
        ofPoint p3(x1, y2);
        
        mat.transformPoint(p0);
        mat.transformPoint(p1);
        mat.transformPoint(p2);
        mat.transformPoint(p3);
        
        _rectTransformed[0] = p0;
        _rectTransformed[1] = p1;
        _rectTransformed[2] = p2;
        _rectTransformed[3] = p3;
        
        //-- work out global bounding box.
        
        vector<ofPoint> points;
        points.push_back(_rectTransformed[0]);
        points.push_back(_rectTransformed[1]);
        points.push_back(_rectTransformed[2]);
        points.push_back(_rectTransformed[3]);
        
        _pixelBounds->__setNull();						// reset before enclosing new points.
        _pixelBounds->__encloseRect(points);
    }
    
    //--------------------------------------------------------------
    //
    bool flDisplayObject::enabledSmoothing() { return _enabledSmoothing; }
    void flDisplayObject::enabledSmoothing(bool value) { _enabledSmoothing = value; }
    
    //--------------------------------------------------------------
    //
    bool flDisplayObject::enabledAntiAliasing() { return _enabledAntiAliasing; }
    void flDisplayObject::enabledAntiAliasing(bool value) { _enabledAntiAliasing = value; }
    
    //--------------------------------------------------------------
    //
    int flDisplayObject::mouseX() {
        // if it has a reference to stage then it must have been added as a child to stage.
        if(_stage) {
            ofPoint p;
            p.x = _stage->mouseX();
            
            _concatenatedMatrixInv.transformPoint(p);
            //		_mouseX = p.x - _rect->x();
            _mouseX = p.x;
        } else {
            _mouseX = 0;
        }
        return _mouseX;
    }
    //--------------------------------------------------------------
    //
    int flDisplayObject::mouseY() {
        // if it has a reference to stage then it must have been added as a child to stage.
        if(_stage) {
            ofPoint p;
            p.y = _stage->mouseY();
            
            _concatenatedMatrixInv.transformPoint(p);
            //            _mouseY = p.y - _rect->y();
            _mouseY = p.y;
        } else {
            _mouseY = 0;
        }
        return _mouseY;
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flDisplayObject::_updateRect() {
        ////        _rect->__setZero();
        //        
        ////        _rect->width(_targetWidth);
        ////        _rect->height(_targetHeight);
        //        
        //        //--------------------------------------
        //        _realWidth = _rect->width();
        //        _realHeight = _rect->height();
        //        
        //        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        //        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        ////        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
        ////        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
        //        //--------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flDisplayObject::__compoundAlpha(){ return _compoundAlpha; }
    void flDisplayObject::__compoundAlpha(float value){ _compoundAlpha = value; }
}
