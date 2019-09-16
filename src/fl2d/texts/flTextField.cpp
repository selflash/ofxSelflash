#include "flTextField.h"

namespace fl2d {
    
    string flTextField::TEXT_FIELD_TYPE_DYNAMIC = "dynamic";
    string flTextField::TEXT_FIELD_TYPE_INPUT = "input";
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField::flTextField() {
        _typeID = FL_TYPE_TEXT_FIELD;
        
        name("flTextField");
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(flDefinition::UI_DEACTIVE_COLOR);
        //        _normalColor.setHex(0x333333);
        //        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        //        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        //        _textColor.setHex(0xffffff);
        
        _text = "";
        
        _type = TEXT_FIELD_TYPE_DYNAMIC;
        
        //        _targetWidth = 0 / 0.f;
        //        _targetHeight = 0 / 0.f;
        _targetWidth = numeric_limits<float>::quiet_NaN();
        _targetHeight = numeric_limits<float>::quiet_NaN();
        
        //        cout << isnan(_targetWidth) << endl;
        
        _textWidth = 0;
        _textHeight = 0;
        
        _autoSize = flTextFieldAutoSize::LEFT;
        _tx = 0;
        _numLine = 0;
        
        _addedListeners = false;
        
        mouseEnabled(false);
        
        _graphics = new flGraphics();
        
        _isActive = false;
        _enabled = true;
        
        _activeLineWidth = 3;
        
        //        _enabledAntiAliasing = false;
    }
    
