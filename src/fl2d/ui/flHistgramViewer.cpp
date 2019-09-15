#include "flHistgramViewer.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flHistgramViewer::flHistgramViewer(float width, float height) {
        //cout << "[flHistgramViewer]flHistgramViewer()" << endl;
        
        _target = this;
        name("flHistgramViewer");
        
        //        buttonMode(true);
        useHandCursor(true);
        
        _uiWidth = width;
        _uiHeight = height;
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        
        //------------------------------------------
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        addEventListener(flMouseEvent::ROLL_OVER, this, &flHistgramViewer::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flHistgramViewer::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flHistgramViewer::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        _value = 1.0;
        _tempValue = 1.0;
        _min = 0.001;
        _weight = 0.005;
        _startPos = new ofPoint(0, 0);
        //------------------------------------------
        
        _valueHistory.resize((int)_uiWidth);
        //        _avelageHistroy.resize((int)_uiWidth);
        for(int i = 0; i < _valueHistory.size(); i++) _line.addVertex(0, 0);
    }
    
    //--------------------------------------------------------------
    //
    flHistgramViewer::~flHistgramViewer() {
        //cout << "[flHistgramViewer]~flHistgramViewer()" << endl;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flHistgramViewer::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flHistgramViewer::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flHistgramViewer::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
        
        _uiWidth = 0.0;
        _uiHeight = 0.0;
        
        _label = NULL;
        
        _value = 0.0;
        _tempValue = 0.0;
        _min = 0.0;
        _weight = 0.0;
        
        delete _startPos;
        _startPos = NULL;
        
        _valueHistory.clear();
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_update() {
        if(isMouseDown()) {
            _valueScale = _tempValue + ((mouseY() - _startPos->y) * _weight);
            _valueScale = max(_valueScale, _min);
            //            if(!isnan(_max)) if(_max <= _value) _value = _max;
            //            if(_valueScale <= _min) _valueScale = _min;
            ofLogNotice() << "_valueScale = " << _valueScale;
            
            //            if(_roundEnabled) {
            //                _valueText->text(ofToString(MathUtil::roundd(_value)));
            //            } else {
            //                _valueText->text(ofToString(_value));
            //            }
        }
        
        //------------------------------------------
        {
            int l = _valueHistory.size();
            for(int i = 0; i < l; i++) {
                int ni = i + 1;
                if(ni >= l) ni = 0;
                _valueHistory[i] = _valueHistory[ni];
            }
        }
        //------------------------------------------
        
        //        //------------------------------------------
        //        {
        //            int l = _avelageHistroy.size();
        //            float sum = 0;
        //            for(int i = 0; i < l; i++) {
        //                int ni = i + 1;
        //                if(ni >= l) ni = 0;
        //                _avelageHistroy[i] = _avelageHistroy[ni];
        //            }
        //
        //            _average = 0;
        //            for(const float& n :  _valueHistory) {
        //                _average += n;
        //            }
        //            _average /= (float)l;
        //            _avelageHistroy[l - 1] = _average;
        //        }
        //        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_draw() {
        ofPushStyle();
        
        float iy = _uiHeight * 0.5f;
        
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        ofSetLineWidth(1);
        ofDrawLine(0, iy, _uiWidth, iy);
        
        //------------------------------------------
        {
            int l = _valueHistory.size();
            for(int i = 0; i < l; i++) {
                float vx = i + 1;
                float vy = iy - (_valueHistory[i] * 10) * _valueScale;
                vy = max(vy, 0.0f);
                vy = min(vy, _uiHeight - 1);
                _line[i].x = vx;
                _line[i].y = vy;
            }
        }
        
        //        GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
        GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
        ofEnableSmoothing();
        ofEnableAntiAliasing();
        
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        ofSetLineWidth(2);
        _line.draw();
        if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        //        if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        //------------------------------------------
        
        //        //------------------------------------------
        //        {
        //            int l = _avelageHistroy.size();
        //            for(int i = 0; i < l; i++) {
        //                float vx = i + 1;
        //                float vy = iy - (_avelageHistroy[i] * 10) * _valueScale;
        //                vy = max(vy, 0.0f);
        //                vy = min(vy, _uiHeight - 1);
        //                _line[i].x = vx;
        //                _line[i].y = vy;
        //            }
        //
        //
        //            GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
        //            ofEnableSmoothing();
        //            ofEnableAntiAliasing();
        //
        //            ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        //            ofSetLineWidth(2);
        //            _line.draw();
        //            if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        //        }
        //        //------------------------------------------
        
        //------------------------------------------
        float textHeight = flFont::getMaxStringHeight();
        ofPushMatrix();
        ofTranslate(2, textHeight);
        ofPushStyle();
        //        ofSetColor(_textColor, 255 * _compoundAlpha);
        flFont::drawString(ofToString(_value), 5, -1);
        ofPopStyle();
        ofPopMatrix();
        
        //        ofPushMatrix();
        //        ofTranslate(2, textHeight * 2);
        //        ofPushStyle();
        ////        ofSetColor(_textColor, 255 * _compoundAlpha);
        //        Font::drawString(ofToString(_average), 5, -1);
        //        ofPopStyle();
        //        ofPopMatrix();
        //------------------------------------------
        
        ofPopStyle();
    }
    
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flHistgramViewer::label() { return _label; }
    void flHistgramViewer::label(flTextField* value) { _label = value; }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_drawTrackGraphics(
                                            const ofFloatColor& lineColor,
                                            const ofFloatColor& fillColor,
                                            float thickness
                                            ) {
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_over() {
        _drawTrackGraphics(_overColor, _normalColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_out() {
        if(isMouseDown()) return;
        
        _drawTrackGraphics(_lineColor, _normalColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_press() {
        _tempValue = _valueScale;
        _startPos->x = mouseX();
        _startPos->y = mouseY();
        
        //        _valueText->textColor(_labelActiveColor);
        
        _drawTrackGraphics(_overColor, _activeColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_release() {
        if(isMouseOver()) {
            _over();
            return;
        }
        
        _drawTrackGraphics(_lineColor, _normalColor, 1);
    }
    
    //==============================================================
    // Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flHistgramViewer::_mouseEventHandler(flEvent& event) {
        //cout << "[flHistgramViewer]_mouseEventHandler(" << event.type() << ")" << endl;
        //cout << "[flHistgramViewer]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //cout << "[flHistgramViewer]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //cout << "[flHistgramViewer]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _out();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
            addEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
            if(stage()) stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            removeEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
            if(stage()) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
            //            if(event.target() == stage()) _release();
            _release();
        }
    }
    
}
