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
			enum BITMAPDATA_TYPE {
				BITMAPDATA_TYPE_NONE = 0,
				BITMAPDATA_TYPE_BITMAPDATA,
				BITMAPDATA_TYPE_OF_IMAGE,
				BITMAPDATA_TYPE_OF_TEXTURE,
				BITMAPDATA_TYPE_OF_FBO
			};

			BITMAPDATA_TYPE _dataType = BITMAPDATA_TYPE_NONE;
            
            flBitmapData _bitmapData = flBitmapData(0, 0);
            flBitmapData* _bitmapDataPtr = NULL;
            
			ofImage _image;
			ofImage* _imagePtr = NULL;
            
			ofTexture _texture;
			ofTexture* _texturePtr = NULL;
            
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
            
//            virtual float width();
//            virtual void width(float value);
//            
//            virtual float height();
//            virtual void height(float value);
//            
//            virtual float scaleX();
//            virtual void scaleX(float value);
//            
//            virtual float scaleY();
//            virtual void scaleY(float value);
            
    //        template <class T>
    //        virtual void data<T>(T* value);
			virtual ofTexture data() { return *_texturePtr; }
			virtual ofTexture& dataReference() { return *_texturePtr; }

            virtual void data(ofTexture value);
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
