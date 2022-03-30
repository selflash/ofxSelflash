#include "flDisplayObject.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flDisplayObject::flDisplayObject() {
//        ofLog() << "[flDisplayObject]flDisplayObject()";
        _typeID = FL_TYPE_DISPLAY_OBJECT;
        _target = this;
        name("flDisplayObject");
        
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
        
        _rect = new flRectangle();
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _mouseX = 0;
        _mouseY = 0;
    }
    
    //--------------------------------------------------------------
    flDisplayObject::~flDisplayObject() {
		//if (parent()) ((flDisplayObjectContainer*)parent())->removeChild(this);

        //dispatchEvent(new flEvent(flEvent::DEINIT));

		removeAllEventListeners();

        _target = NULL;
        _name = "";
        
		_stage = NULL;
		_parent = NULL;
        _mask = NULL;
		__maskOwner = NULL;
        
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
        
        delete _rect;
        _rect = NULL;
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _mouseX = 0;
        _mouseY = 0;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flDisplayObject::setup() {
        _setup();
		_afterSetup();
    } 

    //--------------------------------------------------------------
    void flDisplayObject::tearDown() {
        _tearDown();

		dispatchEvent(new flEvent(flEvent::DEINIT));
    }
    
    //--------------------------------------------------------------
    void flDisplayObject::update() {
        _update();        
        _updateRect();
		_afterUpdate();
	}
    
    //--------------------------------------------------------------
    void flDisplayObject::draw(bool applyMatrix) {
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
        //        bool bIdentity = true;
        //        bIdentity = matrix().isIdentity();
        //        bIdentity = false;
        
        if(applyMatrix){
            //            glPushMatrix();
            ofPushMatrix();
            //            glMultMatrixf(matrix().getPtr());
            ofMultMatrix(_transform.__matrix.getPtr());
        }
        
        ofPushStyle();
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _draw();
		_afterDraw();
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

		//------------------------------------------
		if (_mask != NULL) {
			_endUsingStencil();
		}
		//------------------------------------------
    };
    
    //--------------------------------------------------------------
    void flDisplayObject::_setup() {
        
    }

    //--------------------------------------------------------------
    void flDisplayObject::_afterSetup() {
        
    }   

    //--------------------------------------------------------------
    void flDisplayObject::_tearDown() {
        
    }
    
    //--------------------------------------------------------------
    void flDisplayObject::_update() {
        
    }
    
    //--------------------------------------------------------------
    void flDisplayObject::_afterUpdate() {
        
    }
    
    //--------------------------------------------------------------
    void flDisplayObject::_draw() {
        
    }

	//--------------------------------------------------------------
	void flDisplayObject::_afterDraw() {

	}

    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    string flDisplayObject::name() { return _name; }
    void flDisplayObject::name(string value) { _name = value; }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObject::stage() { return _stage; }
    void flDisplayObject::__stage(flDisplayObject* value, bool dispatch) {
        //ofLog() << "[flDisplayObject]__stage(" << value << ")" << name();
        
        //今までステージへの参照がもっていなくてvalueにステージへの参照が入ってる時
		//もともとステージにAddされていなくて、Addされたら
        if(!_stage && value) {
            _stage = value;
            
			if (dispatch) {
				flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
				//event->target(_target);
				//event->_target = _target;
				dispatchEvent(event);
			}
        }

        //既にステージへの参照がもっていてvalueにステージへの参照が入っていない時
		//もともとステージにAddされていて、Removeされたら
        if(_stage && !value) {
            _stage = value;
            
			if (dispatch) {
				flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
				//event->target(_target);
				dispatchEvent(event);
			}
        }
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObject::parent() { return _parent; }
    void flDisplayObject::__parent(flDisplayObject* value, bool dispatch) {
        //ofLog() << "[flDisplayObject]__parent(" << value << ")" << name();
        
        //今まで親への参照がもっていなくてvalueに親への参照が入ってる時
        if(!_parent && value) {
            _parent = value;
            _compoundAlpha = _parent->__compoundAlpha() * _alpha;
            
			if (dispatch) {
				flEvent* event = new flEvent(flEvent::ADDED);
				//event->target(_target);
				dispatchEvent(event);
			}
        }
        //既に親への参照がもっていてvalueに親への参照が入っていない時
        if(_parent && !value) {
            _parent = value;
            
			if (dispatch) {
				flEvent* event = new flEvent(flEvent::REMOVED);
				//event->target(_target);
				dispatchEvent(event);
			}
        }
    }
    
    //--------------------------------------------------------------
    // TODO
	void flDisplayObject::mask(flDisplayObject* value) { 
		if (value == NULL && _mask != NULL) {
			_mask->__maskOwner = NULL;
		}

		_mask = value;
		_mask->__maskOwner = this;
	}
    flDisplayObject* flDisplayObject::mask() { return _mask; }
    
    //--------------------------------------------------------------
    float flDisplayObject::x() { return _transform.__matrix.tx(); }
    void flDisplayObject::x(float value) { _transform.__matrix.tx(value); }
    //--------------------------------------------------------------
    float flDisplayObject::y() { return _transform.__matrix.ty(); }
    void flDisplayObject::y(float value) { _transform.__matrix.ty(value); }
    //--------------------------------------------------------------
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
    float flDisplayObject::width() {
		//if (_mask) return _mask->width();
  //      if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
  //      return _realWidth * scaleX();
		_updateRect();
		if (_mask) return _mask->width();
		if (_realWidth == 0.0) return 0.0;
		return _realWidth * scaleX();
	}
    void flDisplayObject::width(float value) {
        _targetWidth = value;
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
    }
    
    //--------------------------------------------------------------
    float flDisplayObject::height() {
		//if (_mask) return _mask->height();
		//if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
  //      return _realHeight * scaleY();
		_updateRect();
		if (_mask) return _mask->height();
		if (_realHeight == 0.0) return 0.0;
		return _realHeight * scaleY();
    }
    void flDisplayObject::height(float value) {
        _targetHeight = value;
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
    }
    
    //--------------------------------------------------------------
    float flDisplayObject::scaleX() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _transform.__matrix.scaleX();
    }
    void flDisplayObject::scaleX(float value) {
        if (value != 1.0) _targetWidth = numeric_limits<float>::quiet_NaN();
        _transform.__matrix.scaleX(value);
    }
    //--------------------------------------------------------------
    float flDisplayObject::scaleY() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _transform.__matrix.scaleY();
    }
    void flDisplayObject::scaleY(float value) {
        if (value != 1.0) _targetHeight = numeric_limits<float>::quiet_NaN();
        _transform.__matrix.scaleY(value);
    }
    
    //--------------------------------------------------------------
    float flDisplayObject::scaleZ() { return _scaleZ; }
    void flDisplayObject::scaleZ(float value) { _scaleZ = value; }
    
    //--------------------------------------------------------------
    float flDisplayObject::rotation() { return _transform.__matrix.rotation() * RAD_TO_DEG; }
    void flDisplayObject::rotation(float value) { _transform.__matrix.rotate(value * DEG_TO_RAD); }
    //--------------------------------------------------------------
    float flDisplayObject::rotationX() { return _rotationX; }
    void flDisplayObject::rotationX(float value) { _rotationX = value; }
    //--------------------------------------------------------------
    float flDisplayObject::rotationY() { return _rotationY; }
    void flDisplayObject::rotationY(float value) { _rotationY = value; }
    //--------------------------------------------------------------
    float flDisplayObject::rotationZ() { return _rotationZ; }
    void flDisplayObject::rotationZ(float value) { _rotationZ = value; }
    
    //--------------------------------------------------------------
    float flDisplayObject::alpha() { return _alpha; }
    void flDisplayObject::alpha(float value) { _alpha = value; }
    
    //--------------------------------------------------------------
    bool flDisplayObject::visible() { return _visible; }
    void flDisplayObject::visible(bool value) { _visible = value; }
    
    //--------------------------------------------------------------
    int flDisplayObject::blendMode() { return _blendMode; }
    void flDisplayObject::blendMode(int value) {
        if(value < 0 || 13 < value) return;
        _blendMode = value;
    }
    
    //--------------------------------------------------------------
    int flDisplayObject::__level() { return _level; }
    void flDisplayObject::__level(int value) { _level = value; }
    
    //--------------------------------------------------------------
    flTransform& flDisplayObject::transform() { return _transform; }
    void flDisplayObject::transform(const flTransform& value) { _transform = value; }
    
    //--------------------------------------------------------------
