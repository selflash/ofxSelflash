#include "flBitmapData.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flBitmapData::flBitmapData(int width, int height, bool transparent, int fillColor) {
        _typeID = FL_TYPE_BITMAPDATA;
        //        _target = this;
        
        //        name("flBitmapData");
        
        _width = width;
        _height = height;
        _transparent = transparent;
        
        _image = new ofImage();
        //_image->allocate(_width, _height, OF_IMAGE_COLOR_ALPHA);
        
        _pixels = (unsigned char*)malloc(_width * _height * 4);
        
        // �s�N�Z���f�[�^������
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
            //�A���t�@�p�Ɋi�[
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
    flBitmapData::~flBitmapData() {
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
    //    void flBitmapData::setup() {
    //        
    //    }
    //
    //    //--------------------------------------------------------------
    //    //
    //    void flBitmapData::update() {
    //        
    //    }
    
    //--------------------------------------------------------------
    // TODO _image->getPixels()�����Ȃ��ł�����pixels��p�ӂ��Ă���
    void flBitmapData::draw(ofImage& source) {
        //        cout << "[flBitmapData]draw()" << endl;
		if (!source.isAllocated()) return;
        unsigned char * pixels2;
        //        pixels2 = source.getPixels(); //0.8.*
        pixels2 = source.getPixels().getData();
        
        
        //_width = source.getWidth();
        //_height = source.getHeight();
        
        // �s�N�Z���f�[�^������
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
                    //�������Ȃ�
                } else if(a == 255) {
                    // �O�i��RGB�̒l���̗p
                    _pixels[i] = pixels2[i];
                    _pixels[i+1] = pixels2[i+1];
                    _pixels[i+2] = pixels2[i+2];
                    //pixels1[i+3] = 255;
                } else {
                    // �w�iRGB�̒l���擾
                    r1 = _pixels[i];
                    g1 = _pixels[i+1];
                    b1 = _pixels[i+2];
                    
                    // �O�i��RGB�̒l���擾
                    r2 = pixels2[i];
                    g2 = pixels2[i+1];
                    b2 = pixels2[i+2];
                    /*
                     int r = (r2 * a + r1 * (256 - a)) / 256;
                     int g = (g2 * a + g1 * (256 - a)) / 256;
                     int b = (b2 * a + b1 * (256 - a)) / 256;
                     */
                    
                    //�A���t�@�u�����f�B���O�̍�����
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
            //�A���t�@�p�Ɋi�[
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR_ALPHA);
        } else {
            colorSize = 3;
            totalCount = _width * _height * colorSize;
            
            for(i = 0; i < totalCount; i += colorSize) {
                // �O�i��RGB�̒l���̗p
                //_pixels[i] = pixels2[i];
                //_pixels[i+1] = pixels2[i+1];
                //_pixels[i+2] = pixels2[i+2];
            }
            
            _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flBitmapData::_draw() {
        //        cout << "[flBitmapData::_daraw()" << endl;
        //        ofPushStyle();
        //        ofSetColor(255, 0 , 0);
        //        ofDrawCircle(0, 0, 100);
        //        ofPopStyle();
    }
    /*
     //--------------------------------------------------------------
     //
     ofTexture& flBitmapData::getTextureReference() {
     return _image->getTextureReference();
     }
     */
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    float flBitmapData::width() { return _width; }
    void flBitmapData::width(float value) { _width = value; }
    //--------------------------------------------------------------
    float flBitmapData::height() { return _height; }
    void flBitmapData::height(float value) { _height = value; }
    
    //--------------------------------------------------------------
    int flBitmapData::getPixel(int x, int y) {
        return 0;
    }
    //--------------------------------------------------------------
    int flBitmapData::getPixel32(int x, int y) {
        return 0;
    }
    
    //--------------------------------------------------------------
    void flBitmapData::dispose() {
        
    }
    
    //--------------------------------------------------------------
    void flBitmapData::fillRect(flRectangle rect, ofColor color) {
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
    void flBitmapData::clear() {
        //        ofPixels& pixels = _image->getPixels();
        //        pixels.clear();
        
        // �s�N�Z���f�[�^������
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
            //�A���t�@�p�Ɋi�[
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
    void flBitmapData::setPixel(int x, int y, ofColor color) {
        //        cout << "[flBitmapData]setPixel(" << x << ", " << y << ")" << endl;
        // �s�N�Z���f�[�^������
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
    void flBitmapData::__draw(float x, float y) {
        if(_image->isAllocated()) _image->draw(x, y);
    }
    
}
