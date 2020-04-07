#include "Container.h"

//==============================================================
// Constructor / Destructor
//==============================================================

//-------------------------------------------------------------
Container::Container() {
    ofLog() << "[Container]Container()";
    
    _target = this;
    name("Container");
    
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

//-------------------------------------------------------------
Container::~Container() {
    ofLog() << "[Container]~Container()";
    
    _forceX = 0;
    _forceY = 0;
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//-------------------------------------------------------------
void Container::_setup() {
    ofLog() << "[Container]_setup()";
    
    _setupBoxes();
    
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &Container::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_UP, this, &Container::_mouseEventHandler);
    
    //addEventListener(Event::ADDED, this, eventHandler);
    //addEventListener(Event::REMOVED, this, eventHandler);
    //addEventListener(Event::ADDED_TO_STAGE, this, eventHandler);
    //addEventListener(Event::REMOVED_FROM_STAGE, this, eventHandler);
    //dispatchEvent(new Event(MouseEvent::MOUSE_OVER));
}

//-------------------------------------------------------------
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
    
//    box1_1->rotation(box1_1->rotation() + 0.25);
}

//-------------------------------------------------------------
void Container::_draw() {
    ofPushStyle();
    
    ofNoFill();
    ofSetLineWidth(1);
    
    {
        flRectangle rect = box1->getRect(this);
        ofSetColor(0, 0, 255, 150);
        ofDrawRectangle(rect.left(), rect.top(), rect.width(), rect.height());
    }
//    {
//        flRectangle rect = box1_1->getRect(box1);
//        ofSetColor(0, 0, 255, 150);
//        ofDrawRectangle(rect.left(), rect.top(), rect.width(), rect.height());
//    }

    ofPopStyle();
}

//==============================================================
// Public Method
//==============================================================

//==============================================================
// Protected / Private Method
//==============================================================

