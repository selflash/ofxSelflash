#pragma once

#include "ofMain.h"
#include "Flash2D.h"
#include "Flash3D.h"
using namespace fl3d;

#include "MathUtil.h"
#include "BasicController.h"
#include "BokehDOF.h"

class DepthOfFieldController : public BasicController {
    public:
        
    protected:
        std::string _status;
        
        BokehDOF* _bokehDOF;
        
    private:
        float _nearClip;
        float _farClip;
        float _focalLength;
        float _focalDepth;
        float _fstop;
        
        int _ringCount;
        int _ringSamples;
        float _texel;
        float _depthBlurSize;
        float _maxBlur;
        
        float _highlightThreshold;
        float _higilightGain;
        float _edgeBias;
        float _feather;
        float _ditherAmount;
        
        float _fringe;
    
    public:
        DepthOfFieldController();
        ~DepthOfFieldController();
        
        //virtual void setup();
        //virtual void update();
        //virtual void draw();
        
        BokehDOF* bokehDOF();
        void bokehDOF(BokehDOF* value);
    
        //--------------------------------------
        float nearClip();
        void nearClip(float value);
        
        float farClip();
        void farClip(float value);
        
        float focalLength();
        void focalLength(float value);
        
        float focalDepth();
        void focalDepth(float value);
        
        float fstop();
        void fstop(float value);
        
        
        int ringCount();
        void ringCount(int value);
        
        int ringSamples();
        void ringSamples(int value);
        
        float texel();
        void texel(float value);
        
        float depthBlurSize();
        void depthBlurSize(float value);
        
        float maxBlur();
        void maxBlur(float value);
        
        
        float highlightThreshold();
        void highlightThreshold(float value);
        
        float higilightGain();
        void higilightGain(float value);
        
        float edgeBias();
        void edgeBias(float value);
        
        float feather();
        void feather(float value);
        
        float ditherAmount();
        void ditherAmount(float value);
        
        float fringe();
        void fringe(float value);
        //--------------------------------------
    
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _uiEventHandler(Event& event);
        
    private:
};
