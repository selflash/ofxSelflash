#include "DeviceSettingsController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
DeviceSettingsController::DeviceSettingsController(string title) {
    cout << "[DeviceCameraViewer]DeviceCameraViewer()" << endl;
    _target = this;
    
    name("DeviceCameraViewer");
    useHandCursor(true);
    
    titleTf->text("[" + title + "]");
    
    _status = "[Status]";
}

//--------------------------------------------------------------
//
DeviceSettingsController::~DeviceSettingsController() {
    cout << "[DeviceCameraViewer]~DeviceCameraViewer()" << endl;
    _target = NULL;
    
    _status = "";
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void DeviceSettingsController::_setup() {
    cout << "[DeviceCameraViewer]_setup()" << endl;
    
    flBasicController::_setup();
    
    _normalBackWidth = 800;
    _normalBackHeight = 783 + 10;
    _minBackWidth = _normalBackWidth;
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    flTextField* label = NULL;
    flRadioButtonGroup* radioButtonGroup = NULL;
    //--------------------------------------

    marginLeft = 5;
    marginTop = 35 + 20 + 5;
    spacing = 150;
    lineSpacing = 22;
    //--------------------------------------
    {
        int camWidth = 1280 * 0.2;
        int camHeight = 720 * 0.2;
        flGraphics* g;
        
        int borderWidth = 2;

        //Color Image
        _colorViewer = new flSprite();
        _colorViewer->setup();
        g = _colorViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        _colorViewer->x(5);
        _colorViewer->y(marginTop);
        _colorViewer->mouseEnabled(false);
        _colorViewer->mouseChildren(false);
        addChild(_colorViewer);
        _colorBitmap = new flBitmap();
        _colorBitmap->width(camWidth);
        _colorBitmap->height(camHeight);
        _colorBitmap->x(2);
        _colorBitmap->y(2);
        _colorViewer->addChild(_colorBitmap);
        
        //Depth Image
        _depthViewer = new flSprite();
        _depthViewer->setup();
        g = _depthViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        _depthViewer->x(5 + borderWidth + camWidth + borderWidth + 5);
        _depthViewer->y(marginTop);
        _depthViewer->mouseEnabled(false);
        _depthViewer->mouseChildren(false);
        addChild(_depthViewer);
        _depthBitmap = new flBitmap();
        _depthBitmap->width(camWidth);
        _depthBitmap->height(camHeight);
        _depthBitmap->x(2);
        _depthBitmap->y(2);
        _depthViewer->addChild(_depthBitmap);

        //Ir Image
        _irViewer = new flSprite();
        _irViewer->setup();
        g = _irViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        _irViewer->x(5 + borderWidth + camWidth + borderWidth + 5 + borderWidth + camWidth + borderWidth + 5);
        _irViewer->y(marginTop);
        _irViewer->mouseEnabled(false);
        _irViewer->mouseChildren(false);
        addChild(_irViewer);
        _irBitmap = new flBitmap();
        _irBitmap->width(camWidth);
        _irBitmap->height(camHeight);
        _irBitmap->x(2);
        _irBitmap->y(2);
        _irViewer->addChild(_irBitmap);

        //Depth In Color Image
        _depthInColorViewer = new flSprite();
        _depthInColorViewer->setup();
        //    _videoTexture.allocate(camWidth, camHeight, GL_RGBA);
        g = _depthInColorViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        _depthInColorViewer->x(5);
        _depthInColorViewer->y(marginTop + camHeight + 20 + 5);
        _depthInColorViewer->mouseEnabled(false);
        _depthInColorViewer->mouseChildren(false);
        addChild(_depthInColorViewer);
        _depthInColorBitmap = new flBitmap();
        _depthInColorBitmap->width(camWidth);
        _depthInColorBitmap->height(camHeight);
        _depthInColorBitmap->x(2);
        _depthInColorBitmap->y(2);
        _depthInColorViewer->addChild(_depthInColorBitmap);

        //Color In Depth Image
        _colorInDepthViewer = new flSprite();
        _colorInDepthViewer->setup();
        g = _colorInDepthViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        _colorInDepthViewer->x(5 + borderWidth + camWidth + borderWidth + 5);
        _colorInDepthViewer->y(marginTop + camHeight + 20 + 5);
        _colorInDepthViewer->mouseEnabled(false);
        _colorInDepthViewer->mouseChildren(false);
        addChild(_colorInDepthViewer);
        _colorInDepthBitmap = new flBitmap();
        _colorInDepthBitmap->width(camWidth);
        _colorInDepthBitmap->height(camHeight);
        _colorInDepthBitmap->x(2);
        _colorInDepthBitmap->y(2);
        _colorInDepthViewer->addChild(_colorInDepthBitmap);

        //ofLog() << "_colorInDepthViewer.x : " << _colorInDepthViewer->x();
        //ofLog() << "_colorInDepthViewer.y : " << _colorInDepthViewer->y() + _colorInDepthViewer->height();
    }
    
    marginLeft = 270 + 270;
    marginTop = 390;
    spacing = 150;
    lineSpacing = 22;
    
    check001 = new flCheckBox();
    check001->labelText("Enable Depth Camera");
    check001->x(marginLeft + spacing * 0);
    check001->y(marginTop + lineSpacing * 0);
    check001->selected(true);
    //    check001->enabled(false);
    check001->addEventListener(flCheckBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(check001);
    
    label = new flTextField();
    label->text("Depth Configuration");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    label = new flTextField();
    label->text("Depth Mode");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    spacing = 150;
    radioButtonGroup = new flRadioButtonGroup();
    radioButtonGroups.push_back(radioButtonGroup);
    radio001 = radioButtonGroup->createRadioButton();
    radio001->labelText("NFOV 2X2BINNED(320 x 288)");
    radio001->x(marginLeft + spacing * 0);
    radio001->y(marginTop + lineSpacing * 3);
    radio001->selected(true);
    //radio001->enabled(false);
    radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio001);
    radio002 = radioButtonGroup->createRadioButton();
    radio002->labelText("NFOV UNBINNED(640 x 576)");
    radio002->x(marginLeft + spacing * 0);
    radio002->y(marginTop + lineSpacing * 4);
    radio002->selected(true);
    //radio002->enabled(false);
    radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio002);
    radio003 = radioButtonGroup->createRadioButton();
    radio003->labelText("WFOV 2X2BINNED(512 x 512)");
    radio003->x(marginLeft + spacing * 0);
    radio003->y(marginTop + lineSpacing * 5);
    radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio003);
    radio004 = radioButtonGroup->createRadioButton();
    radio004->labelText("WFOV UNBINNED(1024 x 1024)");
    radio004->x(marginLeft + spacing * 0);
    radio004->y(marginTop + lineSpacing * 6);
    radio004->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio004);
    radio004 = radioButtonGroup->createRadioButton();
    radio004->labelText("PASSIVE IR(1024 x 1024)");
    radio004->x(marginLeft + spacing * 0);
    radio004->y(marginTop + lineSpacing * 7);
    radio004->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio004);
    //    ofLog() << "radio004 : " << radio004->y() + radio004->height();
    
    
    
    marginLeft = 5;
    marginTop = 390;
    spacing = 150;
    lineSpacing = 22;

    check001 = new flCheckBox();
    check001->labelText("Enable Color Camera");
    check001->x(marginLeft + spacing * 0);
    check001->y(marginTop + lineSpacing * 0);
    check001->selected(true);