//-------------------------------------------------------------
void Container::_setupBoxes() {
    //--------------------------------------
    //ボックス1
    box1 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box1->title("Default");
    box1->name("Box1");
    box1->x(20);
    box1->y(150);
//    box1->rotation(45);
    addChild(box1);
    box1->setup();
    
    box1_1 = new InteractiveBox(200, 140, ofColor(0, 255, 0));
    box1_1->name("Box1-1");
    box1_1->x(10);
    box1_1->y(140);
    box1->addChild(box1_1);
    box1_1->setup();

    box1_2 = new InteractiveBox(200, 140, ofColor(0, 0, 255));
    box1_2->name("Box1-2");
    box1_2->x(190);
    box1_2->y(170);
    box1->addChild(box1_2);
    box1_2->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス2
    box2 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box2->title("Box2.mouseChildren = false");
    box2->name("Box2");
    box2->x(440);
    box2->y(150);
    addChild(box2);
//    box2->rotation(45);
    box2->setup();
    box2->mouseChildren(false);

    box2_1 = new InteractiveBox(200, 140, ofColor(0, 255, 0));
    box2_1->name("Box2-1");
    box2_1->x(10);
    box2_1->y(140);
    box2->addChild(box2_1);
    box2_1->setup();

    box2_2 = new InteractiveBox(200, 140, ofColor(0, 0, 255));
    box2_2->name("Box2-2");
    box2_2->x(190);
    box2_2->y(170);
    box2->addChild(box2_2);
    box2_2->setup();
    //--------------------------------------

    //--------------------------------------
    //ボックス3
    box3 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box3->title("Box3-1.mouseEnabled = false");
    box3->name("Box3");
    box3->x(860);
    box3->y(150);
    addChild(box3);
    box3->setup();

    box3_1 = new InteractiveBox(200, 140, ofColor(0, 255, 0));
    box3_1->name("Box3-1");
    box3_1->x(10);
    box3_1->y(140);
    box3->addChild(box3_1);
    box3_1->setup();
    box3_1->mouseEnabled(false);

    box3_2 = new InteractiveBox(200, 140, ofColor(0, 0, 255));
    box3_2->name("Box3-2");
    box3_2->x(190);
    box3_2->y(170);
    box3->addChild(box3_2);
    box3_2->setup();
    //--------------------------------------

    //--------------------------------------
    //ボックス4
    box4 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box4->title("Box4-1.mouseEnabled = false");
    box4->name("Box4");
    box4->x(1280);
    box4->y(150);
    addChild(box4);
    box4->setup();

    box4_1 = new InteractiveBox(200, 200, ofColor(0, 255, 0));
    box4_1->name("Box4-1");
    box4_1->x(140);
    box4_1->y(60);
    box4->addChild(box4_1);
    box4_1->setup();
    box4_1->mouseEnabled(false);

    box4_1_1 = new InteractiveBox(200, 140, ofColor(0, 0, 255));
    box4_1_1->name("Box4-1-1");
    box4_1_1->x(50);
    box4_1_1->y(85);
    box4_1->addChild(box4_1_1);
    box4_1_1->setup();
    //--------------------------------------

    //--------------------------------------
    //ボックス5
    box5 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box5->title("Box5-1-1.mouseEnabled = false");
    box5->name("Box5");
    box5->x(20);
    box5->y(490);
    addChild(box5);
    box5->setup();

    box5_1 = new InteractiveBox(300, 180, ofColor(0, 255, 0));
    box5_1->name("Box5-1");
    box5_1->x(93);
    box5_1->y(80);
    box5_1->setup();
    box5->addChild(box5_1);

    box5_1_1 = new InteractiveBox(200, 140, ofColor(0, 0, 255));
    box5_1_1->name("Box5-1-1");
    box5_1_1->x(40);
    box5_1_1->y(85);
    box5_1_1->setup();
    box5_1_1->mouseEnabled(false);
    box5_1->addChild(box5_1_1);
    //--------------------------------------

    //--------------------------------------
    //ボックス6
    box6 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box6->title("Box6.mouseChildren = false");
    box6->name("Box6");
    box6->x(440);
    box6->y(490);
    addChild(box6);
    box6->setup();
    box6->mouseChildren(false);

    box6_1 = new InteractiveBox(200, 200, ofColor(0, 255, 0));
    box6_1->name("Box6-1");
    box6_1->x(100);
    box6_1->y(60);
    box6->addChild(box6_1);
    box6_1->setup();

    box6_1_1 = new InteractiveBox(100, 140, ofColor(0, 0, 255));
    box6_1_1->name("Box6-1-1");
    box6_1_1->x(50);
    box6_1_1->y(85);
    box6_1->addChild(box6_1_1);
    box6_1_1->setup();
    //--------------------------------------

    //--------------------------------------
    //ボックス7
    box7 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box7->title("Box7.mouseChildren = mouseEnabled = false");
    box7->name("Box7");
    box7->x(860);
    box7->y(490);
    addChild(box7);
    box7->setup();
    box7->mouseEnabled(false);
    box7->mouseChildren(false);

    box7_1 = new InteractiveBox(200, 200, ofColor(0, 255, 0));
    box7_1->name("Box7-1");
    box7_1->x(100);
    box7_1->y(60);
    box7->addChild(box7_1);
    box7_1->setup();

    box7_1_1 = new InteractiveBox(100, 140, ofColor(0, 0, 255));
    box7_1_1->name("Box7-1-1");
    box7_1_1->x(50);
    box7_1_1->y(85);
    box7_1->addChild(box7_1_1);
    box7_1_1->setup();
    //--------------------------------------

    //--------------------------------------
    //ボックス8
    box8 = new InteractiveBox(400, 320, ofColor(255, 0, 0));
    box8->title("Box8.mouseEnabled = false");
    box8->name("Box8");
    box8->x(1280);
    box8->y(490);
    box8->setup();
    box8->mouseEnabled(false);
    addChild(box8);

    box8_1 = new InteractiveBox(360, 180, ofColor(0, 255, 0));
    box8_1->name("Box8-1");
    box8_1->x(20);
    box8_1->y(100);
    box8_1->setup();
    box8->addChild(box8_1);

    box8_1_1 = new InteractiveBox(200, 140, ofColor(0, 0, 255));
    box8_1_1->name("Box8-1-1");
    box8_1_1->x(150);
    box8_1_1->y(70);
    box8_1_1->setup();
    box8_1->addChild(box8_1_1);
    //--------------------------------------
}

//==============================================================
// Protected / Private Event Handler
//==============================================================

//-------------------------------------------------------------
void Container::_moveEventHandler(flEvent& event) {
    //    $this->graphics->clear();
    //    $this->graphics->drawRect(-$this->x(), -$this->y(), ofGetScreenWidth(), ofGetScreenHeight());
    //    $this->graphics->endFill();
}

//-------------------------------------------------------------
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
