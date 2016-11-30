#include "MovieClip.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    MovieClip::MovieClip(int maxFrameNum) {
        _typeID = FL_TYPE_MOVIE_CLIP;
        _target = this;
        
        name("MovieClip");
        
        _setTotalFrames(maxFrameNum);
        
        frameRate = 1;
        
        _frameIndex = 0;
        _frame = _frames[_frameIndex];
        
        _bPlay = false;
        
        play();
    }

    //--------------------------------------------------------------
    //
    MovieClip::~MovieClip() {
        _target = NULL;
        
        frameRate = 1;
        
        _frameIndex = 0;
        
        _bPlay = false;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    /*
    //--------------------------------------------------------------
    //
    void MovieClip::addFrameSequence(string dirPath, string fileName, int numOfDigits, string fileExtension, int numOfFiles) {
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
    void MovieClip::addFrame(ofImage& image) {
        addFrame(image.getPixels(), image.width, image.height, image.type);
    }

    //--------------------------------------------------------------
    //
    void MovieClip::addFrame(unsigned char* pixels, int w, int h, int imageType) {
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
    ofLog( OF_LOG_WARNING, "MovieClip :: addFrame() - invalid imageType" );
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
    void MovieClip::play() {
        _bPlay = true;
    }

    //--------------------------------------------------------------
    //
    void MovieClip::stop() {
        _bPlay = false;
    }

    //--------------------------------------------------------------
    //
    void MovieClip::gotoAndPlay(int frameNum) {
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
    void MovieClip::gotoAndStop(int frameNum) {
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
    void MovieClip::nextFrame() {
        _frameIndex += frameRate;
        if(_frameIndex > totalFrames() - 1) _frameIndex = 0;
        _frame = _frames[_frameIndex];
    }
    //--------------------------------------------------------------
    //
    void MovieClip::prevFrame() {
        _frameIndex -= frameRate;
        if(_frameIndex < 0) _frameIndex = totalFrames() - 1;
        _frame = _frames[_frameIndex];
    }

    //--------------------------------------------------------------
    //
    int MovieClip::totalFrames() { return _frames.size(); }
    //--------------------------------------------------------------
    //
    int MovieClip::currentFrame() { return _frameIndex + 1; }

    //==============================================================
    // PROTECTED METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void MovieClip::updateOnFrame() {
        _removeFrameChildren();
        
        if(_bPlay) nextFrame();
        
        _addFrameChildren();
    }

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void MovieClip::_setTotalFrames(int total) {
        int t1 = total;
        int t2 = _frames.size();
        int t = MAX(t1, t2);
        
        for(int i = 0; i < t; i++) {
            // number of frames has increased, add more.
            if(i > t2 - 1) {
                _frames.push_back(new Sprite());
            } else if(i > t1 - 1) {		// number of frames has decreased, remove some.
                Sprite* frameToRemove;
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
    void MovieClip::addFrameObject(int frameNum, DisplayObject* child) {
        if(totalFrames() < frameNum) throw "[MovieClip]addFrameObject";
        
        DisplayObjectContainer* frameContainer = _frames[frameNum - 1];
        frameContainer->addChild(child);
    }

    //--------------------------------------------------------------
    //
    void MovieClip::_addFrameChildren() {
        for(int i = 0; i < _frame->children.size(); i++) {
            DisplayObject *child;
            child = _frame->children[i];
            
            children.push_back(child);
            child->stage(stage());
            child->parent(this);
            child->level(this->level() + 1);
        }
    }

    //--------------------------------------------------------------
    //
    void MovieClip::_removeFrameChildren() {
        DisplayObjectContainer::removeAllChildren();
    }

}