//    check001->enabled(false);
    check001->addEventListener(flCheckBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(check001);
    
    label = new flTextField();
    label->text("Color Configuration");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    label = new flTextField();
    label->text("Format");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);

    spacing = 65;
    radioButtonGroup = new flRadioButtonGroup();
    radioButtonGroups.push_back(radioButtonGroup);
    radio001 = radioButtonGroup->createRadioButton();
    radio001->labelText("BGRA");
    radio001->x(marginLeft + spacing * 0);
    radio001->y(marginTop + lineSpacing * 3);
    radio001->selected(true);
    //radio001->enabled(false);
    radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio001);
    radio002 = radioButtonGroup->createRadioButton();
    radio002->labelText("MJPG");
    radio002->x(marginLeft + spacing * 1);
    radio002->y(marginTop + lineSpacing * 3);
    radio002->selected(true);
    //radio002->enabled(false);
    radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio002);
    radio003 = radioButtonGroup->createRadioButton();
    radio003->labelText("NV12");
    radio003->x(marginLeft + spacing * 2);
    radio003->y(marginTop + lineSpacing * 3);
    radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio003);
    radio004 = radioButtonGroup->createRadioButton();
    radio004->labelText("YUY2");
    radio004->x(marginLeft + spacing * 3);
    radio004->y(marginTop + lineSpacing * 3);
    radio004->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio004);
