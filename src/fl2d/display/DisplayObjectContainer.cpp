#include "DisplayObjectContainer.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    DisplayObjectContainer::DisplayObjectContainer() {
        _typeID = FL_TYPE_DISPLAY_OBJECT_CONTAINER;
        _target = this;
        
        name("DisplayObjectContainer");
        
        _mouseChildren = true;
        //_tabChildren = false;
    }

    //--------------------------------------------------------------
    //
    DisplayObjectContainer::~DisplayObjectContainer() {
        _target = NULL;
        
        children.clear();
        
        _mouseChildren = false;
        //_tabChildren = false;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void DisplayObjectContainer::update() {
    //    float tempLeft = _rect->left();
    //    float tempRight = _rect->right();
    //    float tempTop = _rect->top();
    //    float tempBottom = _rect->bottom();
    //    
    //    _rect->_setToPoint(0, 0);
        
//        int i; int l;
//        DisplayObject* child;
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
        
        //--------------------------------------
        _rect->__setNull();
        
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
        
//        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
        //--------------------------------------
        
        _update();
    }

    //--------------------------------------------------------------
    //
    void DisplayObjectContainer::draw() {
        if(!visible()) return;
        ofDisableLighting();
        
        //-- matrix transform.
        bool bIdentity = true;
        bIdentity = matrix().isIdentity();
        bIdentity = false;
        
        if(!bIdentity) {
            glPushMatrix();
            glMultMatrixf(matrix().getPtr());
        }
        glDisable(GL_DEPTH_TEST);
        
        //ofSetColor(255, 255, 255, __compoundAlpha * 255);
        ofEnableAlphaBlending();
        if(_smoothing) ofEnableSmoothing();
        _draw();
        ofDisableSmoothing();
        //oF„Åß„ÅØÊ®ôÊ∫ñ„Åß„ÅØ„Ç¢„É´„Éï„Ç°„Éñ„É¨„É≥„Éá„Ç£„É≥„Ç∞ÊúâÂäπ
        //ofDisableAlphaBlending();
        
        for(int i = 0; i < children.size(); i++) {
            DisplayObject* child;
            child = children[i];
            //child->drawOnFrame();
            child->draw();
        }
        
        if(!bIdentity) {
            glPopMatrix();
        }
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    bool DisplayObjectContainer::mouseChildren() { return _mouseChildren; }
    void DisplayObjectContainer::mouseChildren(bool value) { _mouseChildren = value; }

    //--------------------------------------------------------------
    //
    int DisplayObjectContainer::numChildren() { return children.size(); }

    //--------------------------------------------------------------
    //
    bool DisplayObjectContainer::contains(DisplayObject* child) {
        for(int i = 0; i < children.size(); i++) {
            if(children[i] == child) return true;
        }
        return false;
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::stage() { return _stage; }
    void DisplayObjectContainer::stage(DisplayObject* value) {
        //cout << "[DisplayObjectContainer]stage(" << value << ")" << name() << endl;
        
        //‰ªä„Åæ„Åß„Çπ„ÉÜ„Éº„Ç∏„Å∏„ÅÆÂèÇÁÖß„Åå„ÇÇ„Å£„Å¶„ÅÑ„Å™„Åè„Å¶value„Å´„Çπ„ÉÜ„Éº„Ç∏„Å∏„ÅÆÂèÇÁÖß„ÅåÂÖ•„Å£„Å¶„ÇãÊôÇ
        if(!_stage && value) {
            _stage = value;
            
            Event* event = new Event(Event::ADDED_TO_STAGE);
            event->target(_target);
            dispatchEvent(event);
        }
        //Êó¢„Å´„Çπ„ÉÜ„Éº„Ç∏„Å∏„ÅÆÂèÇÁÖß„Åå„ÇÇ„Å£„Å¶„ÅÑ„Å¶value„Å´„Çπ„ÉÜ„Éº„Ç∏„Å∏„ÅÆÂèÇÁÖß„ÅåÂÖ•„Å£„Å¶„ÅÑ„Å™„ÅÑÊôÇ
        if(_stage && !value) {
            _stage = value;
            
            Event* event = new Event(Event::REMOVED_FROM_STAGE);
            event->target(_target);
            dispatchEvent(event);
        }
        
        for(int i = 0; i < children.size(); i++) {
            DisplayObject* displayObject = children[i];
            displayObject->stage(_stage);
        }
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::addChild(DisplayObject* child) {
    //    cout << "[DisplayObjectContainer]addChild((" << child->name() << ")" << endl;
        //if(child == NULL) throw "TypeError: Error #2007: „Éë„É©„É°„Éº„Çø„Éº child „ÅØ null ‰ª•Â§ñ„Åß„Å™„Åë„Çå„Å∞„Å™„Çä„Åæ„Åõ„Çì„ÄÇ";
        
        if(child->parent()){
            ((DisplayObjectContainer*)(child->parent()))->removeChild(child);
        }
        
        children.push_back(child);
        child->stage(this->_stage);
        child->parent(this);
        child->level(this->level()+1);
        
        return child;
    }
    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::addChild(DisplayObject* child, int x, int y) {
    //    cout << "[DisplayObjectContainer]addChild(" << child->name() << ", " << x << ", " << y << ")" << endl;
        //if(child == NULL) throw "TypeError: Error #2007: „Éë„É©„É°„Éº„Çø„Éº child „ÅØ null ‰ª•Â§ñ„Åß„Å™„Åë„Çå„Å∞„Å™„Çä„Åæ„Åõ„Çì„ÄÇ";
        
        if(child->parent()){
            ((DisplayObjectContainer*)(child->parent()))->removeChild(child);
        }
        
        children.push_back(child);
        child->x(x);
        child->y(y);
        child->stage(this->_stage);
        child->parent(this);
        child->level(this->level()+1);
        
        return child;
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::addChildAt(DisplayObject* child, int index) {
        //if(child == NULL) throw "TypeError: Error #2007: „Éë„É©„É°„Éº„Çø„Éº child „ÅØ null ‰ª•Â§ñ„Åß„Å™„Åë„Çå„Å∞„Å™„Çä„Åæ„Åõ„Çì„ÄÇ";
        
        if(index < 0 || index > children.size() - 1) return NULL;
        if(child->parent()) {
            ((DisplayObjectContainer*)(child->parent()))->removeChild(child);
        }
        children.insert(children.begin() + index, child);
        child->stage(this->_stage);
        child->parent(this);
        child->level(this->level() + 1);
        
        return child;
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::removeChild(DisplayObject* child) {
        //if(child == NULL) throw "TypeError: Error #2007: „Éë„É©„É°„Éº„Çø„Éº child „ÅØ null ‰ª•Â§ñ„Åß„Å™„Åë„Çå„Å∞„Å™„Çä„Åæ„Åõ„Çì„ÄÇ";
        
        //children()の箇所はリファクタリングとかで外に出したらダメ
        for(int i = 0; i < children.size(); i++){
            if(children[i] == child){
                child->stage(NULL);
                child->parent(NULL);
                child->level(-1);
                children.erase(children.begin() + i);
                return child;
            }
        }
        
        throw "DisplayObjectContainer::removeChild\n";
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::removeChildAt(int index) {
        
        //children()の箇所はリファクタリングとかで外に出したらダメ
        if(index < 0 || index > children.size() - 1) return NULL;
        DisplayObject* child;
        child = children[index];
        child->stage(NULL);
        child->parent(NULL);
        child->level(-1);
        children.erase(children.begin() + index);
        return child;
    }

    //--------------------------------------------------------------
    //
    void DisplayObjectContainer::removeAllChildren() {
        int i = 0;
        int t = children.size();
        
        DisplayObject* child;
        
        for(i; i < t; i++){
            child = children[i];
            child->stage(NULL);
            child->parent(NULL);
            child->level(-1);
            children.erase(children.begin() + i);
            --i;
            --t;
        }
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::getChildAt(int index) {
        if(index < 0 || index > children.size() - 1) return NULL;
        return children[index];
    }

    //--------------------------------------------------------------
    //
    DisplayObject* DisplayObjectContainer::getChildByName(string name) {
        for(int i = 0; i < children.size(); i++){
            if(children[i]->name() == name) return children[i];
        }
        
        return NULL;
    }

    //--------------------------------------------------------------
    //
    int DisplayObjectContainer::getChildIndex(DisplayObject* child) {
        for(int i = 0; i < children.size(); i++){
            if(children[i] == child) return i;
        }
        
        return -1;
    }

    //--------------------------------------------------------------
    //
    vector<DisplayObject*> DisplayObjectContainer::getObjectsUnderPoint(ofPoint point) {
        // TODO Êú™ÂÆüË£Ö
        return children;
    }

    //--------------------------------------------------------------
    //
    void DisplayObjectContainer::setChildIndex(DisplayObject* child, int index) {
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
    //
    void DisplayObjectContainer::swapChildren(DisplayObject* child1, DisplayObject* child2) {
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
    //
    void DisplayObjectContainer::swapChildrenAt(int index1, int index2) {
        if(index1 == index2) return;
        
        DisplayObject* child1 = getChildAt(index1);
        DisplayObject* child2 = getChildAt(index2);
        
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
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    bool DisplayObjectContainer::_hasChildren(DisplayObject* displayObject) {
        bool b;
        b = false;
        b = b || (displayObject->typeID() == FL_TYPE_DISPLAY_OBJECT_CONTAINER);
        b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
        b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
        
        return b;
    }

}
