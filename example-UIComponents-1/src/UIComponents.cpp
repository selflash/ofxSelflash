#include "UIComponents.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
UIComponents::UIComponents() {
    cout << "[UIComponents]UIComponents()" << endl;
    _target = this;
    name("UIComponents");
    
    //useHandCursor(true);
    
    flGraphics* g;
    g = graphics();
    //graphics->lineStyle(0.5);
    g->beginFill(0xffffff, 0.1);
    g->clear();
    g->drawRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    g->endFill();
}

//--------------------------------------------------------------
//
UIComponents::~UIComponents() {
    cout << "[UIComponents]~UIComponents()" << endl;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void UIComponents::_setup() {
    cout << "[UIComponents]_setup()" << endl;
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    //--------------------------------------
    marginLeft = 40;
    marginTop = 50;
    spacing = 100;
    lineSpacing = 40;
    
    //スライダー
    //デフォルト
    slider001 = new flSlider();
    slider001->label("SLIDER");
    slider001->x(marginLeft + spacing * 0);
    slider001->y(marginTop + lineSpacing * 0);
    addChild(slider001);
    //横幅、最小値、最大値、初期値を指定
    slider002 = new flSlider(100, 0.0, 10.0, 0.5);
    slider002->label("SLIDER");
    slider002->x(marginLeft + spacing * 0);
    slider002->y(marginTop + lineSpacing * 1);
    addChild(slider002);
    
    //レンジスライダー
    rangeSlider001 = new flRangeSlider();
    rangeSlider001->label("RANGE SLIDER");
    rangeSlider001->x(marginLeft + spacing * 0);
    rangeSlider001->y(marginTop + lineSpacing * 2);
    rangeSlider001->min(-100);
    rangeSlider001->max(1300);
    rangeSlider001->minValue(300);
    rangeSlider001->maxValue(500);
    addChild(rangeSlider001);
    
    rangeSlider002 = new flRangeSlider(200, -100, 1300, 300, 500);
    rangeSlider002->label("RANGE SLIDER");
    rangeSlider002->x(marginLeft + spacing * 0);
    rangeSlider002->y(marginTop + lineSpacing * 3);
    addChild(rangeSlider002);
    //--------------------------------------
    //--------------------------------------
    //カラースライダー
    marginLeft = 40;
    marginTop = 210;
    spacing = 100;
    lineSpacing = 60;
    
    colorSlider001 = new flColorSlider();
    colorSlider001->label("COLOR SLIDER");
    colorSlider001->x(marginLeft + spacing * 0);
    colorSlider001->y(marginTop + lineSpacing * 0);
    addChild(colorSlider001);
    //--------------------------------------
    
    //--------------------------------------
    //ボタン
    marginLeft = 270;
    marginTop = 50;
    lineSpacing = 30;
    
    btn001 = new flButton(100);
    btn001->label("BUTTON");
    btn001->x(marginLeft + spacing * 0);
    btn001->y(marginTop + lineSpacing * 0);
    btn001->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn001);
    btn002 = new flButton(100);
    btn002->label("TOGGLE");
    btn002->toggleEnabled(true);
    btn002->x(marginLeft + spacing * 0);
    btn002->y(marginTop + lineSpacing * 1);
    btn002->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn002);
    btn003 = new flButton(100);
    btn003->label("WHITE");
    btn003->x(marginLeft + spacing * 0);
    btn003->y(marginTop + lineSpacing * 2);
    btn003->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn003);
    btn004 = new flButton(100);
    btn004->label("GLAY");
    btn004->x(marginLeft + spacing * 0);
    btn004->y(marginTop + lineSpacing * 3);
    btn004->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn004);
    btn005 = new flButton(100);
    btn005->label("BLACK");
    btn005->x(marginLeft + spacing * 0);
    btn005->y(marginTop + lineSpacing * 4);
    btn005->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn005);
    //--------------------------------------
    
    //--------------------------------------
    //ラジオボタン
    marginLeft = 400;
    marginTop = 50;
    lineSpacing = 30;
    
    radio001 = new flRadioButton();
    radio001->label("RADIO BUTTON");
    radio001->x(marginLeft + spacing * 0);
    radio001->y(marginTop + lineSpacing * 0);
    addChild(radio001);
    radio002 = new flRadioButton();
    radio002->label("RADIO BUTTON");
    radio002->x(marginLeft + spacing * 0);
    radio002->y(marginTop + lineSpacing * 1);
    addChild(radio002);
    radio003 = new flRadioButton();
    radio003->label("RADIO BUTTON");
    radio003->x(marginLeft + spacing * 0);
    radio003->y(marginTop + lineSpacing * 2);
    addChild(radio003);
    //--------------------------------------
    
    //--------------------------------------
    //コンボボックス
    marginLeft = 700;
    marginTop = 50;
    spacing = 150;
    lineSpacing = 40;
    
    comboBox001 = new flComboBox();
    comboBox001->name("COMBO BOX 1");
    comboBox001->label("COMBO BOX 1");
    comboBox001->x(marginLeft + spacing * 0);
    comboBox001->y(marginTop + lineSpacing * 0);
    comboBox001->addItem<string>("TEST0", "test0");
    comboBox001->addItem<string>("TEST1", "test1");
    comboBox001->addItem<string>("TEST2", "test2");
    comboBox001->addItem<string>("TEST3", "test3");
    comboBox001->addItem<string>("TEST4", "test4");
    comboBox001->addItem<string>("TEST5", "test5");
    comboBox001->addItem<string>("TEST6", "test6");
    comboBox001->addItem<string>("TEST7", "test7");
    comboBox001->selectedIndex(1, false);