//    ofLog() << "radio004 : " << radio004->y() + radio004->height();

    marginLeft = 5;
    marginTop = radio004->y() + radio004->height();
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Resolution");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    label = new flTextField();
    label->text("16 : 9");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    radioButtonGroup = new flRadioButtonGroup();
    radioButtonGroups.push_back(radioButtonGroup);
    radio101 = radioButtonGroup->createRadioButton();
    radio101->labelText("720p (1280 x 720)");
    radio101->x(marginLeft + spacing * 0);
    radio101->y(marginTop + lineSpacing * 2);
    radio101->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio101);
    radio102 = radioButtonGroup->createRadioButton();
    radio102->labelText("1080p (1920 x 1080)");
    radio102->x(marginLeft + spacing * 0);
    radio102->y(marginTop + lineSpacing * 3);
    radio102->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio102);
    radio103 = radioButtonGroup->createRadioButton();
    radio103->labelText("1440p (2560 x 1440)");
    radio103->x(marginLeft + spacing * 0);
    radio103->y(marginTop + lineSpacing * 4);
    radio103->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio103);
    radio104 = radioButtonGroup->createRadioButton();
    radio104->labelText("2160p (3840 x 2160)");
    radio104->x(marginLeft + spacing * 0);
    radio104->y(marginTop + lineSpacing * 5);
    radio104->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio104);
    
    label = new flTextField();
    label->text("4 : 3");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 6);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    radio105 = radioButtonGroup->createRadioButton();
    radio105->labelText("1536p (2048 x 1536)");
    radio105->x(marginLeft + spacing * 0);
    radio105->y(marginTop + lineSpacing * 7);
    radio105->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio105);
    radio106 = radioButtonGroup->createRadioButton();
    radio106->labelText("3072p (4096 x 3072)");
    radio106->x(marginLeft + spacing * 0);
    radio106->y(marginTop + lineSpacing * 8);
    radio106->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio106);
