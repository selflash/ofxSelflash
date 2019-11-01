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
    lineSpacing = 22;
    
    //スライダー
    //デフォルト
    label = new flTextField();
    label->text("Slider1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    slider001 = new flSlider(150);
    slider001->x(marginLeft + spacing * 0);
    slider001->y(marginTop + lineSpacing * 1);
    slider001->addEventListener(flSliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(slider001);
    
    //横幅、最小値、最大値、初期値を指定
    label = new flTextField();
    label->text("Slider2 (Inverse)");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 2);
    //    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Vec2 Slider Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Vec3 Slider Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    vec3Slider001 = new flVec3Slider(150 - 15);
    vec3Slider001->x(marginLeft + spacing * 0);
    vec3Slider001->y(marginTop + lineSpacing * 1);
    vec3Slider001->addEventListener(flVec3SliderEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(vec3Slider001);
    //cout << vec3Slider001->y() + vec3Slider001->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //インプットテキストフィールド
    marginLeft = 10;
    marginTop = 537;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Text Field Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    text001 = new flTextField();
    text001->text("Test", 0x0000);
    text001->width(150);
    text001->x(marginLeft + spacing * 0);
    text001->y(marginTop + lineSpacing * 1);
    text001->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    text001->addEventListener(flEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(text001);
    text002 = new flTextField();
    text002->text("Test", 0x0000);
    text002->width(150);
    text002->x(marginLeft + spacing * 0);
    text002->y(marginTop + lineSpacing * 2);
    text002->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    text002->addEventListener(flEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(text002);
    //cout << text002->y() + text002->height() << endl;
    
    addChild(text001);
    //--------------------------------------
    
    
    //--------------------------------------
    //カラーピッカー
    marginLeft = 10;
    marginTop = 610;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Color Picker Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Button Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    button001 = new flButton(150);
    button001->labelText("Button");
    button001->x(marginLeft + spacing * 0);
    button001->y(marginTop + lineSpacing * 1);
    button001->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button001);
    button002 = new flButton(150);
    button002->labelText("Lock", "selected");
    button002->labelText("Unlock", "notSelected");
    button002->toggleEnabled(true);
    button002->x(marginLeft + spacing * 0);
    button002->y(marginTop + lineSpacing * 2);
    button002->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    button002->addEventListener(flMouseEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(button002);
    button003 = new flButton(150);
    button003->labelText("White");
    button003->x(marginLeft + spacing * 0);
    button003->y(marginTop + lineSpacing * 3);
    button003->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button003);
    button004 = new flButton(150);
    button004->labelText("Glay");
    button004->x(marginLeft + spacing * 0);
    button004->y(marginTop + lineSpacing * 4);
    button004->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button004);
    button005 = new flButton(150);
    button005->labelText("Black");
    button005->x(marginLeft + spacing * 0);
    button005->y(marginTop + lineSpacing * 5);
    button005->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button005);
    button006 = new flButton(150);
    button006->labelText("Disable");
    button006->x(marginLeft + spacing * 0);
    button006->y(marginTop + lineSpacing * 6);
    button006->enabled(false);
    button006->addEventListener(flMouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(button006);
    //    cout << button006->y() + button006->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //チェックボックス
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 163;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Check Box Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    check001 = new flCheckBox();
    check001->labelText("Check Box 1");
    check001->x(marginLeft + spacing * 0);
    check001->y(marginTop + lineSpacing * 1);
    check001->selected(true);
    //    check001->enabled(false);
    check001->addEventListener(flCheckBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(check001);
    check002 = new flCheckBox();
    check002->labelText("Check Box 2");
    check002->x(marginLeft + spacing * 0);
    check002->y(marginTop + lineSpacing * 2);
    check002->addEventListener(flCheckBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(check002);
    check003 = new flCheckBox();
    check003->labelText("Check Box 3");
    check003->x(marginLeft + spacing * 0);
    check003->y(marginTop + lineSpacing * 3);
    check003->addEventListener(flCheckBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(check003);
    //    cout << check003->y() + check003->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //ラジオボタン
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 250;
    lineSpacing = 22;
    
    radioButtonGroup = new flRadioButtonGroup();
    
    label = new flTextField();
    label->text("Radio Button Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    radio001 = radioButtonGroup->createRadioButton();
    radio001->labelText("Radio Button 1");
    radio001->x(marginLeft + spacing * 0);
    radio001->y(marginTop + lineSpacing * 1);
    radio001->selected(true);
    //radio001->enabled(false);
    radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(radio001);
    radio002 = radioButtonGroup->createRadioButton();
    radio002->labelText("Radio Button 2");
    radio002->x(marginLeft + spacing * 0);
    radio002->y(marginTop + lineSpacing * 2);
    radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(radio002);
    radio003 = radioButtonGroup->createRadioButton();
    radio003->labelText("Radio Button 3");
    radio003->x(marginLeft + spacing * 0);
    radio003->y(marginTop + lineSpacing * 3);
    radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(radio003);
    //    cout << radio003->y() + radio003->height() << endl;
    
    //When delete the radio button.
    //    removeChild(radio001);
    //    delete radio001;
    //    radio001 = NULL;
    //When leave the group.
    //    radioButtonGroup->removeRadioButton(radio001);
    //You can delete only the radio button group.
    //    delete radioButtonGroup;
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 337;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Joystick1 Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    //    marginLeft = 10 + 150 + 10 + 10;
    //    marginTop = 275;
    spacing = 22;
    lineSpacing = 22;
    
    joystick1001 = new flJoyStick1(100);
    joystick1001->label(label);
    joystick1001->x(marginLeft + spacing * 0);
    joystick1001->y(marginTop + lineSpacing * 1);
    joystick1001->type(flJoyStick1::HORIZONTALLY);
    joystick1001->addEventListener(flJoyStick1Event::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1001);
    joystick1002 = new flJoyStick1(100);
    joystick1002->label(label);
    joystick1002->x(marginLeft + spacing * 1);
    joystick1002->y(marginTop + lineSpacing * 1);
    joystick1002->type(flJoyStick1::HORIZONTALLY);
    joystick1002->addEventListener(flJoyStick1Event::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1002);
    joystick1003 = new flJoyStick1(100);
    joystick1003->label(label);
    joystick1003->x(marginLeft + spacing * 2);
    joystick1003->y(marginTop + lineSpacing * 1);
    joystick1003->type(flJoyStick1::HORIZONTALLY);
    addChild(joystick1003);
    joystick1004 = new flJoyStick1(100);
    joystick1004->label(label);
    joystick1004->x(marginLeft + spacing * 3);
    joystick1004->y(marginTop + lineSpacing * 1);
    joystick1004->type(flJoyStick1::HORIZONTALLY);
    addChild(joystick1004);
    joystick1005 = new flJoyStick1(100);
    joystick1005->label(label);
    joystick1005->x(marginLeft + spacing * 4);
    joystick1005->y(marginTop + lineSpacing * 1);
    joystick1005->type(flJoyStick1::HORIZONTALLY);
    addChild(joystick1005);
    joystick1006 = new flJoyStick1(100);
    joystick1006->label(label);
    joystick1006->x(marginLeft + spacing * 5);
    joystick1006->y(marginTop + lineSpacing * 1);
    joystick1006->type(flJoyStick1::HORIZONTALLY);
    addChild(joystick1006);
    joystick1007 = new flJoyStick1(100);
    joystick1007->label(label);
    joystick1007->x(marginLeft + spacing * 6);
    joystick1007->y(marginTop + lineSpacing * 1);
    joystick1007->type(flJoyStick1::HORIZONTALLY);
    addChild(joystick1007);
    //cout << joystick1007->y() + joystick1007->height() << endl;
    
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 470;
    spacing = 22;
    lineSpacing = 22;
    
    joystick1101 = new flJoyStick1(150);
    joystick1101->label(label);
    joystick1101->x(marginLeft + spacing * 0);
    joystick1101->y(marginTop + lineSpacing * 0);
    joystick1101->type(flJoyStick1::VERTICALLY);
    joystick1101->addEventListener(flJoyStick1Event::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1101);
    joystick1102 = new flJoyStick1(150);
    joystick1102->label(label);
    joystick1102->x(marginLeft + spacing * 0);
    joystick1102->y(marginTop + lineSpacing * 1);
    joystick1102->type(flJoyStick1::VERTICALLY);
    joystick1102->addEventListener(flJoyStick1Event::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(joystick1102);
    //    cout << joystick1102->y() + joystick1102->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //ジョイスティック
    marginLeft = 10 + 150 + 10 + 10;
    marginTop = 506;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Joystick2 Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    joystick2001 = new flJoyStick2(100);
    joystick2001->label(label);
    joystick2001->x(marginLeft + spacing * 0 + 25);
    joystick2001->y(marginTop + lineSpacing * 1);
    addChild(joystick2001);
    //cout << joystick2001->y() + joystick2001->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //ナンバーダイアラー
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 10;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Number Dialer Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    label = new flTextField();
    label->text("Number Dialer 1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    dialer001 = new flNumberDialer(150);
    dialer001->label(label);
    dialer001->x(marginLeft + spacing * 0);
    dialer001->y(marginTop + lineSpacing * 2);
    dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer001);
    
    label = new flTextField();
    label->text("Number Dialer 2");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 3);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    dialer002 = new flNumberDialer(150);
    dialer002->label(label);
    dialer002->dragVector(flNumberDialer::HORIZONTALLY);
    dialer002->x(marginLeft + spacing * 0);
    dialer002->y(marginTop + lineSpacing * 4);
    dialer002->value(-500);
    dialer002->stepValue(10);
    dialer002->max(100);
    dialer002->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer002);
    
    label = new flTextField();
    label->text("Number Dialer 3");
    label->x(marginLeft + spacing * 0 + 40);
    label->y(marginTop + lineSpacing * 5 + 10);
    label->rotation(90);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    dialer003 = new flNumberDialer(100);
    dialer003->label(label);
    dialer003->type(flNumberDialer::VERTICALLY);
    dialer003->x(marginLeft + spacing * 0);
    dialer003->y(marginTop + lineSpacing * 5 + 10);
    dialer003->value(10.1);
    dialer003->stepValue(0.1);
    dialer003->min(-100);
    dialer003->max(100);
    dialer003->addEventListener(flNumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(dialer003);
    //    cout << dialer003->y() + dialer003->width() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //コンボボックス
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 250;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Combo Box Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    label = new flTextField();
    label->text("Combo Box 1");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 1);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    comboBox001 = new flComboBox();
    comboBox001->name("Combo Box 1");
    comboBox001->label(label);
    comboBox001->x(marginLeft + spacing * 0);
    comboBox001->y(marginTop + lineSpacing * 2);
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
    label->y(marginTop + lineSpacing * 3);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    comboBox002 = new flComboBox();
    comboBox002->name("Combo Box 2");
    comboBox002->label(label);
    comboBox002->x(marginLeft + spacing * 0);
    comboBox002->y(marginTop + lineSpacing * 4);
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
    label->y(marginTop + lineSpacing * 5);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    comboBox003 = new flComboBox();
    comboBox003->name("Combo Box 3");
    comboBox003->label(label);
    comboBox003->x(marginLeft + spacing * 0);
    comboBox003->y(marginTop + lineSpacing * 6);
    comboBox003->addItem<flComboBox*>("Combo Box 1", comboBox001);
    comboBox003->addItem<flComboBox*>("Combo Box 2", comboBox002);
    comboBox003->selectedIndex(1, false);
    comboBox003->addEventListener(flComboBoxEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(comboBox003);
    //    cout << comboBox003->y() + comboBox003->height() << endl;
    
    //    comboBox003->removeAll();
    //    comboBox003->addItem<float>("0.0", 0.0);
    //    comboBox003->addItem<float>("0.1", 0.1);
    //    comboBox003->addItem<float>("0.2", 0.2);
    //    comboBox003->addItem<float>("0.3", 0.3);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 250;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Angler");
    label->x(marginLeft + spacing * 0 + 25);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    angler000 = new flAngler(36 + 18 + 18);
    angler000->label(label);
    angler000->x(marginLeft + spacing * 0 + 25);
    angler000->y(marginTop + lineSpacing * 1);
//    angler000->alpha(0.0);
    addChild(angler000);
    //--------------------------------------
    
    //--------------------------------------
    //2Dパッド
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 403;
    spacing = 170;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Pad2D Example");
    label->x(marginLeft + spacing * 0);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10;
    marginTop = 403 + 22;
    spacing = 170;
    lineSpacing = 130;
    
    //    pad001 = new flPad2D(160, 160, -500, 500, -500, 500);
    pad001 = new flPad2D(110, 110);
    pad001->x(marginLeft + spacing * 0 + (170 / 2 - 110 / 2));
    pad001->y(marginTop + lineSpacing * 0);
    pad001->addEventListener(flPadEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(pad001);
    
    pad002 = new flPad2D(150, 150, 0, 1000, 0, 1000);
    pad002->x(marginLeft + spacing * 0 + (170 / 2 - 150 / 2));
    pad002->y(marginTop + lineSpacing * 1);
    pad002->addEventListener(flPadEvent::CHANGE, this, &UIComponents::_uiEventHandler);
    addChild(pad002);
    
    cout << pad002->y() + pad002->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //2Dパッド
    marginLeft = 10 + 150 + 10 + 10 + 150 + 10 + 10 + 150 + 10 + 10;
    marginTop = 10;
    spacing = 150;
    lineSpacing = 22;
    
    label = new flTextField();
    label->text("Histgram Viewer Example");
    label->x(marginLeft + spacing * 0 - 12);
    label->y(marginTop + lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    addChild(label);
    
    hViewer001 = new flHistgramViewer(150, 150);
    //    hViewer001->labelText("Histgram 1");
    hViewer001->x(marginLeft + spacing * 0);
    hViewer001->y(marginTop + lineSpacing * 1);
    //    hViewer001->addEventListener(flHistgramViewerEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(hViewer001);
    
    //--------------------------------------
}

//--------------------------------------------------------------
//
void UIComponents::_update() {
    float elapsedTime = ofGetElapsedTimef();
    float n = sin(elapsedTime * 2) * 10;
    //ofLogNotice() << n;
    hViewer001->value(n);
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
        
        //        if(radio == radio002) {
        //            radio001->enabled(radio->selected());
        //        }
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
    if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::UP) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::DOWN) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::LEFT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::RIGHT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    
    //ジョイスティック2D
    if(event.type() == flJoyStick2Event::CHANGE) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::UP) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::DOWN) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::LEFT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::RIGHT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
}
