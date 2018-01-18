#include "Sprite.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Sprite::Sprite() {
//        cout << "[Sprite]Sprite()" << endl;
        
        _typeID = FL_TYPE_SPRITE;
        _target = this;
        
        name("Sprite");
        
        client = NULL;
        
        _graphics = new Graphics();
        
        _buttonMode = false;
        _dropTarget	= NULL;
        _hitArea = NULL;
        _useHandCursor = false;
        
        _draggableArea = NULL;
        
        ofAddListener(ofEvents().update, this, &Sprite::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Sprite::~Sprite() {
//        cout << "[Sprite]~Sprite()" << endl;
        
        _target = NULL;
        
        client = NULL;
        
        delete _graphics;
        _graphics = NULL;
        
        _buttonMode = false;
        _dropTarget	= NULL;
        _hitArea = NULL;
        _useHandCursor = false;
        
        delete _draggableArea;
        _draggableArea = NULL;
        
        ofRemoveListener(ofEvents().update, this, &Sprite::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void Sprite::_updateEventHandler(ofEventArgs& args) {
        Event* event = new Event(Event::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //TODO
    void Sprite::update() {
        _update();
        
        _updateRect();
    }

    //--------------------------------------------------------------
    //
    void Sprite::draw(bool applyMatrix) {
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
//        if(!bIdentity){
        if(applyMatrix){
//            glPushMatrix();
            ofPushMatrix();
//            glMultMatrixf(matrix().getPtr());
            ofMultMatrix(matrix().getPtr());
        }
        
        ofPushStyle();
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _graphics->__draw();
        _draw();
        
        for(int i = 0; i < children.size(); i++){
            DisplayObject* child;
            child = children[i];
            //child->drawOnFrame();
            child->draw();
        }
        ofPopStyle();
        
//        if(!bIdentity) {
        if(applyMatrix) {
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

        //--------------------------------------
        //ヒットエリアの表示
    //    ofNoFill();
    //    ofSetLineWidth(1);
    //    ofSetColor(255, 0, 0, 100);
    //    ofRect(x(), y(), width(), height());
    //    ofRect(_rect->x(), _rect->y(), _rect->width(), _rect->height());
        //--------------------------------------
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

//    //--------------------------------------------------------------
//    //
//    const float Sprite::width() { return _realWidth * scaleX(); }
//    void Sprite::width(float value) {
//        //DisplayObjectContainer::width(value);
//        
//        _width = value;
//        //scaleX(_width / _realWidth);
//
//        
////        _width = value;
////        
////        if(graphics->__rect->isNull()) return;
////        
////        //--------------------------------------
////        _rect->left(graphics->__rect->left());
////        _rect->right(graphics->__rect->right());
////
////        int i; int l;
////        DisplayObject* child;
////
////        l = children.size();
////        for(i = 0; i < l; i++) {
////            child = children[i];
////            float n1 = child->x();
////            _rect->__expandToX(n1);
////            _rect->__expandToX(n1 + child->width());
////        }
////        
////        _realWidth = _rect->width();
////        //--------------------------------------
////        
////        scaleX(_width / _realWidth);
//    }
//    //--------------------------------------------------------------
//    //
//    const float Sprite::height() { return _realHeight * scaleY(); }
//    void Sprite::height(float value) {
////        DisplayObjectContainer::height(value);
//        
//        _height = value;
//        //scaleY(_height / _realHeight);
//        
////        _height = value;
////        
////        if(graphics->__rect->isNull()) return;
////        
////        //--------------------------------------
////        _rect->top(graphics->__rect->top());
////        _rect->bottom(graphics->__rect->bottom());
////        
////        int i; int l;
////        DisplayObject* child;
////        
////        l = children.size();
////        for(i = 0; i < l; i++) {
////            child = children[i];
////            float n2 = child->y();
////            _rect->__expandToY(n2);
////            _rect->__expandToY(n2 + child->height());
////        }
////        
////        _realHeight = _rect->height();
////        //--------------------------------------
////        
////        scaleY(_height / _realHeight);
//    }
    
    //--------------------------------------------------------------
    //
    float Sprite::width() {
        _updateRect();
        if(_realWidth == 0.0) return 0.0;
        return _realWidth * scaleX();
    }
    void Sprite::width(float value) {
        _targetWidth = value;
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
    }

    //--------------------------------------------------------------
    //
    float Sprite::height() {
        _updateRect();
        if(_realHeight == 0.0) return 0.0;
        return _realHeight * scaleY();
    }
    void Sprite::height(float value) {
        _targetHeight = value;
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
    }
    
    //--------------------------------------------------------------
    //
    float Sprite::scaleX() { return _matrix.scaleX(); }
    void Sprite::scaleX(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleX(value);
    }
    //--------------------------------------------------------------
    //
    float Sprite::scaleY() { return _matrix.scaleY(); }
    void Sprite::scaleY(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleY(value);
    }
    
    //--------------------------------------------------------------
    //
    bool Sprite::useHandCursor() { return _useHandCursor; }
    void Sprite::useHandCursor(bool value) { _useHandCursor = value; }

    //--------------------------------------------------------------
    //TODO
//    float Sprite::alpha() { return _alpha; }
//    void Sprite::alpha(float value) {
//        _alpha = value;
//        _graphics->__alpha = _alpha;
//    }

    //--------------------------------------------------------------
    //
    Sprite* Sprite::hitArea() { return _hitArea; }
    void Sprite::hitArea(Sprite* value) {
        /*
         ・memo [AS3におけるhitAreaの挙動]
         ・addChildされていないと反応しない
         ・hitAreaに設定するSpriteのmouseEnabledはfalseしないといけない
         ・hitAreaに設定するSpriteを他のhitAreaにする事はできない
         ・もっとも上にaddChildされたSpriteが優先される
         */
        
        if(value == NULL) {
            value->client = NULL;
            _hitArea = NULL;
        } else {
            value->client = this;
            _hitArea = value;
        }
    }
    
    //--------------------------------------------------------------
    //
    bool Sprite::hitTestPoint(float x, float y, bool shapeFlag) {
        ofPoint p(x, y);
        //グローバル座標からローカル座標に変換
        _concatenatedMatrixInv.transformPoint(p);
        
        if(shapeFlag) {
            return _graphics->__rect->pointTest(p.x, p.y);
        } else {
            return _rect->pointTest(p.x, p.y);
        }
    }
    
    //--------------------------------------------------------------
    //TODO
    void Sprite::startDrag(bool lockCenter, Rectangle* bounds) {
        _draggableArea = bounds;
        
        //TODO 実装がスマートじゃないなー・・
        //ofPoint* p = new ofPoint(stage()->mouseX(), stage()->mouseY());
        ofPoint* p = new ofPoint(ofGetMouseX(), ofGetMouseY());
        _draggablePoint = parent()->globalToLocal(*p);
        _draggablePoint.x -= x();
        _draggablePoint.y -= y();
        
        //cout << "x = " << p->x << " y = " << p->y << endl;
        
        ofAddListener(ofEvents().mouseDragged, this, &Sprite::_mouseDragging);
    }

    //--------------------------------------------------------------
    //
    void Sprite::stopDrag() {
        ofRemoveListener(ofEvents().mouseDragged, this, &Sprite::_mouseDragging);
        
        _draggableArea = NULL;
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Sprite::_updateRect() {
        _rect->__setToRect(*_graphics->__rect);
        
        int i; int l;
        DisplayObject* child;
        
        l = children.size();
        for(i = 0; i < l; i++) {
            child = children[i];
//                _rect->__expandToRect(*child->getRect(this));
            float cx = child->x();
            float cy = child->y();
            _rect->__expandTo(cx + child->getRect(this).left(), cy + child->getRect(this).top());
            _rect->__expandTo(cx + child->getRect(this).right(), cy + child->getRect(this).bottom());
        }
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        
//        cout << "Sprite _realWidth" << _realWidth << " Sprite _realHeight" << _realHeight << endl;
        
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
//        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
    }
    
    //--------------------------------------------------------------
    //
    void Sprite::__compoundAlpha(float value){
        _compoundAlpha = value;
        _graphics->__compoundAlpha(_compoundAlpha);
    }

    //--------------------------------------------------------------
    //
    void Sprite::_mouseDragging(int x, int y, int id) {
        if(!_mouseEnabled) return;
        
        //ofPoint* p1 = new ofPoint(stage()->mouseX(), stage()->mouseY());
        ofPoint* p1 = new ofPoint(x, y);
        ofPoint p2 = parent()->globalToLocal(*p1);
        
        float n1, n2;
        n1 = p2.x - _draggablePoint.x;
        n2 = p2.y - _draggablePoint.y;
        
        if(_draggableArea){
            if(n1 < _draggableArea->left()) n1 = _draggableArea->left();
            if(n1 > _draggableArea->right()) n1 = _draggableArea->right();
            if(n2 < _draggableArea->top()) n2 = _draggableArea->top();
            if(n2 > _draggableArea->bottom()) n2 = _draggableArea->bottom();
        }
        
        this->x(n1);
        this->y(n2);
        
        dispatchEvent(new MouseEvent(MouseEvent::DRAGGING));
    }

}