//    ofLog() << "radio106 : " << radio106->y() + radio106->height();

    marginLeft = 5;
    marginTop = radio106->y() + radio106->height();
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Power Frequency");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    spacing = 65;
    radioButtonGroup = new flRadioButtonGroup();
    radioButtonGroups.push_back(radioButtonGroup);
    radio105 = radioButtonGroup->createRadioButton();
    radio105->labelText("50Hz");
    radio105->x(marginLeft + spacing * 0);
    radio105->y(marginTop + lineSpacing * 1);
    radio105->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio105);
    radio106 = radioButtonGroup->createRadioButton();
    radio106->labelText("60Hz");
    radio106->x(marginLeft + spacing * 1);
    radio106->y(marginTop + lineSpacing * 1);
    radio106->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio106);
    //    ofLog() << "radio106 : " << radio106->y() + radio106->height();
    
    label = new flTextField();
    label->text("Framerate");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    spacing = 75;
    radioButtonGroup = new flRadioButtonGroup();
    radioButtonGroups.push_back(radioButtonGroup);
    radio105 = radioButtonGroup->createRadioButton();
    radio105->labelText("30FPS");
    radio105->x(marginLeft + spacing * 0);
    radio105->y(marginTop + lineSpacing * 3);
    radio105->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio105);
    radio106 = radioButtonGroup->createRadioButton();
    radio106->labelText("15FPS");
    radio106->x(marginLeft + spacing * 1);
    radio106->y(marginTop + lineSpacing * 3);
    radio106->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio106);
    radio106 = radioButtonGroup->createRadioButton();
    radio106->labelText("5FPS");
    radio106->x(marginLeft + spacing * 2);
    radio106->y(marginTop + lineSpacing * 3);
    radio106->addEventListener(flRadioButtonEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(radio106);
    check001 = new flCheckBox();
    check001->labelText("Disable Streaming LED");
    check001->x(marginLeft + spacing * 0);
    check001->y(marginTop + lineSpacing * 4);
    check001->selected(true);
    //    check001->enabled(false);
    check001->addEventListener(flCheckBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(check001);
    //ofLog() << "check001 : " << check001->y() + check001->height();
    
    
    marginLeft = 270;
    marginTop = 390 + 22;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Color Contols");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    label = new flTextField();
    label->text("Expousure Time");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider101 = new flSlider(150, 10.0, 0.0, 5);
    slider101->x(marginLeft + spacing * 0);
    slider101->y(marginTop + lineSpacing * 2);
    slider101->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider101);
    label = new flTextField();
    label->text("White Balance");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 3);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider102 = new flSlider(150, 10.0, 0.0, 5);
    slider102->x(marginLeft + spacing * 0);
    slider102->y(marginTop + lineSpacing * 4);
    slider102->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider102);
    label = new flTextField();
    label->text("Brightness");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 5);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider103 = new flSlider(150, 10.0, 0.0, 5);
    slider103->x(marginLeft + spacing * 0);
    slider103->y(marginTop + lineSpacing * 6);
    slider103->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider103);
    label = new flTextField();
    label->text("Contrast");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 7);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider104 = new flSlider(150, 10.0, 0.0, 5);
    slider104->x(marginLeft + spacing * 0);
    slider104->y(marginTop + lineSpacing * 8);
    slider104->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider104);
    label = new flTextField();
    label->text("Saturation");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 9);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider105 = new flSlider(150, 10.0, 0.0, 5);
    slider105->x(marginLeft + spacing * 0);
    slider105->y(marginTop + lineSpacing * 10);
    slider105->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider105);
    label = new flTextField();
    label->text("Sharpness");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 11);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider106 = new flSlider(150, 10.0, 0.0, 5);
    slider106->x(marginLeft + spacing * 0);
    slider106->y(marginTop + lineSpacing * 12);
    slider106->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider106);
    label = new flTextField();
    label->text("Gain");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 13);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider107 = new flSlider(150, 10.0, 0.0, 5);
    slider107->x(marginLeft + spacing * 0);
    slider107->y(marginTop + lineSpacing * 14);
    slider107->addEventListener(flSliderEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(slider107);
    check101 = new flCheckBox();
    check101->labelText("Backlight Compensation");
    check101->x(marginLeft + spacing * 0);
    check101->y(marginTop + lineSpacing * 15);
    check101->selected(false);
//    check101->enabled(false);
    check001->addEventListener(flCheckBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
    addChild(check101);
    
    
    


//    label = new flTextField();
//    label->text("FPS");
//    label->x(marginLeft + spacing * 0);
//    label->y(marginTop + lineSpacing * 0);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    label->mouseEnabled(false);
//    addChild(label);
//    comboBox001 = new flComboBox(259);
//    //    comboBox001->name("Color Format");
//    comboBox001->label(label);
//    comboBox001->x(marginLeft + spacing * 0);
//    comboBox001->y(marginTop + lineSpacing * 1);
//    comboBox001->addItem<string>("5 FPS", "test0");
//    comboBox001->addItem<string>("15 FPS", "test1");
//    comboBox001->addItem<string>("30 FPS", "test2");
//    comboBox001->selectedIndex(1, false);
//    //    comboBox001->visible(false);
//    comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
//    addChild(comboBox001);
//
//    label = new flTextField();
//    label->text("Color Format");
//    label->x(marginLeft + spacing * 0);
//    label->y(marginTop + lineSpacing * 2);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    label->mouseEnabled(false);
//    addChild(label);
//    comboBox002 = new flComboBox(259);
////    comboBox002->name("Color Format");
//    comboBox002->label(label);
//    comboBox002->x(marginLeft + spacing * 0);
//    comboBox002->y(marginTop + lineSpacing * 3);
//    comboBox002->addItem<string>("COLOR MJPG", "test0");
//    comboBox002->addItem<string>("COLOR NV12", "test1");
//    comboBox002->addItem<string>("COLOR YUY2", "test2");
//    comboBox002->addItem<string>("COLOR BGRA32", "test3");
//    comboBox002->addItem<string>("DEPTH16", "test4");
//    comboBox002->addItem<string>("IR16", "test5");
//    comboBox002->addItem<string>("CUSTOM8", "test6");
//    comboBox002->addItem<string>("CUSTOM16", "test7");
//    comboBox002->addItem<string>("CUSTOM", "test7");
//    comboBox002->selectedIndex(1, false);
//    //    comboBox002->visible(false);
//    comboBox002->addEventListener(flComboBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
//    addChild(comboBox002);
//
//    label = new flTextField();
//    label->text("Color RESOLUTION");
//    label->x(marginLeft + spacing * 0);
//    label->y(marginTop + lineSpacing * 4);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    label->mouseEnabled(false);
//    addChild(label);
//    comboBox003 = new flComboBox(259);
////    comboBox003->name("Color Format");
//    comboBox003->label(label);
//    comboBox003->x(marginLeft + spacing * 0);
//    comboBox003->y(marginTop + lineSpacing * 5);
//    comboBox003->addItem<string>("OFF", "test0");
//    comboBox003->addItem<string>("720P (1280 x 720)", "test1");
//    comboBox003->addItem<string>("1080P (1920 x 1080)", "test2");
//    comboBox003->addItem<string>("1440P (2560 x 1440)", "test3");
//    comboBox003->addItem<string>("1536P (2048 x 1536)", "test4");
//    comboBox003->addItem<string>("2160P (3840 x 2160)", "test5");
//    comboBox003->addItem<string>("3072P (4096 x 3072)", "test6");
//    comboBox003->selectedIndex(1, false);
//    //    comboBox003->visible(false);
//    comboBox003->addEventListener(flComboBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
//    addChild(comboBox003);
//
//    label = new flTextField();
//    label->text("Depth Mode");
//    label->x(marginLeft + spacing * 0);
//    label->y(marginTop + lineSpacing * 6);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    label->mouseEnabled(false);
//    addChild(label);
//    comboBox004 = new flComboBox(259);
////    comboBox004->name("Color Format");
//    comboBox004->label(label);
//    comboBox004->x(marginLeft + spacing * 0);
//    comboBox004->y(marginTop + lineSpacing * 7);
//    comboBox004->addItem<string>("OFF", "test0");
//    comboBox004->addItem<string>("NFOV 2X2BINNED (320 x 288)", "test1");
//    comboBox004->addItem<string>("NFOV UNBINNED (640 x 576)", "test2");
//    comboBox004->addItem<string>("WFOV 2X2BINNED (512 x 512)", "test3");
//    comboBox004->addItem<string>("WFOV UNBINNED (1024 x 1024)", "test4");
//    comboBox004->addItem<string>("PASSIVE IR (1024 x 1024)", "test5");
//    comboBox004->selectedIndex(1, false);
//    //    comboBox004->visible(false);
//    comboBox004->addEventListener(flComboBoxEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
//    addChild(comboBox004);
//    ofLog() << "comboBox004 : " << comboBox004->y() + comboBox004->height();
//
//    marginLeft = 5;
//    marginTop = 365;
//    spacing = 150;
//    lineSpacing = 22;
//
//    label = new flTextField();
//    label->text("Depth Delay Off Color Usec");
//    label->x(marginLeft + spacing * 0);
//    label->y(marginTop + lineSpacing * 0);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    label->mouseEnabled(false);
//    addChild(label);
//    dialer001 = new flNumberDialer(150);
//    dialer001->label(label);
//    dialer001->x(marginLeft + spacing * 0);
//    dialer001->y(marginTop + lineSpacing * 1);
//    dialer001->value(0);
//    dialer001->stepValue(0.001);
//    dialer001->min(-1);
//    dialer001->max(1);
//    dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
//    addChild(dialer001);
//
//    label = new flTextField();
//    label->text("Subordinate Delay Off Master Usec");
//    label->x(marginLeft + spacing * 0);
//    label->y(marginTop + lineSpacing * 2);
//    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    label->mouseEnabled(false);
//    addChild(label);
//    dialer002 = new flNumberDialer(150);
//    dialer002->label(label);
//    dialer002->x(marginLeft + spacing * 0);
//    dialer002->y(marginTop + lineSpacing * 3);
//    dialer002->value(0);
//    dialer002->stepValue(0.001);
//    dialer002->min(-1);
//    dialer002->max(1);
//    dialer002->addEventListener(flNumberDialerEvent::CHANGE, this, &DeviceSettingsController::_uiEventHandler);
//    addChild(dialer002);
}

//--------------------------------------------------------------
//
void DeviceSettingsController::_update() {
    //cout << "[DeviceCameraViewer]update()" << endl;
}

//--------------------------------------------------------------
//
void DeviceSettingsController::_draw() {
    //cout << "[DeviceCameraViewer]draw()" << endl;
    
    if(_isMinimize) return;
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    //--------------------------------------
    
    marginLeft = 5;
    marginTop = 35;
    spacing = 150;
    lineSpacing = 20;
    
//    int camWidth = 1280 * 0.2;
//    int camHeight = 720 * 0.2;

    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    flFont::drawString("Device S/N : ", 5, marginTop);
    flFont::drawString("Color", 5, marginTop + lineSpacing);
    flFont::drawString("Depth", 270, marginTop + lineSpacing);
    flFont::drawString("IR", 535, marginTop + lineSpacing);
    flFont::drawString("Depth In Color", 5, marginTop + lineSpacing + 169);
    flFont::drawString("Color In Depth", 270, marginTop + lineSpacing + 169);
    ofPopStyle();
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void DeviceSettingsController::_uiEventHandler(flEvent& event) {
    //    cout << "[DeviceCameraViewer]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    
    //コンボボックス
    else if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
    }
    
    //チェックボックス
	else if(event.type() == flCheckBoxEvent::CHANGE) {
        flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
        flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
    }

    //ラジオボタン
	else if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
	else if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialerEvent& numberDialerEvent = *(flNumberDialerEvent*) &event;
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
    }
    
    //2Dパッド
	else if(event.type() == flPadEvent::CHANGE) {
        flPadEvent& padEvent = *(flPadEvent*) &event;
        flPad2D* pad = (flPad2D*)(event.currentTarget());
    }
    
    //スライダー
	else if(event.type() == flSliderEvent::CHANGE) {
        flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
        flSlider* slider = (flSlider*)(event.currentTarget());
    }
    
    //Vec2スライダー
	else if(event.type() == flVec2SliderEvent::CHANGE) {
        flVec2SliderEvent& sliderEvent = *(flVec2SliderEvent*) &event;
        flVec2Slider* slider = (flVec2Slider*)(event.currentTarget());
    }
    
    //Vec3スライダー
	else if(event.type() == flVec3SliderEvent::CHANGE) {
        flVec3SliderEvent& sliderEvent = *(flVec3SliderEvent*) &event;
        flVec3Slider* slider = (flVec3Slider*)(event.currentTarget());
    }
    
    //レンジスライダー
	else if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
	else if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
        flColorSlider* slider = (flColorSlider*)(event.currentTarget());
    }
    
    //ジョイスティック1D
	else if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::UP) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::DOWN) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::LEFT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::RIGHT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    
    //ジョイスティック2D
	else if(event.type() == flJoyStick2Event::CHANGE) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::UP) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::DOWN) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::LEFT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::RIGHT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
}
