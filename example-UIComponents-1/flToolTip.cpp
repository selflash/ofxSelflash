#include "flToolTip.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flToolTip::flToolTip() {
        //    cout << "[flToolTip]ToolTip()" << endl;
        _target = this;
        name("flToolTip");
        
        mouseEnabled(false);
        mouseChildren(false);
        
        _fontHeight = flFont::getLineHeight(10);
//        ofLog() << "_fontHeight = " << _fontHeight;
        
        _updateWindow();
    }
    
    //--------------------------------------------------------------
    flToolTip::~flToolTip() {
        //    cout << "[flToolTip]~ToolTip()" << endl;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    //void flBasicDraggableObject::_setup() {
    //    cout << "[flBasicDraggableObject]_setup()" << endl;
    //
    //}
    
    //--------------------------------------------------------------
    void flToolTip::_update() {
    //    cout << width() << ", " << height() << endl;
    
    }
    
    //--------------------------------------------------------------
    void flToolTip::_draw() {
        //--------------------------------------
        ofPushStyle();
        ofSetColor(255, 255, 255);
        flFont::drawString(_text, 10, 3, _fontHeight - 5);
        ofPopStyle();
        //--------------------------------------
    }

    //==============================================================
    // Public Mehtod
    //==============================================================

    //--------------------------------------------------------------
    string flToolTip::text() { return _text;}
    void flToolTip::text(string value) {
        _text = value;
        _updateWindow();
    }

    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flToolTip::_updateWindow() {
        ofRectangle rect = flFont::getStringBoundingBox(_text);
        int w = rect.width + 6;
        //        int h = rect.height;
        int n = count(_text.cbegin(), _text.cend(), '\n');
        int h = 18 * (n + 1);
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->beginFill(0x000000, 0.5);
        g->drawRect(0, 0, w, h);
        g->lineStyle(1, 0xffffff);
        g->moveTo(-1, -1);
        g->lineTo(w + 1, -1);
        g->lineTo(w + 1, h + 1);
        g->lineTo(-1, h + 1);
        g->lineTo(-1, -1);
        g->endFill();
    }

}
