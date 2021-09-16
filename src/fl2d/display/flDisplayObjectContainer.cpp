#include "flDisplayObjectContainer.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flDisplayObjectContainer::flDisplayObjectContainer() {
        _typeID = FL_TYPE_DISPLAY_OBJECT_CONTAINER;
        _target = this;        
        name("flDisplayObjectContainer");
        
        _mouseChildren = true;
        //_tabChildren = false;
    }
    
    //--------------------------------------------------------------
    flDisplayObjectContainer::~flDisplayObjectContainer() {
        _target = NULL;
        
		//for (auto& child : children) {
		//	if(contains(child)) removeChild(child);
		//	delete child;
		//}
		//removeAllChildren();
		//for (auto& child : children) {
		//	delete child;
		//}

		int i = 0;
		int l = children.size();
		flDisplayObject* child = NULL;
		for (i; i < l; i++) {
			child = children[i];
			child->removeAllEventListeners();
			child->stage(NULL);
			child->parent(NULL);
			child->level(-1);
			delete child;

			children.erase(children.begin() + i);
			--i;
			--l;
		}
        children.clear();
        
        _mouseChildren = false;
        //_tabChildren = false;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flDisplayObjectContainer::update() {
        //    float tempLeft = _rect->left();
        //    float tempRight = _rect->right();
        //    float tempTop = _rect->top();
        //    float tempBottom = _rect->bottom();
        //    
        //    _rect->_setToPoint(0, 0);
        
        //        int i; int l;
        //        flDisplayObject* child;
        //        
        //        l = children.size();
        //        for(i = 0; i < l; i++) {
        //            child = children[i];
        //            float n1 = child->x();
        //            float n2 = child->y();
        //            _rect->__expandTo(n1, n2);
        //            _rect->__expandTo(n1 + child->width(), n2 + child->height());
        //        }
        //    _rect->__expandTo(tempLeft, tempTop);
        //    _rect->__expandTo(tempRight, tempBottom);
        
        flDisplayObject::update();        
    }
    
    //--------------------------------------------------------------
    void flDisplayObjectContainer::draw(bool applyMatrix) {
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
        
        if(applyMatrix){
            //glPushMatrix();
            ofPushMatrix();
            //glMultMatrixf(matrix().getPtr());
            ofMultMatrix(_transform.matrix().getPtr());
        }
        
        ofPushStyle();
        //ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _draw();
        
        for(int i = 0; i < children.size(); i++) {
            flDisplayObject* child;
            child = children[i];
            //child->drawOnFrame();
            child->draw();
        }
        ofPopStyle();
        
        if(applyMatrix){
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

		//------------------------------------------
		if (_mask != NULL) {
			_endUsingStencil();
		}
		//------------------------------------------
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    bool flDisplayObjectContainer::mouseChildren() { return _mouseChildren; }
    void flDisplayObjectContainer::mouseChildren(bool value) { _mouseChildren = value; }
    
    //--------------------------------------------------------------
    int flDisplayObjectContainer::numChildren() { return children.size(); }
    
    //--------------------------------------------------------------
    bool flDisplayObjectContainer::contains(flDisplayObject* child) {
        for(int i = 0; i < children.size(); i++) {
            if(children[i] == child) return true;
        }
        return false;
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::stage() { return _stage; }
    void flDisplayObjectContainer::stage(flDisplayObject* value) {
        //cout << "[flDisplayObjectContainer]stage(" << value << ")" << name() << endl;
        
        //もともとステージにAddされていなくて、Addされたら
        if(!_stage && value) {
            _stage = value;
            
			for (int i = 0; i < children.size(); i++) {
				flDisplayObject* child = children[i];
				child->stage(_stage);

				flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
				child->dispatchEvent(event);
			}

            flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
            dispatchEvent(event);
        }

		//もともとステージにAddされていて、Removeされたら
		if(_stage && !value) {
            _stage = value;
            
			for (int i = 0; i < children.size(); i++) {
				flDisplayObject* child = children[i];
				child->stage(_stage);

				flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
				child->dispatchEvent(event);
			}

            flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
            dispatchEvent(event);
        }        
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::addChild(flDisplayObject* child) {
        //    cout << "[flDisplayObjectContainer]addChild((" << child->name() << ")" << endl;
        //if(child == NULL) throw "TypeError: Error #2007: ° child  null ‰§∞";
        
		//bool isChild = contains(child);

        if(child->parent()){
            ((flDisplayObjectContainer*)(child->parent()))->_removeChild(child);
        }
        
        children.push_back(child);
        child->stage(this->_stage);
        child->parent(this);
        child->level(this->level()+1);
        
        _updateRect();

		if (!child->hasEventListener(flEvent::DEINIT)) {
			child->addEventListener(flEvent::DEINIT, this, &flDisplayObjectContainer::_childEventHandler);
		}

		//if (!isChild) {
		//	flEvent* event = new flEvent(flEvent::ADDED);
		//	child->dispatchEvent(event);
		//}

		//bool onStage = bool(_stage != NULL);
		//if (onStage) {
		//	flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
		//	child->dispatchEvent(event);
		//}
        
        return child;
    }
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::addChild(flDisplayObject* child, int x, int y) {
        //    cout << "[flDisplayObjectContainer]addChild(" << child->name() << ", " << x << ", " << y << ")" << endl;
        //if(child == NULL) throw "TypeError: Error #2007: ° child  null ‰§∞";
        
		//bool isChild = contains(child);

        if(child->parent()){
            ((flDisplayObjectContainer*)(child->parent()))->_removeChild(child);
        }
        
        children.push_back(child);
        child->x(x);
        child->y(y);
        child->stage(this->_stage);
        child->parent(this);
        child->level(this->level()+1);
        
        _updateRect();

		if (!child->hasEventListener(flEvent::DEINIT)) {
			child->addEventListener(flEvent::DEINIT, this, &flDisplayObjectContainer::_childEventHandler);
		}

		//if (!isChild) {
		//	flEvent* event = new flEvent(flEvent::ADDED);
		//	child->dispatchEvent(event);
		//}	

		//bool onStage = bool(_stage != NULL);
		//if (onStage) {
		//	flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
		//	child->dispatchEvent(event);
		//}
        
        return child;
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::addChildAt(flDisplayObject* child, int index) {
        //if(child == NULL) throw "TypeError: Error #2007: ° child  null ‰§∞";
        
        if(index < 0 || index > children.size() - 1) return NULL;

		//bool isChild = contains(child);

        if(child->parent()) {
            ((flDisplayObjectContainer*)(child->parent()))->_removeChild(child);
        }

        children.insert(children.begin() + index, child);
        child->stage(this->_stage);
        child->parent(this);
        child->level(this->level() + 1);
        
        _updateRect();

		if (!child->hasEventListener(flEvent::DEINIT)) {
			child->addEventListener(flEvent::DEINIT, this, &flDisplayObjectContainer::_childEventHandler);
		}

		//if (!isChild) {
		//	flEvent* event = new flEvent(flEvent::ADDED);
		//	child->dispatchEvent(event);
		//}

		//bool onStage = bool(_stage != NULL);
		//if (onStage) {
		//	flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
		//	child->dispatchEvent(event);
		//}
        
        return child;
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::removeChild(flDisplayObject* child) {
        //if(child == NULL) throw "TypeError: Error #2007: ° child  null ‰§∞";
        
        //children.size()の箇所はリファクタリングとかで外に出したらダメ
        for(int i = 0; i < children.size(); i++){
            if(children[i] == child){
                child->stage(NULL);
                child->parent(NULL);
                child->level(-1);
				//if (child->hasEventListener(flEvent::FINALIZE)) {
				//	child->removeEventListener(flEvent::FINALIZE, this, &flDisplayObjectContainer::_childEventHandler);
				//}
                children.erase(children.begin() + i);
                
                _updateRect();

				//flEvent* event = new flEvent(flEvent::REMOVED);
				//child->dispatchEvent(event);

				//bool onStage = bool(_stage != NULL);
				//if (onStage) {
				//	flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
				//	child->dispatchEvent(event);
				//}
                
                return child;
            }
        }
        
        throw "flDisplayObjectContainer::removeChild\n";
    }

	//--------------------------------------------------------------
	flDisplayObject* flDisplayObjectContainer::_removeChild(flDisplayObject* child) {
		//if(child == NULL) throw "TypeError: Error #2007: ° child  null ‰§∞";

		//children.size()の箇所はリファクタリングとかで外に出したらダメ
		for (int i = 0; i < children.size(); i++) {
			if (children[i] == child) {
				//child->stage(NULL);
				//child->parent(NULL);
				//child->level(-1);
				//if (child->hasEventListener(flEvent::FINALIZE)) {
				//	child->removeEventListener(flEvent::FINALIZE, this, &flDisplayObjectContainer::_childEventHandler);
				//}
				children.erase(children.begin() + i);

				_updateRect();

				return child;
			}
		}

		throw "flDisplayObjectContainer::_removeChild\n";
	}
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::removeChildAt(int index) {
        
        //children.size()の箇所はリファクタリングとかで外に出したらダメ
        if(index < 0 || index > children.size() - 1) return NULL;
        flDisplayObject* child;
        child = children[index];
        child->stage(NULL);
        child->parent(NULL);
        child->level(-1);
		//if (child->hasEventListener(flEvent::FINALIZE)) {
		//	child->removeEventListener(flEvent::FINALIZE, this, &flDisplayObjectContainer::_childEventHandler);
		//}
		children.erase(children.begin() + index);
        
        _updateRect();

		//flEvent* event = new flEvent(flEvent::REMOVED);
		//child->dispatchEvent(event);

		//bool onStage = bool(_stage != NULL);
		//if (onStage) {
		//	flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
		//	child->dispatchEvent(event);
		//}
        
        return child;
    }
    
    //--------------------------------------------------------------
    void flDisplayObjectContainer::removeAllChildren() {
        int i = 0;
        int l = children.size();
        
        flDisplayObject* child;
        
        for(i; i < l; i++){
            child = children[i];
            child->stage(NULL);
            child->parent(NULL);
            child->level(-1);
			//if (child->hasEventListener(flEvent::FINALIZE)) {
			//	child->removeEventListener(flEvent::FINALIZE, this, &flDisplayObjectContainer::_childEventHandler);
			//}
			children.erase(children.begin() + i);

			//flEvent* event = new flEvent(flEvent::REMOVED);
			//child->dispatchEvent(event);

			//bool onStage = bool(_stage != NULL);
			//if (onStage) {
			//	flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
			//	child->dispatchEvent(event);
			//}

            --i;
            --l;
        }
        
        _updateRect();        
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::getChildAt(int index) {
        if(index < 0 || index > children.size() - 1) return NULL;
        return children[index];
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flDisplayObjectContainer::getChildByName(string name) {
        for(int i = 0; i < children.size(); i++){
            if(children[i]->name() == name) return children[i];
        }
        
        return NULL;
    }
    
    //--------------------------------------------------------------
    int flDisplayObjectContainer::getChildIndex(flDisplayObject* child) {
        for(int i = 0; i < children.size(); i++){
            if(children[i] == child) return i;
        }
        
        return -1;
    }
    
    //--------------------------------------------------------------
    vector<flDisplayObject*> flDisplayObjectContainer::getObjectsUnderPoint(ofPoint point) {
        // TODO ￡
        return children;
    }
    
    //--------------------------------------------------------------
    void flDisplayObjectContainer::setChildIndex(flDisplayObject* child, int index) {
        if(index < 0 || index > children.size() - 1) return;
        
        for(int i = 0; i < children.size(); i++){
            if(children[i] == child){
                children.erase(children.begin() + i);
                children.insert(children.begin() + index, child);
                return;
            }
        }
    }
    
    //--------------------------------------------------------------
    void flDisplayObjectContainer::swapChildren(flDisplayObject* child1, flDisplayObject* child2) {
        int index1 = getChildIndex(child1);
        int index2 = getChildIndex(child2);
        
        if(index1 == -1 || index2 == -1) return;
        
        for(int i = 0; i < children.size(); i++){
            if(children[i] == child1 || children[i] == child2) {
                children.erase(children.begin() + i--);
            }
        }
        
        if(index1 < index2){
            children.insert(children.begin() + index1, child2);
            children.insert(children.begin() + index2, child1);
        } else {
            children.insert(children.begin() + index2, child1);
            children.insert(children.begin() + index1, child2);
        }
    }
    
    //--------------------------------------------------------------
    void flDisplayObjectContainer::swapChildrenAt(int index1, int index2) {
        if(index1 == index2) return;
        
        flDisplayObject* child1 = getChildAt(index1);
        flDisplayObject* child2 = getChildAt(index2);
        
        if(child1 == NULL || child2 == NULL) return;
        
        if(index2 > index1){
            children.erase(children.begin() + index2);
            children.erase(children.begin() + index1);
        } else {
            children.erase(children.begin() + index1);
            children.erase(children.begin() + index2);
        }
        
        if(index1 < index2){
            children.insert(children.begin() + index1, child2);
            children.insert(children.begin() + index2, child1);
        } else {
            children.insert(children.begin() + index2, child1);
            children.insert(children.begin() + index1, child2);
        }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flDisplayObjectContainer::_updateRect() {
//        _hitAreaRect->__setNull();
        _rect->__setZero();
        
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
    bool flDisplayObjectContainer::_hasChildren(flDisplayObject* displayObject) {
        bool b;
        b = false;
        b = b || (displayObject->typeID() == FL_TYPE_DISPLAY_OBJECT_CONTAINER);
        b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
        b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
        b = b || (displayObject->typeID() == FL_TYPE_UIBASE);

        return b;
    }

	//==============================================================
	// Protected / Private Event Handler
	//==============================================================

	//--------------------------------------------------------------
	void flDisplayObjectContainer::_childEventHandler(flEvent& event) {
		//ofLog() << "[flDisplayObjectContainer]_childEventHandler(" << event.type() << ")";
		//ofLog() << "[flDisplayObjectContainer]this          = " << this << "," << ((flDisplayObject*)this)->name();
		//ofLog() << "[flDisplayObjectContainer]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
		//ofLog() << "[flDisplayObjectContainer]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();

		if (event.type() == flEvent::ADDED) {
			if (event.target() == this) {

			}
			else {

			}
		}
		else if (event.type() == flEvent::ADDED_TO_STAGE) {
			if (event.target() == this) {

			}
			else {

			}
		}
		else if (event.type() == flEvent::REMOVED) {
			if (event.target() == this) {

			}
			else {
				flEvent* event_ = new flEvent(flEvent::REMOVED);
				event_->__target = event.target();
				dispatchEvent(event_);
			}
		}
		else if (event.type() == flEvent::DEINIT) {
			if (event.target() == this) {

			}
			else {
				flDisplayObject* child = ((flDisplayObject*)event.target());
				//if (child->hasEventListener(flEvent::FINALIZE)) {
					child->removeEventListener(flEvent::DEINIT, this, &flDisplayObjectContainer::_childEventHandler);
				//}

				flEvent* event_ = new flEvent(flEvent::DEINIT);
				event_->__target = child;
				dispatchEvent(event_);
			}
		}
	}

}
