#include "flSprite.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flSprite::flSprite() {
        //        ofLog() << "[Sprite]Sprite()";
        
        _typeID = FL_TYPE_SPRITE;
        _target = this;
        
        name("flSprite");
        
        __hitAreaObject = NULL;
        
        _graphics = new flGraphics();
        
        _buttonMode = false;
        _dropTarget	= NULL;
        _hitArea = NULL;
        _useHandCursor = false;
        
        _draggableArea = NULL;
        
        ofAddListener(ofEvents().update, this, &flSprite::_updateEventHandler);
        
        //--------------------------------------
        //Tooltip
        addEventListener(flMouseEvent::ROLL_OVER, this, &flSprite::_mouseEventHandler_flSprite);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flSprite::_mouseEventHandler_flSprite);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flSprite::_mouseEventHandler_flSprite);
        //--------------------------------------
    }
    
    //--------------------------------------------------------------
    flSprite::~flSprite() {
        //ofLog() << "[flSprite]~flSprite()";
        
        _target = NULL;
        
        __hitAreaObject = NULL;
        
        if(_graphics != NULL) delete _graphics;
        _graphics = NULL;
        
        _buttonMode = false;
        _dropTarget	= NULL;
        _hitArea = NULL;
        _useHandCursor = false;
        
		if (_draggableArea != NULL) delete _draggableArea;
        _draggableArea = NULL;
        
        ofRemoveListener(ofEvents().update, this, &flSprite::_updateEventHandler);
        
        //--------------------------------------
        //Tooltip
        if(_toolTip != NULL) delete _toolTip;
		_toolTip = NULL;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flSprite::_mouseEventHandler_flSprite);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flSprite::_mouseEventHandler_flSprite);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flSprite::_mouseEventHandler_flSprite);
        //--------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    //TODO
    void flSprite::update() {
        flDisplayObjectContainer::update();
        
        //--------------------------------------
        //Tooltip
        if(_toolTipEnabled && _toolTip->visible()) {
            if(stage() != NULL) {
//                float stageWidth = stage()->width();
//                float stageHeight = stage()->height();
                float stageWidth = ofGetWidth();
                float stageHeight = ofGetHeight();
                float stageMouseX = stage()->mouseX();
                float stageMouseY = stage()->mouseY();
                float toolTipWidth = _toolTip->width();
                float toolTipHeight = _toolTip->height();

                if(stageWidth < stageMouseX + 30 + toolTipWidth) {
                    _toolTip->x(stageMouseX - 30 - toolTipWidth);
                } else {
                    _toolTip->x(stageMouseX + 30);
                }
                
                if(stageHeight < stageMouseY + 10 + toolTipHeight) {
                    _toolTip->y(stageMouseY - 10 - toolTipHeight);
                } else {
                    _toolTip->y(stageMouseY + 10);
                }
            }
        }
        //--------------------------------------
    }
    
    //--------------------------------------------------------------
    void flSprite::draw(bool applyMatrix) {
        if(!visible() && applyMatrix) return;

		//------------------------------------------
		if (_mask != NULL) {
			_beginDrawingStencil();

			//draw mask shapes
			ofPushMatrix();
			ofMultMatrix(_mask->parent()->transform().matrix().getPtr());
			_mask->draw();
			ofPopMatrix();
			
			_beginUsingStencil();
		}
		//draw scene to be masked
		//------------------------------------------

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
        //bool bIdentity = true;
        //bIdentity = matrix().isIdentity();
        //bIdentity = false;
		//if(!bIdentity){
        if(applyMatrix){
			//glPushMatrix();
            ofPushMatrix();
			//glMultMatrixf(matrix().getPtr());
            ofMultMatrix(_transform.matrix().getPtr());
        }

        ofPushStyle();
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _graphics->__draw();

		//if (parent()) {
		//	ofSetColor(255, 0, 0, 255 * _compoundAlpha);
		//	int index = ((flDisplayObjectContainer*)parent())->getChildIndex(this);
		//	flFont::drawString(ofToString(index), 10, 40);
		//}

        _draw();
        
        for(int i = 0; i < children.size(); i++){
            flDisplayObject* child;
            child = children[i];
			if (child->__maskOwner != NULL) continue;
			//child->drawOnFrame();
            child->draw();
        }
        ofPopStyle();
        
        //if(!bIdentity) {
        if(applyMatrix) {
            //glPopMatrix();
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
        if(_rectVisible) {
//        if(true) {
            ofPushMatrix();
            ofMultMatrix(_transform.__matrix.getPtr());

            ofNoFill();
            ofSetLineWidth(1);
            
            {
                flRectangle rect = getRect(this);
//                flRectangle rect = *_rect;
                ofSetColor(255, 0, 0, 150);
                ofDrawRectangle(rect.left(), rect.top(), rect.width(), rect.height());
            }
//            {
//                int i; int l;
//                l = children.size();
//                for(i = 0; i < l; i++) {
//                    flDisplayObject* child = children[i];
//                    flRectangle rect = child->getRect(this);
//                    ofSetColor(0, 255, 0, 150);
//                    ofDrawRectangle(rect.left(), rect.top(), rect.width(), rect.height());
//                }
//            }
            
            ofPopMatrix();
        }
        //--------------------------------------

		//------------------------------------------
		if (_mask != NULL) {			 
			_endUsingStencil();
		}
		//------------------------------------------
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //    //--------------------------------------------------------------
    //    //
    //    const float flSprite::width() { return _realWidth * scaleX(); }
    //    void flSprite::width(float value) {
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
    //    const float flSprite::height() { return _realHeight * scaleY(); }
    //    void flSprite::height(float value) {
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
    float flSprite::width() {
        _updateRect();
		if (_mask) return _mask->width();
        if (_realWidth == 0.0) return 0.0;
        return _realWidth * scaleX();
    }
    void flSprite::width(float value) {
        _targetWidth = value;
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
    }
    
    //--------------------------------------------------------------
    float flSprite::height() {
        _updateRect();
		if (_mask) return _mask->height();
		if (_realHeight == 0.0) return 0.0;
        return _realHeight * scaleY();
    }
    void flSprite::height(float value) {
        _targetHeight = value;
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
    }
    
//    //--------------------------------------------------------------
//    float flSprite::scaleX() { return _matrix.scaleX(); }
//    void flSprite::scaleX(float value) {
//        _targetHeight = numeric_limits<float>::quiet_NaN();
//        _matrix.scaleX(value);
//    }
//    //--------------------------------------------------------------
//    float flSprite::scaleY() { return _matrix.scaleY(); }
//    void flSprite::scaleY(float value) {
//        _targetHeight = numeric_limits<float>::quiet_NaN();
//        _matrix.scaleY(value);
//    }
    
    //--------------------------------------------------------------
    bool flSprite::useHandCursor() { return _useHandCursor; }
    void flSprite::useHandCursor(bool value) { _useHandCursor = value; }
    
    //--------------------------------------------------------------
    //TODO
    //    float flSprite::alpha() { return _alpha; }
    //    void flSprite::alpha(float value) {
    //        _alpha = value;
    //        _graphics->__alpha = _alpha;
    //    }
    
    //--------------------------------------------------------------
    flSprite* flSprite::hitArea() { return _hitArea; }
    void flSprite::hitArea(flSprite* value) {
        /*
         ・memo [AS3におけるhitAreaの挙動]
         ・addChildされていないと反応しない
         ・hitAreaに設定するflSpriteのmouseEnabledはfalseしないといけない
         ・hitAreaに設定するflSpriteを他のhitAreaにする事はできない
         ・もっとも上にaddChildされたflSpriteが優先される
         
         ・must be addedChild.
         */
        
        if(value == NULL) {
            value->__hitAreaObject = NULL;
            _hitArea = NULL;
        } else {
            value->__hitAreaObject = this;
            _hitArea = value;
        }
    }
    
    //--------------------------------------------------------------
    bool flSprite::hitTestPoint(float x, float y, bool shapeFlag) {
		//if (_mask != NULL) {
		//	bool isHit = _mask->hitTestPoint(x, y, shapeFlag);
		//	//ofLog() << "hitTestPoint" << isHit;
		//	return isHit;
		//}

        ofPoint p(x, y);

        //グローバル座標からローカル座標に変換
        //Transform to local from global.
        _transform.__concatenatedMatrixInv.transformPoint(p);
        
        if(shapeFlag) {
            return _graphics->__rect->pointTest(p.x, p.y);
        } else {
            return _rect->pointTest(p.x, p.y);
        }
    }
    
    //--------------------------------------------------------------
    //TODO
    void flSprite::startDrag(bool lockCenter, flRectangle* bounds) {
        _draggableArea = bounds;

		_startDragPoint.x = x();
		_startDragPoint.y = y();
        
        //TODO 実装がスマートじゃないなー・・
        //it's not cool...
        //ofPoint* p = new ofPoint(stage()->mouseX(), stage()->mouseY());
        //ofPoint* p = new ofPoint(ofGetMouseX(), ofGetMouseY());
		_tempPoint.x = ofGetMouseX();
		_tempPoint.y = ofGetMouseY();
        _draggablePoint = parent()->globalToLocal(_tempPoint);
        _draggablePoint.x -= x();
        _draggablePoint.y -= y();
        
        ofAddListener(ofEvents().mouseDragged, this, &flSprite::_mouseDragging);
    }
    
    //--------------------------------------------------------------
    void flSprite::stopDrag() {
        ofRemoveListener(ofEvents().mouseDragged, this, &flSprite::_mouseDragging);
        
        _draggableArea = NULL;
    }
    
    //--------------------------------------------------------------
    bool flSprite::toolTipEnabled() { return _toolTipEnabled; }
    void flSprite::toolTipEnabled(bool value) {
        if(_toolTipEnabled == value) return;
        _toolTipEnabled = value;
        
        if(_toolTipEnabled) {
            _toolTip = new flToolTip();
            _toolTip->text(_toolTipText);
        } else {
            if(_toolTip->parent() != NULL) {
                ((flDisplayObjectContainer*)_toolTip->parent())->removeChild(_toolTip);
            }
            delete _toolTip;
            _toolTip = NULL;
        }
    }
    
    //--------------------------------------------------------------
    // TODO Include a shape line.
    flRectangle flSprite::getBounds(flDisplayObject* targetCoordinateSpace) {
        _tempRect.__setNull();
        
        {
            //Graphics rect
            const flRectangle& tempRect = *_graphics->__rect;
            float x1 = tempRect.left();
            float y1 = tempRect.top();
            float x2 = tempRect.right();
            float y2 = tempRect.bottom();
            
            _tempPoint1.set(x1, y1);
            _tempPoint2.set(x2, y1);
            _tempPoint3.set(x2, y2);
            _tempPoint4.set(x1, y2);
            
            //Local to global.
            const flMatrix& localToGlobalMatrix = _transform.__concatenatedMatrix;
            localToGlobalMatrix.transformPoint(_tempPoint1);
            localToGlobalMatrix.transformPoint(_tempPoint2);
            localToGlobalMatrix.transformPoint(_tempPoint3);
            localToGlobalMatrix.transformPoint(_tempPoint4);
            
            //Global to local.
            const flMatrix& globalToTargetLocalMatrix = targetCoordinateSpace->_transform.__concatenatedMatrixInv;
            globalToTargetLocalMatrix.transformPoint(_tempPoint1);
            globalToTargetLocalMatrix.transformPoint(_tempPoint2);
            globalToTargetLocalMatrix.transformPoint(_tempPoint3);
            globalToTargetLocalMatrix.transformPoint(_tempPoint4);
            
            _tempRect.__encloseRect(_tempPoint1, _tempPoint2, _tempPoint3, _tempPoint4);
        }
        
        {
            int i; int l;
            l = children.size();
            for(i = 0; i < l; i++) {
                flDisplayObject* child = children[i];
                if(!child->visible()) continue;
                flRectangle childRect = child->getRect(targetCoordinateSpace);
                
                float x1 = childRect.left();
                float y1 = childRect.top();
                float x2 = childRect.right();
                float y2 = childRect.bottom();
                
                _tempPoint1.set(x1, y1);
                _tempPoint2.set(x2, y1);
                _tempPoint3.set(x2, y2);
                _tempPoint4.set(x1, y2);
                
                _tempRect.__expandTo(_tempPoint1);
                _tempRect.__expandTo(_tempPoint2);
                _tempRect.__expandTo(_tempPoint3);
                _tempRect.__expandTo(_tempPoint4);
            }
        }
        
        return _tempRect;
    }
    
    //--------------------------------------------------------------
    // TODO Not include a shape line.
    flRectangle flSprite::getRect(flDisplayObject* targetCoordinateSpace) {
        _tempRect.__setNull();

        {
            //Graphics rect
            const flRectangle& tempRect = *_graphics->__rect;
            float x1 = tempRect.left();
            float y1 = tempRect.top();
            float x2 = tempRect.right();
            float y2 = tempRect.bottom();
            
            _tempPoint1.set(x1, y1);
            _tempPoint2.set(x2, y1);
            _tempPoint3.set(x2, y2);
            _tempPoint4.set(x1, y2);
            
            //Local to global.
            const flMatrix& localToGlobalMatrix = _transform.__concatenatedMatrix;
            localToGlobalMatrix.transformPoint(_tempPoint1);
            localToGlobalMatrix.transformPoint(_tempPoint2);
            localToGlobalMatrix.transformPoint(_tempPoint3);
            localToGlobalMatrix.transformPoint(_tempPoint4);
            
            //Global to local.
            const flMatrix& globalToTargetLocalMatrix = targetCoordinateSpace->_transform.__concatenatedMatrixInv;
            globalToTargetLocalMatrix.transformPoint(_tempPoint1);
            globalToTargetLocalMatrix.transformPoint(_tempPoint2);
            globalToTargetLocalMatrix.transformPoint(_tempPoint3);
            globalToTargetLocalMatrix.transformPoint(_tempPoint4);
            
            _tempRect.__encloseRect(_tempPoint1, _tempPoint2, _tempPoint3, _tempPoint4);
        }
        
        {
            int i; int l;
            l = children.size();
            for(i = 0; i < l; i++) {
                flDisplayObject* child = children[i];
                if(!child->visible()) continue;
                flRectangle childRect = child->getRect(targetCoordinateSpace);

                float x1 = childRect.left();
                float y1 = childRect.top();
                float x2 = childRect.right();
                float y2 = childRect.bottom();
                
                _tempPoint1.set(x1, y1);
                _tempPoint2.set(x2, y1);
                _tempPoint3.set(x2, y2);
                _tempPoint4.set(x1, y2);
                
                _tempRect.__expandTo(_tempPoint1);
                _tempRect.__expandTo(_tempPoint2);
                _tempRect.__expandTo(_tempPoint3);
                _tempRect.__expandTo(_tempPoint4);
            }
        }
        
        return _tempRect;
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    //Calculate width and height.
    void flSprite::_updateRect() {
        if(_graphics != NULL) _rect->__setToRect(*_graphics->__rect);
        
        int i; int l;
        l = children.size();
        for(i = 0; i < l; i++) {
            flDisplayObject* child = children[i];
            
            //=========================================== Matrix.
            //This the code is moved here from flStage._updateChildrenOne().
            //transform child matrix by world matrix.
            flMatrix worldMatrix;
            worldMatrix = transform().concatenatedMatrix();
            worldMatrix.concat(child->transform().matrix());
            child->__updateTransform(worldMatrix);

            if(!child->visible()) continue; 

            flRectangle childRect = child->__getRect(this);
            _rect->__expandTo(childRect.left(), childRect.top());
            _rect->__expandTo(childRect.right(), childRect.bottom());
        }
       
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
//        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);

		//if (_mask != NULL) {
		//	ofPoint p = ofPoint(_mask->x(), _mask->y());
		//	ofPoint global = _mask->parent()->localToGlobal(p);
		//	ofPoint local = globalToLocal(global);

		//	_rect->__contractToLeft(local.x);
		//	_rect->__contractToRight(local.x + _mask->width());
		//	_rect->__contractToTop(local.y);
		//	_rect->__contractToBottom(local.y + _mask->height());
		//}
    }
    
    //--------------------------------------------------------------
    void flSprite::__compoundAlpha(float value) {
        _compoundAlpha = value;
        _graphics->__compoundAlpha(_compoundAlpha);
    }
    
    //--------------------------------------------------------------
    void flSprite::_mouseDragging(int x, int y, int id) {
        if(!_mouseEnabled) return;
        
        //ofPoint* p1 = new ofPoint(stage()->mouseX(), stage()->mouseY());
        //ofPoint* p1 = new ofPoint(x, y);
		_tempPoint.x = x;
		_tempPoint.y = y;
        ofPoint p2 = parent()->globalToLocal(_tempPoint);
        
        float n1, n2;
        n1 = p2.x - _draggablePoint.x;
        n2 = p2.y - _draggablePoint.y;
        
        n1 = flmath::roundd(n1);
        n2 = flmath::roundd(n2);

        if(_draggableArea){
            if(n1 < _draggableArea->left()) n1 = _draggableArea->left();
            if(n1 > _draggableArea->right()) n1 = _draggableArea->right();
            if(n2 < _draggableArea->top()) n2 = _draggableArea->top();
            if(n2 > _draggableArea->bottom()) n2 = _draggableArea->bottom();
        }
        
        this->x(n1);
        this->y(n2);
        
        dispatchEvent(new flMouseEvent(flMouseEvent::DRAGGING));
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flSprite::_updateEventHandler(ofEventArgs& args) {
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
    }

    //--------------------------------------------------------------
    void flSprite::_mouseEventHandler_flSprite(flEvent& event) {
        //        ofLog() << "[flUIBase]_mouseEventHandler_flSprite(" << event.type() << ")";
        //        ofLog() << "[flUIBase]this          = " << this << "," << ((flDisplayObject*) this)->name();
        //        ofLog() << "[flUIBase]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
        //        ofLog() << "[flUIBase]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) {
                if(_toolTipEnabled) {
                    float stageMouseX = stage()->mouseX();
                    float stageMouseY = stage()->mouseY();
                    _toolTip->x(stageMouseX + 20);
                    _toolTip->y(stageMouseY + 10);
                    ((flDisplayObjectContainer*)stage())->addChild(_toolTip);
                }
            }
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) {
                if(_toolTipEnabled) {
                    if(_toolTip->parent() != NULL) {
                        ((flDisplayObjectContainer*)_toolTip->parent())->removeChild(_toolTip);
                    }
                }
            }
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(_toolTipEnabled) {
                if(_toolTip->parent() != NULL) {
                    ((flDisplayObjectContainer*)_toolTip->parent())->removeChild(_toolTip);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            
        }
    }
    
}
