#include "flMovieClip.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flMovieClip::flMovieClip(int maxFrameNum) {
        _typeID = FL_TYPE_MOVIE_CLIP;
        _target = this;
        
        name("flMovieClip");
        
        _setTotalFrames(maxFrameNum);
        
        frameRate = 1;
        
        _frameIndex = 0;
        _frame = _frames[_frameIndex];
        
        _bPlay = false;
        
        play();
        
        ofAddListener(ofEvents().update, this, &flMovieClip::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    flMovieClip::~flMovieClip() {
        _target = NULL;
        
        frameRate = 1;
        
        _frameIndex = 0;
        
        _bPlay = false;
        
        ofRemoveListener(ofEvents().update, this, &flMovieClip::_updateEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::_updateEventHandler(ofEventArgs& args) {
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    /*
     //--------------------------------------------------------------
     //
     void flMovieClip::addFrameSequence(string dirPath, string fileName, int numOfDigits, string fileExtension, int numOfFiles) {
     ofImage image;
     char imagePath[255];
     
     for(int i = 0; i < numOfFiles; i++) {
     string str;
     str = "";
     str += "%s%s%0";
     str += ofToString(numOfDigits, 0);
     str += "d.%s";
     
     sprintf(imagePath, str.c_str(), dirPath.c_str(), fileName.c_str(), i, fileExtension.c_str());
     
     printf("load image %s\n", imagePath);
     image.loadImage(imagePath);
     
     addFrame(image);
     image.clear();
     }
     
     //width = _frames[0] -> getWidth();
     //height = _frames[0] -> getHeight();
     }
     
     //--------------------------------------------------------------
     //
     void flMovieClip::addFrame(ofImage& image) {
     addFrame(image.getPixels(), image.width, image.height, image.type);
     }
     
     //--------------------------------------------------------------
     //
     void flMovieClip::addFrame(unsigned char* pixels, int w, int h, int imageType) {
     _frames.push_back(new ofTexture());
     ofTexture* frame = _frames.back();
     
     GLint glDataType;
     if(imageType == OF_IMAGE_GRAYSCALE) {
     glDataType = GL_LUMINANCE;
     }
     else if(imageType == OF_IMAGE_COLOR) {
     glDataType = GL_RGB;
     }
     else if(imageType == OF_IMAGE_COLOR_ALPHA) {
     glDataType = GL_RGBA;
     }
     else {
     ofLog( OF_LOG_WARNING, "flMovieClip :: addFrame() - invalid imageType" );
     return;
     }
     
     _frame->allocate(w, h, glDataType);
     _frame->loadData(pixels, w, h, glDataType);
     
     ++_framesTotal;
     }
     */
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flMovieClip::play() {
        _bPlay = true;
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::stop() {
        _bPlay = false;
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::gotoAndPlay(int frameNum) {
        int index = frameNum - 1;
        
        if(_frameIndex != index) {
            _frameIndex = frameNum - 1;
            _frameIndex = ofClamp(_frameIndex, 0, totalFrames() - 1);
            _frame = _frames[_frameIndex];
        }
        
        play();
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::gotoAndStop(int frameNum) {
        int index = frameNum - 1;
        
        if(_frameIndex != index) {
            _frameIndex = index;
            _frameIndex = ofClamp(_frameIndex, 0, totalFrames() - 1);
            _frame = _frames[_frameIndex];
        }
        
        stop();
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::nextFrame() {
        _frameIndex += frameRate;
        if(_frameIndex > totalFrames() - 1) _frameIndex = 0;
        _frame = _frames[_frameIndex];
    }
    //--------------------------------------------------------------
    //
    void flMovieClip::prevFrame() {
        _frameIndex -= frameRate;
        if(_frameIndex < 0) _frameIndex = totalFrames() - 1;
        _frame = _frames[_frameIndex];
    }
    
    //--------------------------------------------------------------
    //
    int flMovieClip::totalFrames() { return _frames.size(); }
    //--------------------------------------------------------------
    //
    int flMovieClip::currentFrame() { return _frameIndex + 1; }
    
    //==============================================================
    // PROTECTED METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flMovieClip::updateOnFrame() {
        _removeFrameChildren();
        
        if(_bPlay) nextFrame();
        
        _addFrameChildren();
    }
    
    //==============================================================
    // PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flMovieClip::_setTotalFrames(int total) {
        int t1 = total;
        int t2 = _frames.size();
        int t = MAX(t1, t2);
        
        for(int i = 0; i < t; i++) {
            // number of frames has increased, add more.
            if(i > t2 - 1) {
                _frames.push_back(new flSprite());
            } else if(i > t1 - 1) {		// number of frames has decreased, remove some.
                flSprite* frameToRemove;
                frameToRemove = _frames[i];
                
                _frames.erase(_frames.begin() + i);
                
                --i;
                --t;
                
                delete frameToRemove;
                frameToRemove = NULL;
            }
        }
        
        _frameIndex = 0;
        this->_frame = _frames[_frameIndex];
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::addFrameObject(int frameNum, flDisplayObject* child) {
        if(totalFrames() < frameNum) throw "[flMovieClip]addFrameObject";
        
        flDisplayObjectContainer* frameContainer = _frames[frameNum - 1];
        frameContainer->addChild(child);
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::_addFrameChildren() {
        for(int i = 0; i < _frame->children.size(); i++) {
            flDisplayObject *child;
            child = _frame->children[i];
            
            children.push_back(child);
            child->stage(stage());
            child->parent(this);
            child->level(this->level() + 1);
        }
    }
    
    //--------------------------------------------------------------
    //
    void flMovieClip::_removeFrameChildren() {
        flDisplayObjectContainer::removeAllChildren();
    }
    
}
