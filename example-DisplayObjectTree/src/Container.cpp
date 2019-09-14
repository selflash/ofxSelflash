#include "Container.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
Container::Container() {
    cout << "[Container]Container()" << endl;
    _target = this;
    name("CONTAINER");
    
    useHandCursor(true);
    
    //    Graphics* g;
    //    g = graphics();
    //    //graphics->lineStyle(0.5);
    //    g->beginFill(0xcccccc, 0);
    //    g->clear();
    //    g->drawRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    //    g->endFill();
    
    _forceX = 0;
    _forceY = 0;
}

//--------------------------------------------------------------
//
Container::~Container() {
    cout << "[Container]~Container()" << endl;
    
    _forceX = 0;
    _forceY = 0;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void Container::_setup() {
    cout << "[Container]_setup()" << endl;
    
    _setupBoxes();
    
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &Container::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_UP, this, &Container::_mouseEventHandler);
    
    //addEventListener(Event::ADDED, this, eventHandler);
    //addEventListener(Event::REMOVED, this, eventHandler);
    //addEventListener(Event::ADDED_TO_STAGE, this, eventHandler);
    //addEventListener(Event::REMOVED_FROM_STAGE, this, eventHandler);
    //dispatchEvent(new Event(MouseEvent::MOUSE_OVER));
}

//--------------------------------------------------------------
//
void Container::_update() {
    flGraphics* g;
    g = graphics();
    g->clear();
    g->drawRect(-x(), -y(), ofGetScreenWidth(), ofGetScreenHeight());
    g->endFill();
    
    //--------------------------------------
    if(!isMouseDown()){
        _forceX *= 0.95;
        _forceY *= 0.95;
        
        float temp;
        temp = x();
        temp += _forceX;
        x(temp);
        
        temp = y();
        temp += _forceY;
        y(temp);
    } else {
        _preX = x();
        _preY = y();
    }
    //--------------------------------------
}

//--------------------------------------------------------------
//
void Container::_draw() {
    
}

//==============================================================
// PRIVATE METHOD
//==============================================================

