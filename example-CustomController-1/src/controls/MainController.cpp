#include "MainController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
MainController::MainController() {
	cout << "[MainController]MainController()" << endl;
	_target = this;

	name("MainController");
	useHandCursor(true);

	_title = "";

	_status = "[Status]";

	_controller0 = NULL;
	_controller1 = NULL;
	_controller2 = NULL;
}

//--------------------------------------------------------------
//
MainController::~MainController() {
	cout << "[MainController]~MainController()" << endl;
	_target = NULL;

	_status = "";

	delete _controller0;
	_controller0 = NULL;

	delete _controller1;
	_controller1 = NULL;

	delete _controller2;
	_controller2 = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void MainController::_setup() {
	cout << "[MainController]_setup()" << endl;

	flBasicController::_setup();

	_defaultWindowWidth = 420;
	_defaultWindowHeight = 695;
	//_minBackWidth = _defaultWindowWidth;
	//_backWidth = _defaultWindowWidth;
	//_backHeight = _defaultWindowHeight;

	//flGraphics* g;
	//g = graphics();
	//g->clear();
	//g->lineStyle(1, 0xffffff);
	//g->beginFill(0x000000, 0.7);
	//g->drawRect(0, 0, _backWidth, _backHeight);
	//g->moveTo(0, 220);
	//g->lineTo(_backWidth, 220);
	//g->moveTo(_backWidth * 0.5, 220);
	//g->lineTo(_backWidth * 0.5, _backHeight);
	//g->moveTo(0, 315 + 22);
	//g->lineTo(_backWidth * 0.5, 315 + 22);
	//g->moveTo(0, 455 + 22);
	//g->lineTo(_backWidth * 0.5, 455 + 22);
	//g->endFill();

	float marginLeft; float marginTop;
	float spacing; float lineSpacing;
	flTextField* textField = NULL;

	//--------------------------------------
//    marginLeft = 5;
//    marginTop = 22;
//    spacing = 205;
//    lineSpacing = 22;
//
//    button001 = new flButton(200);
//    button001->labelText("Full Screen");
//    button001->x(marginLeft + spacing * 0);
//    button001->y(marginTop + lineSpacing * 0);
//    button001->toggleEnabled(true);
//    button001->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
//    addChild(button001);
//
//    textField = new flTextField();
//    textField->text("Window Depth");
//    textField->x(marginLeft + spacing * 0);
//    textField->y(marginTop + lineSpacing * 1);
//    textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//    textField->mouseEnabled(false);
//    addChild(textField);
//    comboBox001 = new flComboBox(200);
//    comboBox001->label(textField);
//    comboBox001->x(marginLeft + spacing * 0);
//    comboBox001->y(marginTop + lineSpacing * 2);
//    comboBox001->addItem<string>("Default", "default");
//    comboBox001->addItem<string>("Always on Bottom", "alwaysOnBottom");
//    comboBox001->addItem<string>("Always on Top", "alwaysOnTop");
//    comboBox001->selectedIndex(0);
//    comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &MainController::_uiEventHandler);
//    addChild(comboBox001);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 5;
	marginTop = 22;
	spacing = 205;
	lineSpacing = 22;

	textField = new flTextField();
	textField->text("Background Color");
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
	textField->mouseEnabled(false);
	addChild(textField);
	colorSlider001 = new flColorSlider(185, false);
	colorSlider001->label(textField);
	//    colorSlider001->label()->width(200);
	//    colorSlider001->label()->autoSize(flTextFieldAutoSize::CENTER);
	colorSlider001->x(marginLeft + spacing * 0);
	colorSlider001->y(marginTop + lineSpacing * 1);
	colorSlider001->redValue<float>(0.5);
	colorSlider001->greenValue<float>(0.5);
	colorSlider001->blueValue<float>(0.5);
	colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &MainController::_uiEventHandler);
	addChild(colorSlider001);
	ofBackground(colorSlider001->redValue(), colorSlider001->greenValue(), colorSlider001->blueValue());
	//--------------------------------------

	//--------------------------------------
	marginLeft = 5;
	marginTop = 175;
	spacing = 205;
	lineSpacing = 22;

	textField = new flTextField();
	textField->text("Model");
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
	textField->mouseEnabled(false);
	addChild(textField);
	comboBox101 = new flComboBox(200);
	comboBox101->label(textField);
	comboBox101->x(marginLeft + spacing * 0);
	comboBox101->y(marginTop + lineSpacing * 1);
	//    addChild(comboBox101);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 215;
	marginTop = 22;
	spacing = 205;
	lineSpacing = 22;

	//   button101 = new flButton(95);
	//   button101->label("Save");
	//   button101->x(marginLeft + spacing * 0);
	//   button101->y(marginTop + lineSpacing * 0);
	//   button101->addEventListener(flButtonEvent::MOUSE_DOWN, this, &MainController::_uiEventHandler);
	//    addChild(button101);
	//
	//   button102 = new flButton(95);
	//   button102->label("Load");
	//   button102->x(marginLeft + spacing * 0 + 102.5);
	//   button102->y(marginTop + lineSpacing * 0);
	//   button102->addEventListener(flButtonEvent::MOUSE_DOWN, this, &MainController::_uiEventHandler);
	//    addChild(button102);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 215;
	marginTop = 22 * 4;
	spacing = 205;
	lineSpacing = 21;

	textField = new flTextField();
	textField->text("Camera Position");
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
	textField->mouseEnabled(false);
	addChild(textField);
//    joystick2001 = new flJoyStick2(55, 15);
    joystick2001 = new flJoyStick2(55);
	joystick2001->label(textField);
	joystick2001->x(marginLeft + spacing * 0);
	joystick2001->y(marginTop + lineSpacing * 1);
	joystick2001->addEventListener(flJoyStick2Event::CHANGE, this, &MainController::_uiEventHandler);
	addChild(joystick2001);
	joystick1001 = new flJoyStick1(55);
	joystick1001->label(textField);
	joystick1001->x(marginLeft + spacing * 0 + 70);
	joystick1001->y(marginTop + lineSpacing * 1);
	joystick1001->type(flJoyStick1::VERTICALLY);
	joystick1001->addEventListener(flJoyStick1Event::CHANGE, this, &MainController::_uiEventHandler);
	addChild(joystick1001);
	text001 = new flTextField();
	text001->text("X : ");
	text001->x(marginLeft + spacing * 0 + 90);
	text001->y(marginTop + lineSpacing * 1);
	text001->autoSize(flTextFieldAutoSize::LEFT);
	text001->mouseEnabled(false);
	addChild(text001);
	text002 = new flTextField();
	text002->text("Y : ");
	text002->x(marginLeft + spacing * 0 + 90);
	text002->y(marginTop + lineSpacing * 2);
	text002->autoSize(flTextFieldAutoSize::LEFT);
	text002->mouseEnabled(false);
	addChild(text002);
	text003 = new flTextField();
	text003->text("Z : ");
	text003->x(marginLeft + spacing * 0 + 90);
	text003->y(marginTop + lineSpacing * 3);
	text003->autoSize(flTextFieldAutoSize::LEFT);
	text003->mouseEnabled(false);
	addChild(text003);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 215;
	marginTop = 175;
	spacing = 205;
	lineSpacing = 22;

	textField = new flTextField();
	textField->text("Model Orientation");
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
	textField->mouseEnabled(false);
	addChild(textField);
	comboBox111 = new flComboBox(200);
	comboBox111->label(textField);
	comboBox111->x(marginLeft + spacing * 0);
	comboBox111->y(marginTop + lineSpacing * 1);
	comboBox111->addItem<string>("Front", "front");
	comboBox111->addItem<string>("Back", "back");
	comboBox111->addItem<string>("Left", "left");
	comboBox111->addItem<string>("Right", "right");
	comboBox111->addItem<string>("Top", "top");
	comboBox111->addItem<string>("Bottom", "bottom");
	comboBox111->selectedIndex(0);
	addChild(comboBox111);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 5;
	marginTop = 225;
	spacing = 205;
	lineSpacing = 22;

	textField = new flTextField();
	textField->text("Pose Type");
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
	textField->mouseEnabled(false);
	//    addChild(textField);
	comboBox201 = new flComboBox(200);
	comboBox201->label(textField);
	comboBox201->x(marginLeft + spacing * 0);
	comboBox201->y(marginTop + lineSpacing * 1);
	comboBox201->addItem<string>("A Pose", "aPose");
	comboBox201->addItem<string>("T Pose", "tPose");
	comboBox201->selectedIndex(1);
	//    addChild(comboBox201);

	check207 = new flCheckBox();
	check207->labelText("Show Grid");
	check207->x(marginLeft + spacing * 0);
	check207->y(marginTop + lineSpacing * 0);
	check207->selected(true);
	addChild(check207);

	check208 = new flCheckBox();
	check208->labelText("Show Axis Guide");
	check208->x(marginLeft + spacing * 0);
	check208->y(marginTop + lineSpacing * 1);
	check208->selected(true);
	addChild(check208);

	check209 = new flCheckBox();
	check209->labelText("Show Skeleton");
	check209->x(marginLeft + spacing * 0);
	check209->y(marginTop + lineSpacing * 2);
	//    check209->selected(true);
	addChild(check209);

	check201 = new flCheckBox();
	check201->labelText("Show T-Pose Mesh");
	check201->x(marginLeft + spacing * 0);
	check201->y(marginTop + lineSpacing * 3);
	check201->selected(true);
	check201->addEventListener(flCheckBoxEvent::CHANGE, this, &MainController::_uiEventHandler);
	addChild(check201);

	check202 = new flCheckBox();
	check202->labelText("Skinned Mesh");
	check202->x(marginLeft + spacing * 0);
	check202->y(marginTop + lineSpacing * 4);
	check202->addEventListener(flCheckBoxEvent::CHANGE, this, &MainController::_uiEventHandler);
	//    addChild(check202);

	check203 = new flCheckBox();
	check203->labelText("Show Items");
	check203->x(marginLeft + spacing * 0);
	check203->y(marginTop + lineSpacing * 4);
	check203->addEventListener(flCheckBoxEvent::CHANGE, this, &MainController::_uiEventHandler);
	addChild(check203);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 5;
	marginTop = 320 + 22;
	spacing = 205;
	lineSpacing = 22;

	check220 = new flCheckBox();
	check220->labelText("Fill Enabled");
	check220->x(marginLeft + spacing * 0);
	check220->y(marginTop + lineSpacing * 0);
	addChild(check220);

	check221 = new flCheckBox();
	check221->labelText("Texture Enabled");
	check221->x(marginLeft + spacing * 0);
	check221->y(marginTop + lineSpacing * 1);
	check221->selected(true);
	addChild(check221);

	check222 = new flCheckBox();
	check222->labelText("Vertices Enabled");
	check222->x(marginLeft + spacing * 0);
	check222->y(marginTop + lineSpacing * 2);
	addChild(check222);

	check223 = new flCheckBox();
	check223->labelText("Wireframe Enabled");
	check223->x(marginLeft + spacing * 0);
	check223->y(marginTop + lineSpacing * 3);
	addChild(check223);

	check224 = new flCheckBox();
	check224->labelText("Normal Enabled");
	check224->x(marginLeft + spacing * 0);
	check224->y(marginTop + lineSpacing * 4);
	addChild(check224);

	check225 = new flCheckBox();
	check225->labelText("Culling Enabled");
	check225->x(marginLeft + spacing * 0);
	check225->y(marginTop + lineSpacing * 5);
	check225->selected(true);
	addChild(check225);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 5;
	marginTop = 460 + 22;
	spacing = 207;
	lineSpacing = 22;

	textField = new flTextField();
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->text("Controllers");
	textField->width(200);
	textField->height(20);
	textField->autoSize(flTextFieldAutoSize::CENTER);
	textField->mouseEnabled(false);
	addChild(textField);

	button301 = new flButton(200);
	button301->labelText("Network Controller");
	button301->x(marginLeft + spacing * 0);
	button301->y(marginTop + lineSpacing * 1);
	button301->toggleEnabled(true);
	button301->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
	addChild(button301);
	button311 = new flButton(200);
	button311->labelText("Weight Controller");
	button311->x(marginLeft + spacing * 0);
	button311->y(marginTop + lineSpacing * 2);
	button311->toggleEnabled(true);
	button311->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
	//    addChild(button311);
	button321 = new flButton(200);
	button321->labelText("Joint Controller");
	button321->x(marginLeft + spacing * 0);
	button321->y(marginTop + lineSpacing * 2);
	button321->toggleEnabled(true);
	button321->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
	addChild(button321);
	//--------------------------------------

	//--------------------------------------
	marginLeft = 5;
	marginTop = 528 + 22;
	spacing = 207;
	lineSpacing = 22;

	textField = new flTextField();
	textField->x(marginLeft + spacing * 0);
	textField->y(marginTop + lineSpacing * 0);
	textField->text("Output Settings");
	textField->width(200);
	textField->height(20);
	textField->autoSize(flTextFieldAutoSize::CENTER);
	textField->mouseEnabled(false);
	addChild(textField);

	check351 = new flCheckBox();
	check351->labelText("Low");
	check351->x(marginLeft + spacing * 0);
	check351->y(marginTop + lineSpacing * 1);
	check351->selected(true);
	addChild(check351);

	check352 = new flCheckBox();
	check352->labelText("Medium");
	check352->x(marginLeft + spacing * 0);
	check352->y(marginTop + lineSpacing * 2);
	check352->selected(true);
	addChild(check352);

	check353 = new flCheckBox();
	check353->labelText("High");
	check353->x(marginLeft + spacing * 0);
	check353->y(marginTop + lineSpacing * 3);
	check353->selected(true);
	addChild(check353);

	check354 = new flCheckBox();
	check354->labelText("OBJ");
	check354->x(marginLeft + spacing * 0);
	check354->y(marginTop + lineSpacing * 4);
	check354->selected(true);
	addChild(check354);

	check355 = new flCheckBox();
	check355->labelText("glTF2.0");
	check355->x(marginLeft + spacing * 0);
	check355->y(marginTop + lineSpacing * 5);
	check355->selected(true);
	addChild(check355);

	check350 = new flCheckBox();
	check350->labelText("Update Skinned Mesh");
	check350->x(marginLeft + spacing * 0);
	check350->y(marginTop + lineSpacing * 4);
	check350->selected(true);
	//    addChild(check350);
//
//    button350 = new flButton(200);
//    button350->labelText("Set Weights");
//    button350->x(marginLeft + spacing * 0);
//    button350->y(marginTop + lineSpacing * 5);
//    //    addChild(button350);

	//--------------------------------------

	//--------------------------------------
	marginLeft = 215;
	marginTop = 225;
	spacing = 205;
	lineSpacing = 22;

	button401 = new flButton(200);
	//    button401->labelText("Show Original Color");
	button401->labelText("Hide All Weights");
	button401->x(marginLeft + spacing * 0);
	button401->y(marginTop + lineSpacing * 0);
	addChild(button401);

	button402 = new flButton(200);
	button402->labelText("Show All Weights");
	button402->x(marginLeft + spacing * 0);
	button402->y(marginTop + lineSpacing * 1);
	addChild(button402);

	button403 = new flButton(200);
	button403->labelText("Check Weights");
	button403->x(marginLeft + spacing * 0);
	button403->y(marginTop + lineSpacing * 2);
	addChild(button403);

	check411 = new flCheckBox();
	check411->labelText("Neck");
	check411->x(marginLeft + spacing * 0);
	check411->y(marginTop + lineSpacing * 3);
	check411->selected(true, true);
	addChild(check411);

	check412 = new flCheckBox();
	check412->labelText("Shoulder Center");
	check412->x(marginLeft + spacing * 0);
	check412->y(marginTop + lineSpacing * 4);
	check412->selected(true, true);
	addChild(check412);

	check413 = new flCheckBox();
	check413->labelText("Chest");
	check413->x(marginLeft + spacing * 0);
	check413->y(marginTop + lineSpacing * 5);
	check413->selected(true, true);
	addChild(check413);

	check414 = new flCheckBox();
	check414->labelText("Spine");
	check414->x(marginLeft + spacing * 0);
	check414->y(marginTop + lineSpacing * 6);
	check414->selected(true, true);
	addChild(check414);

	check415 = new flCheckBox();
	check415->labelText("Hip Center");
	check415->x(marginLeft + spacing * 0);
	check415->y(marginTop + lineSpacing * 7);
	check415->selected(true, true);
	addChild(check415);

	check416 = new flCheckBox();
	check416->labelText("Shoulder Left");
	check416->x(marginLeft + spacing * 0);
	check416->y(marginTop + lineSpacing * 8);
	check416->selected(true, true);
	addChild(check416);

	check417 = new flCheckBox();
	check417->labelText("Elbow Left");
	check417->x(marginLeft + spacing * 0);
	check417->y(marginTop + lineSpacing * 9);
	check417->selected(true, true);
	addChild(check417);

	check418 = new flCheckBox();
	check418->labelText("Wrist Left");
	check418->x(marginLeft + spacing * 0);
	check418->y(marginTop + lineSpacing * 10);
	check418->selected(true, true);
	addChild(check418);

	check419 = new flCheckBox();
	check419->labelText("Shoulder Right");
	check419->x(marginLeft + spacing * 0);
	check419->y(marginTop + lineSpacing * 11);
	check419->selected(true, true);
	addChild(check419);

	check420 = new flCheckBox();
	check420->labelText("Elbow Right");
	check420->x(marginLeft + spacing * 0);
	check420->y(marginTop + lineSpacing * 12);
	check420->selected(true, true);
	addChild(check420);

	check421 = new flCheckBox();
	check421->labelText("Wrist Right");
	check421->x(marginLeft + spacing * 0);
	check421->y(marginTop + lineSpacing * 13);
	check421->selected(true, true);
	addChild(check421);

	check422 = new flCheckBox();
	check422->labelText("Hip Left");
	check422->x(marginLeft + spacing * 0);
	check422->y(marginTop + lineSpacing * 14);
	check422->selected(true, true);
	addChild(check422);

	check423 = new flCheckBox();
	check423->labelText("Knee Left");
	check423->x(marginLeft + spacing * 0);
	check423->y(marginTop + lineSpacing * 15);
	check423->selected(true, true);
	addChild(check423);

	check424 = new flCheckBox();
	check424->labelText("Ankle Left");
	check424->x(marginLeft + spacing * 0);
	check424->y(marginTop + lineSpacing * 16);
	check424->selected(true, true);
	addChild(check424);

	check425 = new flCheckBox();
	check425->labelText("Hip Right");
	check425->x(marginLeft + spacing * 0);
	check425->y(marginTop + lineSpacing * 17);
	check425->selected(true, true);
	addChild(check425);

	check426 = new flCheckBox();
	check426->labelText("Knee Right");
	check426->x(marginLeft + spacing * 0);
	check426->y(marginTop + lineSpacing * 18);
	check426->selected(true, true);
	addChild(check426);

	check427 = new flCheckBox();
	check427->labelText("Ankle Right");
	check427->x(marginLeft + spacing * 0);
	check427->y(marginTop + lineSpacing * 19);
	check427->selected(true, true);
	addChild(check427);
	//--------------------------------------

	//--------------------------------------
	check501 = new flCheckBox();
	check501->labelText("Test");
	check501->x(marginLeft + spacing * 0);
	check501->y(marginTop + lineSpacing * 20);
	addChild(check501);
	//--------------------------------------

	//--------------------------------------
	//ネットワークコントローラー
	_controller0 = new NetworkController();
	_controller0->setup();
	_controller0->addEventListener(flEvent::CLOSE, this, &MainController::_uiEventHandler);

	_controller1 = new SubController1("Weight Controller");
	_controller1->setup();
	_controller1->addEventListener(flEvent::CLOSE, this, &MainController::_uiEventHandler);
	_controller1->addEventListener("uiEvent", this, &MainController::_uiEventHandler);

	_controller2 = new SubController2("Joint Controller");
	_controller2->setup();
	_controller2->addEventListener(flEvent::CLOSE, this, &MainController::_uiEventHandler);
	_controller2->addEventListener("uiEvent", this, &MainController::_uiEventHandler);
	//--------------------------------------
}

