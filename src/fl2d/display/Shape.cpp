#include "Shape.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Shape::Shape() {
        _typeID = FL_TYPE_SHAPE;
        //_target = this;
        
        name("Shape");
        
        _graphics = new Graphics();
        
        ofAddListener(ofEvents().update, this, &Shape::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Shape::~Shape() {
        //_target = NULL;
        
        delete _graphics;
        _graphics = NULL;
        
        ofRemoveListener(ofEvents().update, this, &Shape::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    void Shape::_updateEventHandler(ofEventArgs& args) {
        Event* event = new Event(Event::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Shape::update() {
        //--------------------------------------
        _rect->__setToRect(*_graphics->__rect);
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        
        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
//        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
        //--------------------------------------
        
        _update();
        
        _updateRect();
    }
    
    //--------------------------------------------------------------
    //
    void Shape::draw() {
        if(!visible()) return;
        
        GLboolean preLighting = glIsEnabled(GL_LIGHTING);
        GLboolean preBlendmodeAlpha = glIsEnabled(OF_BLENDMODE_ALPHA);
        GLboolean preDepthTest = glIsEnabled(GL_DEPTH_TEST);
        GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
        GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
        
        ofDisableLighting();
        ofEnableAlphaBlending();
        glDisable(GL_DEPTH_TEST);
        if(_enabledSmoothing) { ofEnableSmoothing(); }
        if(_enabledAntiAliasing) { ofEnableAntiAliasing(); }
        
        //------------------------------------------
        //-- matrix transform.
        bool bIdentity = true;
        bIdentity = matrix().isIdentity();
        bIdentity = false;
        
        if(!bIdentity){
            glPushMatrix();
            glMultMatrixf(matrix().getPtr());
        }
        
        ofPushStyle();
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _graphics->__draw();
        _draw();
        ofPopStyle();
        
        if(!bIdentity){
            glPopMatrix();
        }
        //------------------------------------------
        
        if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
        if(preBlendmodeAlpha == GL_TRUE) { ofEnableAlphaBlending(); } else { ofDisableAlphaBlending(); }
        if(preLighting == GL_TRUE) { ofEnableLighting(); } else { ofDisableLighting(); }
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //TODO
//    float Shape::alpha() { return _alpha; }
//    void Shape::alpha(float value) {
//        _alpha = value;
//        _graphics->__alpha = _alpha;
//    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Shape::_updateRect() {
        _rect->__setToRect(*_graphics->__rect);
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        
        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
//        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
    }

    //--------------------------------------------------------------
    //
    void Shape::__compoundAlpha(float value){
        _compoundAlpha = value;
        _graphics->__compoundAlpha(_compoundAlpha);
    }
}

