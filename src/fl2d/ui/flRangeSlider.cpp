#include "flRangeSlider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flRangeSlider::flRangeSlider(float trackWidth, float min, float max, float minValue, float maxValue) {
        //cout << "[flRangeSlider]flRangeSlider()" << endl;
        
        //DEBUGG用
        _trackAlpha = 1.0;
        
        //------------------------------------------
        _target = this;
        name("flRangeSlider");
        
        _label = NULL;
        _roundEnabled = false;
        _enabled = true;

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
        //バーとつまみのコンテナ
        track = new flSprite();
        track->name("track");
        track->x(0);
        track->y(0);
        track->mouseEnabled(false);
        addChild(track);
        
        //------------------------------------------
        //バー
        bar = new flSprite();
        bar->name("bar");
        bar->useHandCursor(true);
        bar->addEventListener(flMouseEvent::ROLL_OVER, this, &flRangeSlider::_mouseEventHandler);
        bar->addEventListener(flMouseEvent::ROLL_OUT, this, &flRangeSlider::_mouseEventHandler);
        bar->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(bar);
        
        //つまみ
        minThumb = new flSprite();
        minThumb->name("minThumb");
        g = minThumb->graphics();
        g->clear();
        g->beginFill(0xff0000);
        g->drawRect(0, 0, _thumbWidth, _trackHeight - 1);
        g->endFill();
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        minThumb->y(0);
        minThumb->alpha(0);
        minThumb->useHandCursor(true);
        minThumb->addEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        minThumb->addEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        minThumb->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(minThumb);
        
        //つまみ
        maxThumb = new flSprite();
        maxThumb->name("maxThumb");
        g = maxThumb->graphics();
        g->clear();
        g->beginFill(0x00ff00);
        g->drawRect(0, 0, _thumbWidth, _trackHeight - 1);
        g->endFill();
        maxThumb->x((_maxValue - _min) / _percent);
        maxThumb->y(0);
        maxThumb->alpha(0);
        maxThumb->useHandCursor(true);
        maxThumb->addEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->addEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(maxThumb);
        
        //------------------------------------------
        _minValueText = new flTextField();
        _minValueText->x(0);
        _minValueText->width(_trackWidth);
        _minValueText->autoSize(flTextFieldAutoSize::LEFT);
        _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _minValueText->text(ofToString(_minValue));
        _minValueText->mouseEnabled(false);
        _minValueText->y(_trackHeight * 0.5 - _minValueText->textHeight() * 0.5);
        addChild(_minValueText);
        
        _maxValueText = new flTextField();
        _maxValueText->x(0);
        _maxValueText->width(_trackWidth);
        _maxValueText->autoSize(flTextFieldAutoSize::RIGHT);
        _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _maxValueText->text(ofToString(_maxValue));
        _maxValueText->mouseEnabled(false);
        _maxValueText->y(_trackHeight * 0.5 - _maxValueText->textHeight() * 0.5);
        addChild(_maxValueText);
        //------------------------------------------
        
        _draggablePoint = new ofPoint(0, 0);
        
        //バーのグラフィックス
        bar->x(minThumb->x() + _thumbWidth);
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    //
    flRangeSlider::~flRangeSlider() {
        //cout << "[flRangeSlider]~flRangeSlider()" << endl;
        
        //DEBUGG用
        _trackAlpha = 0.0;
        
        _label = NULL;
        _roundEnabled = false;
        _enabled = false;

        _min = 0.0;
        _max = 0.0;
        _minValue = 0.0;
        _maxValue = 0.0;
        _range = 0.0;
        
        _trackWidth = 0.0;
        _trackHeight = 0.0;
        _thumbWidth = 0.0;
        
        _percent = 0.0;
        
        delete track;
        track = NULL;
        
        bar->removeEventListener(flMouseEvent::ROLL_OVER, this, &flRangeSlider::_mouseEventHandler);
        bar->removeEventListener(flMouseEvent::ROLL_OUT, this, &flRangeSlider::_mouseEventHandler);
        bar->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete bar;
        bar = NULL;
        
        minThumb->removeEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        minThumb->removeEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        minThumb->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete minThumb;
        minThumb = NULL;
        
        maxThumb->removeEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->removeEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete maxThumb;
        maxThumb = NULL;
        
        _barWidth = 0.0;
        
        delete _minValueText;
        _minValueText = NULL;
        
        delete _maxValueText;
        _maxValueText = NULL;
        
        delete _draggablePoint;
        _draggablePoint = NULL;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::_setup() {
        //cout << "[flRangeSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_update() {
        if(bar->isMouseDown()) {
            _barPress();
        }
        if(minThumb->isMouseDown()) {
            _minThumbPress();
        }
        if(maxThumb->isMouseDown()) {
            _maxThumbPress();
        }

        //        cout << "[flRangeSlider]bar->width = " << bar->width() << endl;
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flRangeSlider::label() { return _label; }
    void flRangeSlider::label(flTextField* value) {
        _label = value;
        if (_label != NULL) {
            if (_enabled) {
                _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
            }
            else {
                _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
            }
        }
    }
    
    //--------------------------------------------------------------
//    void flRangeSlider::textColor(int color) {
//        _minValueText->textColor(color);
//        _maxValueText->textColor(color);
//    }
    
    //--------------------------------------------------------------
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
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
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
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
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
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        if(bar->isMouseDown() || minThumb->isMouseDown() || maxThumb->isMouseDown()) {
            _setActiveColor();
        } else if(bar->isMouseOver() || minThumb->isMouseOver() || maxThumb->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
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
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        if(bar->isMouseDown() || minThumb->isMouseDown() || maxThumb->isMouseDown()) {
            _setActiveColor();
        } else if(bar->isMouseOver() || minThumb->isMouseOver() || maxThumb->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
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
    float flRangeSlider::range() { return _range; }

    //--------------------------------------------------------------
    bool flRangeSlider::roundEnabled() { return _roundEnabled; }
    void flRangeSlider::roundEnabled(bool value) { _roundEnabled = value; }
    
    //--------------------------------------------------------------
    bool flRangeSlider::enabled() { return _enabled; }
    void flRangeSlider::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if (_label != NULL) {
            if (_enabled) {
                _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
            }
            else {
                _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
            }
        }
        
        //バー
        if (_enabled) {
            _setNormalColor();
            //            _drawTrackGraphics(_normalBarColor, _normalBarColor, 1);
            //            _drawBarGraphics(_normalBarColor, _activeBarColor, 1);
        }
        else {
            _setNormalColor();
            
            //            _drawTrackGraphics(_normalBarColor, _normalBarColor, 1);
            //            _drawBarGraphics(_normalBarColor, _disableNormalBarColor, 1);
        }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::_over() {
        if(bar->isMouseDown()) return;
        if(minThumb->isMouseDown()) return;
        if(maxThumb->isMouseDown()) return;

        //        _valueText->visible(true);
        _setOverColor();
        
        //        dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OVER));
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_barOut() {
        if(bar->isMouseDown()) return;
        if(minThumb->isMouseDown()) return;
        if(maxThumb->isMouseDown()) return;

        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_thumbOut() {
        if(bar->isMouseOver()) return;
        if(bar->isMouseDown()) return;
        if(minThumb->isMouseDown()) return;
        if(maxThumb->isMouseDown()) return;

        _setNormalColor();

//        if(track->isMouseOver()) {
//            //            _valueText->visible(true);
//            _setBarOverColor();
//        } else {
//            //            _valueText->visible(false);
//            _setNormalColor();
//        }
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_barPress() {
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
        minThumb->x(temp1 - _thumbWidth);
        maxThumb->x(temp2);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _minValue = _min + ((minThumb->x() + _thumbWidth) * _percent);
        _maxValue = _min + (maxThumb->x() * _percent);
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
        bar->x(minThumb->x() + _thumbWidth);
        _setActiveColor();
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
    
    //--------------------------------------------------------------
    void flRangeSlider::_minThumbPress() {
//        ofLog() << "[flRangeSlider]_thumbPress()";

        //------------------------------------------
        //サムの位置の更新
        float temp;
        temp = mouseX() - _draggablePoint->x;
        if(temp < 0) {
            temp = 0;
        } else if(temp > maxThumb->x() - 1) {
            temp = maxThumb->x() - 1;
        }
        minThumb->x(temp - _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        _minValue = _min + ((minThumb->x() + _thumbWidth) * _percent);
        _maxValue = _min + (maxThumb->x() * _percent);
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
        bar->x(minThumb->x() + _thumbWidth);
        _setActiveColor();
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
    
    //--------------------------------------------------------------
    void flRangeSlider::_maxThumbPress() {
//        ofLog() << "[flRangeSlider]_maxThumbPress()";

        //------------------------------------------
        //サムの位置の更新
        float temp;
        temp = mouseX() - _draggablePoint->x;
        if(temp < minThumb->x() + _thumbWidth + 1) {
            temp = minThumb->x() + _thumbWidth + 1;
        } else if(temp > _trackWidth) {
            temp = _trackWidth;
        }
        maxThumb->x(temp);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        _minValue = _min + ((minThumb->x() + _thumbWidth) * _percent);
        _maxValue = _min + (maxThumb->x() * _percent);
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
        _setActiveColor();
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
    
    //--------------------------------------------------------------
    void flRangeSlider::_release() {
//        ofLog() << "[flRangeSlider]_release()";
        if(
           bar->isMouseOver() ||
           minThumb->isMouseOver() ||
           maxThumb->isMouseOver()
           ) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setNormalColor() {
//        _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setOverColor() {
        _minValueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setSelectedBarOverColor() {
        //        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setSelectedThumbOverColor() {
        //        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setActiveColor() {
        _minValueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setDisableNormalColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setDisableActiveColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_drawTrackGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = track->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        //            g->beginFill(0xff0000, _barAlpha);
        g->beginFill(fillColor.getHex(), _trackAlpha);
        g->drawRect(0, 0, _trackWidth, _trackHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_drawBarGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = bar->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        //            g->beginFill(0xff0000, _barAlpha);
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
//        g->drawRect(minThumb->x() + _thumbWidth, 0, _barWidth, _trackHeight);
        g->drawRect(0, 0, _barWidth, _trackHeight);
        g->endFill();
    }
    
//    //--------------------------------------------------------------
//    void flRangeSlider::_over() {
//        if(track->isMouseDown()) return;
//        if(bar->isMouseDown()) return;
//        if(minThumb->isMouseDown()) return;
//        if(maxThumb->isMouseDown()) return;
//
//        //------------------------------------------
//        _drawTrackGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//        _drawBarGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//        //------------------------------------------
//
//        //------------------------------------------
//        _minValueText->visible(true);
//        _maxValueText->visible(true);
//        //------------------------------------------
//    }
//    //--------------------------------------------------------------
//    void flRangeSlider::_out() {
//        if(track->isMouseDown()) return;
//        if(bar->isMouseDown()) return;
//        if(minThumb->isMouseDown()) return;
//        if(maxThumb->isMouseDown()) return;
//
//        //------------------------------------------
//        _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//        //------------------------------------------
//
//        //------------------------------------------
//        _minValueText->visible(false);
//        _maxValueText->visible(false);
//        //------------------------------------------
//    }
//    //--------------------------------------------------------------
//    void flRangeSlider::_press() {
//        //------------------------------------------
//        _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//        _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//        //------------------------------------------
//    }
//    //--------------------------------------------------------------
//    void flRangeSlider::_release() {
//        if(minThumb->isMouseOver() || track->isMouseOver()) {
//            //------------------------------------------
//            _drawTrackGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//            _drawBarGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//            //------------------------------------------
//
//            //------------------------------------------
//            _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//            _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//            //------------------------------------------
//        } else {
//            //------------------------------------------
//            _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//            _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//            //------------------------------------------
//
//            //------------------------------------------
//            _minValueText->visible(false);
//            _maxValueText->visible(false);
//            //------------------------------------------
//        }
//    }
    
    //==============================================================
    // Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flRangeSlider]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flRangeSlider]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flRangeSlider]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flRangeSlider]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == bar) _over();
//            else if(event.target() == minThumb) _thumbOver();
//            else if(event.target() == maxThumb) _thumbOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == bar) _barOut();
//            else if(event.target() == minThumb) _thumbOut();
//            else if(event.target() == maxThumb) _thumbOut();
        }
        
        //Mouse Over
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == minThumb || event.target() == maxThumb) _over();
        }
        
        //Mouse Out
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == minThumb || event.target() == maxThumb) _thumbOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == bar) {
                _draggablePoint->x = mouseX() - (minThumb->x() + _thumbWidth);
                _barPress();
            }
            if(event.target() == minThumb) {
                _draggablePoint->x = mouseX() - (minThumb->x() + _thumbWidth);
//                _draggablePoint->x = mouseX() - thumb->x() - _thumbWidth * 0.5;
                _minThumbPress();
            }
            else if(event.target() == maxThumb) {
                _draggablePoint->x = mouseX() - maxThumb->x();
                _maxThumbPress();
            }

            if(stage()) {
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            }

            
//            if(event.target() == maxThumb) {
//                _draggablePoint->x = mouseX() - maxThumb->x();
//                _press();
//            }
//            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            
//            if(minThumb->isMouseOver() || maxThumb->isMouseOver()) {
//                if(event.target() == minThumb || event.target() == maxThumb) {
//                    _thumbDown();
//                    addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
//                    if(stage()) {
//                        stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
//                    }
//                }
//            } else {
////                if(event.target() == track) {
////                    _barDown();
////                    addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
////                    if(stage()) {
////                        stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
////                    }
////                }
//            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
//            removeEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            }
            _release();

//            if(event.currentTarget() == stage()) {
//                _draggablePoint->x = 0;
//                _draggablePoint->y = 0;
//
//                _release();
//                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
//            }
        }
    }
    
}
