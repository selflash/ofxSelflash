#include "NetworkController.h"


//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
SocketController::SocketController() {
    cout << "[SocketController]SocketController()" << endl;
    _target = this;
    
    name("SocketController");
    useHandCursor(true);
}

//--------------------------------------------------------------
//
SocketController::~SocketController() {
    cout << "[SocketController]~SocketController()" << endl;
    _target = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void SocketController::_setup() {
    cout << "[SocketController]_setup()" << endl;
    
    //    flGraphics* g;
    //    g = graphics();
    //    g->clear();
    //    g->lineStyle(1, 0xffffff);
    //    g->beginFill(0x000000, 0.7);
    //    g->drawRect(0, 0, 500, 500);
    //    g->endFill();
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    
    //----------------------------------------------------------
    marginLeft = 5;
    marginTop = 5;
    spacing = 100;
    lineSpacing = 18 + 5;
    flTextField* textField = NULL;
    
    _textField001 = new flTextField();
    _textField001->width(180);
    _textField001->height(20);
    _textField001->x(marginLeft + spacing * 0);
    _textField001->y(marginTop + lineSpacing * 0);
    _textField001->text(_name);
    addChild(_textField001);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 1);
    textField->text("Binded");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 2);
    textField->text("Connected");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 3);
    textField->text("Local IP");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 4);
    textField->text("Local Port");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 5);
    textField->text("Target IP");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 6);
    textField->text("Target Port");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 7);
    textField->text("Remote IP");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 8);
    textField->text("Remote Port");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 9);
    textField->text("Send Data");
    addChild(textField);
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 10);
    textField->text("Received Data");
    addChild(textField);
    
    marginLeft = 120;
    marginTop = 5;
    spacing = 100;
    lineSpacing = 18 + 5;
    
    _textField101 = new flTextField();
    _textField101->width(180);
    _textField101->height(20);
    _textField101->x(marginLeft + spacing * 0);
    _textField101->y(marginTop + lineSpacing * 1);
    addChild(_textField101);
    _textField102 = new flTextField();
    _textField102->width(180);
    _textField102->height(20);
    _textField102->x(marginLeft + spacing * 0);
    _textField102->y(marginTop + lineSpacing * 2);
    addChild(_textField102);
    _textField103 = new flTextField();
    _textField103->width(180);
    _textField103->height(20);
    _textField103->x(marginLeft + spacing * 0);
    _textField103->y(marginTop + lineSpacing * 3);
    _textField103->textColor(0x0000);
    _textField103->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    addChild(_textField103);
    _textField104 = new flTextField();
    _textField104->width(180);
    _textField104->height(20);
    _textField104->x(marginLeft + spacing * 0);
    _textField104->y(marginTop + lineSpacing * 4);
    _textField104->textColor(0x0000);
    _textField104->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    addChild(_textField104);
    _textField105 = new flTextField();
    _textField105->width(180);
    _textField105->height(20);
    _textField105->x(marginLeft + spacing * 0);
    _textField105->y(marginTop + lineSpacing * 5);
    _textField105->textColor(0x0000);
    _textField105->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    addChild(_textField105);
    _textField106 = new flTextField();
    _textField106->width(180);
    _textField106->height(20);
    _textField106->x(marginLeft + spacing * 0);
    _textField106->y(marginTop + lineSpacing * 6);
    _textField106->textColor(0x0000);
    _textField106->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    addChild(_textField106);
    _textField107 = new flTextField();
    _textField107->width(180);
    _textField107->height(20);
    _textField107->x(marginLeft + spacing * 0);
    _textField107->y(marginTop + lineSpacing * 7);
    addChild(_textField107);
    _textField108 = new flTextField();
    _textField108->width(180);
    _textField108->height(20);
    _textField108->x(marginLeft + spacing * 0);
    _textField108->y(marginTop + lineSpacing * 8);
    addChild(_textField108);
    _textField109 = new flTextField();
    _textField109->width(180);
    _textField109->height(20);
    _textField109->x(marginLeft + spacing * 0);
    _textField109->y(marginTop + lineSpacing * 9);
    addChild(_textField109);
    _textField110 = new flTextField();
    _textField110->width(180);
    _textField110->height(20);
    _textField110->x(marginLeft + spacing * 0);
    _textField110->y(marginTop + lineSpacing * 10);
    addChild(_textField110);
    //----------------------------------------------------------
    
    marginLeft = 5;
    marginTop = 260;
    spacing = 100 + 5;
    lineSpacing = 18 + 5;
    
    _button001 = new flButton(100);
    _button001->labelText("Bind");
    _button001->x(marginLeft + spacing * 0);
    _button001->y(marginTop + lineSpacing * 0);
    _button001->addEventListener(flButtonEvent::MOUSE_DOWN, this, &SocketController::_uiEventHandler);
    addChild(_button001);
    
    _button002 = new flButton(100);
    _button002->labelText("Connect");
    _button002->x(marginLeft + spacing * 1);
    _button002->y(marginTop + lineSpacing * 0);
    _button002->addEventListener(flButtonEvent::MOUSE_DOWN, this, &SocketController::_uiEventHandler);
    addChild(_button002);
    
    _button003 = new flButton(100);
    _button003->labelText("Disconnect");
    _button003->x(marginLeft + spacing * 2);
    _button003->y(marginTop + lineSpacing * 0);
    _button003->addEventListener(flButtonEvent::MOUSE_DOWN, this, &SocketController::_uiEventHandler);
    addChild(_button003);
    
    _textField002 = new flTextField();
    _textField002->text("Hello World", 0x0000);
    _textField002->width(420 - 10);
    _textField002->height(20);
    _textField002->x(marginLeft + spacing * 0);
    _textField002->y(marginTop + lineSpacing * 1);
    _textField002->type(flTextField::TEXT_FIELD_TYPE_INPUT);
    addChild(_textField002);
    
    _button011 = new flButton(100);
    _button011->labelText("Send(Target)");
    _button011->x(marginLeft + spacing * 0);
    _button011->y(marginTop + lineSpacing * 2);
    _button011->addEventListener(flButtonEvent::MOUSE_DOWN, this, &SocketController::_uiEventHandler);
    addChild(_button011);
    
    //    _button012 = new flButton(100);
    //    _button012->labelText("Send(Remote)");
    //    _button012->x(marginLeft + spacing * 1);
    //    _button012->y(marginTop + lineSpacing * 2);
    //    _button012->addEventListener(flButtonEvent::MOUSE_DOWN, this, &SocketController::_uiEventHandler);
    //    addChild(_button012);
}

