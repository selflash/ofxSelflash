#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flColorPickerEvent.h"

namespace fl2d {
    
    class flCircleColorPicker : public flUIBase {
        
    public:
        
    protected:
        
    private:
        float _uiWidth;
        float _uiHeight;
        
        ofImage* _pixelCaptureImage;
        ofImage* _colorWheelImage;
        ofColor* _selectedPixel;
        
        float _radius;
        
    public:
        flCircleColorPicker(float width = 100, float height = 100);
        virtual ~flCircleColorPicker();
        
        virtual void label(flTextField* value);
        
        const ofColor& getPixel(int x, int y);
        
        int red();
        int green();
        int blue();
        
        string hexCode();
        int hue();
        int saturation();
        int brightness();
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _onOver();
        virtual void _onOut();
        virtual void _onPress();
        virtual void _onRelease();
        virtual void _onMove();
        
    private:
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}
