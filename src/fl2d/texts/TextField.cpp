#include "TextField.h"

namespace fl2d {
    
    string TextField::TEXT_FIELD_TYPE_DYNAMIC = "dynamic";
    string TextField::TEXT_FIELD_TYPE_INPUT = "input";
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField::TextField() {
        _typeID = FL_TYPE_TEXT_FIELD;
        
        name("TextField");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(FlashConfig::UI_DEACTIVE_COLOR);
        //        _normalColor.setHex(0x333333);
        //        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        //        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
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
        
        _autoSize = TextFieldAutoSize::LEFT;
        _tx = 0;
        _numLine = 0;
        
        _addedListeners = false;
        
        mouseEnabled(false);
        
        _graphics = new Graphics();
        
        _isActive = false;
        _enabled = true;
        
        _activeLineWidth = 3;
        
        //        _enabledAntiAliasing = false;
    }
    
    //--------------------------------------------------------------
    //
    TextField::~TextField() {
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
    void TextField::update() {
        
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
    void TextField::draw(bool applyMatrix) {
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
    void TextField::_draw() {
        
        //---------------------------------
        ofPushMatrix();
        
        if(_autoSize == TextFieldAutoSize::NONE) _tx = 2;
        if(_autoSize == TextFieldAutoSize::LEFT) _tx = 2;
        if(_autoSize == TextFieldAutoSize::RIGHT) _tx = _realWidth - _textWidth;
        if(_autoSize == TextFieldAutoSize::CENTER) _tx = (_realWidth * 0.5) - (_textWidth * 0.5);
        
        //        ofTranslate(_tx, -_textHeight);
        ofTranslate(_tx, Font::getMaxStringHeight());
        
        //        _font.drawStringAsShapes(_text, -bounds.width / 2, bounds.height / 2);
        //        _font.drawStringAsShapes(_text, 0, 0);
        
        ofPushStyle();
        ofSetColor(_textColor, 255 * _compoundAlpha);
        //        if(_enabledAntiAliasing) { ofEnableAntiAliasing(); }
        Font::drawString(_text, 1, -1);
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
    //    const float TextField::width() {
    //        _rect->__expandToRect(*_graphics->__rect);
    //        return _rect->width();
    //    }
    //    void TextField::width(const float& value) { _rect->__expandTo(_rect->x() + value, 0); }
    //    //--------------------------------------------------------------
    //    //
    //    const float TextField::height() {
    //        _rect->__expandToRect(*_graphics->__rect);
    //        return _rect->height();
    //    }
    //    void TextField::height(const float& value) { _rect->__expandTo(0, _rect->y() + value); }
    
    //--------------------------------------------------------------
    //
    float TextField::width() { return _realWidth * scaleX(); }
    void TextField::width(float value) {
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
    float TextField::height() { return _realHeight * scaleY(); }
    void TextField::height(float value) {
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
    float TextField::textWidth() { return _textWidth * scaleX(); }
    //--------------------------------------------------------------
    //
    float TextField::textHeight() { return _textHeight * scaleY(); }
    
    //--------------------------------------------------------------
    //
    float TextField::alpha() { return _alpha; }
    void TextField::alpha(float value) {
        float temp = value;
        if(temp >= 1.0) temp = 1.0;
        if(temp <= 0.0) temp = 0.0;
        
        _alpha = temp;
        //        _textColor.a = _alpha;
        //        _graphics->__alpha = _alpha;
    }
    
    //--------------------------------------------------------------
    //
    int TextField::textColor() { return _textColor.getHex(); }
    void TextField::textColor(int value) {
        _textColor.setHex(value);
        //        _textColor.a = _alpha;
    }
    void TextField::textColor(ofFloatColor value) {
        _textColor.setHex(value.getHex());
        //        _textColor.a = _alpha;
    }
    
    //--------------------------------------------------------------
    //
    const string TextField::text() {
        //        string temp = "";
        //        int l = _texts.size();
        //        for(int i = 0; i < l; i++) {
        //            temp += _texts[i];
        //        }
        //        return temp;
        
        return _text;
    }
    void TextField::text(const string& value, int color) {
        _text = value;
        
        _numLine = flstringutil::getLength(_text, "\n") + 1;
        
        ofRectangle bounds = Font::getStringBoundingBox(_text, 0, 0);
        _textWidth = bounds.width + 6;
        _textHeight = _numLine * Font::getMaxStringHeight() + 3;
        
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
    void TextField::appendText(const string& value) { _text += value; }
    
    //--------------------------------------------------------------
    //
    const string& TextField::type() { return _type; }
    void TextField::type(const string& value) {
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
    string TextField::autoSize() { return _autoSize; }
    void TextField::autoSize(string value) { _autoSize = value; }
    
    //--------------------------------------------------------------
    //
    bool TextField::active() { return _isActive; }
    void TextField::active(bool value) {
        if(_isActive == value) return;
        _isActive = value;
        
        if(_enabled) {
            if(_isActive) {
                _drawGraphics(_activeColor.getHex(), 0xffffff, _activeLineWidth);
                
                ofAddListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
                ofAddListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
                
                addEventListener(FocusEvent::FOCUS_OUT, this, &TextField::_eventHandler);
            } else {
                _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
                
                ofRemoveListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
                ofRemoveListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
                
                removeEventListener(FocusEvent::FOCUS_OUT, this, &TextField::_eventHandler);
            }
        }
    }
    //--------------------------------------------------------------
    //
    bool TextField::enabled() { return _enabled; }
    void TextField::enabled(bool value) {
        if(_enabled == value) return;
        _enabled = value;
        
        mouseEnabled(_enabled);
        
        if(_enabled) {
            if(_isActive) {
                _drawGraphics(_activeColor.getHex(), 0xffffff, _activeLineWidth);
                
                ofAddListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
                ofAddListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
                
                addEventListener(FocusEvent::FOCUS_OUT, this, &TextField::_eventHandler);
            } else {
                _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
                
                ofRemoveListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
                ofRemoveListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
                
                removeEventListener(FocusEvent::FOCUS_OUT, this, &TextField::_eventHandler);
            }
        } else {
            _drawGraphics(_deactiveColor.getHex(), 0xcccccc, 1);
            
            if(_isActive) {
                ofRemoveListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
                ofRemoveListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
                
                removeEventListener(FocusEvent::FOCUS_OUT, this, &TextField::_eventHandler);
            }
        }
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void TextField::_addListeners() {
        if(_addedListeners) return;
        _addedListeners = true;
        
        mouseEnabled(true);
        
        _drawGraphics(_normalColor.getHex(), 0xffffff, 1);
        
        //        addEventListener(MouseEvent::MOUSE_UP, this, &TextField::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &TextField::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void TextField::_removeListeners() {
        if(!_addedListeners) return;
        _addedListeners = false;
        
        mouseEnabled(false);
        
        _graphics->clear();
        
        //        removeEventListener(MouseEvent::MOUSE_UP, this, &TextField::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, this, &TextField::_mouseEventHandler);
    }
    
    
    //--------------------------------------------------------------
    //
    void TextField::__compoundAlpha(float value){
        _compoundAlpha = value;
        _graphics->__compoundAlpha(_compoundAlpha);
    }
    
    //--------------------------------------------------------------
    //
    void TextField::_drawGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        Graphics* g = _graphics;
        //_graphics->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        g->drawRect(0, 0, width(), height());
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void TextField::_drawGraphics(int lineColor, int fillColor, float thickness) {
        Graphics* g = _graphics;
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
    void TextField::_mouseEventHandler(Event& event) {
        if(debug()) cout << "[TextField]_mouseEventHandler(" + event.type() + ")" << endl;
        
        //        if(event.type() == MouseEvent::MOUSE_UP) {
        //            active(!active());
        //        }
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            active(!active());
        }
    }
    
    //--------------------------------------------------------------
    //
    void TextField::_keyPressedEventHandler(ofKeyEventArgs& event) {
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
    void TextField::_keyReleasedEventHandler(ofKeyEventArgs& event) {
        
    }
    
    //--------------------------------------------------------------
    //
    void TextField::_eventHandler(Event& event) {
        //cout << "[TextField]_eventHandler(" << event.type() << ")" << endl;
        //cout << "[TextField]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //cout << "[TextField]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //cout << "[TextField]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == FocusEvent::FOCUS_OUT) {
            Event* event = new Event(Event::CHANGE);
            dispatchEvent(event);
            
            active(false);
        }
    }
    
}
