#include "flHistgramViewer.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flHistgramViewer::flHistgramViewer(float width, float height) {
        //ofLog() << "[flHistgramViewer]flHistgramViewer()";
        
        _target = this;
        name("flHistgramViewer");
        
        useHandCursor(true);
        
        _uiWidth = width;
        _uiHeight = height;
        
        //------------------------------------------
        _value = 0.0;
        _tempValue = 1.0;
        _min = 0.001;
        _weight = 0.005;
        //------------------------------------------
        
        flGraphics* g;
        
        //------------------------------------------
        addEventListener(flMouseEvent::ROLL_OVER, this, &flHistgramViewer::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flHistgramViewer::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flHistgramViewer::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        _valueText = new flTextField();
        _valueText->name("flHistgramViewer.velueText");
        _valueText->x(2);
        _valueText->y(0);
        _valueText->width(_uiWidth - 4);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text(ofToString(_value, 2));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        _valueHistory.resize((int)_uiWidth);
        //        _avelageHistroy.resize((int)_uiWidth);
        for(int i = 0; i < _valueHistory.size(); i++) _line.addVertex(0, 0);
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flHistgramViewer::~flHistgramViewer() {
        //ofLog() << "[flHistgramViewer]~flHistgramViewer()";
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flHistgramViewer::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flHistgramViewer::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flHistgramViewer::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
        
        _uiWidth = 0.0;
        _uiHeight = 0.0;
        
        removeChild(_valueText);
        delete _valueText;
        _valueText = NULL;
        
        _value = 0.0;
        _tempValue = 0.0;
        _min = 0.0;
        _weight = 0.0;
        
        _valueHistory.clear();
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setup() {
        
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_update() {
        flUIBase::_update();

        if(isMouseDown()) {
            //            _valueScale = _tempValue + ((mouseY() - _startPos.y) * _weight);
            //            _valueScale = max(_valueScale, _min);
            //            //            if(!isnan(_max)) if(_max <= _value) _value = _max;
            //            //            if(_valueScale <= _min) _valueScale = _min;
            //            ofLogNotice() << "_valueScale = " << _valueScale;
            
            _onPress();
            
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
    void flHistgramViewer::_draw() {
        ofPushStyle();
        
        float iy = _uiHeight * 0.5f;
        
        ofColor lineColor;
        
        //------------------------------------------
        if(_enabled) {
            if(isMouseDown()) {
                lineColor = flDefinition::UI_LINE_ACTIVE_COLOR;
            }
            else if(isMouseOver()) {
                lineColor = flDefinition::UI_LINE_OVER_COLOR;
            } else {
                lineColor = flDefinition::UI_LINE_NORMAL_COLOR;
            }
        } else {
            lineColor = flDefinition::UI_LINE_DISABLE_NORMAL_COLOR;
        }
        //------------------------------------------

        //------------------------------------------
        ofSetColor(lineColor, lineColor.a * _compoundAlpha);
        ofSetLineWidth(1);
        ofDrawLine(0, iy, _uiWidth, iy);
        //------------------------------------------

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
        
        ofSetColor(lineColor, lineColor.a * _compoundAlpha);
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
//        float textHeight = flFont::getMaxStringHeight();
//        ofPushMatrix();
//        ofTranslate(2, textHeight);
//        ofPushStyle();
//        //        ofSetColor(_textColor, 255 * _compoundAlpha);
//        flFont::drawString(ofToString(_value), 5, -1);
//        ofPopStyle();
//        ofPopMatrix();
        
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
    void flHistgramViewer::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if (_enabled) {
            _setNormalColor();
        } else {
            _setDisableNormalColor();
        }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flHistgramViewer::_onOver() {
        if(isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_onOut() {
        if(isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_onPress() {
        _valueScale = _tempValue + ((mouseY() - _startPos.y) * _weight);
        _valueScale = max(_valueScale, _min);
        //            if(!isnan(_max)) if(_max <= _value) _value = _max;
        //            if(_valueScale <= _min) _valueScale = _min;
        //        ofLogNotice() << "_valueScale = " << _valueScale;
        
        _setActiveColor();
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_onRelease() {
        if(isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flHistgramViewer::_drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flHistgramViewer::_mouseEventHandler(flEvent& event) {
		if (!_enabled) return;
//        ofLog() << "[flHistgramViewer]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flHistgramViewer]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flHistgramViewer]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flHistgramViewer]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _onOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _onOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
                _tempValue = _valueScale;
                _startPos.x = mouseX();
                _startPos.y = mouseY();
                _onPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _onRelease();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flHistgramViewer::_mouseEventHandler);
            }
        }
    }
    
}