    //--------------------------------------------------------------
    //
    flTextField::~flTextField() {
        _text = "";
        
        _type = TEXT_FIELD_TYPE_DYNAMIC;
        
        _textWidth = 0;
        _textHeight = 0;
        
        _autoSize = "";
        _tx = 0;
        _numLine = 0;
        
        _addedListeners = false;
        
        delete _graphics;
        _graphics = NULL;
        
        _isActive = false;
        _enabled = false;
        
        _activeLineWidth = 0;
        
        //        _enabledAntiAliasing = false;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    // TODO
    void flTextField::update() {
        
        //--------------------------------------
        if(isnan(_targetWidth)) {
            _rect->width(_textWidth);
        } else {
            _rect->width(_targetWidth);
        }
        
        if(isnan(_targetHeight)) {
            _rect->height(_textHeight);
        } else {
            _rect->height(_targetHeight);
        }
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        
        //        if(!isnan(_targetWidth)) scaleX(_targetWidth / _realWidth);
        //        if(!isnan(_targetHeight)) scaleY(_targetHeight / _realHeight);
        //        if(_width != -9999.0) scaleX(_width / _realWidth);
        //        if(_height != -9999.0) scaleY(_height / _realHeight);
        //--------------------------------------
        
        _update();
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::draw(bool applyMatrix) {
        if(!visible() && applyMatrix) return;
        
        // save off current state of blend enabled
        GLboolean blendEnabled;
        glGetBooleanv(GL_BLEND, &blendEnabled);
        // save off current state of src / dst blend functions
        GLint blendSrc; GLint blendDst;
        glGetIntegerv(GL_BLEND_SRC_ALPHA, &blendSrc);
        glGetIntegerv(GL_BLEND_DST_ALPHA, &blendDst);
        ofEnableAlphaBlending();
        
        GLboolean preLighting = glIsEnabled(GL_LIGHTING);
        GLboolean preDepthTest = glIsEnabled(GL_DEPTH_TEST);
        GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
        GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
        ofDisableLighting();
        glDisable(GL_DEPTH_TEST);
        if(_enabledSmoothing) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        if(_enabledAntiAliasing) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        
        //------------------------------------------
        //-- matrix transform.
        //        bool bIdentity = true;
        //        bIdentity = matrix().isIdentity();
        //        bIdentity = false;
        
        if(applyMatrix){
            //            glPushMatrix();
            ofPushMatrix();
            //            glMultMatrixf(matrix().getPtr());
            ofMultMatrix(matrix().getPtr());
        }
        
        ofPushStyle();
        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _graphics->__draw();
        _draw();
        ofPopStyle();
        
        if(applyMatrix){
            //            glPopMatrix();
            ofPopMatrix();
        }
        //------------------------------------------
        
        if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
        if(preLighting == GL_TRUE) { ofEnableLighting(); } else { ofDisableLighting(); }
        
        // restore saved state of blend enabled and blend functions
        if (blendEnabled) { glEnable(GL_BLEND); } else { glDisable(GL_BLEND); }
        glBlendFunc(blendSrc, blendDst);
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::_draw() {
        
        //---------------------------------
        ofPushMatrix();
        
        if(_autoSize == flTextFieldAutoSize::NONE) {
            _tx = 2;
        }
        else if(_autoSize == flTextFieldAutoSize::LEFT) {
            _tx = 2;
        }
        else if(_autoSize == flTextFieldAutoSize::RIGHT) {
            _tx = _realWidth - _textWidth;
            _tx = floor(_tx);
        }
        else if(_autoSize == flTextFieldAutoSize::CENTER) {
            _tx = (_realWidth * 0.5) - (_textWidth * 0.5);
            _tx = floor(_tx);
        }
        
        //        ofTranslate(_tx, -_textHeight);
        ofTranslate(_tx, flFont::getMaxStringHeight());
        
        //        _font.drawStringAsShapes(_text, -bounds.width / 2, bounds.height / 2);
        //        _font.drawStringAsShapes(_text, 0, 0);
        
        ofPushStyle();
        ofSetColor(_textColor, 255 * _compoundAlpha);
        //        if(_enabledAntiAliasing) { ofEnableAntiAliasing(); }
        flFont::drawString(_text, 1, -2);
        //        if(_enabledAntiAliasing) { ofDisableAntiAliasing(); }
        ofPopStyle();
        
        ofPopMatrix();
        //---------------------------------
        
        //---------------------------------
        //DEBUG
        if(false) {
            ofPushStyle();
            ofSetHexColor(0xff0000);
            float n = 5 / scaleX();
            ofDrawLine(-n, 0, n, 0);
            ofDrawLine(0, -n, 0, n);
            
            ofNoFill();
            //            ofRect(0, 0, _textWidth, _textHeight);
            ofDrawRectangle(0, 0, width(), height());
            //            ofRect(0, 0, _targetWidth, _targetHeight);
            //            ofRect(_rect->left(), _rect->top(), _rect->right(), _rect->bottom());
            
            //ofSetHexColor(0x000000);
            //string t = ofToString(name()) + " x:" + ofToString(x()) + " y:" + ofToString(y());
            //ofDrawBitmapString(t, -50, -10);
            //ofSetHexColor(0xffffff);
            ofPopStyle();
        }
        //---------------------------------
        
        //        ofSetColor(255, 255, 255, 255);
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //    //--------------------------------------------------------------
    //    //
    //    const float flTextField::width() {
    //        _rect->__expandToRect(*_graphics->__rect);
    //        return _rect->width();
    //    }
    //    void flTextField::width(const float& value) { _rect->__expandTo(_rect->x() + value, 0); }
    //    //--------------------------------------------------------------
    //    //
    //    const float flTextField::height() {
    //        _rect->__expandToRect(*_graphics->__rect);
    //        return _rect->height();
    //    }
    //    void flTextField::height(const float& value) { _rect->__expandTo(0, _rect->y() + value); }
    
    //--------------------------------------------------------------
    //
    float flTextField::width() { return _realWidth * scaleX(); }
    void flTextField::width(float value) {
        _targetWidth = value;
        
        //--------------------------------------
        if(isnan(_targetWidth)) {
            _rect->width(_textWidth);
        } else {
            _rect->width(_targetWidth);
        }
        
        if(isnan(_targetHeight)) {
            _rect->height(_textHeight);
        } else {
            _rect->height(_targetHeight);
        }
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //--------------------------------------
        
        //---------------------------------
        if(_type == TEXT_FIELD_TYPE_INPUT) {
            if(_enabled) {
                if(_isActive) {
                    _drawGraphics(0xcc0000, 0xffffff, _activeLineWidth);
                } else {
                    _drawGraphics(0x000000, 0xffffff, 1);
                }
            } else {
                _drawGraphics(_deactiveColor.getHex(), 0xcccccc, 1);                
            }
        }
        //---------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flTextField::height() { return _realHeight * scaleY(); }
    void flTextField::height(float value) {
        _targetHeight = value;
        
        //--------------------------------------
        if(isnan(_targetWidth)) {
            _rect->width(_textWidth);
        } else {
            _rect->width(_targetWidth);
        }
        
        if(isnan(_targetHeight)) {
            _rect->height(_textHeight);
        } else {
            _rect->height(_targetHeight);
        }
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //--------------------------------------
        
        //---------------------------------
        if(_type == TEXT_FIELD_TYPE_INPUT) {
            if(_enabled) {
                if(_isActive) {
                    _drawGraphics(0xcc0000, 0xffffff, _activeLineWidth);
                } else {
                    _drawGraphics(0x000000, 0xffffff, 1);
                }
            } else {
                _drawGraphics(_deactiveColor.getHex(), 0xcccccc, 1);
            }
        }
        //---------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flTextField::textWidth() { return _textWidth * scaleX(); }
    //--------------------------------------------------------------
    //
    float flTextField::textHeight() { return _textHeight * scaleY(); }
    
    //--------------------------------------------------------------
    //
    float flTextField::alpha() { return _alpha; }
    void flTextField::alpha(float value) {
        float temp = value;
        if(temp >= 1.0) temp = 1.0;
        if(temp <= 0.0) temp = 0.0;
        
        _alpha = temp;
        //        _textColor.a = _alpha;
        //        _graphics->__alpha = _alpha;
    }
    
    //--------------------------------------------------------------
    //
    int flTextField::textColor() { return _textColor.getHex(); }
    void flTextField::textColor(int value) {
        _textColor.setHex(value);
        //        _textColor.a = _alpha;
    }
    void flTextField::textColor(ofFloatColor value) {
        _textColor.setHex(value.getHex());
        //        _textColor.a = _alpha;
    }
    
    //--------------------------------------------------------------
    //
    const string flTextField::text() {
        //        string temp = "";
        //        int l = _texts.size();
        //        for(int i = 0; i < l; i++) {
        //            temp += _texts[i];
        //        }
        //        return temp;
        
        return _text;
    }
    void flTextField::text(const string& value, int color) {
        _text = value;
        
        _numLine = flstringutil::getLength(_text, "\n") + 1;
        
        ofRectangle bounds = flFont::getStringBoundingBox(_text, 0, 0);
        _textWidth = bounds.width + 6;
        _textHeight = _numLine * flFont::getMaxStringHeight() + 3;
        
        if(color != -1) textColor(color);
        
        
        //--------------------------------------
        if(isnan(_targetWidth)) {
            _rect->width(_textWidth);
        } else {
            _rect->width(_targetWidth);
        }
        
        if(isnan(_targetHeight)) {
            _rect->height(_textHeight);
        } else {
            _rect->height(_targetHeight);
        }
        
        _realWidth = _rect->width();
        _realHeight = _rect->height();
        //--------------------------------------
        
        //---------------------------------
        if(_type == TEXT_FIELD_TYPE_INPUT) {
            if(_enabled) {
                if(_isActive) {
                    _drawGraphics(_activeColor.getHex(), 0xffffff, _activeLineWidth);
                } else {
                    _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
                }
            }
        }
        //---------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::appendText(const string& value) { _text += value; }
    
    //--------------------------------------------------------------
    //
    const string& flTextField::type() { return _type; }
    void flTextField::type(const string& value) {
        _type = value;
        
        if(_type == TEXT_FIELD_TYPE_DYNAMIC) {
            _removeListeners();
        } else
            if(_type == TEXT_FIELD_TYPE_INPUT) {
                _addListeners();
            }
    }
    
    //--------------------------------------------------------------
    //
    string flTextField::autoSize() { return _autoSize; }
    void flTextField::autoSize(string value) { _autoSize = value; }
    
    //--------------------------------------------------------------
    //
    bool flTextField::active() { return _isActive; }
    void flTextField::active(bool value) {
        if(_isActive == value) return;
        _isActive = value;
        
        if(_enabled) {
            if(_isActive) {
                _drawGraphics(_activeColor.getHex(), 0xffffff, _activeLineWidth);
                
                ofAddListener(ofEvents().keyPressed, this, &flTextField::_keyPressedEventHandler);
                ofAddListener(ofEvents().keyReleased, this, &flTextField::_keyReleasedEventHandler);
                
                addEventListener(flFocusEvent::FOCUS_OUT, this, &flTextField::_eventHandler);
            } else {
                _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
                
                ofRemoveListener(ofEvents().keyPressed, this, &flTextField::_keyPressedEventHandler);
                ofRemoveListener(ofEvents().keyReleased, this, &flTextField::_keyReleasedEventHandler);
                
                removeEventListener(flFocusEvent::FOCUS_OUT, this, &flTextField::_eventHandler);
            }
        }
    }
    //--------------------------------------------------------------
    //
    bool flTextField::enabled() { return _enabled; }
    void flTextField::enabled(bool value) {
        if(_enabled == value) return;
        _enabled = value;
        
        mouseEnabled(_enabled);
        
        if(_enabled) {
            if(_isActive) {
                _drawGraphics(_activeColor.getHex(), 0xffffff, _activeLineWidth);
                
                ofAddListener(ofEvents().keyPressed, this, &flTextField::_keyPressedEventHandler);
                ofAddListener(ofEvents().keyReleased, this, &flTextField::_keyReleasedEventHandler);
                
                addEventListener(flFocusEvent::FOCUS_OUT, this, &flTextField::_eventHandler);
            } else {
                _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
                
                ofRemoveListener(ofEvents().keyPressed, this, &flTextField::_keyPressedEventHandler);
                ofRemoveListener(ofEvents().keyReleased, this, &flTextField::_keyReleasedEventHandler);
                
                removeEventListener(flFocusEvent::FOCUS_OUT, this, &flTextField::_eventHandler);
            }
        } else {
            _drawGraphics(_deactiveColor.getHex(), 0xcccccc, 1);
            
            if(_isActive) {
                ofRemoveListener(ofEvents().keyPressed, this, &flTextField::_keyPressedEventHandler);
                ofRemoveListener(ofEvents().keyReleased, this, &flTextField::_keyReleasedEventHandler);
                
                removeEventListener(flFocusEvent::FOCUS_OUT, this, &flTextField::_eventHandler);
            }
        }
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flTextField::_addListeners() {
        if(_addedListeners) return;
        _addedListeners = true;
        
        mouseEnabled(true);
        
        _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
        
        //        addEventListener(MouseEvent::MOUSE_UP, this, &flTextField::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flTextField::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::_removeListeners() {
        if(!_addedListeners) return;
        _addedListeners = false;
        
        mouseEnabled(false);
        
        _graphics->clear();
        
        //        removeEventListener(MouseEvent::MOUSE_UP, this, &flTextField::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flTextField::_mouseEventHandler);
    }
    
    
    //--------------------------------------------------------------
    //
    void flTextField::__compoundAlpha(float value){
        _compoundAlpha = value;
        _graphics->__compoundAlpha(_compoundAlpha);
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::_drawGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        flGraphics* g = _graphics;
        //_graphics->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        g->drawRect(0, 0, width(), height());
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void flTextField::_drawGraphics(int lineColor, int fillColor, float thickness) {
        flGraphics* g = _graphics;
        g->clear();
        g->lineStyle(thickness, lineColor);
        g->beginFill(fillColor);
        g->drawRect(0, 0, width(), height());
        g->endFill();
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flTextField::_mouseEventHandler(flEvent& event) {
        if(debug()) cout << "[flTextField]_mouseEventHandler(" + event.type() + ")" << endl;
        
        //        if(event.type() == MouseEvent::MOUSE_UP) {
        //            active(!active());
        //        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            active(!active());
        }
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::_keyPressedEventHandler(ofKeyEventArgs& event) {
        //        char str = (char)event.key;
        
        //エンターキーなら区切り文字を
        if(event.key == OF_KEY_RETURN) {
            event.key = '\r\n';
            _text.end();
        }
        
        if(event.key == OF_KEY_LEFT) {
            //TODO
            return;
        }
        if(event.key == OF_KEY_RIGHT) {
            //TODO
            return;
        }
        if(event.key == OF_KEY_UP) {
            //TODO
            return;
        }
        if(event.key == OF_KEY_DOWN) {
            //TODO
            return;
        }
        
        //デリートキーなら一文字削除
        if(event.key == OF_KEY_DEL || event.key == OF_KEY_BACKSPACE) {
            if(text().size() != 0) {
                text(_text.substr(0, _text.size() - 1));
            } else {
                text("");
            }
        } else {
            text(text() + (char)event.key);
        }
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::_keyReleasedEventHandler(ofKeyEventArgs& event) {
        
    }
    
    //--------------------------------------------------------------
    //
    void flTextField::_eventHandler(flEvent& event) {
        //cout << "[flTextField]_eventHandler(" << event.type() << ")" << endl;
        //cout << "[flTextField]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //cout << "[flTextField]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //cout << "[flTextField]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == flFocusEvent::FOCUS_OUT) {
            flEvent* event = new flEvent(flEvent::CHANGE);
            dispatchEvent(event);
            
            active(false);
        }
    }
    
}
