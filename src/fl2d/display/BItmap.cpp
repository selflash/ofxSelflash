
#include "Bitmap.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(BitmapData* bitmapData, string pixelSnapping, bool smoothing) {
//        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap(BitmapData)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 0;
        
        name("Bitmap");
        
        _bitmapData = bitmapData;
        
        _imageWidth = _bitmapData->width();
        _imageHeight = _bitmapData->height();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
//        width(_bitmapData->width());
//        height(_bitmapData->height());
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofImage* image) {
//        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap(ofImage ptr)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 1;
        
        name("Bitmap");
        
        _image_ptr = image;

        _imageWidth = _image_ptr->getWidth();
        _imageHeight = _image_ptr->getHeight();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
//        width(_image_ptr->getWidth());
//        height(_image_ptr->getHeight());
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }
    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofImage image) {
//        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap(ofImage)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 2;
        
        name("Bitmap");

        _image = image;

        _imageWidth = _image.getWidth();
        _imageHeight = _image.getWidth();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
//        width(_image.getWidth());
//        height(_image.getHeight());
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofTexture* texture) {
//        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap(ofTexture ptr)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 3;
        
        name("Bitmap");
        
        _texture_ptr = texture;
        
        _imageWidth = _texture_ptr->getWidth();
        _imageHeight = _texture_ptr->getWidth();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
//        width(_texture_ptr->getWidth());
//        height(_texture_ptr->getHeight());
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }
    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofTexture texture) {
//        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap(ofTexture)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 4;
        
        name("Bitmap");
        
        _texture = texture;
        
        _imageWidth = _texture.getWidth();
        _imageHeight = _texture.getWidth();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
//        width(_texture.getWidth());
//        height(_texture.getHeight());
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofFbo fboImage) {
//        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap(ofFbo)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 5;
        
        name("Bitmap");

        _fboImage = fboImage;
        
        _imageWidth = _fboImage.getWidth();
        _imageHeight = _fboImage.getWidth();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
//        width(_fboImage.getWidth());
//        height(_fboImage.getHeight());
        
        ofRemoveListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Bitmap::~Bitmap() {
//        delete _bitmapData;
        
        _bitmapData = NULL;
        _image_ptr = NULL;
        _texture_ptr = NULL;
        
        ofRemoveListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void Bitmap::_updateEventHandler(ofEventArgs& args) {
        Event* event = new Event(Event::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void Bitmap::draw() {
        if(!visible()) return;
        ofDisableLighting();
        
        //-- matrix transform.
        bool bIdentity = true;
        bIdentity = matrix().isIdentity();
        bIdentity = false;
        
        if(!bIdentity){
            glPushMatrix();
            glMultMatrixf(matrix().getPtr());
        }
        glDisable(GL_DEPTH_TEST);
        
        ofSetColor(255, 255, 255, 255 * __compoundAlpha);
        ofEnableAlphaBlending();
        if(_smoothing) ofEnableSmoothing();
        
        //--------------------------------------
        //draw image
        ofPushStyle();        
        switch(_mode) {
            case 0: _bitmapData->__draw(0, 0); break;
            case 1: _image_ptr->draw(0, 0); break;
            case 2: _image.draw(0, 0); break;
            case 3: _texture_ptr->draw(0, 0); break;
            case 4: _texture.draw(0, 0); break;
            case 5: _fboImage.draw(0, 0); break;
        }
        ofPopStyle();
        //--------------------------------------

        _draw();
        
        ofDisableSmoothing();
        //oFでは標準ではアルファブレンディング有効
        //ofDisableAlphaBlending();
        
        if(!bIdentity){
            glPopMatrix();
        }
    }

    /*
    //--------------------------------------------------------------
    //
    ofTexture& Bitmap::getTextureReference() {
        return bitmapData->getTextureReference();
    }
    */ 

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    //const float Bitmap::width() {
        //_rect->__expandToRect(bitmapImage->__rect());
    //    return _rect->width();
    //}
    //--------------------------------------------------------------
    //
    //const float Bitmap::height() {
        //_rect->__expandToRect(graphics->__rect());
    //    return _rect->height();
    //}

    
    //--------------------------------------------------------------
    //
//    float Bitmap::width() {
//        _updateRect();
//        
//        return _rect->width() * scaleX();
//    }
//    void Bitmap::width(float value) {
////        _updateRect();
//        _rect->width(value);
//    }
//    //--------------------------------------------------------------
//    //
//    float Bitmap::height() {
//        _updateRect();
//        
//        return _rect->height() * scaleY();
//    }
//    void Bitmap::height(float value) {
////        _updateRect();
//        _rect->height(value);
//    }
    
    //--------------------------------------------------------------
    //
    float Bitmap::width() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _realWidth * scaleX();
    }
    void Bitmap::width(float value) {
        _targetWidth = value;
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
    }
    
    //--------------------------------------------------------------
    //
    float Bitmap::height() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _realHeight * scaleY();
    }
    void Bitmap::height(float value) {
        _targetHeight = value;
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
    }
    
    //--------------------------------------------------------------
    //
    float Bitmap::scaleX() {
        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        return _matrix.scaleX();
    }
    void Bitmap::scaleX(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleX(value);
    }
    //--------------------------------------------------------------
    //
    float Bitmap::scaleY() {
        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        return _matrix.scaleY();
    }
    void Bitmap::scaleY(float value) {
        _targetHeight = numeric_limits<float>::quiet_NaN();
        _matrix.scaleY(value);
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    
    //--------------------------------------------------------------
    //
    void Bitmap::_updateRect() {
//        _rect->__setZero();
//        _rect->width(_imageWidth);
//        _rect->height(_imageHeight);
        
        //--------------------------------------
//        _realWidth = _rect->width();
//        _realHeight = _rect->height();
        
//        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
//        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
        //--------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    //void Bitmap::updateOnFrame() {

    //}

    //--------------------------------------------------------------
    //
    //void Bitmap::drawOnFrame() {
    //_drawBitmap();
    //}

}
