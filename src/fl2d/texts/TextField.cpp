#include "TextField.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    TextField::TextField() {
        _typeID = TYPE_TEXT_FIELD;
        
        name("TextField");
        
        _normalColor = new ofFloatColor();
        _normalColor->setHex(0x333333);
        
        _overColor = new ofFloatColor();
        _overColor->setHex(FlashConfig::UI_OVER_COLOR);
        
        _activeColor = new ofFloatColor();
        _activeColor->setHex(FlashConfig::UI_ACTIVE_COLOR);
        
        _textColor = new ofFloatColor();
        _textColor->setHex(0xffffff);
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
    }

    //--------------------------------------------------------------
    //
    TextField::~TextField() {
        delete _normalColor;
        _normalColor = NULL;
        
        delete _overColor;
        _overColor = NULL;
        
        delete _activeColor;
        _activeColor = NULL;
        
        delete _textColor;
        _textColor = NULL;
        
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
    void TextField::draw() {
        
        if(!visible()) return;
        
        //-- matrix transform.
        bool bIdentity = true;
        bIdentity = matrix().isIdentity();
        bIdentity = false;
        
        if(!bIdentity){
            glPushMatrix();
            glMultMatrixf(matrix().getPtr());
        }
        
        _graphics->__draw();
        _draw();
        
        if(!bIdentity){
            glPopMatrix();
        }
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
        
        ofSetColor(*_textColor);
        Font::drawString(_text, 1, -3);
        ofPopStyle();
        
        ofPopMatrix();
        //---------------------------------
        
        //---------------------------------
        //DEBUG
        if(false) {
            ofPushStyle();
            ofSetHexColor(0xff0000);
            float n = 5 / scaleX();
            ofLine(-n, 0, n, 0);
            ofLine(0, -n, 0, n);
            
            ofNoFill();
//            ofRect(0, 0, _textWidth, _textHeight);
            ofRect(0, 0, width(), height());
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
            if(_isActive) {
                _drawGraphics(0xcc0000, 0xffffff);
            } else {
                _drawGraphics(0x000000, 0xffffff);
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
            if(_isActive) {
                _drawGraphics(0xcc0000, 0xffffff);
            } else {
                _drawGraphics(0x000000, 0xffffff);
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
        _textColor->a = _alpha;
        _graphics->__alpha = _alpha;
    }

    //--------------------------------------------------------------
    //
    int TextField::textColor() { return _textColor->getHex(); }
    void TextField::textColor(int value) {
        _textColor->setHex(value);
        _textColor->a = _alpha;
    }

    //--------------------------------------------------------------
    //
    const string& TextField::text() { return _text; }
    void TextField::text(const string& value, int color) {
        _text = value;
        
        _numLine = StringUtil::getLength(_text, "\n") + 1;
        
		ofRectangle bounds = Font::getStringBoundingBox(_text, 0, 0);
        _textWidth = bounds.width + 6;
        _textHeight = _numLine * Font::getMaxStringHeight();
        
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
            if(_isActive) {
                _drawGraphics(_activeColor->getHex(), 0xffffff);
            } else {
                _drawGraphics(_normalColor->getHex(), 0xffffff);
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
        _isActive = value;
        
        if(_isActive) {
            _drawGraphics(_activeColor->getHex(), 0xffffff);
            
            ofAddListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
            ofAddListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
            
            addEventListener(FocusEvent::FOCUS_OUT, this, &TextField::_eventHandler);
        } else {
            _drawGraphics(_normalColor->getHex(), 0xffffff);
            
            ofRemoveListener(ofEvents().keyPressed, this, &TextField::_keyPressedEventHandler);
            ofRemoveListener(ofEvents().keyReleased, this, &TextField::_keyReleasedEventHandler);
            
            removeEventListener(FocusEvent::FOCUS_OUT, &TextField::_eventHandler);
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
        
        _drawGraphics(_normalColor->getHex(), 0xffffff);
        
        addEventListener(MouseEvent::MOUSE_UP, this, &TextField::_mouseEventHandler);
    }

    //--------------------------------------------------------------
    //
    void TextField::_removeListeners() {
        if(!_addedListeners) return;
        _addedListeners = false;
        
        mouseEnabled(false);
        
        _graphics->clear();
        
        removeEventListener(MouseEvent::MOUSE_UP, &TextField::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    void TextField::_drawGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor) {
        Graphics* g = _graphics;
        //_graphics->clear();
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        g->drawRect(0, 0, width(), height());
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void TextField::_drawGraphics(int lineColor, int fillColor) {
        Graphics* g = _graphics;
        g->clear();
        g->lineStyle(1, lineColor);
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
        cout << "[TextField]_mouseEventHandler(" + event.type() + ")" << endl;
        
        if(event.type() == MouseEvent::MOUSE_UP) {
            active(true);
        }
    }

    //--------------------------------------------------------------
    //
    void TextField::_keyPressedEventHandler(ofKeyEventArgs& event) {
        //エンターキーなら区切り文字を
        if(event.key == OF_KEY_RETURN) {
            event.key = '\n';
            _text.end();
        }
        //デリートキーなら一文字削除
        if(event.key == OF_KEY_DEL || event.key == OF_KEY_BACKSPACE) {
            if(text().size() != 0) {
                text(_text.substr(0, _text.size() - 1));
            } else {
                text("");
            }
        }else{
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
            active(false);
        }
    }
    
}