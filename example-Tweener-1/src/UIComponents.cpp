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
    
    useHandCursor(true);
    
    Graphics* g;
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
    _target = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void UIComponents::_setup() {
    cout << "[UIComponents]_setup()" << endl;
    
    //--------------------------------------
    BasicController::_setup();
    
    _normalBackWidth = 440;
    _normalBackHeight = 800;
    _minBackWidth = _normalBackWidth;
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    Graphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.5);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    
    titleTf->text("[TWEENER CONTROLLER]");
    //--------------------------------------
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    
    //--------------------------------------
    marginLeft = 10;
    marginTop = 40;
    spacing = 110;
    lineSpacing = 25;
    
    label101 = new TextField();
    label101->x(marginLeft + spacing * 0);
    label101->y(marginTop + lineSpacing * 0);
    label101->text("duration");
    label101->autoSize(TextFieldAutoSize::LEFT);
    label101->textColor(0x0);
    addChild(label101);
    
    label102 = new TextField();
    label102->x(marginLeft + spacing * 0);
    label102->y(marginTop + lineSpacing * 1);
    label102->text("delay");
    label102->autoSize(TextFieldAutoSize::LEFT);
    label102->textColor(0x0);
    addChild(label102);
    
    label103 = new TextField();
    label103->x(marginLeft + spacing * 0);
    label103->y(marginTop + lineSpacing * 2);
    label103->text("x");
    label103->autoSize(TextFieldAutoSize::LEFT);
    label103->textColor(0x0);
    addChild(label103);
    
    label104 = new TextField();
    label104->x(marginLeft + spacing * 0);
    label104->y(marginTop + lineSpacing * 3);
    label104->text("y");
    label104->autoSize(TextFieldAutoSize::LEFT);
    label104->textColor(0x0);
    addChild(label104);
    
    label105 = new TextField();
    label105->x(marginLeft + spacing * 0);
    label105->y(marginTop + lineSpacing * 4);
    label105->text("z");
    label105->autoSize(TextFieldAutoSize::LEFT);
    label105->textColor(0x0);
    addChild(label105);
    
    label106 = new TextField();
    label106->x(marginLeft + spacing * 0);
    label106->y(marginTop + lineSpacing * 5);
    label106->text("alpha");
    label106->autoSize(TextFieldAutoSize::LEFT);
    label106->textColor(0x0);
    addChild(label106);
    
    label107 = new TextField();
    label107->x(marginLeft + spacing * 0);
    label107->y(marginTop + lineSpacing * 6);
    label107->text("width");
    label107->autoSize(TextFieldAutoSize::LEFT);
    label107->textColor(0x0);
    addChild(label107);
    
    label108 = new TextField();
    label108->x(marginLeft + spacing * 0);
    label108->y(marginTop + lineSpacing * 7);
    label108->text("height");
    label108->autoSize(TextFieldAutoSize::LEFT);
    label108->textColor(0x0);
    addChild(label108);
    
    label109 = new TextField();
    label109->x(marginLeft + spacing * 0);
    label109->y(marginTop + lineSpacing * 8);
    label109->text("scaleX");
    label109->autoSize(TextFieldAutoSize::LEFT);
    label109->textColor(0x0);
    addChild(label109);
    
    label110 = new TextField();
    label110->x(marginLeft + spacing * 0);
    label110->y(marginTop + lineSpacing * 9);
    label110->text("scaleY");
    label110->autoSize(TextFieldAutoSize::LEFT);
    label110->textColor(0x0);
    addChild(label110);
    
    label111 = new TextField();
    label111->x(marginLeft + spacing * 0);
    label111->y(marginTop + lineSpacing * 10);
    label111->text("rotation");
    label111->autoSize(TextFieldAutoSize::LEFT);
    label111->textColor(0x0);
    addChild(label111);
    
    label112 = new TextField();
    label112->x(marginLeft + spacing * 0);
    label112->y(marginTop + lineSpacing * 11);
    label112->text("rotationX");
    label112->autoSize(TextFieldAutoSize::LEFT);
    label112->textColor(0x0);
    addChild(label112);
    
    label113 = new TextField();
    label113->x(marginLeft + spacing * 0);
    label113->y(marginTop + lineSpacing * 12);
    label113->text("rotationY");
    label113->autoSize(TextFieldAutoSize::LEFT);
    label113->textColor(0x0);
    addChild(label113);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 120;
    marginTop = 40;
    spacing = 110;
    lineSpacing = 25;
    
    text101 = new TextField();
    text101->x(marginLeft + spacing * 0);
    text101->y(marginTop + lineSpacing * 0);
    text101->name("duration");
    text101->text("1");
    text101->width(100);
    text101->height(15);
    text101->type(TEXT_FIELD_TYPE_INPUT);
    text101->textColor(0x0);
    text101->mouseEnabled(true);
    text101->buttonMode(true);
    addChild(text101);
    
    text102 = new TextField();
    text102->x(marginLeft + spacing * 0);
    text102->y(marginTop + lineSpacing * 1);
    text102->name("delay");
    text102->text("0");
    text102->width(100);
    text102->height(15);
    text102->type(TEXT_FIELD_TYPE_INPUT);
    text102->textColor(0x0);
    text102->mouseEnabled(true);
    text102->buttonMode(true);
    addChild(text102);
    
    text103 = new TextField();
    text103->x(marginLeft + spacing * 0);
    text103->y(marginTop + lineSpacing * 2);
    text103->name("x");
    text103->text(ofToString(round(ofRandom(0, ofGetWidth()))));
    text103->width(100);
    text103->height(15);
    text103->type(TEXT_FIELD_TYPE_INPUT);
    text103->textColor(0x0);
    text103->mouseEnabled(true);
    text103->buttonMode(true);
    addChild(text103);
    
    text104 = new TextField();
    text104->x(marginLeft + spacing * 0);
    text104->y(marginTop + lineSpacing * 3);
    text104->name("y");
    text104->text(ofToString(round(ofRandom(0, ofGetWidth()))));
    text104->width(100);
    text104->height(15);
    text104->type(TEXT_FIELD_TYPE_INPUT);
    text104->textColor(0x0);
    text104->mouseEnabled(true);
    text104->buttonMode(true);
    addChild(text104);
    
    text105 = new TextField();
    text105->x(marginLeft + spacing * 0);
    text105->y(marginTop + lineSpacing * 4);
    text105->name("z");
    text105->text("0");
    text105->width(100);
    text105->height(15);
    text105->type(TEXT_FIELD_TYPE_INPUT);
    text105->textColor(0x0);
    text105->mouseEnabled(true);
    text105->buttonMode(true);
    addChild(text105);
    
    text106 = new TextField();
    text106->x(marginLeft + spacing * 0);
    text106->y(marginTop + lineSpacing * 5);
    text106->name("alpha");
    text106->text("0.5");
    text106->width(100);
    text106->height(15);
    text106->type(TEXT_FIELD_TYPE_INPUT);
    text106->textColor(0x0);
    text106->mouseEnabled(true);
    text106->buttonMode(true);
    addChild(text106);
    
    text107 = new TextField();
    text107->x(marginLeft + spacing * 0);
    text107->y(marginTop + lineSpacing * 6);
    text107->name("width");
    text107->text("0");
    text107->width(100);
    text107->height(15);
    text107->type(TEXT_FIELD_TYPE_INPUT);
    text107->textColor(0x0);
    text107->mouseEnabled(true);
    text107->buttonMode(true);
    addChild(text107);
    
    text108 = new TextField();
    text108->x(marginLeft + spacing * 0);
    text108->y(marginTop + lineSpacing * 7);
    text108->name("height");
    text108->text("0");
    text108->width(100);
    text108->height(15);
    text108->type(TEXT_FIELD_TYPE_INPUT);
    text108->textColor(0x0);
    text108->mouseEnabled(true);
    text108->buttonMode(true);
    addChild(text108);
    
    text109 = new TextField();
    text109->x(marginLeft + spacing * 0);
    text109->y(marginTop + lineSpacing * 8);
    text109->name("scaleX");
    text109->text("0");
    text109->width(100);
    text109->height(15);
    text109->type(TEXT_FIELD_TYPE_INPUT);
    text109->textColor(0x0);
    text109->mouseEnabled(true);
    text109->buttonMode(true);
    addChild(text109);
    
    text110 = new TextField();
    text110->x(marginLeft + spacing * 0);
    text110->y(marginTop + lineSpacing * 9);
    text110->name("scaleY");
    text110->text("0");
    text110->width(100);
    text110->height(15);
    text110->type(TEXT_FIELD_TYPE_INPUT);
    text110->textColor(0x0);
    text110->mouseEnabled(true);
    text110->buttonMode(true);
    addChild(text110);
    
    text111 = new TextField();
    text111->x(marginLeft + spacing * 0);
    text111->y(marginTop + lineSpacing * 10);
    text111->name("rotation");
    text111->text("0");
    text111->width(100);
    text111->height(15);
    text111->type(TEXT_FIELD_TYPE_INPUT);
    text111->textColor(0x0);
    text111->mouseEnabled(true);
    text111->buttonMode(true);
    addChild(text111);
    
    text112 = new TextField();
    text112->x(marginLeft + spacing * 0);
    text112->y(marginTop + lineSpacing * 11);
    text112->name("rotationX");
    text112->text("0");
    text112->width(100);
    text112->height(15);
    text112->type(TEXT_FIELD_TYPE_INPUT);
    text112->textColor(0x0);
    text112->mouseEnabled(true);
    text112->buttonMode(true);
    addChild(text112);
    
    text113 = new TextField();
    text113->x(marginLeft + spacing * 0);
    text113->y(marginTop + lineSpacing * 12);
    text113->name("rotationY");
    text113->text("0");
    text113->width(100);
    text113->height(15);
    text113->type(TEXT_FIELD_TYPE_INPUT);
    text113->textColor(0x0);
    text113->mouseEnabled(true);
    text113->buttonMode(true);
    addChild(text113);
    
    btn101 = new Button(100);
    btn101->x(10 + spacing * 0);
    btn101->y(marginTop + lineSpacing * 13);
    btn101->label("START");
    btn101->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn101);
    
    btn102 = new Button(100);
    btn102->x(10 + spacing * 1);
    btn102->y(marginTop + lineSpacing * 13);
    btn102->label("RESET");
    btn102->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn102);
    
    btn103 = new Button(210);
    btn103->x(10 + spacing * 0);
    btn103->y(marginTop + lineSpacing * 14);
    btn103->label("PAUSE / RESUME");
    btn103->toggleEnabled(true);
    btn103->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn103);
    
    comboBox101 = new ComboBox(200);
    comboBox101->name("easing");
    comboBox101->label("");
    comboBox101->x(marginLeft + spacing * 1);
    comboBox101->y(marginTop + lineSpacing * 0 - 18);
    comboBox101->addItem<int>("EASE_LINEAR", 0, 0xffffff);

    comboBox101->addItem<int>("EASE_IN_QUAD", 1, 0xffff99);
    comboBox101->addItem<int>("EASE_OUT_QUAD", 2, 0xffff99);
    comboBox101->addItem<int>("EASE_IN_OUT_QUAD", 3, 0xffff99);
    
    comboBox101->addItem<int>("EASE_IN_CUBIC", 4, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_CUBIC", 5, 0xff99ff);
    comboBox101->addItem<int>("EASE_IN_OUT_CUBIC", 6, 0xff99ff);
    
    comboBox101->addItem<int>("EASE_IN_QUART", 7, 0xffff99);
    comboBox101->addItem<int>("EASE_OUT_QUART", 8, 0xffff99);
    comboBox101->addItem<int>("EASE_IN_OUT_QUART", 9, 0xffff99);
    
    comboBox101->addItem<int>("EASE_IN_QUINT", 10, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_QUINT", 11, 0xff99ff);
    comboBox101->addItem<int>("EASE_IN_OUT_QUINT", 12, 0xff99ff);
    
    comboBox101->addItem<int>("EASE_IN_SINE", 13, 0xffff99);
    comboBox101->addItem<int>("EASE_OUT_SINE", 14, 0xffff99);
    comboBox101->addItem<int>("EASE_IN_OUT_SINE", 15, 0xffff99);
    
    comboBox101->addItem<int>("EASE_IN_EXPO", 16, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_EXPO", 17, 0xff99ff);
    comboBox101->addItem<int>("EASE_IN_OUT_EXPO", 18, 0xff99ff);
    
    comboBox101->addItem<int>("EASE_IN_CIRC", 19, 0xffff99);
    comboBox101->addItem<int>("EASE_OUT_CIRC", 20, 0xffff99);
    comboBox101->addItem<int>("EASE_IN_OUT_CIRC", 21, 0xffff99);
    
    comboBox101->addItem<int>("EASE_IN_ELASTIC", 22, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_ELASTIC", 23, 0xff99ff);
    comboBox101->addItem<int>("EASE_IN_OUT_ELASTIC", 24, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_IN_ELASTIC", 25, 0xff99ff);
    
    comboBox101->addItem<int>("EASE_IN_BACK", 26, 0xffff99);
    comboBox101->addItem<int>("EASE_OUT_BACK", 27, 0xffff99);
    comboBox101->addItem<int>("EASE_IN_OUT_BACK", 28, 0xffff99);
    comboBox101->addItem<int>("EASE_OUT_IN_BACK", 29, 0xffff99);
    
    comboBox101->addItem<int>("EASE_IN_BOUNCE", 30, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_BOUNCE", 31, 0xff99ff);
    comboBox101->addItem<int>("EASE_IN_OUT_BOUNCE", 32, 0xff99ff);
    comboBox101->addItem<int>("EASE_OUT_IN_BOUNCE", 33, 0xff99ff);
    
    comboBox101->selectedIndex(0, false);
    addChild(comboBox101);
    //--------------------------------------

    
    
    //--------------------------------------
    marginLeft = 10;
    marginTop = 420;
    spacing = 110;
    lineSpacing = 25;
    
    label201 = new TextField();
    label201->x(marginLeft + spacing * 0);
    label201->y(marginTop + lineSpacing * 0);
    label201->text("duration");
    label201->autoSize(TextFieldAutoSize::LEFT);
    label201->textColor(0x0);
    addChild(label201);
    
    label202 = new TextField();
    label202->x(marginLeft + spacing * 0);
    label202->y(marginTop + lineSpacing * 1);
    label202->text("delay");
    label202->autoSize(TextFieldAutoSize::LEFT);
    label202->textColor(0x0);
    addChild(label202);
    
    label203 = new TextField();
    label203->x(marginLeft + spacing * 0);
    label203->y(marginTop + lineSpacing * 2);
    label203->text("x");
    label203->autoSize(TextFieldAutoSize::LEFT);
    label203->textColor(0x0);
    addChild(label203);
    
    label204 = new TextField();
    label204->x(marginLeft + spacing * 0);
    label204->y(marginTop + lineSpacing * 3);
    label204->text("y");
    label204->autoSize(TextFieldAutoSize::LEFT);
    label204->textColor(0x0);
    addChild(label204);
    
    label205 = new TextField();
    label205->x(marginLeft + spacing * 0);
    label205->y(marginTop + lineSpacing * 4);
    label205->text("z");
    label205->autoSize(TextFieldAutoSize::LEFT);
    label205->textColor(0x0);
    addChild(label205);
    
    label206 = new TextField();
    label206->x(marginLeft + spacing * 0);
    label206->y(marginTop + lineSpacing * 5);
    label206->text("alpha");
    label206->autoSize(TextFieldAutoSize::LEFT);
    label206->textColor(0x0);
    addChild(label206);
    
    label207 = new TextField();
    label207->x(marginLeft + spacing * 0);
    label207->y(marginTop + lineSpacing * 6);
    label207->text("width");
    label207->autoSize(TextFieldAutoSize::LEFT);
    label207->textColor(0x0);
    addChild(label207);
    
    label208 = new TextField();
    label208->x(marginLeft + spacing * 0);
    label208->y(marginTop + lineSpacing * 7);
    label208->text("height");
    label208->autoSize(TextFieldAutoSize::LEFT);
    label208->textColor(0x0);
    addChild(label208);
    
    label209 = new TextField();
    label209->x(marginLeft + spacing * 0);
    label209->y(marginTop + lineSpacing * 8);
    label209->text("scaleX");
    label209->autoSize(TextFieldAutoSize::LEFT);
    label209->textColor(0x0);
    addChild(label209);
    
    label210 = new TextField();
    label210->x(marginLeft + spacing * 0);
    label210->y(marginTop + lineSpacing * 9);
    label210->text("scaleY");
    label210->autoSize(TextFieldAutoSize::LEFT);
    label210->textColor(0x0);
    addChild(label210);
    
    label211 = new TextField();
    label211->x(marginLeft + spacing * 0);
    label211->y(marginTop + lineSpacing * 10);
    label211->text("rotation");
    label211->autoSize(TextFieldAutoSize::LEFT);
    label211->textColor(0x0);
    addChild(label211);
    
    label212 = new TextField();
    label212->x(marginLeft + spacing * 0);
    label212->y(marginTop + lineSpacing * 11);
    label212->text("rotationX");
    label212->autoSize(TextFieldAutoSize::LEFT);
    label212->textColor(0x0);
    addChild(label212);
    
    label213 = new TextField();
    label213->x(marginLeft + spacing * 0);
    label213->y(marginTop + lineSpacing * 12);
    label213->text("rotationY");
    label213->autoSize(TextFieldAutoSize::LEFT);
    label213->textColor(0x0);
    addChild(label213);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 120;
    marginTop = 420;
    spacing = 110;
    lineSpacing = 25;
    
    text201 = new TextField();
    text201->x(marginLeft + spacing * 0);
    text201->y(marginTop + lineSpacing * 0);
    text201->name("duration");
    text201->text("1");
    text201->width(100);
    text201->height(15);
    text201->type(TEXT_FIELD_TYPE_INPUT);
    text201->textColor(0x0);
    text201->mouseEnabled(true);
    text201->buttonMode(true);
    addChild(text201);
    
    text202 = new TextField();
    text202->x(marginLeft + spacing * 0);
    text202->y(marginTop + lineSpacing * 1);
    text202->name("delay");
    text202->text("0");
    text202->width(100);
    text202->height(15);
    text202->type(TEXT_FIELD_TYPE_INPUT);
    text202->textColor(0x0);
    text202->mouseEnabled(true);
    text202->buttonMode(true);
    addChild(text202);
    
    text203 = new TextField();
    text203->x(marginLeft + spacing * 0);
    text203->y(marginTop + lineSpacing * 2);
    text203->name("x");
    text203->text(ofToString(round(ofRandomf() * 10)));
    text203->width(100);
    text203->height(15);
    text203->type(TEXT_FIELD_TYPE_INPUT);
    text203->textColor(0x0);
    text203->mouseEnabled(true);
    text203->buttonMode(true);
    addChild(text203);
    
    text204 = new TextField();
    text204->x(marginLeft + spacing * 0);
    text204->y(marginTop + lineSpacing * 3);
    text204->name("y");
    text204->text(ofToString(round(ofRandomf() * 10)));
    text204->width(100);
    text204->height(15);
    text204->type(TEXT_FIELD_TYPE_INPUT);
    text204->textColor(0x0);
    text204->mouseEnabled(true);
    text204->buttonMode(true);
    addChild(text204);
    
    text205 = new TextField();
    text205->x(marginLeft + spacing * 0);
    text205->y(marginTop + lineSpacing * 4);
    text205->name("z");
    text205->text("0");
    text205->width(100);
    text205->height(15);
    text205->type(TEXT_FIELD_TYPE_INPUT);
    text205->textColor(0x0);
    text205->mouseEnabled(true);
    text205->buttonMode(true);
    addChild(text205);
    
    text206 = new TextField();
    text206->x(marginLeft + spacing * 0);
    text206->y(marginTop + lineSpacing * 5);
    text206->name("alpha");
    text206->text("0.5");
    text206->width(100);
    text206->height(15);
    text206->type(TEXT_FIELD_TYPE_INPUT);
    text206->textColor(0x0);
    text206->mouseEnabled(true);
    text206->buttonMode(true);
    addChild(text206);
    
    text207 = new TextField();
    text207->x(marginLeft + spacing * 0);
    text207->y(marginTop + lineSpacing * 6);
    text207->name("width");
    text207->text("0");
    text207->width(100);
    text207->height(15);
    text207->type(TEXT_FIELD_TYPE_INPUT);
    text207->textColor(0x0);
    text207->mouseEnabled(true);
    text207->buttonMode(true);
    addChild(text207);
    
    text208 = new TextField();
    text208->x(marginLeft + spacing * 0);
    text208->y(marginTop + lineSpacing * 7);
    text208->name("height");
    text208->text("0");
    text208->width(100);
    text208->height(15);
    text208->type(TEXT_FIELD_TYPE_INPUT);
    text208->textColor(0x0);
    text208->mouseEnabled(true);
    text208->buttonMode(true);
    addChild(text208);
    
    text209 = new TextField();
    text209->x(marginLeft + spacing * 0);
    text209->y(marginTop + lineSpacing * 8);
    text209->name("scaleX");
    text209->text("0");
    text209->width(100);
    text209->height(15);
    text209->type(TEXT_FIELD_TYPE_INPUT);
    text209->textColor(0x0);
    text209->mouseEnabled(true);
    text209->buttonMode(true);
    addChild(text209);
    
    text210 = new TextField();
    text210->x(marginLeft + spacing * 0);
    text210->y(marginTop + lineSpacing * 9);
    text210->name("scaleY");
    text210->text("0");
    text210->width(100);
    text210->height(15);
    text210->type(TEXT_FIELD_TYPE_INPUT);
    text210->textColor(0x0);
    text210->mouseEnabled(true);
    text210->buttonMode(true);
    addChild(text210);
    
    text211 = new TextField();
    text211->x(marginLeft + spacing * 0);
    text211->y(marginTop + lineSpacing * 10);
    text211->name("rotationX");
    text211->text("0");
    text211->width(100);
    text211->height(15);
    text211->type(TEXT_FIELD_TYPE_INPUT);
    text211->textColor(0x0);
    text211->mouseEnabled(true);
    text211->buttonMode(true);
    addChild(text211);
    
    text212 = new TextField();
    text212->x(marginLeft + spacing * 0);
    text212->y(marginTop + lineSpacing * 11);
    text212->name("rotationY");
    text212->text("0");
    text212->width(100);
    text212->height(15);
    text212->type(TEXT_FIELD_TYPE_INPUT);
    text212->textColor(0x0);
    text212->mouseEnabled(true);
    text212->buttonMode(true);
    addChild(text212);
    
    text213 = new TextField();
    text213->x(marginLeft + spacing * 0);
    text213->y(marginTop + lineSpacing * 12);
    text213->name("rotationZ");
    text213->text("0");
    text213->width(100);
    text213->height(15);
    text213->type(TEXT_FIELD_TYPE_INPUT);
    text213->textColor(0x0);
    text213->mouseEnabled(true);
    text213->buttonMode(true);
    addChild(text213);
    
    btn201 = new Button(100);
    btn201->x(10 + spacing * 0);
    btn201->y(marginTop + lineSpacing * 13);
    btn201->label("START");
    btn201->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn201);
    
    btn202 = new Button(100);
    btn202->x(10 + spacing * 1);
    btn202->y(marginTop + lineSpacing * 13);
    btn202->label("RESET");
    btn202->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn202);
    
    btn203 = new Button(210);
    btn203->x(10 + spacing * 0);
    btn203->y(marginTop + lineSpacing * 14);
    btn203->label("PAUSE / RESUME");
    btn203->toggleEnabled(true);
    btn203->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
    addChild(btn203);
    
    comboBox201 = new ComboBox(200);
    comboBox201->name("easing");
    comboBox201->label("");
    comboBox201->x(marginLeft + spacing * 1);
    comboBox201->y(marginTop + lineSpacing * 0 - 18);
    comboBox201->addItem<int>("EASE_LINEAR", 0, 0xffffff);
    
    comboBox201->addItem<int>("EASE_IN_QUAD", 1, 0xffff99);
    comboBox201->addItem<int>("EASE_OUT_QUAD", 2, 0xffff99);
    comboBox201->addItem<int>("EASE_IN_OUT_QUAD", 3, 0xffff99);
    
    comboBox201->addItem<int>("EASE_IN_CUBIC", 4, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_CUBIC", 5, 0xff99ff);
    comboBox201->addItem<int>("EASE_IN_OUT_CUBIC", 6, 0xff99ff);
    
    comboBox201->addItem<int>("EASE_IN_QUART", 7, 0xffff99);
    comboBox201->addItem<int>("EASE_OUT_QUART", 8, 0xffff99);
    comboBox201->addItem<int>("EASE_IN_OUT_QUART", 9, 0xffff99);
    
    comboBox201->addItem<int>("EASE_IN_QUINT", 10, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_QUINT", 11, 0xff99ff);
    comboBox201->addItem<int>("EASE_IN_OUT_QUINT", 12, 0xff99ff);
    
    comboBox201->addItem<int>("EASE_IN_SINE", 13, 0xffff99);
    comboBox201->addItem<int>("EASE_OUT_SINE", 14, 0xffff99);
    comboBox201->addItem<int>("EASE_IN_OUT_SINE", 15, 0xffff99);
    
    comboBox201->addItem<int>("EASE_IN_EXPO", 16, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_EXPO", 17, 0xff99ff);
    comboBox201->addItem<int>("EASE_IN_OUT_EXPO", 18, 0xff99ff);
    
    comboBox201->addItem<int>("EASE_IN_CIRC", 19, 0xffff99);
    comboBox201->addItem<int>("EASE_OUT_CIRC", 20, 0xffff99);
    comboBox201->addItem<int>("EASE_IN_OUT_CIRC", 21, 0xffff99);
    
    comboBox201->addItem<int>("EASE_IN_ELASTIC", 22, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_ELASTIC", 23, 0xff99ff);
    comboBox201->addItem<int>("EASE_IN_OUT_ELASTIC", 24, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_IN_ELASTIC", 25, 0xff99ff);
    
    comboBox201->addItem<int>("EASE_IN_BACK", 26, 0xffff99);
    comboBox201->addItem<int>("EASE_OUT_BACK", 27, 0xffff99);
    comboBox201->addItem<int>("EASE_IN_OUT_BACK", 28, 0xffff99);
    comboBox201->addItem<int>("EASE_OUT_IN_BACK", 29, 0xffff99);
    
    comboBox201->addItem<int>("EASE_IN_BOUNCE", 30, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_BOUNCE", 31, 0xff99ff);
    comboBox201->addItem<int>("EASE_IN_OUT_BOUNCE", 32, 0xff99ff);
    comboBox201->addItem<int>("EASE_OUT_IN_BOUNCE", 33, 0xff99ff);
    
    comboBox201->selectedIndex(0, false);
    addChild(comboBox201);
    //--------------------------------------
    
    
//    //--------------------------------------
//    marginLeft = 40;
//    marginTop = 50;
//    spacing = 100;
//    lineSpacing = 40;
//    
//    //スライダー
//    //デフォルト
//    slider001 = new Slider();
//    slider001->label("SLIDER");
//    slider001->x(marginLeft + spacing * 0);
//    slider001->y(marginTop + lineSpacing * 0);
//    addChild(slider001);
//    //横幅、最小値、最大値、初期値を指定
//    slider002 = new Slider(100, 0.0, 10.0, 0.5);
//    slider002->label("SLIDER");
//    slider002->x(marginLeft + spacing * 0);
//    slider002->y(marginTop + lineSpacing * 1);
//    addChild(slider002);
//    
//    //レンジスライダー
//    rangeSlider001 = new RangeSlider();
//    rangeSlider001->label("RANGE SLIDER");
//    rangeSlider001->x(marginLeft + spacing * 0);
//    rangeSlider001->y(marginTop + lineSpacing * 2);
//    rangeSlider001->min(-100);
//    rangeSlider001->max(1300);
//    rangeSlider001->minValue(300);
//    rangeSlider001->maxValue(500);
//    addChild(rangeSlider001);
//    
//    rangeSlider002 = new RangeSlider(200, -100, 1300, 300, 500);
//    rangeSlider002->label("RANGE SLIDER");
//    rangeSlider002->x(marginLeft + spacing * 0);
//    rangeSlider002->y(marginTop + lineSpacing * 3);
//    addChild(rangeSlider002);
//    //--------------------------------------
//    //--------------------------------------
//    //カラースライダー
//    marginLeft = 40;
//    marginTop = 210;
//    spacing = 100;
//    lineSpacing = 60;
//    
//    colorSlider001 = new ColorSlider();
//    colorSlider001->label("COLOR SLIDER");
//    colorSlider001->x(marginLeft + spacing * 0);
//    colorSlider001->y(marginTop + lineSpacing * 0);
//    addChild(colorSlider001);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //ボタン
//    marginLeft = 270;
//    marginTop = 50;
//    lineSpacing = 30;
//    
//    btn001 = new Button(100);
//    btn001->label("BUTTON");
//    btn001->x(marginLeft + spacing * 0);
//    btn001->y(marginTop + lineSpacing * 0);
//    btn001->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
//    addChild(btn001);
//    btn002 = new Button(100);
//    btn002->label("TOGGLE");
//    btn002->toggleEnabled(true);
//    btn002->x(marginLeft + spacing * 0);
//    btn002->y(marginTop + lineSpacing * 1);
//    btn002->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
//    addChild(btn002);
//    btn003 = new Button(100);
//    btn003->label("WHITE");
//    btn003->x(marginLeft + spacing * 0);
//    btn003->y(marginTop + lineSpacing * 2);
//    btn003->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
//    addChild(btn003);
//    btn004 = new Button(100);
//    btn004->label("GLAY");
//    btn004->x(marginLeft + spacing * 0);
//    btn004->y(marginTop + lineSpacing * 3);
//    btn004->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
//    addChild(btn004);
//    btn005 = new Button(100);
//    btn005->label("BLACK");
//    btn005->x(marginLeft + spacing * 0);
//    btn005->y(marginTop + lineSpacing * 4);
//    btn005->addEventListener(MouseEvent::MOUSE_DOWN, this, &UIComponents::_uiEventHandler);
//    addChild(btn005);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //ラジオボタン
//    marginLeft = 400;
//    marginTop = 50;
//    lineSpacing = 30;
//    
//    radio001 = new RadioButton();
//    radio001->label("RADIO BUTTON");
//    radio001->x(marginLeft + spacing * 0);
//    radio001->y(marginTop + lineSpacing * 0);
//    addChild(radio001);
//    radio002 = new RadioButton();
//    radio002->label("RADIO BUTTON");
//    radio002->x(marginLeft + spacing * 0);
//    radio002->y(marginTop + lineSpacing * 1);
//    addChild(radio002);
//    radio003 = new RadioButton();
//    radio003->label("RADIO BUTTON");
//    radio003->x(marginLeft + spacing * 0);
//    radio003->y(marginTop + lineSpacing * 2);
//    addChild(radio003);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //コンボボックス
//    marginLeft = 700;
//    marginTop = 50;
//    spacing = 150;
//    lineSpacing = 40;
//    
//    comboBox001 = new ComboBox();
//    comboBox001->name("COMBO BOX 1");
//    comboBox001->label("COMBO BOX 1");
//    comboBox001->x(marginLeft + spacing * 0);
//    comboBox001->y(marginTop + lineSpacing * 0);
//    comboBox001->addItem<std::string>("TEST0", "test0");
//    comboBox001->addItem<std::string>("TEST1", "test1");
//    comboBox001->addItem<std::string>("TEST2", "test2");
//    comboBox001->addItem<std::string>("TEST3", "test3");
//    comboBox001->addItem<std::string>("TEST4", "test4");
//    comboBox001->addItem<std::string>("TEST5", "test5");
//    comboBox001->addItem<std::string>("TEST6", "test6");
//    comboBox001->addItem<std::string>("TEST7", "test7");
//    comboBox001->selectedIndex(1, false);
//    addChild(comboBox001);
//    
//    comboBox002 = new ComboBox();
//    comboBox002->name("COMBO BOX 2");
//    comboBox002->label("COMBO BOX 2");
//    comboBox002->x(marginLeft + spacing * 0);
//    comboBox002->y(marginTop + lineSpacing * 1);
//    comboBox002->addItem<float>("0.0", 0.0);
//    comboBox002->addItem<float>("0.1", 0.1);
//    comboBox002->addItem<float>("0.2", 0.2);
//    comboBox002->addItem<float>("0.3", 0.3);
//    comboBox002->selectedIndex(1, false);
//    addChild(comboBox002);
//    
//    comboBox003 = new ComboBox();
//    comboBox003->name("COMBO BOX 3");
//    comboBox003->label("COMBO BOX 3");
//    comboBox003->x(marginLeft + spacing * 0);
//    comboBox003->y(marginTop + lineSpacing * 2);
//    comboBox003->addItem<ComboBox*>("COMBO BOX 1", comboBox001);
//    comboBox003->addItem<ComboBox*>("COMBO BOX 2", comboBox002);
//    comboBox003->selectedIndex(1, false);
//    addChild(comboBox003);
//    
//    //    comboBox003->removeAll();
//    //    comboBox003->addItem<float>("0.0", 0.0);
//    //    comboBox003->addItem<float>("0.1", 0.1);
//    //    comboBox003->addItem<float>("0.2", 0.2);
//    //    comboBox003->addItem<float>("0.3", 0.3);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //2Dパッド
//    marginLeft = 700;
//    marginTop = 200;
//    spacing = 170;
//    lineSpacing = 30;
//    
//    pad001 = new Pad2D(160, 160, -500, 500, -500, 500);
//    pad001->x(marginLeft + spacing * 0);
//    pad001->y(marginTop + lineSpacing * 0);
//    addChild(pad001);
//    
//    pad002 = new Pad2D(160, 160, 0, 1000, 0, 1000);
//    pad002->x(marginLeft + spacing * 1);
//    pad002->y(marginTop + lineSpacing * 0);
//    addChild(pad002);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //インプットテキストフィールド
//    marginLeft = 40;
//    marginTop = 500;
//    spacing = 150;
//    lineSpacing = 30;
//    
//    text001 = new TextField();
//    text001->text("test", 0x0000);
//    text001->x(marginLeft + spacing * 0);
//    text001->y(marginTop + lineSpacing * 0);
//    text001->type(TEXT_FIELD_TYPE_INPUT);
//    addChild(text001);
//    text002 = new TextField();
//    text002->text("test", 0x0000);
//    text002->x(marginLeft + spacing * 0);
//    text002->y(marginTop + lineSpacing * 1);
//    text002->type(TEXT_FIELD_TYPE_INPUT);
//    addChild(text002);
//    
//    addChild(text001);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //カラーピッカー
//    marginLeft = 140;
//    marginTop = 500;
//    spacing = 150;
//    lineSpacing = 30;
//    
//    colorPicker001 = new CircleColorPicker();
//    colorPicker001->label("COLOR PICKER");
//    colorPicker001->x(marginLeft + spacing * 0);
//    colorPicker001->y(marginTop + lineSpacing * 0);
//    addChild(colorPicker001);
//    colorPicker001->addEventListener(ColorPickerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //ジョイスティック
//    marginLeft = 300;
//    marginTop = 500;
//    spacing = 150;
//    lineSpacing = 30;
//    
//    joystick001 = new Joystick();
//    joystick001->label("JOYSTICK");
//    joystick001->x(marginLeft + spacing * 0);
//    joystick001->y(marginTop + lineSpacing * 0);
//    addChild(joystick001);
//    //--------------------------------------
//    
//    //--------------------------------------
//    //ナンバーダイアラー
//    marginLeft = 400;
//    marginTop = 500;
//    spacing = 150;
//    lineSpacing = 50;
//    
//    dialer001 = new NumberDialer();
//    dialer001->label("NUMBER DIALER 1");
//    dialer001->x(marginLeft + spacing * 0);
//    dialer001->y(marginTop + lineSpacing * 0);
//    dialer001->addEventListener(NumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
//    addChild(dialer001);
//    dialer002 = new NumberDialer();
//    dialer002->label("NUMBER DIALER 2");
//    dialer002->x(marginLeft + spacing * 0);
//    dialer002->y(marginTop + lineSpacing * 1);
//    dialer002->value(-500);
//    dialer002->stepValue(10);
//    dialer002->max(0);
//    dialer002->addEventListener(NumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
//    addChild(dialer002);
//    dialer003 = new NumberDialer();
//    dialer003->label("NUMBER DIALER 3");
//    dialer003->type(FL_VERTICALLY);
//    dialer003->x(marginLeft + spacing * 1);
//    dialer003->y(marginTop + lineSpacing * 0);
//    dialer003->value(10.1);
//    dialer003->stepValue(0.1f);
//    dialer003->min(-100);
//    dialer003->max(100);
//    dialer003->addEventListener(NumberDialerEvent::CHANGE, this, &UIComponents::_uiEventHandler);
//    addChild(dialer003);
//    //--------------------------------------
//    
//    addChild(comboBox003);
//    addChild(comboBox002);
//    addChild(comboBox001);
}

//--------------------------------------------------------------
//
void UIComponents::_update() {

}

//--------------------------------------------------------------
//
void UIComponents::_draw() {
    if(_isMinimize) return;
}

//==============================================================
// PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================
//--------------------------------------------------------------
//
void UIComponents::_uiEventHandler(Event& event) {
    //cout << "[UIComponents]_controllerEventHandler(" << event.type() << ")" << endl;
    
    /**
    //ボタン(マウスダウン)
    if(event.type() == MouseEvent::MOUSE_DOWN) {
        MouseEvent& mouseEvent = *(MouseEvent*) &event;
        Button* button = (Button*)(event.currentTarget());
        
        //メインコントローラー
        if(button == btn001);
        if(button == btn002);
        if(button == btn003) ofBackground(255, 255, 255, 255);
        if(button == btn004) ofBackground(120, 120, 120, 255);
        if(button == btn005) ofBackground(0, 0, 0, 255);
    };
    
    //マウスアップ
    if(event.type() == MouseEvent::MOUSE_UP) {
        MouseEvent& mouseEvent = *(MouseEvent*) &event;
        Button* button = (Button*)(event.currentTarget());
        
        if(button == btn001);
        if(button == btn002);
        if(button == btn003);
        if(button == btn004);
        if(button == btn005);
    };
    
    //コンボボックス
    if(event.type() == ComboBoxEvent::CHANGE) {
        ComboBoxEvent& comboBoxEvent = *(ComboBoxEvent*) &event;
        ComboBox* comboBox = (ComboBox*)(event.currentTarget());
    };
    
    //ラジオボタン
    if(event.type() == RadioButtonEvent::CHANGE) {
        RadioButtonEvent& radioButtonEvent = *(RadioButtonEvent*) &event;
        RadioButton* radio = (RadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
    if(event.type() == NumberDialerEvent::CHANGE) {
        NumberDialerEvent& numberDialerEvent = *(NumberDialerEvent*) &event;
        NumberDialer* dialer = (NumberDialer*)(event.currentTarget());
    }
    
    //2Dパッド
    if(event.type() == PadEvent::CHANGE) {
        PadEvent& padEvent = *(PadEvent*) &event;
        Pad2D* pad = (Pad2D*)(event.currentTarget());
    }
    
    //スライダー
    if(event.type() == SliderEvent::CHANGE) {
        SliderEvent& sliderEvent = *(SliderEvent*) &event;
        Slider* slider = (Slider*)(event.currentTarget());
        if(slider == slider001);
        if(slider == slider002);
    }
    
    //レンジスライダー
    if(event.type() == RangeSliderEvent::CHANGE) {
        RangeSliderEvent& rangeSliderEvent = *(RangeSliderEvent*) &event;
        RangeSlider* slider = (RangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
    if(event.type() == ColorSliderEvent::CHANGE) {
        ColorSliderEvent& colorSliderEvent = *(ColorSliderEvent*) &event;
        ColorSlider* slider = (ColorSlider*)(event.currentTarget());
    }
    
    //カラーピッカー
    if(event.type() == ColorPickerEvent::CHANGE) {
        ColorPickerEvent& colorPickerEvent = *(ColorPickerEvent*) &event;
        CircleColorPicker* colorPicker = (CircleColorPicker*)(event.currentTarget());
    }
    
    //ジョイスティックパッド
    if(event.type() == JoystickEvent::UP) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::DOWN) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::LEFT) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::RIGHT) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
*/
}
