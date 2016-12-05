
#include "Bitmap.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(BitmapData* bitmapData, string pixelSnapping, bool smoothing) {
        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap1()" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        
        name("Bitmap");
        
        _mode = 0;
        
        _bitmapData = bitmapData;
        
        //TODO
        width(_bitmapData->width());
        height(_bitmapData->height());

    //    _bitmapData = NULL;
        _bitmapImage = NULL;
        _fboImage = NULL;
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofImage* image) {
        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap2()" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 1;

        _bitmapImage = image;

        //TODO
        width(_bitmapImage->getWidth());
        height(_bitmapImage->getHeight());
        
        _bitmapData = NULL;
    //    _bitmapImage = NULL;
        _fboImage = NULL;
        
        ofAddListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Bitmap::Bitmap(ofFbo* fboImage) {
        debug(true);
        if(debug()) cout << "[Bitmap]Bitmap3()" << endl;
        
        _typeID = FL_TYPE_BITMAP;
        _target = this;
        _mode = 2;
        
        _fboImage = fboImage;
        
        //TODO
        width(_fboImage->getWidth());
        height(_fboImage->getHeight());
        
        _bitmapData = NULL;
        _bitmapImage = NULL;
    //    _fboImage = NULL;
        
        ofRemoveListener(ofEvents().update, this, &Bitmap::_updateEventHandler);
    }

    //--------------------------------------------------------------
    //
    Bitmap::~Bitmap() {
        // don't delete bitmapImage as its managed by ofxFlashLibrary.
        //bitmapImage = NULL;
        
    //    delete _bitmapData;
        _bitmapData = NULL;
        
    //    delete _bitmapImage;
        _bitmapImage = NULL;
        
    //    delete _fboImage;
        _fboImage = NULL;
        
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
        DisplayObject::draw();
    //    if(!visible()) return;
    //    ofDisableLighting();
    //    
    //    //-- matrix transform.
    //    bool bIdentity = true;
    //    bIdentity = matrix().isIdentity();
    //    bIdentity = false;
    //    
    //    if(!bIdentity) {
    //        glPushMatrix();
    //        glMultMatrixf(matrix().getPtr());
    //    }
    //    glDisable(GL_DEPTH_TEST);
    //    
    //    //ofSetColor(255, 255, 255, __compoundAlpha * 255);
    //    ofEnableAlphaBlending();
    //    if(_smoothing) ofEnableSmoothing();
    //	_draw();
    //    ofDisableSmoothing();
    //    //oFでは標準ではアルファブレンディング有効
    //    ofDisableAlphaBlending();
    //
    //    if(!bIdentity) {
    //        glPopMatrix();
    //    }
    }

    //--------------------------------------------------------------
    //
    void Bitmap::_draw() {
        switch(_mode) {
            case 0:
                {
                    ofSetColor(255, 255, 255, __compoundAlpha * 255);
                    _bitmapData->__draw(0, 0);
                }
                break;
                
            case 1:
                {
    //                ofPushMatrix();
    //                ofTranslate(-_bitmapImage->getWidth() * 0.5, -_bitmapImage->getHeight() * 0.5);
                    ofSetColor(255, 255, 255, __compoundAlpha * 255);
                    _bitmapImage->draw(0, 0, width(), height());
    //                ofPopMatrix();
                }
                break;
                
            case 2:
                {
                    //ofPushMatrix();
                    //ofTranslate(-bitmapImage->getWidth()*0.5f, -bitmapImage->getHeight()*0.5f);
                    ofSetColor(255, 255, 255, __compoundAlpha * 255);
                    _fboImage->draw(0, 0, width(), height());
                    //ofPopMatrix();
                }
                break;
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

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    //void Bitmap::updateOnFrame() {

    //}

    //--------------------------------------------------------------
    //
    //void Bitmap::drawOnFrame() {
    //_drawBitmap();
    //}

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

}
