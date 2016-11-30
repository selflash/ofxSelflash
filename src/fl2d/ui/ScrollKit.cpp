#include "ScrollKit.h"

namespace fl2d {

    //--------------------------------------------------------------
    //
    ScrollKit::ScrollKit() {
        
        //base = NULL;
        
        graphics()->lineStyle(0.5, 0x0);
        //graphics->beginFill(0xcccccc);
        graphics()->drawRect(0, 0, 500, 600);
        
        //ベース
        //base = new Shape();
        //base->graphics->lineStyle(0.5, 0x0);
        //base->graphics->beginFill(0xcccccc);
        //base->graphics->drawRect(0, 0, 100, 200);
        //addChild(base);
        
        //ボディ
        _body = (DisplayObject*)new Sprite();
        //_body->mouseEnabled(false);
        //_body->mouseChildren(false);
        //_body->graphics->lineStyle(0.5, 0x0);
        //_body->graphics->beginFill(0xcccccc, 0.5);
        //_body->graphics->drawRect(0, 0, 500, 1000);
        //addChild(body);
        
        addEventListener(MouseEvent::ROLL_OVER, this, &ScrollKit::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &ScrollKit::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &ScrollKit::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_UP, this, &ScrollKit::_mouseEventHandler);
        
        
        // utlitly function to randomise a rectangle
        viewport.x = 0;
        viewport.y = 0;
        viewport.width = 500;
        viewport.height = 600;
    }

    //--------------------------------------------------------------
    //
    ScrollKit::~ScrollKit() {
        
    }

    DisplayObject* ScrollKit::body() {
        return NULL;
    }
    void ScrollKit::body(DisplayObject* value) {
        _body = value;
        //_body->alpha(0.1);
        
        cout << "[PARENT] = " << _body->parent() << endl;
        if(_body->parent()) ((DisplayObjectContainer*)_body->parent())->removeChild(_body);
    }


    //--------------------------------------------------------------
    //
    void ScrollKit::_setup() {
        
    }

    //--------------------------------------------------------------
    //
    void ScrollKit::_update() {
        viewport.x = x() - _body->x();
        viewport.width = 500 + _body->x();
        viewport.y = y();

        
        _body->update();
    }

    //--------------------------------------------------------------
    //
    void ScrollKit::_draw() {
        
        //--
        // 2d view
        
        //drawViewportOutline(viewport);
        
        // keep a copy of your viewport and transform matrices for later
        ofPushView();
        
        
        // tell OpenGL to change your viewport. note that your transform matrices will now need setting up
        ofViewport(viewport);
        
        // setup transform matrices for normal oF-style usage, i.e.
        //  0,0=left,top
        //  ofGetViewportWidth(),ofGetViewportHeight()=right,bottom
        ofSetupScreen();
        ofPushMatrix();
        ofTranslate(0, 250);
        _body->draw();
        ofPopMatrix();
    /*
        ofFill();
        ofSetColor(220);
        for(int x = 0; x < 1000; x += 20) {
            for(int y = 0; y < 1000; y += 20) {
                ofCircle(x, y, sin((x + y) / 100.0f + ofGetElapsedTimef()) * 5.0f);
            }
        }
    */    
        // restore the old viewport (now full view and oF coords)
        ofPopView();
        //--

    }


    //--------------------------------------------------------------
    void ScrollKit::drawViewportOutline(const ofRectangle & $viewport) {
        //ofPushStyle();
        ofFill();
        ofSetColor(50);
        ofSetLineWidth(0);
        ofDrawRectangle($viewport);
        ofNoFill();
        ofSetColor(25);
        ofSetLineWidth(1.0f);
        ofDrawRectangle($viewport);
        //ofPopStyle();
    }