//    comboBox001->visible(false);
    addChild(comboBox001);
    
    comboBox002 = new flComboBox();
    comboBox002->name("COMBO BOX 2");
    comboBox002->label("COMBO BOX 2");
    comboBox002->x(marginLeft + spacing * 0);
    comboBox002->y(marginTop + lineSpacing * 1);
    comboBox002->addItem<float>("0.0", 0.0);
    comboBox002->addItem<float>("0.1", 0.1);
    comboBox002->addItem<float>("0.2", 0.2);
    comboBox002->addItem<float>("0.3", 0.3);
    comboBox002->selectedIndex(1, false);
    addChild(comboBox002);
    
    comboBox003 = new flComboBox();
    comboBox003->name("COMBO BOX 3");
    comboBox003->label("COMBO BOX 3");
    comboBox003->x(marginLeft + spacing * 0);
    comboBox003->y(marginTop + lineSpacing * 2);
    comboBox003->addItem<flComboBox*>("COMBO BOX 1", comboBox001);
    comboBox003->addItem<flComboBox*>("COMBO BOX 2", comboBox002);
    comboBox003->selectedIndex(1, false);
    addChild(comboBox003);
    
    //    comboBox003->removeAll();
    //    comboBox003->addItem<float>("0.0", 0.0);
    //    comboBox003->addItem<float>("0.1", 0.1);
    //    comboBox003->addItem<float>("0.2", 0.2);
    //    comboBox003->addItem<float>("0.3", 0.3);
    //--------------------------------------
    
    //--------------------------------------
    //2Dパッド
    marginLeft = 700;
    marginTop = 200;
    spacing = 170;
    lineSpacing = 30;
    
    pad001 = new flPad2D(160, 160, -500, 500, -500, 500);
    pad001->x(marginLeft + spacing * 0);
    pad001->y(marginTop + lineSpacing * 0);
    addChild(pad001);
    
    pad002 = new flPad2D(160, 160, 0, 1000, 0, 1000);
    pad002->x(marginLeft + spacing * 1);
    pad002->y(marginTop + lineSpacing * 0);
    addChild(pad002);
    //--------------------------------------
    
    //--------------------------------------
    //インプットテキストフィールド
    marginLeft = 40;
    marginTop = 500;
    spacing = 150;
    lineSpacing = 30;
    
    text001 = new flTextField();
    text001->text("test", 0x0000);
    text001->x(marginLeft + spacing * 0);
    text001->y(marginTop + lineSpacing * 0);
    text001->type(TEXT_FIELD_TYPE_INPUT);
    addChild(text001);
    text002 = new flTextField();
    text002->text("test", 0x0000);
    text002->x(marginLeft + spacing * 0);
    text002->y(marginTop + lineSpacing * 1);
    text002->type(TEXT_FIELD_TYPE_INPUT);
    addChild(text002);
    
    addChild(text001);
    //--------------------------------------
    
    //--------------------------------------
    //カラーピッカー
    marginLeft = 140;
    marginTop = 500;
    spacing = 150;
    lineSpacing = 30;
    
    colorPicker001 = new flCircleColorPicker();
    colorPicker001->label("COLOR PICKER");
    colorPicker001->x(marginLeft + spacing * 0);
    colorPicker001->y(marginTop + lineSpacing * 0);
    addChild(colorPicker001);
    colorPicker001->addEventListener(flColorPickerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    //--------------------------------------
    
    //--------------------------------------
    //ジョイスティック
    marginLeft = 300;
    marginTop = 500;
    spacing = 150;
    lineSpacing = 30;
    
    joystick001 = new flJoystick();
    joystick001->label("JOYSTICK");
    joystick001->x(marginLeft + spacing * 0);
    joystick001->y(marginTop + lineSpacing * 0);
    addChild(joystick001);
    //--------------------------------------
    
    //--------------------------------------
    //ナンバーダイアラー
    marginLeft = 400;
    marginTop = 500;
    spacing = 150;
    lineSpacing = 50;
    
    dialer001 = new flNumberDialer();
    dialer001->label("NUMBER DIALER 1");
    dialer001->x(marginLeft + spacing * 0);
    dialer001->y(marginTop + lineSpacing * 0);
    dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer001);
    dialer002 = new flNumberDialer();
    dialer002->label("NUMBER DIALER 2");
    dialer002->x(marginLeft + spacing * 0);
    dialer002->y(marginTop + lineSpacing * 1);
    dialer002->value(-500);
    dialer002->stepValue(10);
    dialer002->max(0);
    dialer002->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer002);
    dialer003 = new flNumberDialer();
    dialer003->label("NUMBER DIALER 3");
    dialer003->type(FL_VERTICALLY);
    dialer003->x(marginLeft + spacing * 1);
    dialer003->y(marginTop + lineSpacing * 0);
    dialer003->value(10.1);
    dialer003->stepValue(0.1f);
    dialer003->min(-100);
    dialer003->max(100);
    dialer003->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer003);
    //--------------------------------------
    
    addChild(comboBox003);
    addChild(comboBox002);
    addChild(comboBox001);
}

