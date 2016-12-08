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
    g->clear();
    g->lineStyle(1, 0xffffff, 0.5);
    g->beginFill(0xffffff, 0.1);
    g->drawRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    g->moveTo(10 + 150 + 10, 0);
    g->lineTo(10 + 150 + 10, ofGetHeight());
    g->moveTo(10 + 150 + 10 + 10 + 150 + 10, 0);
    g->lineTo(10 + 150 + 10 + 10 + 150 + 10, ofGetHeight());
    g->moveTo(10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10, 0);
    g->lineTo(10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10, ofGetHeight());
    g->moveTo(10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10, 0);
    g->lineTo(10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10, ofGetHeight());
    g->moveTo(10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10, 0);
    g->lineTo(10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10, ofGetHeight());
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
    flTextField* label = NULL;
    
    //--------------------------------------
    marginLeft = 10;
    marginTop = 10;
    spacing = 155;
    lineSpacing = 22.5;
    
    //スライダー
    //デフォルト
    label = new flTextField();
    label->text("Slider1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider001 = new flSlider(150);
    slider001->x(marginLeft + spacing * 0);
    slider001->y(marginTop + lineSpacing * 1);
    slider001->addEventListener(flSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(slider001);
    
    //横幅、最小値、最大値、初期値を指定
    label = new flTextField();
    label->text("Slider2");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider002 = new flSlider(150, 10.0, 0.0, 5);
    slider002->value(1);
    slider002->x(marginLeft + spacing * 0);
    slider002->y(marginTop + lineSpacing * 3);
    slider002->addEventListener(flSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(slider002);
    
    //レンジスライダー
    label = new flTextField();
    label->text("Range Slider1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 4);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    rangeSlider001 = new flRangeSlider(150);
    rangeSlider001->x(marginLeft + spacing * 0);
    rangeSlider001->y(marginTop + lineSpacing * 5);
    rangeSlider001->min(-100);
    rangeSlider001->max(1300);
    rangeSlider001->minValue(300);
    rangeSlider001->maxValue(500);
    rangeSlider001->addEventListener(flRangeSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(rangeSlider001);
    
    label = new flTextField();
    label->text("Range Slider2");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 6);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    rangeSlider002 = new flRangeSlider(150, -100, 1300, 300, 500);
    rangeSlider002->x(marginLeft + spacing * 0);
    rangeSlider002->y(marginTop + lineSpacing * 7);
    rangeSlider002->addEventListener(flRangeSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(rangeSlider002);
    //--------------------------------------
    
    //--------------------------------------
    //カラースライダー
    marginLeft = 10;
    marginTop = 190;
    spacing = 100;
    lineSpacing = 108;
    
    label = new flTextField();
    label->text("Color Slider(RGBA)");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    colorSlider001 = new flColorSlider(150 - 15, true);
    colorSlider001->x(marginLeft + spacing * 0);
    colorSlider001->y(marginTop + lineSpacing * 0 + 22.5);
    colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(colorSlider001);
    
    label = new flTextField();
    label->text("Color Slider(RGB)");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    colorSlider002 = new flColorSlider(150 - 15, false);
    colorSlider002->x(marginLeft + spacing * 0);
    colorSlider002->y(marginTop + lineSpacing * 1 + 22.5);
    colorSlider002->addEventListener(flColorSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(colorSlider002);
    //--------------------------------------

    //--------------------------------------
    //Vec2スライダー
    marginLeft = 10;
    marginTop = 385;
    spacing = 100;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Vec2 Slider");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    vec2Slider001 = new flVec2Slider(150 - 15);
    vec2Slider001->x(marginLeft + spacing * 0);
    vec2Slider001->y(marginTop + lineSpacing * 1);
    vec2Slider001->addEventListener(flVec2SliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(vec2Slider001);
    //--------------------------------------

    //--------------------------------------
    //Vec3スライダー
    marginLeft = 10;
    marginTop = 450;
    spacing = 100;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Vec3 Slider");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    vec3Slider001 = new flVec3Slider(150 - 15);
    vec3Slider001->x(marginLeft + spacing * 0);
    vec3Slider001->y(marginTop + lineSpacing * 1);
    vec3Slider001->addEventListener(flVec3SliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(vec3Slider001);
    //--------------------------------------
    
    //--------------------------------------
    //インプットテキストフィールド
    marginLeft = 10;
    marginTop = 550;
    spacing = 150;
    lineSpacing = 22.5;
    
    text001 = new flTextField();
    text001->text("Test", 0x0000);
    text001->width(150);
    text001->x(marginLeft + spacing * 0);
    text001->y(marginTop + lineSpacing * 0);
    text001->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    text001->addEventListener(flEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(text001);
    text002 = new flTextField();
    text002->text("Test", 0x0000);
    text002->width(150);
    text002->x(marginLeft + spacing * 0);
    text002->y(marginTop + lineSpacing * 1);
    text002->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    text002->addEventListener(flEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(text002);
    
    addChild(text001);
    //--------------------------------------

    
    //--------------------------------------
    //カラーピッカー
    marginLeft = 10;
    marginTop = 550 + 22.5 * 2 + 5;
    spacing = 150;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Color Picker");
    label->x(marginLeft + spacing * 0 + 25);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    colorPicker001 = new flCircleColorPicker();
    colorPicker001->label(label);
    colorPicker001->x(marginLeft + spacing * 0 + 25);
    colorPicker001->y(marginTop + lineSpacing * 1);
    addChild(colorPicker001);
    colorPicker001->addEventListener(flColorPickerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    //--------------------------------------
    

    //--------------------------------------
    //ボタン
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 10;
    lineSpacing = 22.5;
    
    button001 = new flButton(150);
    button001->labelText("Button");
    button001->x(marginLeft + spacing * 0);
    button001->y(marginTop + lineSpacing * 0);
    button001->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button001);
    button002 = new flButton(150);
    button002->labelText("Lock", "selected");
    button002->labelText("Unlock", "notSelected");
    button002->toggleEnabled(true);
    button002->x(marginLeft + spacing * 0);
    button002->y(marginTop + lineSpacing * 1);
    button002->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    button002->addEventListener(flMouseEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(button002);
    button003 = new flButton(150);
    button003->labelText("White");
    button003->x(marginLeft + spacing * 0);
    button003->y(marginTop + lineSpacing * 2);
    button003->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button003);
    button004 = new flButton(150);
    button004->labelText("Glay");
    button004->x(marginLeft + spacing * 0);
    button004->y(marginTop + lineSpacing * 3);
    button004->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button004);
    button005 = new flButton(150);
    button005->labelText("Black");
    button005->x(marginLeft + spacing * 0);
    button005->y(marginTop + lineSpacing * 4);
    button005->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button005);
    button006 = new flButton(150);
    button006->labelText("Disable");
    button006->x(marginLeft + spacing * 0);
    button006->y(marginTop + lineSpacing * 5);
    button006->enabled(false);
    button006->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button006);
    //--------------------------------------
    
    //--------------------------------------
    //ラジオボタン
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 145.5;
    lineSpacing = 22.5;
    
    radio001 = new flRadioButton();
    radio001->labelText("Radio Button");
    radio001->x(marginLeft + spacing * 0);
    radio001->y(marginTop + lineSpacing * 0);
    radio001->selected(true);
    radio001->enabled(false);
    radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(radio001);
    radio002 = new flRadioButton();
    radio002->labelText("Radio Button");
    radio002->x(marginLeft + spacing * 0);
    radio002->y(marginTop + lineSpacing * 1);
    radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(radio002);
    radio003 = new flRadioButton();
    radio003->labelText("Radio Button");
    radio003->x(marginLeft + spacing * 0);
    radio003->y(marginTop + lineSpacing * 2);
    radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(radio003);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 145.5 + 22.5 * 3;
    spacing = 150;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Joystick 1D");
    label->x(marginLeft + spacing * 0 + 25);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 145.5 + 22.5 * 3;
    spacing = 22.66;
    lineSpacing = 22.5;
    
    joystick1D001 = new flJoystick1D(100);
    joystick1D001->label(label);
    joystick1D001->x(marginLeft + spacing * 0);
    joystick1D001->y(marginTop + lineSpacing * 1);
    joystick1D001->type(flJoystick1D::HORIZONTALLY);
    joystick1D001->addEventListener(flJoystick1DEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1D001);
    joystick1D002 = new flJoystick1D(100);
    joystick1D002->label(label);
    joystick1D002->x(marginLeft + spacing * 1);
    joystick1D002->y(marginTop + lineSpacing * 1);
    joystick1D002->type(flJoystick1D::HORIZONTALLY);
    joystick1D002->addEventListener(flJoystick1DEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1D002);
    joystick1D003 = new flJoystick1D(100);
    joystick1D003->label(label);
    joystick1D003->x(marginLeft + spacing * 2);
    joystick1D003->y(marginTop + lineSpacing * 1);
    joystick1D003->type(flJoystick1D::HORIZONTALLY);
    addChild(joystick1D003);
    joystick1D004 = new flJoystick1D(100);
    joystick1D004->label(label);
    joystick1D004->x(marginLeft + spacing * 3);
    joystick1D004->y(marginTop + lineSpacing * 1);
    joystick1D004->type(flJoystick1D::HORIZONTALLY);
    addChild(joystick1D004);
    joystick1D005 = new flJoystick1D(100);
    joystick1D005->label(label);
    joystick1D005->x(marginLeft + spacing * 4);
    joystick1D005->y(marginTop + lineSpacing * 1);
    joystick1D005->type(flJoystick1D::HORIZONTALLY);
    addChild(joystick1D005);
    joystick1D006 = new flJoystick1D(100);
    joystick1D006->label(label);
    joystick1D006->x(marginLeft + spacing * 5);
    joystick1D006->y(marginTop + lineSpacing * 1);
    joystick1D006->type(flJoystick1D::HORIZONTALLY);
    addChild(joystick1D006);
    joystick1D007 = new flJoystick1D(100);
    joystick1D007->label(label);
    joystick1D007->x(marginLeft + spacing * 6);
    joystick1D007->y(marginTop + lineSpacing * 1);
    joystick1D007->type(flJoystick1D::HORIZONTALLY);
    addChild(joystick1D007);
    
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 145.5 + 22.5 * 3 + 22.5 * 6;
    spacing = 22.66;
    lineSpacing = 22.5;
    
    joystick1D101 = new flJoystick1D(150);
    joystick1D101->label(label);
    joystick1D101->x(marginLeft + spacing * 0);
    joystick1D101->y(marginTop + lineSpacing * 0);
    joystick1D101->type(flJoystick1D::VERTICALLY);
    joystick1D101->addEventListener(flJoystick1DEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1D101);
    joystick1D102 = new flJoystick1D(150);
    joystick1D102->label(label);
    joystick1D102->x(marginLeft + spacing * 0);
    joystick1D102->y(marginTop + lineSpacing * 1);
    joystick1D102->type(flJoystick1D::VERTICALLY);
    joystick1D102->addEventListener(flJoystick1DEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1D102);
    //--------------------------------------
    
    //--------------------------------------
    //ジョイスティック
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 145.5 + 22.5 * 3 + 22.5 * 6 + 22.5 * 2;
    spacing = 150;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Joystick 2D");
    label->x(marginLeft + spacing * 0 + 25);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    joystick2D001 = new flJoystick2D(100);
    joystick2D001->label(label);
    joystick2D001->x(marginLeft + spacing * 0 + 25);
    joystick2D001->y(marginTop + lineSpacing * 1);
    addChild(joystick2D001);
    //--------------------------------------

    //--------------------------------------
    //ナンバーダイアラー
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 145.5 + 22.5 * 3 + 22.5 * 6 + 22.5 * 2 + 22.5 + 100 + 5;
    spacing = 150;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Number Dialer 1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    dialer001 = new flNumberDialer(150);
    dialer001->label(label);
    dialer001->x(marginLeft + spacing * 0);
    dialer001->y(marginTop + lineSpacing * 1);
    dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer001);
    
    label = new flTextField();
    label->text("Number Dialer 2");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    dialer002 = new flNumberDialer(150);
    dialer002->label(label);
    dialer002->dragVector(flNumberDialer::HORIZONTALLY);
    dialer002->x(marginLeft + spacing * 0);
    dialer002->y(marginTop + lineSpacing * 3);
    dialer002->value(-500);
    dialer002->stepValue(10);
    dialer002->max(100);
    dialer002->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer002);
    
    label = new flTextField();
    label->text("Number Dialer 3");
    label->x(marginLeft + spacing * 0 + 36);
    label->y(marginTop + lineSpacing * 4);
    label->rotation(90);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    dialer003 = new flNumberDialer(150);
    dialer003->label(label);
    dialer003->type(flNumberDialer::VERTICALLY);
    dialer003->x(marginLeft + spacing * 0);
    dialer003->y(marginTop + lineSpacing * 4);
    dialer003->value(10.1);
    dialer003->stepValue(0.1);
    dialer003->min(-100);
    dialer003->max(100);
    dialer003->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer003);
    //--------------------------------------
    
    //--------------------------------------
    //コンボボックス
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 10;
    spacing = 150;
    lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Combo Box 1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    comboBox001 = new flComboBox();
    comboBox001->name("Combo Box 1");
    comboBox001->label(label);
    comboBox001->x(marginLeft + spacing * 0);
    comboBox001->y(marginTop + lineSpacing * 1);
    comboBox001->addItem<string>("Test0", "test0");
    comboBox001->addItem<string>("Test1", "test1");
    comboBox001->addItem<string>("Test2", "test2");
    comboBox001->addItem<string>("Test3", "test3");
    comboBox001->addItem<string>("Test4", "test4");
    comboBox001->addItem<string>("Test5", "test5");
    comboBox001->addItem<string>("Test6", "test6");
    comboBox001->addItem<string>("Test7", "test7");
    comboBox001->selectedIndex(1, false);
//    comboBox001->visible(false);
    comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(comboBox001);
    
    label = new flTextField();
    label->text("Combo Box 2");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    comboBox002 = new flComboBox();
    comboBox002->name("Combo Box 2");
    comboBox002->label(label);
    comboBox002->x(marginLeft + spacing * 0);
    comboBox002->y(marginTop + lineSpacing * 3);
    comboBox002->addItem<float>("0.0", 0.0);
    comboBox002->addItem<float>("0.1", 0.1);
    comboBox002->addItem<float>("0.2", 0.2);
    comboBox002->addItem<float>("0.3", 0.3);
    comboBox002->selectedIndex(1, false);
    comboBox002->addEventListener(flComboBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(comboBox002);
    
    label = new flTextField();
    label->text("Combo Box 3");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 4);
    label->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    comboBox003 = new flComboBox();
    comboBox003->name("Combo Box 3");
    comboBox003->label(label);
    comboBox003->x(marginLeft + spacing * 0);
    comboBox003->y(marginTop + lineSpacing * 5);
    comboBox003->addItem<flComboBox*>("Combo Box 1", comboBox001);
    comboBox003->addItem<flComboBox*>("Combo Box 2", comboBox002);
    comboBox003->selectedIndex(1, false);
    comboBox003->addEventListener(flComboBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(comboBox003);
    
    //    comboBox003->removeAll();
    //    comboBox003->addItem<float>("0.0", 0.0);
    //    comboBox003->addItem<float>("0.1", 0.1);
    //    comboBox003->addItem<float>("0.2", 0.2);
    //    comboBox003->addItem<float>("0.3", 0.3);
    //--------------------------------------
    
    //--------------------------------------
    //2Dパッド
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 10;
    spacing = 170;
    lineSpacing = 30;
    
    pad001 = new flPad2D(160, 160, -500, 500, -500, 500);
    pad001->x(marginLeft + spacing * 0);
    pad001->y(marginTop + lineSpacing * 0);
    pad001->addEventListener(flPadEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(pad001);
    
    pad002 = new flPad2D(160, 160, 0, 1000, 0, 1000);
    pad002->x(marginLeft + spacing * 1);
    pad002->y(marginTop + lineSpacing * 0);
    pad002->addEventListener(flPadEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(pad002);
    //--------------------------------------
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
        if(button == button001);
        if(button == button002);
        if(button == button003) ofBackground(255, 255, 255, 255);
        if(button == button004) ofBackground(120, 120, 120, 255);
        if(button == button005) ofBackground(0, 0, 0, 255);
    };
    
    //マウスアップ
    if(event.type() == flMouseEvent::MOUSE_UP) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == button001);
        if(button == button002);
        if(button == button003);
        if(button == button004);
        if(button == button005);
    };
    //マウスチェンジ
    if(event.type() == flMouseEvent::CHANGE) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == button001);
        if(button == button002) button006->enabled(button->selected());
        if(button == button003);
        if(button == button004);
        if(button == button005);
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
        
        if(radio == radio002) {
            radio001->enabled(radio->selected());
        }
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
    
    //ジョイスティック1D
    if(event.type() == flJoystick1DEvent::CHANGE) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::UP) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::DOWN) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::LEFT) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::RIGHT) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    
    //ジョイスティック2D
    if(event.type() == flJoystick2DEvent::CHANGE) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::UP) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::DOWN) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::LEFT) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::RIGHT) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
}
