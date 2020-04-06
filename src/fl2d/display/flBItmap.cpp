
#include "flBitmap.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
//    template <class T>
//    virtual void flBitmap::data<T>(T* value) {
//
//    }
    void flBitmap::data(ofTexture* value) {
        if(_mode == 1) {
            delete _bitmapData;
            _bitmapData = NULL;
        }
        else if(_mode == 2) {
            _image_ptr = NULL;
        }
        else if(_mode == 3) {
            _image.clear();
        }
        else if(_mode == 5) {
            _texture.clear();
        }
        
        _mode = 4;
        _texture_ptr = value;

		_isAllocated = _texture_ptr->isAllocated();

		if(_isAllocated) 
		{
			_imageWidth = _texture_ptr->getWidth();
			_imageHeight = _texture_ptr->getHeight();
			_hitAreaRect->width(_imageWidth);
			_hitAreaRect->height(_imageHeight);
			_realWidth = _hitAreaRect->width();
			_realHeight = _hitAreaRect->height();

			cout << "_imageHeight = " << _imageHeight << endl;
			cout << "_targetWidth = " << _targetWidth << endl;
			cout << "isnan(_targetWidth) = " << isnan(_targetWidth) << endl;

			if (!isnan(_targetWidth)) {
				scaleX(_targetWidth / _realWidth);
			}
			if (!isnan(_targetHeight)) {
				scaleY(_targetHeight / _realHeight);
			}
		}
		else {
			_imageWidth = 0;
			_imageHeight = 0;
			_hitAreaRect->width(_imageWidth);
			_hitAreaRect->height(_imageHeight);
			_realWidth = _hitAreaRect->width();
			_realHeight = _hitAreaRect->height();
		}
        
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap() {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap()" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 0;
        
        name("flBitmap");
        
        _imageWidth = 0;
        _imageHeight = 0;
        _realWidth = 0;
        _realHeight = 0;
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(flBitmapData* bitmapData, string pixelSnapping, bool smoothing) {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap(flBitmapData)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 1;
        
        name("flBitmap");
        
        _bitmapData = bitmapData;
        
        _imageWidth = _bitmapData->width();
        _imageHeight = _bitmapData->height();
        _hitAreaRect->width(_imageWidth);
        _hitAreaRect->height(_imageHeight);
        _realWidth = _hitAreaRect->width();
        _realHeight = _hitAreaRect->height();
        //TODO
        //        width(_bitmapData->width());
        //        height(_bitmapData->height());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofImage* image) {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap(ofImage ptr)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 2;
        
        name("flBitmap");
        
        _image_ptr = image;
        
        _imageWidth = _image_ptr->getWidth();
        _imageHeight = _image_ptr->getHeight();
        _hitAreaRect->width(_imageWidth);
        _hitAreaRect->height(_imageHeight);
        _realWidth = _hitAreaRect->width();
        _realHeight = _hitAreaRect->height();
        //TODO
        //        width(_image_ptr->getWidth());
        //        height(_image_ptr->getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofImage image) {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap(ofImage)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 3;
        
        name("flBitmap");
        
        _image = image;
        
        _imageWidth = _image.getWidth();
        _imageHeight = _image.getHeight();
        _hitAreaRect->width(_imageWidth);
        _hitAreaRect->height(_imageHeight);
        _realWidth = _hitAreaRect->width();
        _realHeight = _hitAreaRect->height();
        //TODO
        //        width(_image.getWidth());
        //        height(_image.getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofTexture* texture) {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap(ofTexture ptr)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 4;
        
        name("flBitmap");
        
        _texture_ptr = texture;
        
        _imageWidth = _texture_ptr->getWidth();
        _imageHeight = _texture_ptr->getHeight();
        _hitAreaRect->width(_imageWidth);
        _hitAreaRect->height(_imageHeight);
        _realWidth = _hitAreaRect->width();
        _realHeight = _hitAreaRect->height();
        //TODO
        //        width(_texture_ptr->getWidth());
        //        height(_texture_ptr->getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofTexture texture) {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap(ofTexture)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 5;
        
        name("flBitmap");
        
        _texture = texture;
        
        _imageWidth = _texture.getWidth();
        _imageHeight = _texture.getHeight();
        _hitAreaRect->width(_imageWidth);
        _hitAreaRect->height(_imageHeight);
        _realWidth = _hitAreaRect->width();
        _realHeight = _hitAreaRect->height();
        //TODO
        //        width(_texture.getWidth());
        //        height(_texture.getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofFbo fboImage) {
        //        debug(true);
        if(debug()) cout << "[flBitmap]flBitmap(ofFbo)" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 6;
        
        name("flBitmap");
        
        _fboImage = fboImage;
        
        _imageWidth = _fboImage.getWidth();
        _imageHeight = _fboImage.getHeight();
        _hitAreaRect->width(_imageWidth);
        _hitAreaRect->height(_imageHeight);
        _realWidth = _hitAreaRect->width();
        _realHeight = _hitAreaRect->height();
        //TODO
        //        width(_fboImage.getWidth());
        //        height(_fboImage.getHeight());
        
        ofRemoveListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::~flBitmap() {
        //        delete _bitmapData;
        
        _bitmapData = NULL;
        _image_ptr = NULL;
        _texture_ptr = NULL;
        
        ofRemoveListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    void flBitmap::_updateEventHandler(ofEventArgs& args) {
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //    //--------------------------------------------------------------
    //    //
    //    void flBitmap::draw() {
    //        if(!visible()) return;
    //
    //        GLboolean preLighting = glIsEnabled(GL_LIGHTING);
    //        GLboolean preBlendmodeAlpha = glIsEnabled(OF_BLENDMODE_ALPHA);
    //        GLboolean preDepthTest = glIsEnabled(GL_DEPTH_TEST);
    //        GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
    //        GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
    //        
    //        ofDisableLighting();
    //        ofEnableAlphaBlending();
    //        glDisable(GL_DEPTH_TEST);
    //        if(_smoothing) {
    //            ofEnableSmoothing();
    //            ofEnableAntiAliasing();
    //        }
    //        
    //        //------------------------------------------
    //        //-- matrix transform.
    //        bool bIdentity = true;
    //        bIdentity = matrix().isIdentity();
    //        bIdentity = false;
    //        
    //        if(!bIdentity){
    //            glPushMatrix();
    //            glMultMatrixf(matrix().getPtr());
    //        }
    //        
    //        ofPushStyle();
    //        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
    //        _draw();
    //        ofPopStyle();
    //        
    //        if(!bIdentity){
    //            glPopMatrix();
    //        }
    //        //------------------------------------------
    //        
    //        if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
    //        if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
    //        if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
    //        if(preBlendmodeAlpha == GL_TRUE) { ofEnableAlphaBlending(); } else { ofDisableAlphaBlending(); }
    //        if(preLighting == GL_TRUE) { ofEnableLighting(); } else { ofDisableLighting(); }
    //    }
    
	void flBitmap::_update() {
//        flDisplayObject::update();

		if (!_isAllocated)
		{
			switch (_mode) {
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: 
				_isAllocated = _texture_ptr->isAllocated();
				if (_isAllocated) {
					_imageWidth = _texture_ptr->getWidth();
					_imageHeight = _texture_ptr->getHeight();
					_hitAreaRect->width(_imageWidth);
					_hitAreaRect->height(_imageHeight);
					_realWidth = _hitAreaRect->width();
					_realHeight = _hitAreaRect->height();

					if (!isnan(_targetWidth)) {
						scaleX(_targetWidth / _realWidth);
					}
					if (!isnan(_targetHeight)) {
						scaleY(_targetHeight / _realHeight);
					}
				}
				break;
			case 5: break;
			case 6: break;
			}
		}
	}

    //--------------------------------------------------------------
    void flBitmap::_draw() {
        //--------------------------------------
        //draw image
        //        cout << "_mode = " << _mode << endl;
        switch(_mode) {
            case 1: _bitmapData->__draw(0, 0); break;
            case 2: if(_image_ptr->isAllocated()) _image_ptr->draw(0, 0); break;
            case 3: if (_image.isAllocated()) _image.draw(0, 0); break;
            case 4: if (_texture_ptr->isAllocated()) _texture_ptr->draw(0, 0); break;
            case 5: if (_texture.isAllocated()) _texture.draw(0, 0); break;
            case 6: if (_fboImage.isAllocated()) _fboImage.draw(0, 0); break;
        }
        //--------------------------------------
    }
    
    /*
     //--------------------------------------------------------------
     //
     ofTexture& flBitmap::getTextureReference() {
     return bitmapData->getTextureReference();
     }
     */ 
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //const float flBitmap::width() {
    //_rect->__expandToRect(bitmapImage->__rect());
    //    return _rect->width();
    //}
    //--------------------------------------------------------------
    //const float flBitmap::height() {
    //_rect->__expandToRect(graphics->__rect());
    //    return _rect->height();
    //}
    
    
    //--------------------------------------------------------------
    //    float flBitmap::width() {
    //        _updateRect();
    //        
    //        return _rect->width() * scaleX();
    //    }
    //    void flBitmap::width(float value) {
    ////        _updateRect();
    //        _rect->width(value);
    //    }
    //    //--------------------------------------------------------------
    //    //
    //    float flBitmap::height() {
    //        _updateRect();
    //        
    //        return _rect->height() * scaleY();
    //    }
    //    void flBitmap::height(float value) {
    ////        _updateRect();
    //        _rect->height(value);
    //    }
    
//    //--------------------------------------------------------------
//    float flBitmap::width() {
//        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        return _realWidth * scaleX();
//    }
//    void flBitmap::width(float value) {
//        _targetWidth = value;
//        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//    }
//    
//    //--------------------------------------------------------------
//    float flBitmap::height() {
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleX(_targetHeight / _realHeight);
//        return _realHeight * scaleY();
//    }
//    void flBitmap::height(float value) {
//        _targetHeight = value;
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleX(_targetHeight / _realHeight);
//    }
    
//    //--------------------------------------------------------------
//    float flBitmap::scaleX() {
//        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        return _matrix.scaleX();
//    }
//    void flBitmap::scaleX(float value) {
//        _targetWidth = numeric_limits<float>::quiet_NaN();
//        _matrix.scaleX(value);
//    }
//    //--------------------------------------------------------------
//    float flBitmap::scaleY() {
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleX(_targetHeight / _realHeight);
//        return _matrix.scaleY();
//    }
//    void flBitmap::scaleY(float value) {
//        _targetHeight = numeric_limits<float>::quiet_NaN();
//        _matrix.scaleY(value);
//    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    
    //--------------------------------------------------------------
    void flBitmap::_updateRect() {
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
    //void flBitmap::updateOnFrame() {
    
    //}
    
    //--------------------------------------------------------------
    //void flBitmap::drawOnFrame() {
    //_drawBitmap();
    //}
    
}
