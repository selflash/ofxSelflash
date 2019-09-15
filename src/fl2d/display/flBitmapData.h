/**
 
 ActionScript3.0 Reference
 flash.display.BitmapData
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/BitmapData.html
 
 */

#pragma once

#include "flDisplayObject.h"

namespace fl2d {
    
    class flBitmap;
    class flBitmapData : public flObject {
        friend flBitmap;
        
    public:
        
    protected:
        
    private:
        unsigned char* _pixels;
        ofImage* _image;
        
        //ビットマップイメージがピクセル単位の透明度をサポートするかどうかを定義します。
        bool _transparent;
        
        int _width;
        int _height;
        
        flRectangle _rect;
        
    public:
        flBitmapData(int width, int height, bool transparent = true, int fillColor = 0xFFFFFF);
        virtual ~flBitmapData();
        //virtual ofTexture& getTextureReference();
        
        //            virtual void setup();
        //            virtual void update();
        
        bool transparent();
        
        virtual float width();
        virtual void width(float value);
        virtual float height();
        virtual void height(float value);
        
        //void applyFilter(flBitmapData* sourceflBitmapData, flRectangle* sourceRect, ofPoint* destPoint, flBitmapFilter filter);
        
        flBitmapData clone();
        
        //Object compare(flBitmapData* otherBItmapData);
        
        //copyChannel();
        
        //copyPixels()
        
        void dispose();
        
        //void draw(IBitmapDrawable source, flMatrix matrix = NULL, ColorTransform colorTransform = NULL, string blendMode = NULL, flRectangle* clipRect = NULL, bool smoothing = false);
        
        void draw(ofImage& source);
        
        //            void fillRect(flRectangle rect, int color);
        void fillRect(flRectangle rect, ofColor color);
        void clear();
        
        void floodFill(int x, int y, int color);
        
        //flRectangle* generateFilterRect(flRectangle* sourceRect, flBitmapFilter filter);
        
        int getPixel(int x, int y);
        int getPixel32(int x, int y);
        
        //ByteArray getPixels(flRectangle* rect);
        
        void lock() { };
        void unlock() {
            _image->update();
            //                if(_transparent) {
            //                    //アルファ用に格納
            //                    _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR_ALPHA);
            //                } else {
            //                    _image->setFromPixels(_pixels, _width, _height, OF_IMAGE_COLOR);
            //                }
        }
        //            void setPixel(int x, int y, int color);
        void setPixel(int x, int y, ofColor color);
        
        //hitTest();
        
    protected:
        //for flBitmap
        void __draw(float x, float y);
        
    private:
        virtual void _draw();
        
    };
    
}