//--------------------------------------------------------------
//
void SocketController::_update() {
    //cout << "[SocketController]update()" << endl;
    
    if(!_socket) return;
    _textField101->text(ofToString(_socket->isBinded() ? "true" : "false"));
    _textField102->text(ofToString(_socket->isConnected() ? "true" : "false"));
    //    _textField103->text(ofToString(_socket->localIp()));
    //    _textField104->text(ofToString(_socket->localPort()));
    //    _textField105->text(ofToString(_socket->targetIp()));
    //    _textField106->text(ofToString(_socket->targetPort()));
    _textField107->text(ofToString(_socket->remoteIp()));
    _textField108->text(ofToString(_socket->remotePort()));
    _textField109->text(ofToString(_socket->sendData()));
    _textField110->text(ofToString(_socket->receivedData()));
}

//--------------------------------------------------------------
//
void SocketController::_draw() {
    //cout << "[SocketController]draw()" << endl;
    
    //    ofDrawBitmapString(_status, 10, 20);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
string SocketController::name() { return _name; }
void SocketController::name(string value) {
    _name = value;
    
    if(_textField001) _textField001->text(_name);
}

//--------------------------------------------------------------
//
void SocketController::socket(UDPSocketWrapper* value) {
    _socket = value;
    
    _textField103->text(ofToString(_socket->localIp()));
    _textField104->text(ofToString(_socket->localPort()));
    _textField105->text(ofToString(_socket->targetIp()));
    _textField106->text(ofToString(_socket->targetPort()));
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void SocketController::_uiEventHandler(flEvent& event) {
    //    cout << "[SocketController]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == _button001) {
            bool success = _socket->bind(ofToInt(_textField104->text()));
            _button002->enabled(success);
        }
		else if (button == _button002) {
			_socket->connect(
				_textField105->text(),
				ofToInt(_textField106->text())
			);
		}
		else if(button == _button003) {
            _socket->close();
            _button002->enabled(false);
        }
        //        cout << _textField002->text() << endl;
		else if (button == _button011) {
			_socket->sendMessage(_textField002->text());
		}
        //        if(button == _button012) _networkManager->sendMessageWithUDP(0, text200->text());
    }
    
    //コンボボックス
	else if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
        cout << "selectedValue : " << comboBox->selectedValue<string>() << endl;
    }
    
    //ラジオボタン
	else if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
	else if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
    }
    
    //2Dパッド
	else if(event.type() == flPadEvent::CHANGE) {
        flPad2D* pad = (flPad2D*)(event.currentTarget());
    }
    
    //スライダー
	else if(event.type() == flSliderEvent::CHANGE) {
        flSlider* slider = (flSlider*)(event.currentTarget());
    }
    
    //レンジスライダー
	else if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
	else if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSlider* slider = (flColorSlider*)(event.currentTarget());
    }
    
    //ジョイスティック1D
	else if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::UP) {
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

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
NetworkController::NetworkController() {
    cout << "[NetworkController]NetworkController()" << endl;
    _target = this;
    
    name("NetworkController");
    useHandCursor(true);
}

//--------------------------------------------------------------
//
NetworkController::~NetworkController() {
    cout << "[NetworkController]~NetworkController()" << endl;
    _target = NULL;
    
    _status = "";
    _networkManager = NULL;
    _socketControllers.clear();
    _currentSocketController = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void NetworkController::_setup() {
    cout << "[NetworkController]_setup()" << endl;
    
    flBasicController::_setup();
    
    //    minimizeButton->visible(false);
    //    closeButton->visible(false);
    //    isDraggable(false);
    
    _normalBackWidth = 420;
    _normalBackHeight = 420;
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
    
    titleTf->text("");
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    flTextField* textField = NULL;
    
    //----------------------------------------------------------
    marginLeft = 5;
    marginTop = 5;
    spacing = 80 + 5;
    lineSpacing = 18 + 5;
    
    textField = new flTextField();
    textField->text("Socket List");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 0);
    textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    textField->mouseEnabled(false);
    addChild(textField);
    comboBox001 = new flComboBox();
    comboBox001->label(textField);
    comboBox001->x(marginLeft + spacing * 1);
    comboBox001->y(marginTop + lineSpacing * 0);
    //    comboBox001->addItem<string>("Socket 0", "socket0");
    //    comboBox001->addItem<string>("Socket 1", "socket1");
    //    comboBox001->addItem<string>("Socket 2", "socket2");
    //    comboBox001->addItem<string>("Socket 3", "socket3");
    //    comboBox001->addItem<string>("Socket 4", "socket4");
    //    comboBox001->selectedIndex(0, false);
    comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &NetworkController::_uiEventHandler);
    addChild(comboBox001);
    
    //    marginLeft = 0;
    //    marginTop = 18 + 5;
    //    spacing = 100;
    //    lineSpacing =  18 + 5;
    //
    //    for(int i = 0; i < 5; i++) {
    //        SocketController* socketController = new SocketController();
    //        socketController->setup();
    //        socketController->name("Socket " + ofToString(i));
    //        socketController->x(marginLeft + spacing * 0);
    //        socketController->y(marginTop + lineSpacing * 0);
    //        _socketControllers.push_back(socketController);
    //    }
    //    _currentSocketController = _socketControllers[0];
    //    addChild(_currentSocketController);
}

