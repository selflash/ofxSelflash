
#include "flBitmap.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
       
    //--------------------------------------------------------------
    flBitmap::flBitmap() {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap()";

		_typeID = FL_TYPE_BITMAP;
		_target = this;
		_dataType = BITMAPDATA_TYPE_BITMAPDATA;

		name("flBitmap");

		_bitmapDataPtr = &_bitmapData;

		_imageWidth = _bitmapDataPtr->width();
		_imageHeight = _bitmapDataPtr->height();
		_rect->width(_imageWidth);
		_rect->height(_imageHeight);
		_realWidth = _rect->width();
		_realHeight = _rect->height();
		//TODO
		//        width(_bitmapDataPtr->width());
		//        height(_bitmapDataPtr->height());

		ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(flBitmapData* bitmapData, string pixelSnapping, bool smoothing) {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap(flBitmapData)";
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
		_dataType = BITMAPDATA_TYPE_BITMAPDATA;
        
        name("flBitmap");
        
        _bitmapDataPtr = bitmapData;
        
        _imageWidth = _bitmapDataPtr->width();
        _imageHeight = _bitmapDataPtr->height();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
        //        width(_bitmapDataPtr->width());
        //        height(_bitmapDataPtr->height());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofImage* image) {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap(ofImage ptr)";
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
		_dataType = BITMAPDATA_TYPE_OF_IMAGE;
        
        name("flBitmap");
        
        _imagePtr = image;
        
        _imageWidth = _imagePtr->getWidth();
        _imageHeight = _imagePtr->getHeight();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
        //        width(_imagePtr->getWidth());
        //        height(_imagePtr->getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofImage image) {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap(ofImage)";
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
		_dataType = BITMAPDATA_TYPE_OF_IMAGE;
        
        name("flBitmap");
        
        _image = image;
		_imagePtr = &_image;

		_imageWidth = _imagePtr->getWidth();
		_imageHeight = _imagePtr->getHeight();
		_rect->width(_imageWidth);
		_rect->height(_imageHeight);
		_realWidth = _rect->width();
		_realHeight = _rect->height();
		//TODO
        //        width(_image.getWidth());
        //        height(_image.getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofTexture* texture) {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap(ofTexture ptr)";
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
		_dataType = BITMAPDATA_TYPE_OF_TEXTURE;
        
        name("flBitmap");
        
        _texturePtr = texture;
        
        _imageWidth = _texturePtr->getWidth();
        _imageHeight = _texturePtr->getHeight();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
        //        width(_texturePtr->getWidth());
        //        height(_texturePtr->getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofTexture texture) {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap(ofTexture)";
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
		_dataType = BITMAPDATA_TYPE_OF_TEXTURE;
        
        name("flBitmap");
        
        _texture = texture;
		_texturePtr = &_texture;

		_imageWidth = _texturePtr->getWidth();
		_imageHeight = _texturePtr->getHeight();
		_rect->width(_imageWidth);
		_rect->height(_imageHeight);
		_realWidth = _rect->width();
		_realHeight = _rect->height();
		//TODO
        //        width(_texture.getWidth());
        //        height(_texture.getHeight());
        
        ofAddListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::flBitmap(ofFbo fboImage) {
        //        debug(true);
        if(debug()) ofLog() << "[flBitmap]flBitmap(ofFbo)";
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
		_dataType = BITMAPDATA_TYPE_OF_FBO;
        
        name("flBitmap");
        
        _fboImage = fboImage;
        
        _imageWidth = _fboImage.getWidth();
        _imageHeight = _fboImage.getHeight();
        _rect->width(_imageWidth);
        _rect->height(_imageHeight);
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //TODO
        //        width(_fboImage.getWidth());
        //        height(_fboImage.getHeight());
        
        ofRemoveListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    flBitmap::~flBitmap() {
        //        delete _bitmapDataPtr;
        
        _bitmapDataPtr = NULL;
        _imagePtr = NULL;
        _texturePtr = NULL;
        
        ofRemoveListener(ofEvents().update, this, &flBitmap::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    void flBitmap::_updateEventHandler(ofEventArgs& args) {
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // Setup / Update / Draw
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
		if (!_isAllocated)
		{
			//Update width, height, scaleX, scaleY.
			switch (_dataType) {
				case BITMAPDATA_TYPE_BITMAPDATA: break;
				case BITMAPDATA_TYPE_OF_IMAGE: break;
				case BITMAPDATA_TYPE_OF_TEXTURE:
					if (_texturePtr) {
						_isAllocated = _texturePtr->isAllocated();
						if (_isAllocated) {
							ofLog() << "[flBitmap]_update() _isAllocated = " << _isAllocated;
							_imageWidth = _texturePtr->getWidth();
							_imageHeight = _texturePtr->getHeight();

							_rect->width(_imageWidth);
							_rect->height(_imageHeight);
							_realWidth = _rect->width();
							_realHeight = _rect->height();

							if (!isnan(_targetWidth)) {
								scaleX(_targetWidth / _realWidth);
							}
							if (!isnan(_targetHeight)) {
								scaleY(_targetHeight / _realHeight);
							}
						}
					}
					break;
				case BITMAPDATA_TYPE_OF_FBO: break;
			}
		}
	}

    //--------------------------------------------------------------
    void flBitmap::_draw() {
        //--------------------------------------
        //draw image
        //        ofLog() << "_mode = " << _mode;
        switch(_dataType) {
            case BITMAPDATA_TYPE_BITMAPDATA: _bitmapDataPtr->__draw(0, 0); break;
            case BITMAPDATA_TYPE_OF_IMAGE: if (_imagePtr->isAllocated()) _imagePtr->draw(0, 0); break;
            case BITMAPDATA_TYPE_OF_TEXTURE: if (_texturePtr->isAllocated()) _texturePtr->draw(0, 0); break;
            case BITMAPDATA_TYPE_OF_FBO: if (_fboImage.isAllocated()) _fboImage.draw(0, 0); break;
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
    // Public Method
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
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        return _realHeight * scaleY();
//    }
//    void flBitmap::height(float value) {
//        _targetHeight = value;
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//    }
//    
//    //--------------------------------------------------------------
//    float flBitmap::scaleX() {
//        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        return _transform.__matrix.scaleX();
//    }
//    void flBitmap::scaleX(float value) {
//        _targetWidth = numeric_limits<float>::quiet_NaN();
//        _transform.__matrix.scaleX(value);
//    }
//    //--------------------------------------------------------------
//    float flBitmap::scaleY() {
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
//        return _transform.__matrix.scaleY();
//    }
//    void flBitmap::scaleY(float value) {
//        _targetHeight = numeric_limits<float>::quiet_NaN();
//        _transform.__matrix.scaleY(value);
//    }

	//    template <class T>
//    virtual void flBitmap::data<T>(T* value) {
//
//    }

	//--------------------------------------------------------------
	void flBitmap::data(ofTexture value) {
		//ofLog() << "[flBitmap]data()";

		switch (_dataType) {
			case BITMAPDATA_TYPE_BITMAPDATA:
				delete _bitmapDataPtr;
				_bitmapDataPtr = NULL;
				break;

			case BITMAPDATA_TYPE_OF_IMAGE:
				_imagePtr = NULL;
				_image.clear();
				break;

			case BITMAPDATA_TYPE_OF_TEXTURE:
				_texturePtr = NULL;
				_texture.clear();
				break;
		}

		_dataType = BITMAPDATA_TYPE_OF_TEXTURE;

		_texture = value;
		//const int w = value.getWidth();
		//const int h = value.getHeight();
		//const int glInternalFormat = value.getTextureData().glInternalFormat;
		//_texture.allocate(w, h, glInternalFormat);
		//ofPixels pixles;
		//value.readToPixels(pixles);
		//_texture.loadData(pixles);
		_texturePtr = &_texture;
		_isAllocated = _texturePtr->isAllocated();

		if (_isAllocated)
		{
			_imageWidth = _texturePtr->getWidth();
			_imageHeight = _texturePtr->getHeight();
			_rect->width(_imageWidth);
			_rect->height(_imageHeight);
			_realWidth = _rect->width();
			_realHeight = _rect->height();

			//ofLog() << "_imageHeight = " << _imageHeight;
			//ofLog() << "_targetWidth = " << _targetWidth;
			//ofLog() << "isnan(_targetWidth) = " << isnan(_targetWidth);

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
			_rect->width(_imageWidth);
			_rect->height(_imageHeight);
			_realWidth = _rect->width();
			_realHeight = _rect->height();
		}
	}	
	
	//--------------------------------------------------------------
	void flBitmap::data(ofTexture* value) {
		switch (_dataType) {
			case BITMAPDATA_TYPE_BITMAPDATA:
				//if(_bitmapDataPtr != NULL) delete _bitmapDataPtr;
				_bitmapDataPtr = NULL;
				_bitmapData.clear();
				break;

			case BITMAPDATA_TYPE_OF_IMAGE:
				_imagePtr = NULL;
				_image.clear();
				break;

			case BITMAPDATA_TYPE_OF_TEXTURE:
				_texturePtr = NULL;
				_texture.clear();
				break;
		}

		_dataType = BITMAPDATA_TYPE_OF_TEXTURE;

		_texturePtr = value;
		_isAllocated = _texturePtr->isAllocated();

		if (_isAllocated)
		{
			_imageWidth = _texturePtr->getWidth();
			_imageHeight = _texturePtr->getHeight();
			_rect->width(_imageWidth);
			_rect->height(_imageHeight);
			_realWidth = _rect->width();
			_realHeight = _rect->height();

			ofLog() << "_imageHeight = " << _imageHeight;
			ofLog() << "_targetWidth = " << _targetWidth;
			ofLog() << "isnan(_targetWidth) = " << isnan(_targetWidth);

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
			_rect->width(_imageWidth);
			_rect->height(_imageHeight);
			_realWidth = _rect->width();
			_realHeight = _rect->height();
		}
	}
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flBitmap::_updateRect() {
        //Empty
        
//        ofLog() << "flBitmap::_imageWidth = " << _imageWidth;
//        ofLog() << "flBitmap::_imageHeight = " << _imageHeight;
//        _hitAreaRect->__setZero();
//        _hitAreaRect->width(_imageWidth);
//        _hitAreaRect->height(_imageHeight);
//
//        //--------------------------------------
//        _realWidth = _hitAreaRect->width();
//        _realHeight = _hitAreaRect->height();
//
//        if(_realWidth != 0.0 && !isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
//        if(_realHeight != 0.0 && !isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
////        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
////        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
////        if(_targetWidth != -9999.0) scaleX(_targetWidth / _realWidth);
////        if(_targetHeight != -9999.0) scaleY(_targetHeight / _realHeight);
//        //--------------------------------------
    }
    
    //--------------------------------------------------------------
    //void flBitmap::updateOnFrame() {
    
    //}
    
    //--------------------------------------------------------------
    //void flBitmap::drawOnFrame() {
    //_drawBitmap();
    //}
    
}
