/**
 
 ActionScript3.0 Reference
 flash.display.MovieClip
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/MovieClip.html
 
 */

#pragma once

#include "Sprite.h"

namespace fl2d {
    
    class MovieClip:public Sprite {
        public:
            int frameRate;

        protected:
            
        private:	
            vector<Sprite*>	_frames;
            Sprite* _frame;
            
            int _frameIndex;
            bool _bPlay;

        public:
            MovieClip(int maxFrameNum = 1);
            virtual ~MovieClip();
            
            int totalFrames();
            int currentFrame();
            
            void addFrameObject(int frameNum, DisplayObject* child);
            
            //virtual void addFrameSequence(string dirPath, string fileName, int numOfDigits, string fileExtension, int numOfFiles);
            //virtual void addFrame(ofImage& image);
            //virtual void addFrame(unsigned char* pixels, int w, int h, int imageType);
            
            void play();
            void stop();
            void gotoAndPlay(int frameNum);
            void gotoAndStop(int frameNum);
            void nextFrame();
            void prevFrame();
            
            DisplayObject* addChild(DisplayObject* child) {
                return _frame->addChild(child);
            }
            
            DisplayObject* addChildAt(DisplayObject* child, int index) {
                return _frame->addChildAt(child, index);
            }
            
            bool contains(DisplayObject* child) {
                return _frame->contains(child);
            }
            
            DisplayObject* getChildAt(int index) {
                return _frame->getChildAt(index);
            }
            
            DisplayObject* getChildByName(string name) {
                return _frame->getChildByName(name);
            }
            
            int	getChildIndex(DisplayObject* child) {
                return _frame->getChildIndex(child);
            }
            
            vector<DisplayObject*> getObjectsUnderPoint(ofPoint point) {
                return _frame->getObjectsUnderPoint(point);
            }
            
            DisplayObject* removeChild(DisplayObject* child) {
                return _frame->removeChild(child);
            }
            
            DisplayObject* removeChildAt(int index) {
                return _frame->removeChildAt(index);
            }
            
            void setChildIndex(DisplayObject* child, int index) {
                _frame->setChildIndex(child, index);
            }
            
            void swapChildren(DisplayObject* child1, DisplayObject* child2) {
                _frame->swapChildren(child1, child2);
            }
            
            void swapChildrenAt(int index1, int index2) {
                _frame->swapChildrenAt(index1, index2);
            }
            
        protected:
            virtual void updateOnFrame();
            
        private:
            void _updateEventHandler(ofEventArgs& args);
        
            void _setTotalFrames(int totalFrames = 1);
            
            void _addFrameChildren();
            void _removeFrameChildren();
    };
}
