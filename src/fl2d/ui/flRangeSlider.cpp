#include "flRangeSlider.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flRangeSlider::flRangeSlider(float trackWidth, float min, float max, float minValue, float maxValue) {
        //cout << "[flRangeSlider]flRangeSlider()" << endl;
        
        //DEBUGG用
        _trackAlpha = 1.0;
        _barAlpha = 1.0;
        
        //------------------------------------------
        _target = this;
        name("flRangeSlider");
        
        _roundEnabled = false;
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        
        _min = min;
        _max = max;
        _minValue = minValue;
        _maxValue = maxValue;
        if(_roundEnabled) {
            _minValue = flmath::roundd(_minValue);
            _maxValue = flmath::roundd(_maxValue);
        }    
        _range = _maxValue - _minValue;
        //------------------------------------------
        _trackWidth = trackWidth;
        _trackHeight = 18;
        _thumbWidth = 10;
        
        _percent = (_max - _min) / _trackWidth;    
        //------------------------------------------
        
        flGraphics* g;
        
        //------------------------------------------
        track = new flSprite();
        track->name("track");
        _drawTrackGraphics(_lineColor, _normalColor);
        track->x(0);
        track->y(0);
        track->useHandCursor(true);
        //track->mouseEnabled(false);
        track->addEventListener(flMouseEvent::ROLL_OVER, this, &flRangeSlider::_mouseEventHandler);
        track->addEventListener(flMouseEvent::ROLL_OUT, this, &flRangeSlider::_mouseEventHandler);
        track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        addChild(track);
        
        //------------------------------------------
        //バー
        bar = new flSprite();
        bar->name("bar");
        bar->useHandCursor(true);
        bar->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(bar);
        
        //
        nearThumb = new flSprite();
        nearThumb->name("nearThumb");
        g = nearThumb->graphics();
        g->clear();
        g->beginFill(0xff0000);
        g->drawRect(0, 0, _thumbWidth, _trackHeight - 1);
        g->endFill();
        nearThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        nearThumb->y(0);
        nearThumb->alpha(0);
        nearThumb->useHandCursor(true);
        track->addChild(nearThumb);
        
        //
        farThumb = new flSprite();
        farThumb->name("farThumb");
        g = farThumb->graphics();
        g->clear();
        g->beginFill(0x00ff00);
        g->drawRect(0, 0, _thumbWidth, _trackHeight - 1);
        g->endFill();
        farThumb->x((_maxValue - _min) / _percent);
        farThumb->y(0);
        farThumb->alpha(0);
        farThumb->useHandCursor(true);
        track->addChild(farThumb);
        
        //バーのグラフィックス
        _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
        _drawBarGraphics(_lineColor, _activeColor, 1);
        
        //------------------------------------------
        _minValueText = new flTextField();
        _minValueText->x(0);
        _minValueText->width(_trackWidth);
        _minValueText->autoSize(flTextFieldAutoSize::LEFT);
        _minValueText->textColor(_labelNormalColor);
        _minValueText->text(ofToString(_minValue));
        _minValueText->mouseEnabled(false);
        _minValueText->visible(false);
        _minValueText->y(_trackHeight * 0.5 - _minValueText->textHeight() * 0.5);
        addChild(_minValueText);
        
        _maxValueText = new flTextField();
        _maxValueText->x(0);
        _maxValueText->width(_trackWidth);
        _maxValueText->autoSize(flTextFieldAutoSize::RIGHT);
        _maxValueText->textColor(_labelNormalColor);
        _maxValueText->text(ofToString(_maxValue));
        _maxValueText->mouseEnabled(false);
        _maxValueText->visible(false);
        _maxValueText->y(_trackHeight * 0.5 - _maxValueText->textHeight() * 0.5);
        addChild(_maxValueText);
        //------------------------------------------
        
        _draggablePoint = new ofPoint(0, 0);
    }
    
    //--------------------------------------------------------------
    //
    flRangeSlider::~flRangeSlider() {
        //cout << "[flRangeSlider]~flRangeSlider()" << endl;
        
        //DEBUGG用
        _trackAlpha = 0.0;
        _barAlpha = 0.0;
        
        _roundEnabled = false;
        
        _min = 0.0;
        _max = 0.0;
        _minValue = 0.0;
        _maxValue = 0.0;
        _range = 0.0;
        
        _trackWidth = 0.0;
        _trackHeight = 0.0;
        _thumbWidth = 0.0;
        
        _percent = 0.0;
        
        track->removeEventListener(flMouseEvent::ROLL_OVER, this, &flRangeSlider::_mouseEventHandler);
        track->removeEventListener(flMouseEvent::ROLL_OUT, this, &flRangeSlider::_mouseEventHandler);
        track->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete track;
        track = NULL;
        
        bar->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete bar;
        bar = NULL;
        
        delete nearThumb;
        nearThumb = NULL;
        
        delete farThumb;
        farThumb = NULL;
        
        _barWidth = 0.0;
        
        delete _minValueText;
        _minValueText = NULL;
        
        delete _maxValueText;
        _maxValueText = NULL;
        
        delete _draggablePoint;
        _draggablePoint = NULL;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::_setup() {
        //cout << "[flRangeSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::_update() {
        if(track->isMouseDown() || bar->isMouseDown()) {
            //------------------------------------------
            //サムの位置の更新
            float temp1, temp2;
            temp1 = mouseX() - _draggablePoint->x;
            if(temp1 < 0) {
                temp1 = 0;
            } else if(temp1 > _trackWidth - _barWidth) {
                temp1 = _trackWidth - _barWidth;
            }
            temp2 = temp1 + _barWidth;
            nearThumb->x(temp1 - _thumbWidth);
            farThumb->x(temp2);
            //------------------------------------------
            //------------------------------------------
            //値の更新
            _minValue = _min + ((nearThumb->x() + _thumbWidth) * _percent);
            _maxValue = _min + (farThumb->x() * _percent);
            if(_roundEnabled) {
                _minValue = flmath::roundd(_minValue);
                _maxValue = flmath::roundd(_maxValue);
            }
            _range = _maxValue - _minValue;
            _minValueText->text(ofToString(_minValue));
            _maxValueText->text(ofToString(_maxValue));
            //------------------------------------------
            
            //------------------------------------------
            //表示の更新
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            //イベント
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
            //------------------------------------------
        }
        
        if(nearThumb->isMouseDown()) {
            //------------------------------------------
            //サムの位置の更新
            float temp;
            temp = mouseX() - _draggablePoint->x;
            if(temp < 0) {
                temp = 0;
            } else if(temp > farThumb->x() - 1) {
                temp = farThumb->x() - 1;
            }
            nearThumb->x(temp - _thumbWidth);
            //------------------------------------------
            //------------------------------------------
            //値の更新
            _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
            _minValue = _min + ((nearThumb->x() + _thumbWidth) * _percent);
            _maxValue = _min + (farThumb->x() * _percent);
            if(_roundEnabled) {
                _minValue = flmath::roundd(_minValue);
                _maxValue = flmath::roundd(_maxValue);
            }
            _range = _maxValue - _minValue;
            _minValueText->text(ofToString(_minValue));
            _maxValueText->text(ofToString(_maxValue));
            //------------------------------------------
            
            //------------------------------------------
            //表示の更新
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            //イベント
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
            //------------------------------------------
        }
        
        if(farThumb->isMouseDown()) {
            //------------------------------------------
            //サムの位置の更新
            float temp;
            temp = mouseX() - _draggablePoint->x;
            if(temp < nearThumb->x() + _thumbWidth + 1) {
                temp = nearThumb->x() + _thumbWidth + 1;
            } else if(temp > _trackWidth) {
                temp = _trackWidth;
            }
            farThumb->x(temp);
            //------------------------------------------
            //------------------------------------------
            //値の更新
            _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
            _minValue = _min + ((nearThumb->x() + _thumbWidth) * _percent);
            _maxValue = _min + (farThumb->x() * _percent);
            if(_roundEnabled) {
                _minValue = flmath::roundd(_minValue);
                _maxValue = flmath::roundd(_maxValue);
            }
            _range = _maxValue - _minValue;
            _minValueText->text(ofToString(_minValue));
            _maxValueText->text(ofToString(_maxValue));
            //------------------------------------------
            
            //------------------------------------------
            //表示の更新
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            //イベント
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
            //------------------------------------------
        }
        
        //        cout << "[flRangeSlider]bar->width = " << bar->width() << endl;
    }
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::textColor(int color) {
        _minValueText->textColor(color);
        _maxValueText->textColor(color);
    }
    
    //--------------------------------------------------------------
    //
    float flRangeSlider::min() { return _min; }
    void flRangeSlider::min(float value, bool dispatch) {
        _min = value;
        if(_roundEnabled) _min = flmath::roundd(_min);
        if(_max < _min) _max = _min;
        if(_maxValue < _min) _maxValue = _min;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        //サムの位置の更新
        nearThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        farThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    float flRangeSlider::max() { return _max; }
    void flRangeSlider::max(float value, bool dispatch) {
        _max = value;
        if(_roundEnabled) _max = flmath::roundd(_max);
        if(_min > _max) _min = _max;
        if(_minValue > _max) _minValue = _max;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        //サムの位置の更新
        nearThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        farThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flRangeSlider::minValue() { return _minValue; }
    void flRangeSlider::minValue(float value, bool dispatch) {
        _minValue = value;
        if(_minValue < _min) _min = _minValue;
        if(_roundEnabled) _minValue = flmath::roundd(_minValue);
        if(_minValue > _max) _max = _minValue;
        if(_minValue > _maxValue) _maxValue = _minValue;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        //サムの位置の更新
        nearThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        farThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flRangeSlider::maxValue() { return _maxValue; }
    void flRangeSlider::maxValue(float value, bool dispatch) {
        _maxValue = value;
        if(_maxValue > _max) _max = _maxValue;
        if(_roundEnabled) _maxValue = flmath::roundd(_maxValue);
        if(_maxValue < _min) _min = _maxValue;
        if(_maxValue < _minValue) _minValue = _maxValue;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        //サムの位置の更新
        nearThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        farThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = farThumb->x() - (nearThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flRangeSlider::range() { return _range; }
    
    //--------------------------------------------------------------
    //
    int flRangeSlider::barColor() { return _activeColor.getHex(); }
    void flRangeSlider::barColor(int value) {
        _activeColor.setHex(value);
        
        if(farThumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void flRangeSlider::barColor(int red, int green, int blue, int alpha) {
        _activeColor.r = red;
        _activeColor.g = green;
        _activeColor.b = blue;
        _activeColor.a = alpha;
        
        if(farThumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void flRangeSlider::barColor(const ofColor& color) {
        _activeColor.r = color.r / 255.0;
        _activeColor.g = color.g / 255.0;
        _activeColor.b = color.b / 255.0;
        _activeColor.a = color.a / 255.0;
        
        if(farThumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void flRangeSlider::barColor(const ofFloatColor& color) {
        _activeColor.r = color.r;
        _activeColor.g = color.g;
        _activeColor.b = color.b;
        _activeColor.a = color.a;
        
        if(farThumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    
    //--------------------------------------------------------------
    //
    bool flRangeSlider::roundEnabled() { return _roundEnabled; }
    void flRangeSlider::roundEnabled(bool value) { _roundEnabled = value; }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        flGraphics* g;
        g = track->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        //            g->beginFill(0xff0000, _barAlpha);
        g->beginFill(fillColor.getHex(), _trackAlpha);
        g->drawRect(0, 0, _trackWidth, _trackHeight);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void flRangeSlider::_drawBarGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        flGraphics* g;
        g = bar->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        //            g->beginFill(0xff0000, _barAlpha);
        g->beginFill(fillColor.getHex(), _barAlpha);
        g->drawRect(nearThumb->x() + _thumbWidth, 0, _barWidth, _trackHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::_over() {
        if(track->isMouseDown()) return;
        if(bar->isMouseDown()) return;
        if(nearThumb->isMouseDown()) return;
        if(farThumb->isMouseDown()) return;
        
        //------------------------------------------
        _drawTrackGraphics(_overColor, _normalColor, 1);
        _drawBarGraphics(_overColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        _minValueText->visible(true);
        _maxValueText->visible(true);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flRangeSlider::_out() {
        if(track->isMouseDown()) return;
        if(bar->isMouseDown()) return;
        if(nearThumb->isMouseDown()) return;
        if(farThumb->isMouseDown()) return;
        
        //------------------------------------------
        _drawTrackGraphics(_lineColor, _normalColor, 1);
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        _minValueText->visible(false);
        _maxValueText->visible(false);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flRangeSlider::_press() {
        //------------------------------------------
        _minValueText->textColor(_labelNormalColor);
        _maxValueText->textColor(_labelNormalColor);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flRangeSlider::_release() {
        if(nearThumb->isMouseOver() || track->isMouseOver()) {
            //------------------------------------------
            _drawTrackGraphics(_overColor, _normalColor, 1);
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            _minValueText->textColor(_labelNormalColor);
            _maxValueText->textColor(_labelNormalColor);
            //------------------------------------------
        } else {
            //------------------------------------------
            _drawTrackGraphics(_lineColor, _normalColor, 1);
            _drawBarGraphics(_lineColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            _minValueText->visible(false);
            _maxValueText->visible(false);
            //------------------------------------------
        }
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flRangeSlider::_mouseEventHandler(flEvent& event) {
        //    cout << "[flRangeSlider]_mouseEventHandler(" << event.type() << ")" << endl;
        //    cout << "[flRangeSlider]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //    cout << "[flRangeSlider]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //    cout << "[flRangeSlider]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        //ROLL OVER
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == track) _over();
        }
        
        //ROLL OUT
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == track) _out();
        }
        
        //MOUSE DOWN
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == track) {
                _draggablePoint->x = mouseX() - (nearThumb->x() + _thumbWidth);
                _press();
            }
            if(event.target() == bar) {
                _draggablePoint->x = mouseX() - (nearThumb->x() + _thumbWidth);
                _press();
            }
            if(event.target() == nearThumb) {
                _draggablePoint->x = mouseX() - (nearThumb->x() + _thumbWidth);
                _press();
            }
            if(event.target() == farThumb) {
                _draggablePoint->x = mouseX() - farThumb->x();
                _press();
            }
            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
        }
        
        //MOUSE UP
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _draggablePoint->x = 0;
                _draggablePoint->y = 0;
                
                _release();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            }
        }
    }
    
}