//    const flMatrix& flDisplayObject::matrix() { return _matrix; }
//    void flDisplayObject::matrix(const flMatrix& mat) { _matrix = mat; }

    //--------------------------------------------------------------
    // TODO Include a shape line.
    flRectangle flDisplayObject::getBounds(flDisplayObject* targetCoordinateSpace) {
        _tempRect.__setNull();

        {
            //Rect
//            const flRectangle& tempRect = *_graphics->__rect;
            const flRectangle& tempRect = *_rect;
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
        
        return _tempRect;
    }
    
    //--------------------------------------------------------------
    // TODO Not include a shape line.
    flRectangle flDisplayObject::getRect(flDisplayObject* targetCoordinateSpace) {
        //transform child matrix by world matrix.
        
        _tempRect.__setNull();

        {
            //Rect
//            const flRectangle& tempRect = *_graphics->__rect;
            const flRectangle& tempRect = *_rect;
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
        
        return _tempRect;
    }
    
    //--------------------------------------------------------------
    // TODO Not include a shape line.
    flRectangle flDisplayObject::__getRect(flDisplayObject* targetCoordinateSpace) {
        //transform child matrix by world matrix.
        
        float x1 = _rect->left();
        float y1 = _rect->top();
        float x2 = _rect->right();
        float y2 = _rect->bottom();
        
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

        _tempRect.__setNull();
        _tempRect.__encloseRect(_tempPoint1, _tempPoint2, _tempPoint3, _tempPoint4);
        return _tempRect;
    }
    
    
    //--------------------------------------------------------------
    bool flDisplayObject::hitTestObject(flDisplayObject* obj) {
        // TODO - working if two rectangles of different world matrices make any contact.
        return false;
    }
    
    //--------------------------------------------------------------
    bool flDisplayObject::hitTestPoint(float x, float y, bool shapeFlag) {
		//if (_mask != NULL) {
		//	bool isHit = _mask->hitTestPoint(x, y, shapeFlag);
		//	//ofLog() << "hitTestPoint" << isHit;
		//	return isHit;
		//}

        ofPoint p(x, y);
        //Global to local.
        _transform.__concatenatedMatrixInv.transformPoint(p);
        return _rect->pointTest(p.x, p.y);
    }
    
    //--------------------------------------------------------------
    ofPoint flDisplayObject::globalToLocal(const ofPoint& point) {
        ofPoint p = point;
        //グローバル座標からローカル座標に変換
        _transform.__concatenatedMatrixInv.transformPoint(p);
        return p;
    }
    //--------------------------------------------------------------
    ofPoint flDisplayObject::globalToLocal3D(const ofPoint& point) {
        ofPoint p = point;
        _transform.__concatenatedMatrixInv.transformPoint(p);
        return p;
    }
    
    //--------------------------------------------------------------
    ofPoint flDisplayObject::localToGlobal(const ofPoint& point) {
        ofPoint p = point;
        _transform.__concatenatedMatrix.transformPoint(p);
        return p;
    }
    //--------------------------------------------------------------
    ofPoint flDisplayObject::local3DToGlobal(const ofPoint& point) {
        ofPoint p = point;
        _transform.__concatenatedMatrix.transformPoint(p);
        return p;
    }
    
    
    //--------------------------------------------------------------
    bool flDisplayObject::enabledSmoothing() { return _enabledSmoothing; }
    void flDisplayObject::enabledSmoothing(bool value) { _enabledSmoothing = value; }
    
    //--------------------------------------------------------------
    bool flDisplayObject::enabledAntiAliasing() { return _enabledAntiAliasing; }
    void flDisplayObject::enabledAntiAliasing(bool value) { _enabledAntiAliasing = value; }
    
    //--------------------------------------------------------------
    int flDisplayObject::mouseX() {
        // if it has a reference to stage then it must have been added as a child to stage.
        if(_stage) {
            ofPoint p;
            p.x = _stage->mouseX();
            
            _transform.__concatenatedMatrixInv.transformPoint(p);
            //		_mouseX = p.x - _rect->x();
            _mouseX = p.x;
        } else {
            _mouseX = 0;
        }
        return _mouseX;
    }
    //--------------------------------------------------------------
    int flDisplayObject::mouseY() {
        // if it has a reference to stage then it must have been added as a child to stage.
        if(_stage) {
            ofPoint p;
            p.y = _stage->mouseY();
            
            _transform.__concatenatedMatrixInv.transformPoint(p);
            //            _mouseY = p.y - _rect->y();
            _mouseY = p.y;
        } else {
            _mouseY = 0;
        }
        return _mouseY;
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

	//--------------------------------------------------------------
	void flDisplayObject::_beginDrawingStencil() {
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		//set up to draw stencil

		glClear(GL_STENCIL_BUFFER_BIT);
		glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer  
		glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen  
		glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass  
		//Make pixels in the stencil buffer be set to 1 when the stencil test passes  
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//Set all of the pixels below to be 1 in the stencil buffer...  

	}
	//--------------------------------------------------------------
	void flDisplayObject::_beginUsingStencil() {
		//switch from drawing stencil to scene to be masked  

		glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen  
		//Make the stencil test pass only when the pixel is 1 in the stencil buffer  
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change  
		//Draw all pixels where the stencil buffer is 1...  
	}
	//--------------------------------------------------------------
	void flDisplayObject::_endUsingStencil() {
		//back to normal unmasked drawing 
		glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer  

		glPopAttrib();
	}

    //--------------------------------------------------------------
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
        
        
//        _rect->__setNull();
        _rect->__setZero();
        
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
    void flDisplayObject::__updateTransform(const flMatrix& mat) {
        _transform.__concatenatedMatrix = mat;
        _transform.__concatenatedMatrixInv = mat;
        _transform.__concatenatedMatrixInv.invert();
        
        float x1 = _rect->left();
        float y1 = _rect->top();
        float x2 = _rect->right();
        float y2 = _rect->bottom();
        
        _tempPoint1.set(x1, y1);
        _tempPoint2.set(x2, y1);
        _tempPoint3.set(x2, y2);
        _tempPoint4.set(x1, y2);

        mat.transformPoint(_tempPoint1);
        mat.transformPoint(_tempPoint2);
        mat.transformPoint(_tempPoint3);
        mat.transformPoint(_tempPoint4);

        _transform.__updatePixelBounds(_tempPoint1, _tempPoint2, _tempPoint3, _tempPoint4);
    }
    
    //--------------------------------------------------------------
    float flDisplayObject::__compoundAlpha(){ return _compoundAlpha; }
    void flDisplayObject::__compoundAlpha(float value){ _compoundAlpha = value; }

}