//--------------------------------------------------------------
//
void UIComponents::_update() {

}

//--------------------------------------------------------------
//
void UIComponents::_draw() {

}

//==============================================================
// PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void UIComponents::_uiEventHandler(flEvent& event) {
    //cout << "[UIComponents]_controllerEventHandler(" << event.type() << ")" << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        //メインコントローラー
        if(button == btn001);
        if(button == btn002);
        if(button == btn003) ofBackground(255, 255, 255, 255);
        if(button == btn004) ofBackground(120, 120, 120, 255);
        if(button == btn005) ofBackground(0, 0, 0, 255);
    };
    
    //マウスアップ
    if(event.type() == flMouseEvent::MOUSE_UP) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == btn001);
        if(button == btn002);
        if(button == btn003);
        if(button == btn004);
        if(button == btn005);
    };
    
    //コンボボックス
    if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
    };
    
    //ラジオボタン
    if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
    if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialerEvent& numberDialerEvent = *(flNumberDialerEvent*) &event;
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
    }
    
    //2Dパッド
    if(event.type() == flPadEvent::CHANGE) {
        flPadEvent& padEvent = *(flPadEvent*) &event;
        flPad2D* pad = (flPad2D*)(event.currentTarget());
    }
    
    //スライダー
    if(event.type() == flSliderEvent::CHANGE) {
        flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
        flSlider* slider = (flSlider*)(event.currentTarget());
        if(slider == slider001);
        if(slider == slider002);
    }
    
    //レンジスライダー
    if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
    if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
        flColorSlider* slider = (flColorSlider*)(event.currentTarget());
    }
    
    //カラーピッカー
    if(event.type() == flColorPickerEvent::CHANGE) {
        flColorPickerEvent& colorPickerEvent = *(flColorPickerEvent*) &event;
        flCircleColorPicker* colorPicker = (flCircleColorPicker*)(event.currentTarget());
    }
    
    //ジョイスティックパッド
    if(event.type() == flJoystickEvent::UP) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
    if(event.type() == flJoystickEvent::DOWN) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
    if(event.type() == flJoystickEvent::LEFT) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
    if(event.type() == flJoystickEvent::RIGHT) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
}