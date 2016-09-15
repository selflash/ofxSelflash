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
//    g->beginFill(0xcc00cc, 0);
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
    
    
    int sx = 200;
    int sy = 200;
    
    //--------------------------------------
    //ボックス100
    box100 = new InteractiveBox();
    box100->title("TARGET");
    box100->name("Box100");
    box100->x(sx + 0);
    box100->y(sy + 0);
//    box100->width(200);
//    box100->height(200);
    addChild(box100);
    box100->setup();
    //--------------------------------------
    
    //--------------------------------------
    //ボックス101
    box101 = new InteractiveBox();
    box101->title("HIT AREA");
    box101->name("Box101");
    box101->x(sx + 280);
    box101->y(sy + 0);
//    box101->width(200);
//    box101->height(200);
    addChild(box101);
    box101->setup();
    box101->mouseEnabled(false);
    box100->hitArea(box101);
    //--------------------------------------
    
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
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, &Container::_mouseEventHandler);
            stage()->removeEventListener(flMouseEvent::MOUSE_MOVE, &Container::_moveEventHandler);
            
            _forceX = (x() - _preX) * 0.5;
            _forceY = (y() - _preY) * 0.5;
        }
    }
}