    //--------------------------------------------------------------
    //
    void ScrollKit::_moveEventHandler(Event &event) {
    /*
        cout << "\n----------------------------------------------------------" << endl;
        printf("[ScrollKit]_moveEventHandler(%s) %s\n", ofToString(event.type()).c_str(), name().c_str());
        cout << "target = " << ((DisplayObject*)event.target())->name().c_str() << endl;
        cout << "currnetTarget = " << ((DisplayObject*)event.currentTarget())->name().c_str() << endl;
        cout << "----------------------------------------------------------\n" << endl;
    */    
        //cout << $this->mouseY() << endl;
        
        //cout << "HOGE" << endl;
        
        //float ty = $this->mouseY() - $this->_disy;
        //if(ty > 0) ty = 0;
        //if(ty < $this->height() - $this->body->height()) ty = $this->height() - $this->body->height();
        float ty = mouseY() - _disy;
        //if(ty > 0) ty = 0;
        //if(ty < 600 - 1000) ty = 600 - 1000;
        _body->y(ty);
        
        //$this->body->y(400);
    }

    //--------------------------------------------------------------
    //
    void ScrollKit::_mouseEventHandler(Event& event) {
    /*
        cout << "\n----------------------------------------------------------" << endl;
        printf("[ScrollKit]_mouseEventHandler(%s) %s\n", ofToString(event.type()).c_str(), name().c_str());
        cout << "target = " << ((DisplayObject*)event.target())->name().c_str() << endl;
        cout << "currnetTarget = " << ((DisplayObject*)event.currentTarget())->name().c_str() << endl;
        cout << "stage = " << ((DisplayObject*)event.target())->stage()->name().c_str() << endl;
        cout << "----------------------------------------------------------\n" << endl;
    */    
        
        if(event.type() == MouseEvent::ROLL_OVER) {
            if(event.target() == this) {
    //            $this->graphics->clear();
    //            $this->graphics->beginFill(0xffff00);
    //            $this->graphics->drawRect(0, 0, $this->width(), $this->height());
    //            $this->graphics->endFill();
            }
        }
        if(event.type() == MouseEvent::ROLL_OUT) {
            if(event.target() == this) {
    //            $this->graphics->clear();
    //            $this->graphics->beginFill(0xcccccc);
    //            $this->graphics->drawRect(0, 0, $this->width(), $this->height());
    //            $this->graphics->endFill();
            }
        }
        if(event.type() == MouseEvent::MOUSE_OVER) {
            if(event.target() == this) {
    //            $this->graphics->clear();
    //            $this->graphics->beginFill(0xffff00);
    //            $this->graphics->drawRect(0, 0, $this->width(), $this->height());
    //            $this->graphics->endFill();
            }
        }
        if(event.type() == MouseEvent::MOUSE_OUT) {
            if(event.target() == this) {
    //            $this->graphics->clear();
    //            $this->graphics->beginFill(0xcccccc);
    //            $this->graphics->drawRect(0, 0, $this->width(), $this->height());
    //            $this->graphics->endFill();
            }
        }
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
    //            $this->graphics->clear();
    //            $this->graphics->beginFill(0xff0000);
    //            $this->graphics->drawRect(0, 0, $this->width(), $this->height());
    //            $this->graphics->endFill();
                //$this->startDrag();
                
                _disy = mouseY() - _body->y();

                
                //stage()->addEventListener(MouseEvent::MOUSE_UP, this, &ScrollKit::_mouseEventHandler);
                //stage()->addEventListener(MouseEvent::MOUSE_MOVE, this, &ScrollKit::_moveEventHandler);
            }
        }
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.target() == this) {
    //            $this->graphics->clear();
    //            $this->graphics->beginFill(0xffff00);
    //            $this->graphics->drawRect(0, 0, $this->width(), $this->height());
    //            $this->graphics->endFill();
                //$this->stopDrag();
            }
            if(event.target() == this->stage()) {
                //stage()->removeEventListener(MouseEvent::MOUSE_UP, &ScrollKit::_mouseEventHandler);
                //stage()->removeEventListener(MouseEvent::MOUSE_MOVE, &ScrollKit::_moveEventHandler);
            }
        }
    }

}
