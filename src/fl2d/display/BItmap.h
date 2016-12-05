/**
 
 ActionScript3.0 Reference
 flash.display.Bitmap
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Bitmap.html
 
 */

#pragma once

#include "DisplayObject.h"
#include "BitmapData.h"

namespace fl2d {
    
    class Bitmap : public DisplayObject {
        public:
        
        protected:
            int _mode;
            
            BitmapData* _bitmapData;
            ofBaseDraws* _bitmapImage;        
            ofFbo* _fboImage;
            
        private:
            
        public:
            Bitmap(BitmapData* bitmapData, string pixelSnapping = "auto", bool smoothing = false);
            Bitmap(ofImage* image);
            Bitmap(ofFbo* fboImage);
            ~Bitmap();
            
            virtual void draw();
            //virtual ofTexture& getTextureReference();
            
        protected:
            virtual void _draw();
            //virtual void updateOnFrame();
            //virtual void drawOnFrame();
            
        private:
            void _updateEventHandler(ofEventArgs& args);

            //void _drawBitmap();
            
    };
    
}
