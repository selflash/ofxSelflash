#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

using namespace fl2d;

class InteractiveBox:public flSprite {
    
public:
    
protected:
    
private:
    flTextField* _label;
    
    ofColor _areaColor;
    
    float _graphicsWidth;
    float _graphicsHeight;
    
    bool _showHitArea;
    
public:
    InteractiveBox(float graphicsWidth = 400, float graphicsHeight = 300, ofColor areaColor = ofColor(255, 0, 0));
    virtual ~InteractiveBox();
    
    void title(std::string value);
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
    void showHitArea(bool value) { _showHitArea = value; }
    bool showHitArea() { return _showHitArea; }
    
private:
    void _over();
    void _out();
    void _press();
    void _release();
    
    void _setNormalColor();
    void _setOverColor();
    void _setSelectedOverColor();
    void _setActiveColor();
    void _setDisableNormalColor();
    void _setDisableActiveColor();
    
    void _drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
    
    void _mouseEventHandler(flEvent& event);
};
