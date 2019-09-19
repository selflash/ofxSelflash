#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxSelflash.h"
#include "flBasicController.h"

#include "Config.h"
#include "NetworkController.h"
#include "DeviceSettingsController.h"
#include "SubController1.h"
#include "SubController2.h"
//#include "NativeWindow.h"

using namespace fl2d;

class MainController : public flBasicController {
    
public:
    
protected:
    string _status;
    
private:
    flBasicController* _controller0;
    flBasicController* _controller1;
    flBasicController* _controller2;
    
    vector<flBasicController*> _deviceSettingsControllers;

public:
    MainController();
    virtual ~MainController();
    
    //virtual void setup();
    //virtual void update();
    //virtual void draw();
    
    virtual void normalize();
    
    void toggleShowAll();
    
    inline DeviceSettingsController* deviceSettingsController(int index) { return (DeviceSettingsController*)_deviceSettingsControllers[index]; }

    //サブコントローラー
    inline flBasicController* controller0() { return _controller0; }
    inline flBasicController* controller1() { return _controller1; }
    inline flBasicController* controller2() { return _controller2; }
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
    virtual void _uiEventHandler(flEvent& event);
    
};
