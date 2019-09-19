/**
 
 ActionScript3.0 Reference
 flash.display.Bitmap
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Bitmap.html
 
 */

#pragma once

#include "flDisplayObject.h"
#include "flBitmapData.h"

namespace fl2d {
    
    class flBitmap : public flDisplayObject {
    public:
        
    protected:
        int _mode = 0;
        
        flBitmapData* _bitmapData = NULL;
        
        ofImage* _image_ptr = NULL;
        ofImage _image;
        
        ofTexture* _texture_ptr = NULL;
        ofTexture _texture;
        
        ofFbo _fboImage;
        
		bool _isAllocated = false;
        float _imageWidth = 0;
        float _imageHeight = 0;
        
    private:
        
    public:
        flBitmap();
        flBitmap(flBitmapData* bitmapData, string pixelSnapping = "auto", bool smoothing = false);
        flBitmap(ofImage* image);
        flBitmap(ofImage image);
        flBitmap(ofTexture* texture);
        flBitmap(ofTexture texture);
        flBitmap(ofFbo fboImage);
        virtual ~flBitmap();
        
        //            virtual void draw();
        //virtual ofTexture& getTextureReference();
        
        virtual float width();
        virtual void width(float value);
        
        virtual float height();
        virtual void height(float value);
        
        virtual float scaleX();
        virtual void scaleX(float value);
        
        virtual float scaleY();
        virtual void scaleY(float value);
        
//        template <class T>
//        virtual void data<T>(T* value);
        virtual void data(ofTexture* value);

//        template <class T>
//        virtual void data<T>(T value);

        
    protected:
		virtual void _update();
        virtual void _draw();
        virtual void _updateRect();
        //virtual void updateOnFrame();
        //virtual void drawOnFrame();
        
    private:
        void _updateEventHandler(ofEventArgs& args);
        
        //void _drawBitmap();
        
    };
    
}
