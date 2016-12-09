#pragma once

#include "ofMain.h"

//#define TYPE_OF_IMAGE   0
//#define TYPE_OF_TEXTURE 1
//
//#define TYPE_OF_VIDEOPLAYER 3
//#define TYPE_OF_QTKITPLAYER 4

namespace fl2d {
    
    class Loader {
//        public:
//            
//        private:
//            
//        public:
//            //--------------------------------------------------------------
//            //
//            static ofBaseDraws* loadImage(string path, int type = TYPE_OF_IMAGE) {
//                
//                if(type == TYPE_OF_IMAGE) {
//                    ofImage* image = new ofImage();
//                    if(!image->loadImage(path)) return NULL;
//                    cout << "[Loader] loaded ofImage " << path << endl;
//
//                    return image;
//                }
//        /*
//                if(type == TYPE_OF_TEXTURE){
//                    ofImage image;
//                    if(!image.loadImage(path)) return NULL;
//                    
//                    ofTexture* texture = new ofTexture();
//                    texture->allocate(image.getWidth(), image.getHeight(), image.getTextureReference().getTextureData().glType);
//                    texture->loadData(image.getPixels(), image.getWidth(), image.getHeight(), image.getTextureReference().getTextureData().glType);
//                    
//                    return texture;
//                }
//        */
//                if(type == TYPE_OF_TEXTURE) {
//                    ofDisableArbTex();
//                    ofTexture* texture = new ofTexture();
//                    if(!ofLoadImage(*texture, path)) return NULL;
//                    cout << "[Loader] loaded ofTexture " << path << endl;
//                    ofEnableArbTex();
//                    return texture;
//                }
//            };
//            
//            //--------------------------------------------------------------
//            //
//            static ofBaseVideoPlayer* loadMovie(string path, int type = TYPE_OF_QTKITPLAYER){
//                if(type == TYPE_OF_QTKITPLAYER){
//                    
//    #ifdef TARGET_OSX
//                    ofQTKitPlayer* movie = new ofQTKitPlayer();
//                    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
//                    
//                    movie->setPixelFormat(OF_PIXELS_RGBA);
//                    movie->loadMovie(path, decodeMode);
//                    return movie;
//    #else
//                    return NULL;
//    #endif
//                }
//                
//                if(type == TYPE_OF_VIDEOPLAYER){
//                    ofVideoPlayer* video = new ofVideoPlayer();
//                    video->loadMovie(path);
//                    return video;
//                }
//            };
//            
//            //--------------------------------------------------------------
//            //
//            //static ofSoundPlayer* loadSound(string path){
//            //};
//            
//        private:
    };
    
}