//--------------------------------------------------------------
//
void NetworkController::_update() {
    //cout << "[NetworkController]update()" << endl;
    
    if(_networkManager) {
        _status = "";
    }
}

//--------------------------------------------------------------
//
void NetworkController::_draw() {
    //cout << "[NetworkController]draw()" << endl;
    
    if(_isMinimize) return;
    //    ofDrawBitmapString(_status, 10, 20);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
void NetworkController::networkManager(NetworkManager* value) {
    _networkManager = value;
    
    int l = _networkManager->udpSockets().size();
    
    for(int i = 0; i < l; i++) {
        SocketController* socketController = new SocketController();
        socketController->setup();
        socketController->name("Socket " + ofToString(i));
        socketController->x(0);
        socketController->y(0);
        socketController->socket(_networkManager->udpSockets()[i]);
        _socketControllers.push_back(socketController);
        
        comboBox001->addItem<string>("Socket " + ofToString(i), "socket" + ofToString(i));
    }
    _currentSocketController = _socketControllers[0];
    addChild(_currentSocketController);
    
    comboBox001->selectedIndex(0, false);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void NetworkController::_uiEventHandler(flEvent& event) {
    //    cout << "[NetworkController]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == button202) _networkManager->sendMessageWithUDP(0, text200->text());
        if(button == button302) _networkManager->sendMessageWithUDP(1, text300->text());
        if(button == button402) _networkManager->sendMessageWithUDP(2, text400->text());
        if(button == button502) _networkManager->sendMessageWithUDP(3, text500->text());
        if(button == button602) _networkManager->sendMessageWithUDP(4, text600->text());
        if(button == button702) _networkManager->sendMessageWithUDP(5, text700->text());
        if(button == button802) _networkManager->sendMessageWithUDP(6, text800->text());
    }
    
    //コンボボックス
	else if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
        cout << "selectedValue : " << comboBox->selectedValue<string>() << endl;
        
        
        if(comboBox == comboBox001) {
            if(_currentSocketController) removeChild(_currentSocketController);
            
            if(comboBox001->selectedValue<string>() == "socket0") _currentSocketController = _socketControllers[0];
            if(comboBox001->selectedValue<string>() == "socket1") _currentSocketController = _socketControllers[1];
            if(comboBox001->selectedValue<string>() == "socket2") _currentSocketController = _socketControllers[2];
            if(comboBox001->selectedValue<string>() == "socket3") _currentSocketController = _socketControllers[3];
            if(comboBox001->selectedValue<string>() == "socket4") _currentSocketController = _socketControllers[4];
            if(comboBox001->selectedValue<string>() == "socket5") _currentSocketController = _socketControllers[5];
            if(comboBox001->selectedValue<string>() == "socket6") _currentSocketController = _socketControllers[6];
            if(comboBox001->selectedValue<string>() == "socket7") _currentSocketController = _socketControllers[7];
            if(comboBox001->selectedValue<string>() == "socket8") _currentSocketController = _socketControllers[8];
            if(comboBox001->selectedValue<string>() == "socket9") _currentSocketController = _socketControllers[9];
            if(comboBox001->selectedValue<string>() == "socket10") _currentSocketController = _socketControllers[10];
            
            addChild(_currentSocketController);
        }
    }
    
    //チェックボックス
	else if(event.type() == flCheckBoxEvent::CHANGE) {
        flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
        flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
    }

    //ラジオボタン
	else if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
	else if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
    }
    
    //2Dパッド
	else if(event.type() == flPadEvent::CHANGE) {
        flPad2D* pad = (flPad2D*)(event.currentTarget());
    }
    
    //スライダー
	else if(event.type() == flSliderEvent::CHANGE) {
        flSlider* slider = (flSlider*)(event.currentTarget());
    }
    
    //レンジスライダー
	else if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
	else if(event.type() == flColorSliderEvent::CHANGE) {
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

