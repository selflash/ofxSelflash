#include "DisplayObject.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    DisplayObject::DisplayObject() {
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
        
        _rect = new Rectangle();
//        _rectTransformed = NULL;
        _pixelBounds = new Rectangle();
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _mouseX = 0;
        _mouseY = 0;
    }

    //--------------------------------------------------------------
    //
    DisplayObject::~DisplayObject() {
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
    void DisplayObject::setup() {
        _setup();
    }

    //--------------------------------------------------------------
    //
    void DisplayObject::update() {
        _update();
        
        _updateRect();
    }

    //--------------------------------------------------------------
    //
    void DisplayObject::draw(bool applyMatrix) {
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
    void DisplayObject::_setup() {
        
    }

    //--------------------------------------------------------------
    //
    void DisplayObject::_update() {
        
    }

    //--------------------------------------------------------------
    //
    void DisplayObject::_draw() {
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string DisplayObject::name() { return _name; }
    void DisplayObject::name(string value) { _name = value; }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObject::stage() { return _stage; }
    void DisplayObject::stage(DisplayObject* value) {
        //cout << "[DisplayObject]stage(" << value << ")" << name() << endl;
        
        //今までステージへの参照がもっていなくてvalueにステージへの参照が入ってる時
        if(!_stage && value) {
            _stage = value;
            
            Event* event = new Event(Event::ADDED_TO_STAGE);
            event->target(_target);
            dispatchEvent(event);
        }
        //既にステージへの参照がもっていてvalueにステージへの参照が入っていない時
        if(_stage && !value) {
            _stage = value;
            
            Event* event = new Event(Event::REMOVED_FROM_STAGE);
            event->target(_target);
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObject::parent() { return _parent; }
    void DisplayObject::parent(DisplayObject* value) {
        //cout << "[DisplayObject]parent(" << value << ")" << name() << endl;
        
        //今まで親への参照がもっていなくてvalueに親への参照が入ってる時
        if(!_parent && value) {
            _parent = value;
            _compoundAlpha = _parent->__compoundAlpha() * _alpha;
            
            Event* event = new Event(Event::ADDED);
            event->target(_target);
            dispatchEvent(event);
        }
        //既に親への参照がもっていてvalueに親への参照が入っていない時
        if(_parent && !value) {
            _parent = value;
            
            Event* event = new Event(Event::REMOVED);
            event->target(_target);
            dispatchEvent(event);
        }
    }

    //--------------------------------------------------------------
    // TODO
    void DisplayObject::mask(DisplayObject* value){ }
    DisplayObject* DisplayObject::mask() { return _mask; }
    
    //--------------------------------------------------------------
    //
    float DisplayObject::x() { return _matrix.tx(); }
    void DisplayObject::x(float value) { _matrix.tx(value); }
    //--------------------------------------------------------------
    //
    float DisplayObject::y() { return _matrix.ty(); }
    void DisplayObject::y(float value) { _matrix.ty(value); }
    //--------------------------------------------------------------
    //
    float DisplayObject::z() { return _z; }
    void DisplayObject::z(float value) { _z = value; }
    
//    //--------------------------------------------------------------
//    //
//    float DisplayObject::width() {
//        _updateRect();
//        
//        return _rect->width() * scaleX();
//    }
//    void DisplayObject::width(float value) {
//        _rect->width(value);
//    }
//    //--------------------------------------------------------------
//    //
//    float DisplayObject::height() {
//        _updateRect();
//        
//        return _rect->height() * scaleY();
//    }
//    void DisplayObject::height(float value) {
//        _rect->height(value);
//    }
//    
////    //--------------------------------------------------------------
////    //
////    float DisplayObject::width() {
////        _updateRect();
////        return _realWidth * scaleX();
////    }
////    void DisplayObject::width(float value) { _targetWidth = value; }
////
////    //--------------------------------------------------------------
////    //
////    float DisplayObject::height() {
////        _updateRect();
////        return _realHeight * scaleY();
////    }
////    void DisplayObject::height(float value) { _targetHeight = value; }
//    
//    //--------------------------------------------------------------
//    //
//    float DisplayObject::scaleX() { return _matrix.scaleX(); }
//    void DisplayObject::scaleX(float value) { _matrix.scaleX(value); }
//    //--------------------------------------------------------------
//    //
//    float DisplayObject::scaleY() { return _matrix.scaleY(); }
//    void DisplayObject::scaleY(float value) { _matrix.scaleY(value); }
    
    
    
    //--------------------------------------------------------------
    //
    float DisplayObject::width() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _realWidth * scaleX();
    }
    void DisplayObject::width(float value) {
        _targetWidth = value;
        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
    }
    
    //--------------------------------------------------------------
    //
    float DisplayObject::height() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _realHeight * scaleY();
    }
    void DisplayObject::height(float value) {
        _targetHeight = value;
        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
    }
    
    //--------------------------------------------------------------
    //
    float DisplayObject::scaleX() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _matrix.scaleX();
    }
    void DisplayObject::scaleX(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleX(value);
    }
    //--------------------------------------------------------------
    //
    float DisplayObject::scaleY() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _matrix.scaleY();
    }
    void DisplayObject::scaleY(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleY(value);
    }
    
    //--------------------------------------------------------------
    //
    float DisplayObject::scaleZ() { return _scaleZ; }
    void DisplayObject::scaleZ(float value) { _scaleZ = value; }
    
    //--------------------------------------------------------------
    //
    float DisplayObject::rotation() { return _matrix.rotation() * RAD_TO_DEG; }
    void DisplayObject::rotation(float value) { _matrix.rotate(value * DEG_TO_RAD); }
    //--------------------------------------------------------------
    //
    float DisplayObject::rotationX() { return _rotationX; }
    void DisplayObject::rotationX(float value) { _rotationX = value; }
    //--------------------------------------------------------------
    //
    float DisplayObject::rotationY() { return _rotationY; }
    void DisplayObject::rotationY(float value) { _rotationY = value; }
    //--------------------------------------------------------------
    //
    float DisplayObject::rotationZ() { return _rotationZ; }
    void DisplayObject::rotationZ(float value) { _rotationZ = value; }

    //--------------------------------------------------------------
    //
    float DisplayObject::alpha() { return _alpha; }
    void DisplayObject::alpha(float value) { _alpha = value; }

    //--------------------------------------------------------------
    //
    bool DisplayObject::visible() { return _visible; }
    void DisplayObject::visible(bool value) { _visible = value; }

    //--------------------------------------------------------------
    //
    int DisplayObject::blendMode() { return _blendMode; }
    void DisplayObject::blendMode(int value) {
        if(value < 0 || 13 < value) return;
        _blendMode = value;
    }

    //--------------------------------------------------------------
    //
    int DisplayObject::level() { return _level; }
    void DisplayObject::level(int value) { _level = value; }

    //--------------------------------------------------------------
    //
    const Matrix& DisplayObject::matrix() { return _matrix; }
    void DisplayObject::matrix(const Matrix& mat) { _matrix = mat; }

    //--------------------------------------------------------------
    //
    const Matrix& DisplayObject::concatenatedMatrix() { return _concatenatedMatrix; }
    
    //--------------------------------------------------------------
    // TODO
    Rectangle DisplayObject::getRect(DisplayObject* targetCoordinateSpace) {
        Rectangle rect;
        rect.left(_rect->left() * scaleX());
        rect.right(_rect->right() * scaleX());
        rect.top(_rect->top() * scaleY());
        rect.bottom(_rect->bottom() * scaleY());
        return rect;
    }

    //--------------------------------------------------------------
    //
    bool DisplayObject::hitTestObject(DisplayObject* obj) {
        // TODO - working if two rectangles of different world matrices make any contact.
        return false;
    }

    //--------------------------------------------------------------
    //
    bool DisplayObject::hitTestPoint(float x, float y, bool shapeFlag) {
        ofPoint p(x, y);
        //グローバル座標からローカル座標に変換
        _concatenatedMatrixInv.transformPoint(p);
        return _rect->pointTest(p.x, p.y);
    }

    //--------------------------------------------------------------
    //
    ofPoint DisplayObject::globalToLocal(const ofPoint& point) {
        ofPoint p = point;
        //グローバル座標からローカル座標に変換
        _concatenatedMatrixInv.transformPoint(p);
        return p;
    }

    //--------------------------------------------------------------
    //
    ofPoint DisplayObject::globalToLocal3D(const ofPoint& point) {
        ofPoint p = point;
        _concatenatedMatrixInv.transformPoint(p);
        return p;
    }

    //--------------------------------------------------------------
    //
    ofPoint DisplayObject::local3DToGlobal(const ofPoint& point) {
        ofPoint p = point;
        _concatenatedMatrix.transformPoint(p);
        return p;
    }

    //--------------------------------------------------------------
    //
    ofPoint DisplayObject::localToGlobal(const ofPoint& point) {
        ofPoint p = point;
        _concatenatedMatrix.transformPoint(p);
        return p;
    }
    
    //--------------------------------------------------------------
    //
    void DisplayObject::transform(const Matrix& mat) {
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
    bool DisplayObject::enabledSmoothing() { return _enabledSmoothing; }
    void DisplayObject::enabledSmoothing(bool value) { _enabledSmoothing = value; }

    //--------------------------------------------------------------
    //
    bool DisplayObject::enabledAntiAliasing() { return _enabledAntiAliasing; }
    void DisplayObject::enabledAntiAliasing(bool value) { _enabledAntiAliasing = value; }

    //--------------------------------------------------------------
    //
    int DisplayObject::mouseX() {
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
    int DisplayObject::mouseY() {
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
    void DisplayObject::_updateRect() {
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
    float DisplayObject::__compoundAlpha(){ return _compoundAlpha; }
    void DisplayObject::__compoundAlpha(float value){ _compoundAlpha = value; }
}
