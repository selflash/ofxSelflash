#include "flToolTip.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flToolTip::flToolTip() {
        //    ofLog() << "[flToolTip]ToolTip()";
        _target = this;
        name("flToolTip");
        
//        mouseEnabled(false);
//        mouseChildren(false);
        
        _fontHeight = flFont::getLineHeight(10);
//        ofLog() << "_fontHeight = " << _fontHeight;
        
        _updateWindow();
    }
    
    //--------------------------------------------------------------
    flToolTip::~flToolTip() {
        //    ofLog() << "[flToolTip]~ToolTip()";
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    //void flBasicDraggableObject::_setup() {
    //    ofLog() << "[flBasicDraggableObject]_setup()";
    //
    //}
    
    //--------------------------------------------------------------
    void flToolTip::_update() {
    //    ofLog() << width() << ", " << height();
    
        //If the flFont is not ready, monitor a font is loaded or not.
        if(!_bReady) {
            if(flFont::loaded()) {
                _fontHeight = flFont::getLineHeight(10);
                _updateWindow();                
                _bReady = true;
            }
        }
    }
    
    //--------------------------------------------------------------
    void flToolTip::_draw() {
        //--------------------------------------
        ofPushStyle();
        ofSetColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        flFont::drawString(_text, 10, 3, _fontHeight - 2);
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
        g->beginFill(flDefinition::UI_WINDOW_BACKGROUND_COLOR);
        g->drawRect(0, 0, w, h);
        g->lineStyle(1, flDefinition::UI_WINDOW_BORDER_COLOR);
        g->moveTo(-1, -1);
        g->lineTo(w + 1, -1);
        g->lineTo(w + 1, h + 1);
        g->lineTo(-1, h + 1);
        g->lineTo(-1, -1);
        g->endFill();
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

}
