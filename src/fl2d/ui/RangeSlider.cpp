#include "RangeSlider.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    RangeSlider::RangeSlider(float trackWidth, float min, float max, float minValue, float maxValue) {
        //cout << "[RangeSlider]RangeSlider()" << endl;
        
        //DEBUGG用
        _trackAlpha = 1.0;
        _barAlpha = 1.0;
        
        //------------------------------------------
        _target = this;
        name("RangeSlider");
        
        _roundEnabled = false;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        
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
        
        Graphics* g;
        
        //------------------------------------------
        track = new Sprite();
        track->name("track");
        _drawTrackGraphics(_lineColor, _normalColor);
        track->x(0);
        track->y(0);
        track->useHandCursor(true);
        //track->mouseEnabled(false);
        track->addEventListener(MouseEvent::ROLL_OVER, this, &RangeSlider::_mouseEventHandler);
        track->addEventListener(MouseEvent::ROLL_OUT, this, &RangeSlider::_mouseEventHandler);
        track->addEventListener(MouseEvent::MOUSE_DOWN, this, &RangeSlider::_mouseEventHandler);
        addChild(track);
        
        //------------------------------------------
        //バー
        bar = new Sprite();
        bar->name("bar");
        bar->useHandCursor(true);
        bar->addEventListener(MouseEvent::MOUSE_DOWN, this, &RangeSlider::_mouseEventHandler);
        track->addChild(bar);
        
        //
        nearThumb = new Sprite();
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
        farThumb = new Sprite();
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
        _minValueText = new TextField();
        _minValueText->x(0);
        _minValueText->width(_trackWidth);
        _minValueText->autoSize(TextFieldAutoSize::LEFT);
        _minValueText->textColor(_labelNormalColor);
        _minValueText->text(ofToString(_minValue));
        _minValueText->mouseEnabled(false);
        _minValueText->visible(false);
        _minValueText->y(_trackHeight * 0.5 - _minValueText->textHeight() * 0.5);
        addChild(_minValueText);
        
        _maxValueText = new TextField();
        _maxValueText->x(0);
        _maxValueText->width(_trackWidth);
        _maxValueText->autoSize(TextFieldAutoSize::RIGHT);
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
    RangeSlider::~RangeSlider() {
        //cout << "[RangeSlider]~RangeSlider()" << endl;
        
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
        
        track->removeEventListener(MouseEvent::ROLL_OVER, this, &RangeSlider::_mouseEventHandler);
        track->removeEventListener(MouseEvent::ROLL_OUT, this, &RangeSlider::_mouseEventHandler);
        track->removeEventListener(MouseEvent::MOUSE_DOWN, this, &RangeSlider::_mouseEventHandler);
        delete track;
        track = NULL;
        
        bar->removeEventListener(MouseEvent::MOUSE_DOWN, this, &RangeSlider::_mouseEventHandler);
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
    void RangeSlider::_setup() {
        //cout << "[RangeSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void RangeSlider::_update() {
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
            event->_target = this;
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
            //------------------------------------------
        }
        
        //        cout << "[RangeSlider]bar->width = " << bar->width() << endl;
    }
    
    //--------------------------------------------------------------
    //
    void RangeSlider::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void RangeSlider::textColor(int color) {
        _minValueText->textColor(color);
        _maxValueText->textColor(color);
    }
    
    //--------------------------------------------------------------
    //
    float RangeSlider::min() { return _min; }
    void RangeSlider::min(float value, bool dispatch) {
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
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
    float RangeSlider::max() { return _max; }
    void RangeSlider::max(float value, bool dispatch) {
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
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
    float RangeSlider::minValue() { return _minValue; }
    void RangeSlider::minValue(float value, bool dispatch) {
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
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
    float RangeSlider::maxValue() { return _maxValue; }
    void RangeSlider::maxValue(float value, bool dispatch) {
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
            RangeSliderEvent* event = new RangeSliderEvent(RangeSliderEvent::CHANGE);
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
    float RangeSlider::range() { return _range; }
    
    //--------------------------------------------------------------
    //
    int RangeSlider::barColor() { return _activeColor.getHex(); }
    void RangeSlider::barColor(int value) {
        _activeColor.setHex(value);
        
        if(farThumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void RangeSlider::barColor(int red, int green, int blue, int alpha) {
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
    void RangeSlider::barColor(const ofColor& color) {
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
    void RangeSlider::barColor(const ofFloatColor& color) {
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
    bool RangeSlider::roundEnabled() { return _roundEnabled; }
    void RangeSlider::roundEnabled(bool value) { _roundEnabled = value; }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void RangeSlider::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        Graphics* g;
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
    void RangeSlider::_drawBarGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        Graphics* g;
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
    void RangeSlider::_over() {
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
    void RangeSlider::_out() {
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
    void RangeSlider::_press() {
        //------------------------------------------
        _minValueText->textColor(_labelNormalColor);
        _maxValueText->textColor(_labelNormalColor);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void RangeSlider::_release() {
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
    void RangeSlider::_mouseEventHandler(Event& event) {
        //    cout << "[RangeSlider]_mouseEventHandler(" << event.type() << ")" << endl;
        //    cout << "[RangeSlider]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //    cout << "[RangeSlider]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //    cout << "[RangeSlider]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        //ROLL OVER
        if(event.type() == MouseEvent::ROLL_OVER) {
            if(event.target() == track) _over();
        }
        
        //ROLL OUT
        if(event.type() == MouseEvent::ROLL_OUT) {
            if(event.target() == track) _out();
        }
        
        //MOUSE DOWN
        if(event.type() == MouseEvent::MOUSE_DOWN) {
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
            stage()->addEventListener(MouseEvent::MOUSE_UP, this, &RangeSlider::_mouseEventHandler);
        }
        
        //MOUSE UP
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _draggablePoint->x = 0;
                _draggablePoint->y = 0;
                
                _release();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &RangeSlider::_mouseEventHandler);
            }
        }
    }
    
}
