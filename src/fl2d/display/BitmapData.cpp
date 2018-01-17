#include "BitmapData.h"

/**
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 This class is during development
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**/

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    BitmapData::BitmapData(int width, int height, bool transparent, int fillColor) {
        _typeID = FL_TYPE_BITMAPDATA;
//        _target = this;
        
//        name("BitmapData");
        
        _width = width;
        _height = height;
        _transparent = transparent;
        
        _image = new ofImage();
        //_image->allocate(_width, _height, OF_IMAGE_COLOR_ALPHA);
        
        _pixels = (unsigned char*)malloc(_width * _height * 4);
        
        // ピクセルデータを準備
        int i;
        int colorSize;
        int totalCount;
        
        if(_transparent) {
            colorSize = 4;
            totalCount = _width * _height * colorSize;
            for(i = 0; i < totalCount; i += colorSize) {
                _pixels[i] = 255;
                _pixels[i+1] = 255;
                _pixels[i+2] = 255;
                _pixels[i+3] = 255;
            }
            //アルファ用に格納
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR_ALPHA);
        } else {
            colorSize = 3;
            totalCount = _width * _height * colorSize;
            for(i = 0; i < totalCount; i += colorSize) {
                _pixels[i] = 255;
                _pixels[i+1] = 255;
                _pixels[i+2] = 255;
            }
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR);
        }
    }

    //--------------------------------------------------------------
    //
    BitmapData::~BitmapData() {
        delete _pixels;
        _pixels = NULL;
        
        delete _image;
        _image = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

//    //--------------------------------------------------------------
//    //
//    void BitmapData::setup() {
//        
//    }
//
//    //--------------------------------------------------------------
//    //
//    void BitmapData::update() {
//        
//    }

    //--------------------------------------------------------------
    // TODO _image->getPixels()をしないでちゃんとpixelsを用意しておく
    void BitmapData::draw(ofImage& source) {
//        cout << "[BitmapData]draw()" << endl;
        
        unsigned char * pixels2;
//        pixels2 = source.getPixels(); //0.8.*
        pixels2 = source.getPixels().getData();
        
        
        //_width = source.getWidth();
        //_height = source.getHeight();
        
        // ピクセルデータを準備
        int i;
        int colorSize;
        int totalCount;
        
        int a;
        int r1, g1, b1;
        int r2, g2, b2;
        int r, g, b;
        
        if(_transparent) {
            colorSize = 4;
            totalCount = _width * _height * colorSize;
            
            for(i = 0; i < totalCount; i += colorSize) {
                a = pixels2[i+3];
                
                if(a == 0) {
                    //何もしない
                } else if(a == 255) {
                    // 前景のRGBの値を採用
                    _pixels[i] = pixels2[i];
                    _pixels[i+1] = pixels2[i+1];
                    _pixels[i+2] = pixels2[i+2];
                    //pixels1[i+3] = 255;
                } else {
                    // 背景RGBの値を取得
                    r1 = _pixels[i];
                    g1 = _pixels[i+1];
                    b1 = _pixels[i+2];
                    
                    // 前景のRGBの値を取得
                    r2 = pixels2[i];
                    g2 = pixels2[i+1];
                    b2 = pixels2[i+2];
                    /*
                     int r = (r2 * a + r1 * (256 - a)) / 256;
                     int g = (g2 * a + g1 * (256 - a)) / 256;
                     int b = (b2 * a + b1 * (256 - a)) / 256;
                     */
                    
                    //アルファブレンディングの高速化
                    //http://elksimple.web.fc2.com/memo/alpha.html
                    r = (r2 - r1) * a / 256 + r1;
                    g = (g2 - g1) * a / 256 + g1;
                    b = (b2 - b1) * a / 256 + b1;
                    
                    _pixels[i] = r;
                    _pixels[i+1] = g;
                    _pixels[i+2] = b;
                    //_pixels[i+3] = 255;
                }
            }
            //アルファ用に格納
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR_ALPHA);
        } else {
            colorSize = 3;
            totalCount = _width * _height * colorSize;
            
            for(i = 0; i < totalCount; i += colorSize) {
                // 前景のRGBの値を採用
                //_pixels[i] = pixels2[i];
                //_pixels[i+1] = pixels2[i+1];
                //_pixels[i+2] = pixels2[i+2];
            }
            
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR);
        }
    }

    //--------------------------------------------------------------
    //
    void BitmapData::_draw() {
//        cout << "[BitmapData::_daraw()" << endl;
//        ofPushStyle();
//        ofSetColor(255, 0 , 0);
//        ofDrawCircle(0, 0, 100);
//        ofPopStyle();
    }
    /*
    //--------------------------------------------------------------
    //
    ofTexture& BitmapData::getTextureReference() {
        return _image->getTextureReference();
    }
    */
    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    float BitmapData::width() { return _width; }
    void BitmapData::width(float value) { _width = value; }
    //--------------------------------------------------------------
    //
    float BitmapData::height() { return _height; }
    void BitmapData::height(float value) { _height = value; }

    //--------------------------------------------------------------
    //
    int BitmapData::getPixel(int x, int y) {
		return 0;
    }
    //--------------------------------------------------------------
    //
    int BitmapData::getPixel32(int x, int y) {
		return 0;
    }

    //--------------------------------------------------------------
    //
    void BitmapData::dispose() {
        
    }

    //--------------------------------------------------------------
    //
    void BitmapData::fillRect(Rectangle rect, ofColor color) {
        ofPixels& pixels = _image->getPixels();

        float left = rect.left();
        float right = rect.right();
        float top = rect.top();
        float bottom = rect.bottom();
        
        for(int x = 0; x < _width; x++) {
            for(int y = 0; y < _height; y++) {
                if(x < left) continue;
                if(right < x) continue;
                if(y < top) continue;
                if(bottom < y) continue;
                pixels.setColor(x, y, color);
            }
        }
    }

    //--------------------------------------------------------------
    //
    void BitmapData::clear() {
//        ofPixels& pixels = _image->getPixels();
//        pixels.clear();
        
        // ピクセルデータを準備
        int i;
        int colorSize;
        int totalCount;
        
        if(_transparent) {
            colorSize = 4;
            totalCount = _width * _height * colorSize;
            for(i = 0; i < totalCount; i += colorSize) {
                _pixels[i] = 0;
                _pixels[i+1] = 0;
                _pixels[i+2] = 0;
                _pixels[i+3] = 0;
            }
            //アルファ用に格納
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR_ALPHA);
        } else {
            colorSize = 3;
            totalCount = _width * _height * colorSize;
            for(i = 0; i < totalCount; i += colorSize) {
                _pixels[i] = 0;
                _pixels[i+1] = 0;
                _pixels[i+2] = 0;
            }
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    //
    void BitmapData::setPixel(int x, int y, ofColor color) {
//        cout << "[BitmapData]setPixel(" << x << ", " << y << ")" << endl;
        // ピクセルデータを準備
//        int i;
//        int colorSize;
//        int totalCount;
//        
//        if(_transparent) {
//            colorSize = 4;
//            totalCount = _width * _height * colorSize;
//            for(i = 0; i < totalCount; i += colorSize) {
//                _pixels[i] = 255;
//                _pixels[i+1] = 255;
//                _pixels[i+2] = 0;
//                _pixels[i+3] = 255;
//            }
//        } else {
//            colorSize = 3;
//            totalCount = _width * _height * colorSize;
//            for(i = 0; i < totalCount; i += colorSize) {
//                _pixels[i] = 255;
//                _pixels[i+1] = 0;
//                _pixels[i+2] = 255;
//            }
//        }
        
        ofPixels& pixels = _image->getPixels();
        pixels.setColor(x, y, color);
//        _image->update();
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void BitmapData::__draw(float x, float y) {
        _image->draw(x, y);
    }
        
}
