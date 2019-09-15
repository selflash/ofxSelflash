/**
 
 ActionScript3.0 Reference
 flash.display.MovieClip
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/MovieClip.html
 
 */

#pragma once

#include "flSprite.h"

namespace fl2d {
    
    class flMovieClip:public flSprite {
    public:
        int frameRate;
        
    protected:
        
    private:	
        vector<flSprite*>	_frames;
        flSprite* _frame;
        
        int _frameIndex;
        bool _bPlay;
        
    public:
        flMovieClip(int maxFrameNum = 1);
        virtual ~flMovieClip();
        
        int totalFrames();
        int currentFrame();
        
        void addFrameObject(int frameNum, flDisplayObject* child);
        
        //virtual void addFrameSequence(string dirPath, string fileName, int numOfDigits, string fileExtension, int numOfFiles);
        //virtual void addFrame(ofImage& image);
        //virtual void addFrame(unsigned char* pixels, int w, int h, int imageType);
        
        void play();
        void stop();
        void gotoAndPlay(int frameNum);
        void gotoAndStop(int frameNum);
        void nextFrame();
        void prevFrame();
        
        flDisplayObject* addChild(flDisplayObject* child) {
            return _frame->addChild(child);
        }
        
        flDisplayObject* addChildAt(flDisplayObject* child, int index) {
            return _frame->addChildAt(child, index);
        }
        
        bool contains(flDisplayObject* child) {
            return _frame->contains(child);
        }
        
        flDisplayObject* getChildAt(int index) {
            return _frame->getChildAt(index);
        }
        
        flDisplayObject* getChildByName(string name) {
            return _frame->getChildByName(name);
        }
        
        int	getChildIndex(flDisplayObject* child) {
            return _frame->getChildIndex(child);
        }
        
        vector<flDisplayObject*> getObjectsUnderPoint(ofPoint point) {
            return _frame->getObjectsUnderPoint(point);
        }
        
        flDisplayObject* removeChild(flDisplayObject* child) {
            return _frame->removeChild(child);
        }
        
        flDisplayObject* removeChildAt(int index) {
            return _frame->removeChildAt(index);
        }
        
        void setChildIndex(flDisplayObject* child, int index) {
            _frame->setChildIndex(child, index);
        }
        
        void swapChildren(flDisplayObject* child1, flDisplayObject* child2) {
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