//--------------------------------------------------------------
//
void MainController::_update() {
	//cout << "[MainController]update()" << endl;

	_status = "";
	_status += "FPS : " + ofToString(ofGetFrameRate(), 1) + " / " + ofToString(Config::fps);
	//    _status += "COMMAND LINE PARAMS ----\n";
	//    int i; int l;
	//    l = Config::commandLineParameter.size();
	//    for(i = 1; i < l; i++) {
	//        _status += ofToString(i) + " = " + ofToString(Config::commandLineParameter[i]) +"\n";
	//    }
}

//--------------------------------------------------------------
//
void MainController::_draw() {
	//cout << "[MainController]draw()" << endl;

//    if (_isMinimize) return;

	ofDrawBitmapString(_status, 10, 20);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

////--------------------------------------------------------------
////
//void MainController::normalize() {
//	if (!_isMinimize) return;
//	_isMinimize = false;
//
//	minimizeButton->selected(false);
//
//	//----------------------------------
//	_backWidth = _defaultWindowWidth;
//	_backHeight = _defaultWindowHeight;
//
//	flGraphics* g;
//	g = graphics();
//	g->clear();
//	g->lineStyle(1, 0xffffff);
//	g->beginFill(0x000000, 0.7);
//	g->drawRect(0, 0, _backWidth, _backHeight);
//	g->moveTo(0, 220);
//	g->lineTo(_backWidth, 220);
//	g->moveTo(_backWidth * 0.5, 220);
//	g->lineTo(_backWidth * 0.5, _backHeight);
//	g->moveTo(0, 315 + 22);
//	g->lineTo(_backWidth * 0.5, 315 + 22);
//	g->moveTo(0, 455 + 22);
//	g->lineTo(_backWidth * 0.5, 455 + 22);
//	g->endFill();
//	//----------------------------------
//
//	//----------------------------------
//	int i; int l;
//	l = numChildren();
//	for (i = 0; i < l; i++) {
//		getChildAt(i)->visible(true);
//	}
//
//	if (parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
//	//----------------------------------
//}

//--------------------------------------------------------------
//
void MainController::toggleShowAll() {
	visible(!visible());

}

//==============================================================
// PROTECTED / PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void MainController::_uiEventHandler(flEvent& event) {
	//    cout << "[NuiController]_uiEventHandler(" << event.type() << endl;

	if (event.type() == flEvent::CLOSE) {
		flBasicController* target = (flBasicController*)(event.currentTarget());

		//コントローラー0
		if (target == _controller0) {
			((flStage*)stage())->removeChild(target);
			button301->selected(false, false);
		}
		//コントローラー1
		else if (target == _controller1) {
			((flStage*)stage())->removeChild(target);
			button311->selected(false, false);
		}
		//コントローラー2
		else if (target == _controller2) {
			((flStage*)stage())->removeChild(target);
			button321->selected(false, false);
		}
	}

	else if (event.type() == "uiEvent") {
		flBasicController* target = (flBasicController*)(event.currentTarget());

		if (target == _controller1) {
			flEvent* newEvent = new flEvent("uiEvent1");
			newEvent->target(event.target());
			dispatchEvent(newEvent);
		}
		else if (target == _controller2) {
			flEvent* newEvent = new flEvent("uiEvent2");
			newEvent->target(event.target());
			dispatchEvent(newEvent);
		}
	}

	//ボタン
	else if (event.type() == flButtonEvent::MOUSE_DOWN) {
		flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
		flButton* button = (flButton*)(event.currentTarget());

		//        if(button ==button101) save("xml/calibration.xml");
		//        if(button ==button102) load("xml/calibration.xml");
	}
	//ボタン
	else if (event.type() == flButtonEvent::CHANGE) {
		flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
		flButton* button = (flButton*)(event.currentTarget());

		if (button == button001) {
			ofSetFullscreen(button->selected());
		}

		else if (button == button301) {
			if (button->selected()) {
				_controller0->x(ofGetWidth() - _controller0->width() - 1);
				_controller0->y(1);
				((flStage*)stage())->addChild(_controller0);
			}
			else {
				((flStage*)stage())->removeChild(_controller0);
			}
		}
		else if (button == button311) {
			if (button->selected()) {
				_controller1->x(ofGetWidth() - _controller1->width() - 1);
				_controller1->y(1);
				((flStage*)stage())->addChild(_controller1);
			}
			else {
				((flStage*)stage())->removeChild(_controller1);
			}
		}
		else if (button == button321) {
			if (button->selected()) {
				_controller2->x(ofGetWidth() - _controller2->width() - 1);
				_controller2->y(1);
				((flStage*)stage())->addChild(_controller2);
			}
			else {
				((flStage*)stage())->removeChild(_controller2);
			}
		}
	}

	//コンボボックス
	else if (event.type() == flComboBoxEvent::CHANGE) {
		flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
		flComboBox* comboBox = (flComboBox*)(event.currentTarget());

		if (comboBox == comboBox001) {
			if (comboBox->selectedValue<string>() == "default") {
				//NativeWindow::orderToDefault();
			}
			else if (comboBox->selectedValue<string>() == "alwaysOnBottom") {
				//最背面に配置
				//                ofSetWindowPosition(1925, 0);
				//                ofSetFullscreen(true);
				//NativeWindow::orderToBack();
			}
			else if (comboBox->selectedValue<string>() == "alwaysOnTop") {
				//NativeWindow::orderToFront();
			}
		}
	}

	//チェックボックス
	else if (event.type() == flCheckBoxEvent::CHANGE) {
		flCheckBoxEvent& checkButtonEvent = *(flCheckBoxEvent*) &event;
		flCheckBox* check = (flCheckBox*)(event.currentTarget());

		if (check == check201) {
			check202->selected(false, false);

			check220->selected(false, false);
			check221->selected(true, false);
		}
		else if (check == check202) {
			check201->selected(false, false);

			check220->selected(true, false);
			check221->selected(false, false);
		}
	}

	//ラジオボタン
	else if (event.type() == flRadioButtonEvent::CHANGE) {
		flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
		flRadioButton* radio = (flRadioButton*)(event.currentTarget());
	}

	//ナンバーダイアラー
	else if (event.type() == flNumericDialerEvent::CHANGE) {
		flNumericDialerEvent& numericDialerEvent = *(flNumericDialerEvent*) &event;
		flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
	}

	//2Dパッド
	else if (event.type() == flPadEvent::CHANGE) {
		flPadEvent& padEvent = *(flPadEvent*) &event;
		flPad2D* pad = (flPad2D*)(event.currentTarget());
	}

	//スライダー
	else if (event.type() == flSliderEvent::CHANGE) {
		flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
		flSlider* slider = (flSlider*)(event.currentTarget());
	}

	//レンジスライダー
	else if (event.type() == flRangeSliderEvent::CHANGE) {
		flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
		flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
	}

	//カラースライダー
	else if (event.type() == flColorSliderEvent::CHANGE) {
		flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
		flColorSlider* colorSlider = (flColorSlider*)(event.currentTarget());

		if (colorSlider == colorSlider001) {
			ofBackground(colorSlider->redValue(), colorSlider->greenValue(), colorSlider->blueValue());
		}
	}

	//ジョイスティック1D
	else if (event.type() == flJoyStick1Event::CHANGE) {
		flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
		flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick1Event::UP) {
		flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
		flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick1Event::DOWN) {
		flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
		flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick1Event::LEFT) {
		flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
		flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick1Event::RIGHT) {
		flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
		flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
	}

	//ジョイスティック2D
	else if (event.type() == flJoyStick2Event::CHANGE) {
		flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
		flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick2Event::UP) {
		flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
		flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick2Event::DOWN) {
		flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
		flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick2Event::LEFT) {
		flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
		flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
	}
	else if (event.type() == flJoyStick2Event::RIGHT) {
		flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
		flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
	}
}