//--------------------------------------------------------------
//
void Container::_setupBoxes() {
    //--------------------------------------
    //ボックス1
    box1 = new InteractiveBox(400, 300, 0xff0000);
    box1->title("DEFAULT");
    box1->name("BOX1");
    box1->x(20);
    box1->y(150);
    addChild(box1);
    box1->setup();
    
    box1_1 = new InteractiveBox(150, 100, 0x00ff00);
    box1_1->name("BOX1-1");
    box1_1->x(30);
    box1_1->y(100);
    box1->addChild(box1_1);
    box1_1->setup();
    
    box1_2 = new InteractiveBox(150, 100, 0x00ff00);
    box1_2->name("BOX1-2");
    box1_2->x(220);
    box1_2->y(170);
    box1->addChild(box1_2);
    box1_2->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス2
    box2 = new InteractiveBox(400, 300, 0xff0000);
    box2->title("BOX2.mouseChildren = false");
    box2->name("BOX2");
    box2->x(460);
    box2->y(150);
    addChild(box2);
    box2->setup();
    box2->mouseChildren(false);
    
    box2_1 = new InteractiveBox(150, 100, 0x00ff00);
    box2_1->name("BOX2-1");
    box2_1->x(30);
    box2_1->y(100);
    box2->addChild(box2_1);
    box2_1->setup();
    
    box2_2 = new InteractiveBox(150, 100, 0x00ff00);
    box2_2->name("BOX2-2");
    box2_2->x(220);
    box2_2->y(170);
    box2->addChild(box2_2);
    box2_2->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス3
    box3 = new InteractiveBox(400, 300, 0xff0000);
    box3->title("BOX3-1.mouseEnabled = false");
    box3->name("BOX3");
    box3->x(900);
    box3->y(150);
    addChild(box3);
    box3->setup();
    
    box3_1 = new InteractiveBox(150, 100, 0x00ff00);
    box3_1->name("BOX3-1");
    box3_1->x(30);
    box3_1->y(100);
    box3->addChild(box3_1);
    box3_1->setup();
    box3_1->mouseEnabled(false);
    
    box3_2 = new InteractiveBox(150, 100, 0x00ff00);
    box3_2->name("BOX3-2");
    box3_2->x(220);
    box3_2->y(170);
    box3->addChild(box3_2);
    box3_2->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス4
    box4 = new InteractiveBox(400, 300, 0xff0000);
    box4->title("BOX4-1.mouseEnabled = false");
    box4->name("BOX4");
    box4->x(1340);
    box4->y(150);
    addChild(box4);
    box4->setup();
    
    box4_1 = new InteractiveBox(200, 200, 0x00ff00);
    box4_1->name("BOX4-1");
    box4_1->x(100);
    box4_1->y(60);
    box4->addChild(box4_1);
    box4_1->setup();
    box4_1->mouseEnabled(false);
    
    box4_1_1 = new InteractiveBox(100, 100, 0x0000ff);
    box4_1_1->name("BOX4-1-1");
    box4_1_1->x(50);
    box4_1_1->y(85);
    box4_1->addChild(box4_1_1);
    box4_1_1->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス5
    box5 = new InteractiveBox(400, 300, 0xff0000);
    box5->title("BOX5-1-1.mouseEnabled = false");
    box5->name("BOX5");
    box5->x(20);
    box5->y(490);
    addChild(box5);
    box5->setup();
    
    box5_1 = new InteractiveBox(200, 200, 0x00ff00);
    box5_1->name("BOX5-1");
    box5_1->x(100);
    box5_1->y(60);
    box5->addChild(box5_1);
    box5_1->setup();
    
    box5_1_1 = new InteractiveBox(100, 100, 0x0000ff);
    box5_1_1->name("BOX5-1-1");
    box5_1_1->x(50);
    box5_1_1->y(85);
    box5_1->addChild(box5_1_1);
    box5_1_1->setup();
    box5_1_1->mouseEnabled(false);
    //--------------------------------------
    
    //--------------------------------------
    //ボックス6
    box6 = new InteractiveBox(400, 300, 0xff0000);
    box6->title("BOX6.mouseChildren = false");
    box6->name("BOX6");
    box6->x(460);
    box6->y(490);
    addChild(box6);
    box6->setup();
    box6->mouseChildren(false);
    
    box6_1 = new InteractiveBox(200, 200, 0x00ff00);
    box6_1->name("BOX6-1");
    box6_1->x(100);
    box6_1->y(60);
    box6->addChild(box6_1);
    box6_1->setup();
    
    box6_1_1 = new InteractiveBox(100, 100, 0x0000ff);
    box6_1_1->name("BOX6-1-1");
    box6_1_1->x(50);
    box6_1_1->y(85);
    box6_1->addChild(box6_1_1);
    box6_1_1->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス7
    box7 = new InteractiveBox(400, 300, 0xff0000);
    box7->title("BOX7.mouseChildren = mouseEnabled = false");
    box7->name("BOX7");
    box7->x(900);
    box7->y(490);
    addChild(box7);
    box7->setup();
    box7->mouseEnabled(false);
    box7->mouseChildren(false);
    
    box7_1 = new InteractiveBox(200, 200, 0x00ff00);
    box7_1->name("BOX7-1");
    box7_1->x(100);
    box7_1->y(60);
    box7->addChild(box7_1);
    box7_1->setup();
    
    box7_1_1 = new InteractiveBox(100, 100, 0x0000ff);
    box7_1_1->name("BOX7-1-1");
    box7_1_1->x(50);
    box7_1_1->y(85);
    box7_1->addChild(box7_1_1);
    box7_1_1->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス8
    box8 = new InteractiveBox(400, 300, 0xff0000);
    box8->title("BOX8.mouseEnabled = false");
    box8->name("BOX8");
    box8->x(1340);
    box8->y(490);
    addChild(box8);
    box8->setup();
    box8->mouseEnabled(false);
    
    box8_1 = new InteractiveBox(200, 200, 0x00ff00);
    box8_1->name("BOX8-1");
    box8_1->x(100);
    box8_1->y(60);
    box8->addChild(box8_1);
    box8_1->setup();
    
    box8_1_1 = new InteractiveBox(100, 100, 0x0000ff);
    box8_1_1->name("BOX8-1-1");
    box8_1_1->x(50);
    box8_1_1->y(85);
    box8_1->addChild(box8_1_1);
    box8_1_1->setup();
    //--------------------------------------
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void Container::_moveEventHandler(flEvent& event) {
    //    $this->graphics->clear();
    //    $this->graphics->drawRect(-$this->x(), -$this->y(), ofGetScreenWidth(), ofGetScreenHeight());
    //    $this->graphics->endFill();
}

//--------------------------------------------------------------
//
void Container::_mouseEventHandler(flEvent& event) {
    //    cout << "[Container]_mouseEventHandler(" << event.type() << ")" << endl;
    //    cout << "[PrentBox]this          = " << this << endl;
    //    cout << "[ParetBox]currentTarget = " << event.currentTarget() << endl;
    //    cout << "[ParetBox]target        = " << event.target() << endl;
    
    if(event.type() == flMouseEvent::MOUSE_OVER) {
        if(event.target() == this) {
            
        }
    }
    if(event.type() == flMouseEvent::MOUSE_OUT) {
        if(event.target() == this) {
            
        }
    }
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        if(event.target() == this) {
            startDrag();
            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &Container::_mouseEventHandler);
            stage()->addEventListener(flMouseEvent::MOUSE_MOVE, this, &Container::_moveEventHandler);
        }
    }
    if(event.type() == flMouseEvent::MOUSE_UP) {
        if(event.currentTarget() == stage()) {
            stopDrag();
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &Container::_mouseEventHandler);
            stage()->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &Container::_moveEventHandler);
            
            _forceX = (x() - _preX) * 0.5;
            _forceY = (y() - _preY) * 0.5;
        }
    }
}
