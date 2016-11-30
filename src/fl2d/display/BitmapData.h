/**
 
 ActionScript3.0 Reference
 flash.display.BitmapData
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/BitmapData.html
 
 */

#pragma once

#include "DisplayObject.h"

namespace fl2d {
    
    class Bitmap;
    class BitmapData : public DisplayObject {
        friend Bitmap;
        
        public:
            
        protected:
            
        private:
            unsigned char* _pixels;
            ofImage* _image;
            
            //ビットマップイメージがピクセル単位の透明度をサポートするかどうかを定義します。
            bool _transparent;
            
            int _width;
            int _height;
            
            Rectangle _rect;

        public:
            BitmapData(int width, int height, bool transparent = true, int fillColor = 0xFFFFFF);
            ~BitmapData();
            //virtual ofTexture& getTextureReference();
            
            virtual void setup();
            virtual void update();
            
            bool transparent();
            
            virtual float width();
            virtual void width(float value);
            virtual float height();
            virtual void height(float value);
            
            //void applyFilter(BitmapData* sourceBitmapData, Rectangle* sourceRect, ofPoint* destPoint, BitmapFilter filter);
            
            BitmapData clone();
            
            //Object compare(BitmapData* otherBItmapData);
            
            //copyChannel();
            
            //copyPixels()
            
            void dispose();
            
            //void draw(IBitmapDrawable source, Matrix matrix = NULL, ColorTransform colorTransform = NULL, string blendMode = NULL, Rectangle* clipRect = NULL, bool smoothing = false);
            
            void draw(ofImage& source);
            
            void fillRect(Rectangle rect, int color);
            
            void floodFill(int x, int y, int color);
            
            //Rectangle* generateFilterRect(Rectangle* sourceRect, BitmapFilter filter);
            
            int getPixel(int x, int y);
            int getPixel32(int x, int y);
            
            //ByteArray getPixels(Rectangle* rect);
            
            //void setPixel(int x, int y, int color);
            
            //hitTest();
            
        protected:
            //for Bitmap
            void __draw(float x, float y);
        private:
            virtual void _draw();
            
    };
    
}
