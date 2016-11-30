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
        
        graphics = new Graphics();
    }

    //--------------------------------------------------------------
    //
    Shape::~Shape() {
        //_target = NULL;
        
        delete graphics;
        graphics = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Shape::update() {
        //--------------------------------------
        _rect->__setToRect(*graphics->__rect);
        
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
    void Shape::draw() {
        if(!visible()) return;
        
        //-- matrix transform.
        bool bIdentity = true;
        bIdentity = matrix().isIdentity();
        bIdentity = false;
        
        if(!bIdentity){
            glPushMatrix();
            glMultMatrixf(matrix().getPtr());
        }
        
        glDisable(GL_DEPTH_TEST);
        //ofSetColor(255, 255, 255, __compoundAlpha * 255);
        graphics->__draw();
        _draw();
        
        if(!bIdentity){
            glPopMatrix();
        }
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //TODO
    float Shape::alpha() { return _alpha; }
    void Shape::alpha(float value) {
        _alpha = value;
        graphics->__alpha = _alpha;
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
        
}

