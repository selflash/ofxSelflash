#include "flShape.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flShape::flShape() {
        _typeID = FL_TYPE_SHAPE;
        //_target = this;
        
        name("flShape");
        
        _graphics = new flGraphics();
        
        ofAddListener(ofEvents().update, this, &flShape::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    flShape::~flShape() {
        //_target = NULL;
        
        delete _graphics;
        _graphics = NULL;
        
        ofRemoveListener(ofEvents().update, this, &flShape::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void flShape::_updateEventHandler(ofEventArgs& args) {
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flShape::update() {
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
    void flShape::draw(bool applyMatrix) {
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
        _graphics->__draw();
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
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //TODO
    //    float flShape::alpha() { return _alpha; }
    //    void flShape::alpha(float value) {
    //        _alpha = value;
    //        _graphics->__alpha = _alpha;
    //    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flShape::_updateRect() {
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
    void flShape::__compoundAlpha(float value){
        _compoundAlpha = value;
        _graphics->__compoundAlpha(_compoundAlpha);
    }
}

