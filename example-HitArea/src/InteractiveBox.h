#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

class InteractiveBox:public flSprite {
    
    public:
    
    protected:
    
    private:
        flTextField* _titleTf;
    
        ofFloatColor* _lineColor;
        ofFloatColor* _normalColor;
        ofFloatColor* _overColor;
        ofFloatColor* _activeColor;
    
        ofFloatColor* _areaColor;
    
        float _graphicsWidth;
        float _graphicsHeight;
    
    public:
        InteractiveBox(float graphicsWidth = 200, float graphicsHeight = 200, int areaColor = 0xff0000);
        virtual ~InteractiveBox();

        void title(std::string value);

    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
    
        virtual void _drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor);
    
    private:    
        void _over();
        void _out();
        void _press();
        void _release();
    
        void _mouseEventHandler(flEvent& event);
};
